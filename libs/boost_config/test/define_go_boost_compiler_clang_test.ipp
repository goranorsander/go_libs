//
//  define_go_boost_compiler_clang_test.ipp
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

TEST(boost_define_go_boost_compiler_test_suite, test_define_go_boost_clang_version)
{
    #if defined(GO_BOOST_CLANG_VERSION)
    const int expected_version = __clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__;
    const int go_boost_clang_version = GO_BOOST_CLANG_VERSION;
    EXPECT_EQ(expected_version, go_boost_clang_version);
    #else
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_define_go_boost_comp_clang)
{
    #if !defined(GO_BOOST_COMP_CLANG)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_comp_gcc)
{
    #if defined(GO_BOOST_COMP_GCC)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_comp_gcc_mingw)
{
    #if defined(GO_BOOST_COMP_GCC_MINGW)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_comp_msvc)
{
    #if defined(GO_BOOST_COMP_MSVC)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_comp_msvc_vc90)
{
    #if defined(GO_BOOST_COMP_MSVC_VC90)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_comp_msvc_vc100)
{
    #if defined(GO_BOOST_COMP_MSVC_VC100)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_comp_msvc_vc110)
{
    #if defined(GO_BOOST_COMP_MSVC_VC110)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_comp_msvc_vc120)
{
    #if defined(GO_BOOST_COMP_MSVC_VC120)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_comp_msvc_vc140)
{
    #if defined(GO_BOOST_COMP_MSVC_VC140)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_comp_msvc_vc141)
{
    #if defined(GO_BOOST_COMP_MSVC_VC141)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_gcc_version)
{
    #if defined(GO_BOOST_GCC_VERSION)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_ide_ms_vs2008)
{
    #if defined(GO_BOOST_IDE_MS_VS2008)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_ide_ms_vs2010)
{
    #if defined(GO_BOOST_IDE_MS_VS2010)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_ide_ms_vs2012)
{
    #if defined(GO_BOOST_IDE_MS_VS2012)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_ide_ms_vs2013)
{
    #if defined(GO_BOOST_IDE_MS_VS2013)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_ide_ms_vs2015)
{
    #if defined(GO_BOOST_IDE_MS_VS2015)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_ide_ms_vs2017)
{
    #if defined(GO_BOOST_IDE_MS_VS2017)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_msvc_atl)
{
    #if defined(GO_BOOST_MSVC_ATL)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_msvc_atl_ver)
{
    #if defined(GO_BOOST_MSVC_ATL_VER)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_msvc_full_ver)
{
    #if defined(GO_BOOST_MSVC_FULL_VER)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_msvc_mfc)
{
    #if defined(GO_BOOST_MSVC_MFC)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_msvc_mfc_ver)
{
    #if defined(GO_BOOST_MSVC_MFC_VER)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_msvc_ver)
{
    #if defined(GO_BOOST_MSVC_VER)
    EXPECT_TRUE(false);
    #endif
}

TEST(boost_define_go_boost_compiler_test_suite, test_not_define_go_boost_unicode)
{
    #if defined(GO_BOOST_MSVC_UNICODE)
    EXPECT_TRUE(false);
    #endif
}

}
