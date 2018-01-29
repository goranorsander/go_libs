//
//  define_go_boost_typename_test_suite.cpp
//
//  Copyright 2018 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go_boost/config.hpp>
#include <boost/preprocessor/stringize.hpp>

namespace
{

TEST(boost_define_go_boost_typename_test_suite, test_define_go_boost_typename)
{
    #if defined(GO_BOOST_TYPENAME)
    #if defined(GO_BOOST_TYPENAME_REQUIRED)
    const std::string expected_define("typename");
    const std::string go_boost_typename(BOOST_PP_STRINGIZE(GO_BOOST_TYPENAME));
    #else
    const std::string expected_define("");
    const std::string go_boost_typename("");
    #endif
    EXPECT_EQ(expected_define, go_boost_typename);
    #else
    EXPECT_TRUE(false);
    #endif
}

}
