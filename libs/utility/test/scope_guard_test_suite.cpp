//
//  scope_guard_test_suite.cpp
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
TEST(std_scope_guard_test_suite, cpp11_not_supported) {}
#else

#include <go/utility/scope_guard.hpp>

namespace u = go::utility;

namespace
{

int& scope_exit_count()
{
    static int count = 0;
    return count;
}

void on_scope_exit()
{
    scope_exit_count()++;
}

TEST(std_scope_guard_test_suite, test_scope_guard)
{
    {
        EXPECT_EQ(0, scope_exit_count());
        const u::scope_guard guard1(u::scope_guard::on_scope_exit_function_type(std::bind(on_scope_exit)));
        EXPECT_EQ(0, scope_exit_count());
        {
            EXPECT_EQ(0, scope_exit_count());
            const u::scope_guard guard2(u::scope_guard::on_scope_exit_function_type(std::bind(on_scope_exit)));
            EXPECT_EQ(0, scope_exit_count());
        }
        EXPECT_EQ(1, scope_exit_count());
    }
    EXPECT_EQ(2, scope_exit_count());
}

}

#endif  // Required C++11 feature is not supported by this compiler
