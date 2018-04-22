//
//  scope_guard_test_suite.cpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go_boost/config.hpp>

#include <go_boost/utility/scope_guard.hpp>

namespace u = go_boost::utility;

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
