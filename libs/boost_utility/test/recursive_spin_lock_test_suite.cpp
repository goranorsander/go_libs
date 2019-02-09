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
#include <go_boost/config.hpp>

#include <go_boost/utility/recursive_spin_lock.hpp>

namespace u = go_boost::utility;

namespace
{

TEST(boost_recursive_spin_lock_test_suite, test_recursive_spin_lock)
{
    u::recursive_spin_lock lock;

    lock.lock();

    EXPECT_EQ(true, lock.try_lock());

    lock.unlock();
    lock.unlock();

    EXPECT_EQ(true, lock.try_lock());

    lock.unlock();
}

TEST(boost_recursive_spin_lock_test_suite, test_recursive_spin_lock_lock_guard)
{
    u::recursive_spin_lock lock;

    {
        u::recursive_spin_lock::scoped_lock guard(lock);

        EXPECT_EQ(true, lock.try_lock());

        lock.unlock();
    }

    EXPECT_EQ(true, lock.try_lock());
}

class test_thread
{
public:
    ~test_thread() GO_BOOST_DEFAULT_DESTRUCTOR
    test_thread()
        : m()
        , cv()
        , step_1_complete(false)
        , step_2_complete(false)
        , step_3_complete(false)
        , step_4_complete(false)
    {
    }

    void run()
    {
        // Step 1 - main thread ready to start test
        boost::unique_lock<boost::mutex> lk(m);
        cv.wait(lk, boost::bind(&test_thread::is_step_1_completed, this));

        // Step 2 - worker thread locks the recursive_spin_lock
        lock.lock();
        step_2_complete = true;
        lk.unlock();
        cv.notify_one();

        // Step 3 - main thread try to lock 'lock' when worker thread have 'lock' locked already
        lk.lock();
        cv.wait(lk, boost::bind(&test_thread::is_step_3_completed, this));

        // Step 4 - worker thread unlocks the recursive_spin_lock
        lock.unlock();
        step_4_complete = true;
        lk.unlock();
        cv.notify_one();
    }

    bool is_step_1_completed() const { return step_1_complete; }
    bool is_step_2_completed() const { return step_2_complete; }
    bool is_step_3_completed() const { return step_3_complete; }
    bool is_step_4_completed() const { return step_4_complete; }

    u::recursive_spin_lock lock;

    boost::mutex m;
    boost::condition_variable cv;
    bool step_1_complete;
    bool step_2_complete;
    bool step_3_complete;
    bool step_4_complete;
};

TEST(boost_recursive_spin_lock_test_suite, test_recursive_spin_lock_two_threads)
{
    test_thread t;

    {
        u::recursive_spin_lock::scoped_lock guard(t.lock);

        EXPECT_EQ(true, t.lock.try_lock());

        t.lock.unlock();
    }

    EXPECT_EQ(true, t.lock.try_lock());

    t.lock.unlock();

    // Start worker thread
    boost::thread worker(boost::bind(&test_thread::run, &t));

    // Step 1 - main thread ready to start test
    {
        EXPECT_EQ(true, t.lock.try_lock());

        t.lock.unlock();

        boost::lock_guard<boost::mutex> lk(t.m);
        t.step_1_complete = true;
    }
    t.cv.notify_one();

    // Step 2 - worker thread locks the recursive_spin_lock
    {
        boost::unique_lock<boost::mutex> lk(t.m);
        t.cv.wait(lk, boost::bind(&test_thread::is_step_2_completed, &t));
    }

    // Step 3 - main thread try to lock 'lock' when worker thread have 'lock' locked already
    {
        boost::lock_guard<boost::mutex> lk(t.m);

        EXPECT_EQ(false, t.lock.try_lock());

        t.step_3_complete = true;
    }
    t.cv.notify_one();

    // Step 4 - worker thread unlocks the recursive_spin_lock
    {
        boost::unique_lock<boost::mutex> lk(t.m);
        t.cv.wait(lk, boost::bind(&test_thread::is_step_4_completed, &t));

        EXPECT_EQ(true, t.lock.try_lock());

        t.lock.unlock();
    }

    worker.join();
}

}
