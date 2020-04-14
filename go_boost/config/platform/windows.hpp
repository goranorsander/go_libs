#ifndef GO_BOOST_CONFIG_PLATFORM_WINDOWS_HPP_INCLUDED
#define GO_BOOST_CONFIG_PLATFORM_WINDOWS_HPP_INCLUDED

//
//  windows.hpp
//
//  Copyright 2017-2020 Göran Orsander
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

#if defined(_WIN32) || defined(WIN32)

#define GO_BOOST_PLATFORM_WINDOWS 1

#define GO_BOOST_SIZE_OF_WCHAR_T 2

#endif  // #if defined(_WIN32) || defined(WIN32)

#if defined(_WIN32) || defined(_WIN64)

#if defined(_WIN64)

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

#endif  // #if defined(_WIN64)

#endif  // #if defined(_WIN32) || defined(_WIN64)

#endif  // #ifndef GO_BOOST_CONFIG_PLATFORM_WINDOWS_HPP_INCLUDED
