//
//  define_go_boost_compiler_test_suite.cpp
//
//  Copyright 2018-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#if defined(__clang__)
#include "define_go_boost_compiler_clang_test.ipp"
#elif defined(__GNUC__)
#if defined(__MINGW32__) || defined(__MINGW64__)
#include "define_go_boost_compiler_mingw_gcc_test.ipp"
#else
#include "define_go_boost_compiler_gcc_test.ipp"
#endif  // #if defined(__MINGW32__) || defined(__MINGW64__)
#elif defined(_MSC_VER)
#include "define_go_boost_compiler_visualc_test.ipp"
#endif  // #if defined(__clang__)
