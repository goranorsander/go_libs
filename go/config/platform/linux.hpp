#ifndef GO_CONFIG_PLATFORM_LINUX_HPP_INCLUDED
#define GO_CONFIG_PLATFORM_LINUX_HPP_INCLUDED

//
//  linux.hpp
//
//  Copyright 2017-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <cstdint>

#if defined(__linux__)

#define GO_PLATFORM_LINUX 1

#define GO_SIZE_OF_WCHAR_T 4

#endif  // defined(__linux__)

#if defined(__x86_64__) || defined(__ppc64__)

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

#endif  // #if defined(__x86_64__) || defined(__ppc64__)

#endif  // #ifndef GO_CONFIG_PLATFORM_LINUX_HPP_INCLUDED
