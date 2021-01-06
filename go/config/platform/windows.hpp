#ifndef GO_CONFIG_PLATFORM_WINDOWS_HPP_INCLUDED
#define GO_CONFIG_PLATFORM_WINDOWS_HPP_INCLUDED

//
//  windows.hpp
//
//  Copyright 2017-2021 Göran Orsander
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

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64)

#define GO_PLATFORM_WINDOWS 1

#define GO_SIZE_OF_WCHAR_T 2

#if defined(_WIN64)

#define GO_ADDRESS_MODEL_64 1
#define GO_L(i) i ## ll
#define GO_UL(i) i ## ull

namespace go
{

typedef int64_t int3264_t;
typedef uint64_t uint3264_t;

}

#else

#define GO_ADDRESS_MODEL_32 1
#define GO_L(i) i ## l
#define GO_UL(i) i ## ul

namespace go
{

typedef int32_t int3264_t;
typedef uint32_t uint3264_t;

}

#endif  // #if defined(_WIN64)

#endif  // #if defined(_WIN32) || defined(WIN32) || defined(_WIN64)

#endif  // #ifndef GO_CONFIG_PLATFORM_WINDOWS_HPP_INCLUDED
