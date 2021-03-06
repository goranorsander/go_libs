#ifndef GO_BOOST_CONFIG_PLATFORM_LINUX_HPP_INCLUDED
#define GO_BOOST_CONFIG_PLATFORM_LINUX_HPP_INCLUDED

//
//  linux.hpp
//
//  Copyright 2017-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/cstdint.hpp>

#if defined(__linux__)

#define GO_BOOST_PLATFORM_LINUX 1

#define GO_BOOST_SIZE_OF_WCHAR_T 4

#endif  // defined(__linux__)

#if defined(__x86_64__) || defined(__ppc64__)

#define GO_BOOST_ADDRESS_MODEL_64 1
#define GO_BOOST_L(i) i ## ll
#define GO_BOOST_UL(i) i ## ull

namespace go_boost
{

typedef boost::int64_t int3264_t;
typedef boost::uint64_t uint3264_t;

}

#else

#define GO_BOOST_ADDRESS_MODEL_32 1
#define GO_BOOST_L(i) i ## l
#define GO_BOOST_UL(i) i ## ul

namespace go_boost
{

typedef boost::int32_t int3264_t;
typedef boost::uint32_t uint3264_t;

}

#endif  // #if defined(__x86_64__) || defined(__ppc64__)

#endif  // #ifndef GO_BOOST_CONFIG_PLATFORM_LINUX_HPP_INCLUDED
