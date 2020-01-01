//
//  define_go_platform_windows_test.ipp
//
//  Copyright 2017-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go_gtest/go_test.hpp>

namespace
{

TEST(std_define_go_platform_test_suite, test_define_go_platform_windows)
{
    #if !defined(GO_PLATFORM_WINDOWS)
    EXPECT_TRUE(false);
    #endif
}

TEST(std_define_go_platform_test_suite, test_not_define_go_platform_linux)
{
    #if defined(GO_PLATFORM_LINUX)
    EXPECT_TRUE(false);
    #endif
}

}
