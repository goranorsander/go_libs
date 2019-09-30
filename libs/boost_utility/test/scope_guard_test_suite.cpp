//
//  scope_guard_test_suite.cpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#include <boost/bind.hpp>

#include <go_boost/utility/scope_guard.hpp>

namespace u = go_boost::utility;

namespace
{

unsigned int& scope_exit_count()
{
    static unsigned int count = 0u;
    return count;
}

void on_scope_exit()
{
    scope_exit_count()++;
}

TEST(boost_scope_guard_test_suite, test_scope_guard)
{
    {
        EXPECT_EQ(0u, scope_exit_count());
        const u::scope_guard guard1(u::scope_guard::on_scope_exit_function_type(boost::bind(on_scope_exit)));
        EXPECT_EQ(0u, scope_exit_count());
        {
            EXPECT_EQ(0u, scope_exit_count());
            const u::scope_guard guard2(u::scope_guard::on_scope_exit_function_type(boost::bind(on_scope_exit)));
            EXPECT_EQ(0u, scope_exit_count());
        }
        EXPECT_EQ(1u, scope_exit_count());
    }
    EXPECT_EQ(2u, scope_exit_count());
}

}
