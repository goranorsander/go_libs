//
//  value_guard_test_suite.cpp
//
//  Copyright 2018-2019 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#include <go_boost/utility/value_guard.hpp>

namespace u = go_boost::utility;

namespace
{

TEST(boost_value_guard_test_suite, test_value_guard)
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
