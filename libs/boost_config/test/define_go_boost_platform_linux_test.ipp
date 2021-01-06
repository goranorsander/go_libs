//
//  define_go_boost_platform_linux_test.ipp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_gtest/go_test.hpp>

namespace
{

TEST(boost_define_go_boost_platform_test_suite, test_define_go_boost_platform_linux)
{
    #if !defined(GO_BOOST_PLATFORM_LINUX)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_platform_test_suite, test_not_define_go_boost_platform_windows)
{
    #if defined(GO_BOOST_PLATFORM_WINDOWS)
    EXPECT_TRUE(false);
    #endif
}

}
