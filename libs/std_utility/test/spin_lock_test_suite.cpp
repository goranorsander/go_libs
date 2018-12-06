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
#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_ATOMIC_OPERATIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_spin_lock_test_suite, cpp11_not_supported) {}
#else

#include <go/utility/spin_lock.hpp>
#include <mutex>

namespace u = go::utility;

namespace
{

TEST(std_spin_lock_test_suite, test_spin_lock)
{
    u::spin_lock lock;

    lock.lock();

    EXPECT_EQ(false, lock.try_lock());

    lock.unlock();

    EXPECT_EQ(true, lock.try_lock());

    lock.unlock();
}

TEST(std_spin_lock_test_suite, test_spin_lock_lock_guard)
{
    u::spin_lock lock;

    {
        std::lock_guard<u::spin_lock> guard(lock);

        EXPECT_EQ(false, lock.try_lock());
    }

    EXPECT_EQ(true, lock.try_lock());
}

}

#endif  // Required C++11 feature is not supported by this compiler
