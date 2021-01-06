//
//  define_go_message_test_suite.cpp
//
//  Copyright 2017-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

namespace
{

TEST(std_define_go_message_test_suite, test_define_go_message)
{
    #if !defined(GO_MESSAGE)
    EXPECT_TRUE(false);
    #endif
}

}
