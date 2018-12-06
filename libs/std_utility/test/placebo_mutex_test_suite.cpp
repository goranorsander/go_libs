//
//  placebo_mutex_test_suite.cpp
//
//  Copyright 2018 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_placebo_mutex_test_suite, cpp11_not_supported) {}
#else

#include <go/utility/placebo_mutex.hpp>

namespace u = go::utility;

namespace
{

TEST(std_placebo_mutex_test_suite, test_placebo_mutex)
{
    u::placebo_mutex mutex;

    mutex.lock();

    EXPECT_EQ(true, mutex.try_lock());

    mutex.unlock();

    EXPECT_EQ(true, mutex.try_lock());

    mutex.unlock();
}

TEST(std_placebo_mutex_test_suite, test_placebo_mutex_lock_guard)
{
    u::placebo_mutex mutex;

    {
        std::lock_guard<u::placebo_mutex> guard(mutex);

        EXPECT_EQ(true, mutex.try_lock());
    }

    EXPECT_EQ(true, mutex.try_lock());
}

}

#endif  // Required C++11 feature is not supported by this compiler