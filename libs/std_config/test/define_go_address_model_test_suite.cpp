//
//  define_go_address_model_test_suite.cpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(__linux__)
#if defined(__x86_64__) || defined(__ppc64__)
#include "define_go_address_model_64_test.ipp"
#else
#include "define_go_address_model_32_test.ipp"
#endif  // #if defined(__x86_64__) || defined(__ppc64__)
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64)
#if defined(_WIN64)
#include "define_go_address_model_64_test.ipp"
#else
#include "define_go_address_model_32_test.ipp"
#endif  // #if defined(_WIN64)
#endif  // #if defined(__linux__)
