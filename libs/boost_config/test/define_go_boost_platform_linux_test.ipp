//
//  define_go_boost_platform_linux_test.ipp
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
