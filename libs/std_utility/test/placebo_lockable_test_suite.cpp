//
//  placebo_lockable_test_suite.cpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#if defined(GO_NO_CXX11_MUTEX)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_placebo_lockable_test_suite, cpp11_not_supported) {}
#else

#include <go/utility/placebo_lockable.hpp>
#include <mutex>

namespace u = go::utility;

namespace
{

TEST(std_placebo_lockable_test_suite, test_placebo_lockable)
{
    u::placebo_lockable mutex;

    mutex.lock();

    EXPECT_EQ(true, mutex.try_lock());

    mutex.unlock();

    EXPECT_EQ(true, mutex.try_lock());

    mutex.unlock();
}

#if !defined(GO_NO_CXX11_MUTEX)

TEST(std_placebo_lockable_test_suite, test_placebo_lockable_lock_guard)
{
    u::placebo_lockable mutex;

    {
        std::lock_guard<u::placebo_lockable> guard(mutex);

        EXPECT_EQ(true, mutex.try_lock());
    }

    EXPECT_EQ(true, mutex.try_lock());
}

#endif  // #if !defined(GO_NO_CXX11_MUTEX)

}

#endif  // Required C++11 feature is not supported by this compiler
