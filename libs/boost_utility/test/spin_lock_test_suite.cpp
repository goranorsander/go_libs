//
//  spin_lock_test_suite.cpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go_boost/config.hpp>

#include <boost/thread/mutex.hpp>

#include <go_boost/utility/spin_lock.hpp>

namespace u = go_boost::utility;

namespace
{

TEST(boost_spin_lock_test_suite, test_spin_lock)
{
    u::spin_lock lock;

    lock.lock();

    EXPECT_EQ(false, lock.try_lock());

    lock.unlock();

    EXPECT_EQ(true, lock.try_lock());

    lock.unlock();
}

TEST(boost_spin_lock_test_suite, test_spin_lock_scoped_lock)
{
    u::spin_lock lock;

    {
        u::spin_lock::scoped_lock guard(lock);

        EXPECT_EQ(false, lock.try_lock());
    }

    EXPECT_EQ(true, lock.try_lock());
}

}
