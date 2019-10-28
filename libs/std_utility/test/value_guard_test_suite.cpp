//
//  value_guard_test_suite.cpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_value_guard_test_suite, cpp11_not_supported) {}
#else

#include <go/namespace_alias.hpp>
#include <go/utility/value_guard.hpp>

namespace
{

TEST(std_value_guard_test_suite, test_value_guard)
{
    bool is_guarded_1 = false;
    {
        EXPECT_EQ(false, is_guarded_1);
        const u::value_guard<bool> guard1(is_guarded_1, true);
        EXPECT_EQ(true, is_guarded_1);
        bool is_guarded_2 = false;
        {
            EXPECT_EQ(true, is_guarded_1);
            EXPECT_EQ(false, is_guarded_2);
            const u::value_guard<bool> guard2(is_guarded_2, true);
            EXPECT_EQ(true, is_guarded_1);
            EXPECT_EQ(true, is_guarded_2);
        }
        EXPECT_EQ(true, is_guarded_1);
        EXPECT_EQ(false, is_guarded_2);
    }
    EXPECT_EQ(false, is_guarded_1);
}

}

#endif  // Required C++11 feature is not supported by this compiler
