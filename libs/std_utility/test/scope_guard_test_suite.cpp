//
//  scope_guard_test_suite.cpp
//
//  Copyright 2018-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_scope_guard_test_suite, required_cpp11_feature_not_supported) {}
#else

#include <go/namespace_alias.hpp>
#include <go/utility/scope_guard.hpp>

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

TEST(std_scope_guard_test_suite, test_scope_guard)
{
    {
        EXPECT_EQ(0u, scope_exit_count());
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
        const u::scope_guard guard1(u::scope_guard::on_scope_exit_function_type(std::tr1::bind(on_scope_exit)));
#else
        const u::scope_guard guard1(u::scope_guard::on_scope_exit_function_type(std::bind(on_scope_exit)));
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
        EXPECT_EQ(0u, scope_exit_count());
        {
            EXPECT_EQ(0u, scope_exit_count());
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
            const u::scope_guard guard2(u::scope_guard::on_scope_exit_function_type(std::tr1::bind(on_scope_exit)));
#else
            const u::scope_guard guard2(u::scope_guard::on_scope_exit_function_type(std::bind(on_scope_exit)));
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
            EXPECT_EQ(0u, scope_exit_count());
        }
        EXPECT_EQ(1u, scope_exit_count());
    }
    EXPECT_EQ(2u, scope_exit_count());
}

}

#endif  // Required C++11 feature is not supported by this compiler
