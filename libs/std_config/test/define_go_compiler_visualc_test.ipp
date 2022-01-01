//
//  define_go_compiler_clang_test.ipp
//
//  Copyright 2017-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go_gtest/go_gtest.hpp>

namespace
{

TEST(std_define_go_compiler_test_suite, test_not_define_go_clang_version)
{
    #if defined(GO_CLANG_VERSION)
    EXPECT_TRUE(false);
    #endif
}

TEST(std_define_go_compiler_test_suite, test_not_define_go_comp_clang)
{
    #if defined(GO_COMP_CLANG)
    EXPECT_TRUE(false);
    #endif
}

TEST(std_define_go_compiler_test_suite, test_not_define_go_comp_gcc)
{
    #if defined(GO_COMP_GCC)
    EXPECT_TRUE(false);
    #endif
}

TEST(std_define_go_compiler_test_suite, test_not_define_go_comp_gcc_mingw)
{
    #if defined(GO_COMP_GCC_MINGW)
    EXPECT_TRUE(false);
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_comp_msvc)
{
    #if !defined(GO_COMP_MSVC)
    EXPECT_TRUE(false);
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_comp_msvc_vc90)
{
    #if defined(GO_COMP_MSVC_VC90)
    #if defined(GO_COMP_MSVC_VC100) || defined(GO_COMP_MSVC_VC110) || defined(GO_COMP_MSVC_VC120) || defined(GO_COMP_MSVC_VC140) || defined(GO_COMP_MSVC_VC141)
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_comp_msvc_vc100)
{
    #if defined(GO_COMP_MSVC_VC100)
    #if defined(GO_COMP_MSVC_VC90) || defined(GO_COMP_MSVC_VC110) || defined(GO_COMP_MSVC_VC120) || defined(GO_COMP_MSVC_VC140) || defined(GO_COMP_MSVC_VC141)
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_comp_msvc_vc110)
{
    #if defined(GO_COMP_MSVC_VC110)
    #if defined(GO_COMP_MSVC_VC90) || defined(GO_COMP_MSVC_VC100) || defined(GO_COMP_MSVC_VC120) || defined(GO_COMP_MSVC_VC140) || defined(GO_COMP_MSVC_VC141)
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_comp_msvc_vc120)
{
    #if defined(GO_COMP_MSVC_VC120)
    #if defined(GO_COMP_MSVC_VC90) || defined(GO_COMP_MSVC_VC100) || defined(GO_COMP_MSVC_VC110) || defined(GO_COMP_MSVC_VC140) || defined(GO_COMP_MSVC_VC141)
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_comp_msvc_vc140)
{
    #if defined(GO_COMP_MSVC_VC140)
    #if defined(GO_COMP_MSVC_VC90) || defined(GO_COMP_MSVC_VC100) || defined(GO_COMP_MSVC_VC110) || defined(GO_COMP_MSVC_VC120) || defined(GO_COMP_MSVC_VC141)
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_comp_msvc_vc141)
{
    #if defined(GO_COMP_MSVC_VC141)
    #if defined(GO_COMP_MSVC_VC90) || defined(GO_COMP_MSVC_VC100) || defined(GO_COMP_MSVC_VC110) || defined(GO_COMP_MSVC_VC120) || defined(GO_COMP_MSVC_VC140)
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_not_define_go_gcc_version)
{
    #if defined(GO_GCC_VERSION)
    EXPECT_TRUE(false);
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_ide_ms_vs2008)
{
    #if defined(GO_IDE_MS_VS2008)
    #if defined(GO_IDE_MS_VS2010) || defined(GO_IDE_MS_VS2012) || defined(GO_IDE_MS_VS2013) || defined(GO_IDE_MS_VS2015) || defined(GO_IDE_MS_VS2017)
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_ide_ms_vs2010)
{
    #if defined(GO_IDE_MS_VS2010)
    #if defined(GO_IDE_MS_VS2008) || defined(GO_IDE_MS_VS2012) || defined(GO_IDE_MS_VS2013) || defined(GO_IDE_MS_VS2015) || defined(GO_IDE_MS_VS2017)
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_ide_ms_vs2012)
{
    #if defined(GO_IDE_MS_VS2012)
    #if defined(GO_IDE_MS_VS2008) || defined(GO_IDE_MS_VS2010) || defined(GO_IDE_MS_VS2013) || defined(GO_IDE_MS_VS2015) || defined(GO_IDE_MS_VS2017)
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_ide_ms_vs2013)
{
    #if defined(GO_IDE_MS_VS2013)
    #if defined(GO_IDE_MS_VS2008) || defined(GO_IDE_MS_VS2010) || defined(GO_IDE_MS_VS2012) || defined(GO_IDE_MS_VS2015) || defined(GO_IDE_MS_VS2017)
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_ide_ms_vs2015)
{
    #if defined(GO_IDE_MS_VS2015)
    #if defined(GO_IDE_MS_VS2008) || defined(GO_IDE_MS_VS2010) || defined(GO_IDE_MS_VS2012) || defined(GO_IDE_MS_VS2013) || defined(GO_IDE_MS_VS2017)
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_ide_ms_vs2017)
{
    #if defined(GO_IDE_MS_VS2017)
    #if defined(GO_IDE_MS_VS2008) || defined(GO_IDE_MS_VS2010) || defined(GO_IDE_MS_VS2012) || defined(GO_IDE_MS_VS2013) || defined(GO_IDE_MS_VS2015)
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_msvc_atl)
{
    #if defined(GO_MSVC_ATL)
    #if !defined(_ATL_VER)
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_msvc_atl_ver)
{
    #if defined(GO_MSVC_ATL_VER)
    #if defined(_ATL_VER)
    const std::string expected_version(GO_TO_STRING(_MFX_VER));
    const std::string go_msvc_atl_ver(GO_TO_STRING(GO_MSVC_ATL_VER));
    EXPECT_EQ(expected_version, go_msvc_atl_ver);
    #else
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_msvc_full_ver)
{
    #if defined(GO_MSVC_FULL_VER)
    #if defined(_MSC_FULL_VER)
    #if _MSC_FULL_VER > 100000000
    const int expected_version = _MSC_FULL_VER;
    #else
    const int expected_version = _MSC_FULL_VER * 10;
    #endif
    const int go_msvc_full_ver = GO_MSVC_FULL_VER;
    EXPECT_EQ(expected_version, go_msvc_full_ver);
    #else
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_msvc_mfc)
{
    #if defined(GO_MSVC_MFC)
    #if !defined(_MFC_VER)
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_msvc_mfc_ver)
{
    #if defined(GO_MSVC_MFC_VER)
    #if defined(_MFC_VER)
    const std::string expected_version(GO_TO_STRING(_MFX_VER));
    const std::string go_msvc_mfc_ver(GO_TO_STRING(GO_MSVC_MFC_VER));
    EXPECT_EQ(expected_version, go_msvc_mfc_ver);
    #else
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_msvc_ver)
{
    #if defined(GO_MSVC_VER)
    #if defined(_MSC_VER)
    const int expected_version = _MSC_VER;
    const int go_msvc_ver = GO_MSVC_VER;
    EXPECT_EQ(expected_version, go_msvc_ver);
    #else
    EXPECT_TRUE(false);
    #endif
    #endif
}

TEST(std_define_go_compiler_test_suite, test_define_go_unicode)
{
    #if defined(GO_MSVC_UNICODE)
    #if !(defined(_UNICODE) || defined(UNICODE))
    EXPECT_TRUE(false);
    #endif
    #endif
}

}
