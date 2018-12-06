#ifndef GO_BOOST_CONFIG_COMPILER_GCC_HPP_INCLUDED
#define GO_BOOST_CONFIG_COMPILER_GCC_HPP_INCLUDED

//
//  gcc.hpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#if defined(__GNUC__)

#define GO_BOOST_COMP_GCC 1

#define GO_BOOST_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

// MinGW
#if defined(__MINGW32__) || defined(__MINGW64__)
#define GO_BOOST_COMP_GCC_MINGW 1
#endif  // #if defined(__MINGW32__) || defined(__MINGW64__)

// Compiler message
#define GO_BOOST_MESSAGE(_message_) \
__warning _message_

// C++ keyword typename support
#define GO_BOOST_TYPENAME typename
#define GO_BOOST_TYPENAME_REQUIRED 1

// C++ issue workarounds
#define GO_BOOST_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1
#define GO_BOOST_CHAR16_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1
#define GO_BOOST_CHAR32_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1

// C++ restrictions
#define GO_BOOST_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7 1

// C++11 support
#if (GO_BOOST_GCC_VERSION < 40800)
#define GO_BOOST_NO_CXX11_THREAD_LOCAL_STORAGE 1
#endif  // #if (GO_BOOST_GCC_VERSION < 40800)

#if defined(BOOST_NO_CXX11_CONSTEXPR)
#define GO_BOOST_CONSTEXPR
#else
#define GO_BOOST_CONSTEXPR constexpr
#endif  // #if defined(BOOST_NO_CXX11_CONSTEXPR)

#if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
#define GO_BOOST_DEFAULT_CONSTRUCTOR {}
#define GO_BOOST_DEFAULT_DESTRUCTOR {}
#else
#define GO_BOOST_DEFAULT_CONSTRUCTOR = default;
#define GO_BOOST_DEFAULT_DESTRUCTOR = default;
#endif  // #if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)

#if defined(BOOST_NO_CXX11_NULLPTR)
#define GO_BOOST_NULLPTR NULL
#else
#define GO_BOOST_NULLPTR nullptr
#endif  // #if defined(BOOST_NO_CXX11_NULLPTR)

// C++ keyword override and final support
#if (GO_BOOST_GCC_VERSION < 40700)
#define GO_BOOST_FINAL
#define GO_BOOST_OVERRIDE
#else
#define GO_BOOST_FINAL final
#define GO_BOOST_OVERRIDE override
#endif  // #if (GO_BOOST_GCC_VERSION < 40700)

#endif  // #if defined(__GNUC__)

#endif  // #ifndef GO_BOOST_CONFIG_COMPILER_GCC_HPP_INCLUDED
