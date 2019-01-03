//
//  define_go_platform_test_suite.cpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#if defined(__linux__)
#include "define_go_platform_linux_test.ipp"
#elif defined(_WIN32) || defined(WIN32)
#include "define_go_platform_windows_test.ipp"
#endif  // #if defined(__linux__)
