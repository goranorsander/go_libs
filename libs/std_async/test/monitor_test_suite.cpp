//
//  monitor_test_suite.cpp
//
//  Copyright 2019-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_ATOMIC_OPERATIONS) || defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_monitor_test_suite, required_cpp11_feature_not_supported) {}
#else

#include <condition_variable>
#include <functional>
#include <list>
#include <thread>
#include <go/async/monitor.hpp>
#include <go/namespace_alias.hpp>

namespace
{

TEST(std_monitor_test_suite, test_monitor)
{
    a::monitor<std::list<int>> monitored_list;

    EXPECT_EQ(true, monitored_list->empty());

    monitored_list->push_back(1);
    EXPECT_EQ(false, monitored_list->empty());
    EXPECT_EQ(1u, monitored_list->size());

    monitored_list->push_back(2);
    EXPECT_EQ(false, monitored_list->empty());
    EXPECT_EQ(2u, monitored_list->size());

    monitored_list->clear();
    EXPECT_EQ(true, monitored_list->empty());
}

#if !defined(GO_NO_CXX11_CONDITION_VARIABLE)

class test_thread
{
public:
    ~test_thread() = default;
    test_thread() = default;

    void run()
    {
        // Step 1 - main thread ready to start test
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [this]() -> bool { return step_1_complete; });

        // Step 2 - worker thread locks the monitor
        monitored_int.lock().get() = 2;
        step_2_complete = true;
        lk.unlock();
        cv.notify_one();
    }

    a::monitor<int> monitored_int;

    std::mutex m;
    std::condition_variable cv;
    bool step_1_complete = false;
    bool step_2_complete = false;
};

TEST(std_monitor_test_suite, test_monitor_two_threads)
{
    test_thread t;

    {
        auto guarded_int = t.monitored_int.lock();
        *guarded_int = 0;

        EXPECT_EQ(0, *guarded_int);
    }

    EXPECT_EQ(0, t.monitored_int.lock().get());

    // Start worker thread
    std::thread worker(std::bind(&test_thread::run, &t));

    // Step 1 - main thread ready to start test
    {
        auto guarded_int = t.monitored_int.lock();
        guarded_int.get() = 1;

        EXPECT_EQ(1, guarded_int.get());

        std::lock_guard<std::mutex> lk(t.m);
        t.step_1_complete = true;
    }
    t.cv.notify_one();

    // Step 2 - worker thread locks the monitor
    {
        std::unique_lock<std::mutex> lk(t.m);
        t.cv.wait(lk, [&t]() -> bool { return t.step_2_complete; });

        EXPECT_EQ(2, t.monitored_int.lock().get());
    }

    worker.join();
}

#endif  // #if !defined(GO_NO_CXX11_CONDITION_VARIABLE)

}

#endif  // Required C++11 feature is not supported by this compiler
