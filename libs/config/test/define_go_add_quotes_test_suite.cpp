//
//  define_go_add_quotes_test_suite.cpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#define GO_TEST_DEFINE_VALUE abc123

namespace
{

TEST(std_define_go_add_quotes_test_suite, test_define_go_add_quotes)
{
    #if defined(GO_TO_STRING)
    const std::string expected_define("abc123");
    const std::string go_test_define_value(GO_TO_STRING(GO_TEST_DEFINE_VALUE));
    EXPECT_EQ(expected_define, go_test_define_value);
    #else
    EXPECT_TRUE(false);
    #endif
}

}
