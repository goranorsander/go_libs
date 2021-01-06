//
//  placebo_lockable_test_suite.cpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11_MUTEX)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_placebo_lockable_test_suite, cpp11_not_supported) {}
#else

#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include <go/async/placebo_lockable.hpp>
#include <go/namespace_alias.hpp>

namespace
{

TEST(std_placebo_lockable_test_suite, test_placebo_lockable)
{
    a::placebo_lockable mutex;

    mutex.lock();

    EXPECT_EQ(true, mutex.try_lock());

    mutex.unlock();

    EXPECT_EQ(true, mutex.try_lock());

    mutex.unlock();
}

TEST(std_placebo_lockable_test_suite, test_placebo_lockable_lock_guard)
{
    a::placebo_lockable mutex;

    {
        std::lock_guard<a::placebo_lockable> guard(mutex);

        EXPECT_EQ(true, mutex.try_lock());
    }

    EXPECT_EQ(true, mutex.try_lock());
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

        // Step 2 - worker thread locks the placebo_lockable
        lock.lock();
        step_2_complete = true;
        lk.unlock();
        cv.notify_one();

        // Step 3 - main thread try to lock 'lock' when worker thread have 'lock' locked already
        lk.lock();
        cv.wait(lk, [this]() -> bool { return step_3_complete; });

        // Step 4 - worker thread unlocks the placebo_lockable
        lock.unlock();
        step_4_complete = true;
        lk.unlock();
        cv.notify_one();
    }

    a::placebo_lockable lock;

    std::mutex m;
    std::condition_variable cv;
    bool step_1_complete = false;
    bool step_2_complete = false;
    bool step_3_complete = false;
    bool step_4_complete = false;
};

TEST(std_recursive_spin_lock_test_suite, test_placebo_lockable_two_threads)
{
    test_thread t;

    {
        std::lock_guard<a::placebo_lockable> guard(t.lock);

        EXPECT_EQ(true, t.lock.try_lock());

        t.lock.unlock();
    }

    EXPECT_EQ(true, t.lock.try_lock());

    t.lock.unlock();

    // Start worker thread
    std::thread worker(std::bind(&test_thread::run, &t));

    // Step 1 - main thread ready to start test
    {
        EXPECT_EQ(true, t.lock.try_lock());

        t.lock.unlock();

        std::lock_guard<std::mutex> lk(t.m);
        t.step_1_complete = true;
    }
    t.cv.notify_one();

    // Step 2 - worker thread locks the placebo_lockable
    {
        std::unique_lock<std::mutex> lk(t.m);
        t.cv.wait(lk, [&t]() -> bool { return t.step_2_complete; });
    }

    EXPECT_EQ(true, t.lock.try_lock());

    t.lock.unlock();

    // Step 3 - main thread try to lock 'lock' when worker thread have 'lock' locked already
    {
        std::lock_guard<std::mutex> lk(t.m);

        EXPECT_EQ(true, t.lock.try_lock());

        t.step_3_complete = true;
    }
    t.cv.notify_one();

    // Step 4 - worker thread unlocks the placebo_lockable
    {
        std::unique_lock<std::mutex> lk(t.m);
        t.cv.wait(lk, [&t]() -> bool { return t.step_4_complete; });
    }

    EXPECT_EQ(true, t.lock.try_lock());

    t.lock.unlock();

    worker.join();
}

#endif  // #if !defined(GO_NO_CXX11_CONDITION_VARIABLE)

}

#endif  // Required C++11 feature is not supported by this compiler
