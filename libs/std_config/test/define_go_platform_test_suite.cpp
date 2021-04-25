//
//  define_go_platform_test_suite.cpp
//
//  Copyright 2017-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(__linux__)
#include "define_go_platform_linux_test.ipp"
#elif defined(_WIN32) || defined(WIN32)
#include "define_go_platform_windows_test.ipp"
#endif  // #if defined(__linux__)
