//
//  define_go_boost_message_test_suite.cpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go_boost/config.hpp>

namespace
{

TEST(boost_define_go_boost_message_test_suite, test_define_go_boost_message)
{
    #if !defined(GO_BOOST_MESSAGE)
    EXPECT_TRUE(false);
    #endif
}

}
