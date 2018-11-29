//
//  placebo_mutex_test_suite.cpp
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

#include <go_boost/utility/placebo_mutex.hpp>

namespace u = go_boost::utility;

namespace
{

TEST(boost_placebo_mutex_test_suite, test_placebo_mutex)
{
    u::placebo_mutex mutex;

    mutex.lock();

    EXPECT_EQ(true, mutex.try_lock());

    mutex.unlock();

    EXPECT_EQ(true, mutex.try_lock());

    mutex.unlock();
}

TEST(boost_placebo_mutex_test_suite, test_placebo_mutex_scoped_lock)
{
    u::placebo_mutex mutex;

    {
        u::placebo_mutex::scoped_lock guard(mutex);

        EXPECT_EQ(true, mutex.try_lock());
    }

    EXPECT_EQ(true, mutex.try_lock());
}

}
