//
//  define_go_message_test_suite.cpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

namespace
{

TEST(std_define_go_message_test_suite, test_define_go_message)
{
    #if !defined(GO_MESSAGE)
    EXPECT_TRUE(false);
    #endif
}

}
