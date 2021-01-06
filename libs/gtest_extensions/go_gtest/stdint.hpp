#ifndef GO_GTEST_STDINT_HPP_INCLUDED
#define GO_GTEST_STDINT_HPP_INCLUDED

//
//  stdint.hpp
//
//  Copyright 2019-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

// cstdint and stdint.h issue
// https://stackoverflow.com/questions/126279/c99-stdint-h-header-and-ms-visual-studio
#if defined(_MSC_VER)
#if _MSC_VER < 1310
#include <stdint.h>
#elif _MSC_VER >= 1600
#include <cstdint>
#else
typedef signed __int8 int8_t;
typedef signed __int16 int16_t;
typedef signed __int32 int32_t;
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif  // #if _MSC_VER < 1310
#else
#include <cstdint>
#endif  // #if defined(_MSC_VER)

#endif  // #ifndef GO_GTEST_STDINT_HPP_INCLUDED
