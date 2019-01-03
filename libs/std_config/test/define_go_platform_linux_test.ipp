//
//  define_go_platform_linux_test.ipp
//
//  Copyright 2017-2019 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

namespace
{

TEST(std_define_go_platform_test_suite, test_define_go_platform_linux)
{
    #if !defined(GO_PLATFORM_LINUX)
    EXPECT_TRUE(false);
    #endif
}

TEST(std_define_go_platform_test_suite, test_not_define_go_platform_windows)
{
    #if defined(GO_PLATFORM_WINDOWS)
    EXPECT_TRUE(false);
    #endif
}

}
