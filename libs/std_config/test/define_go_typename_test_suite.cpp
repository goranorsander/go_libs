//
//  define_go_typename_test_suite.cpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

namespace
{

TEST(std_define_go_typename_test_suite, test_define_go_typename)
{
    #if defined(GO_TYPENAME)
    #if defined(GO_CPP_TYPENAME_REQUIRED)
    const std::string expected_define("typename");
    const std::string go_typename(GO_TO_STRING(GO_TYPENAME));
    #else
    const std::string expected_define("");
    const std::string go_typename("");
    #endif
    EXPECT_EQ(expected_define, go_typename);
    #else
    EXPECT_TRUE(false);
    #endif
}

}
