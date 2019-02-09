//
//  recursive_spin_lock_test_suite.cpp
//
//  Copyright 2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_ATOMIC_OPERATIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_recursive_spin_lock_test_suite, cpp11_not_supported) {}
#else

#include <mutex>
#include <go/utility/recursive_spin_lock.hpp>

namespace u = go::utility;

namespace
{

TEST(std_recursive_spin_lock_test_suite, test_recursive_spin_lock)
{
    u::recursive_spin_lock lock;

    lock.lock();

    EXPECT_EQ(true, lock.try_lock());

    lock.unlock();
    lock.unlock();

    EXPECT_EQ(true, lock.try_lock());

    lock.unlock();
}

TEST(std_recursive_spin_lock_test_suite, test_recursive_spin_lock_lock_guard)
{
    u::recursive_spin_lock lock;

    {
        std::lock_guard<u::recursive_spin_lock> guard(lock);

        EXPECT_EQ(true, lock.try_lock());

        lock.unlock();
    }

    EXPECT_EQ(true, lock.try_lock());
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

        // Step 2 - worker thread locks the recursive_spin_lock
        lock.lock();
        step_2_complete = true;
        lk.unlock();
        cv.notify_one();

        // Step 3 - main thread try to lock 'lock' when worker thread have 'lock' locked already
        lk.lock();
        cv.wait(lk, [this]() -> bool { return step_3_complete; });

        // Step 4 - worker thread unlocks the recursive_spin_lock
        lock.unlock();
        step_4_complete = true;
        lk.unlock();
        cv.notify_one();
    }

    u::recursive_spin_lock lock;

    std::mutex m;
    std::condition_variable cv;
    bool step_1_complete = false;
    bool step_2_complete = false;
    bool step_3_complete = false;
    bool step_4_complete = false;
};

TEST(std_recursive_spin_lock_test_suite, test_recursive_spin_lock_two_threads)
{
    test_thread t;

    {
        std::lock_guard<u::recursive_spin_lock> guard(t.lock);

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

    // Step 2 - worker thread locks the recursive_spin_lock
    {
        std::unique_lock<std::mutex> lk(t.m);
        t.cv.wait(lk, [&t]() -> bool { return t.step_2_complete; });
    }

    // Step 3 - main thread try to lock 'lock' when worker thread have 'lock' locked already
    {
        std::lock_guard<std::mutex> lk(t.m);

        EXPECT_EQ(false, t.lock.try_lock());

        t.step_3_complete = true;
    }
    t.cv.notify_one();

    // Step 4 - worker thread unlocks the recursive_spin_lock
    {
        std::unique_lock<std::mutex> lk(t.m);
        t.cv.wait(lk, [&t]() -> bool { return t.step_4_complete; });

        EXPECT_EQ(true, t.lock.try_lock());

        t.lock.unlock();
    }

    worker.join();
}

#endif  // #if !defined(GO_NO_CXX11_CONDITION_VARIABLE)

}

#endif  // Required C++11 feature is not supported by this compiler
