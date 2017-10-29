#ifndef GO_BOOST_CONFIG_COMPILER_GCC_HPP_INCLUDED
#define GO_BOOST_CONFIG_COMPILER_GCC_HPP_INCLUDED

//
//  gcc.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

// MinGW
#if defined(__MINGW32__) || defined(__MINGW64__)
#define GO_BOOST_COMP_GCC_MINGW 1
#endif  // #if defined(__MINGW32__) || defined(__MINGW64__)

#if defined(BOOST_GCC)

// Compiler message
#define GO_BOOST_MESSAGE(_message_) \
__warning _message_

// C++ keyword typename support
#define GO_BOOST_TYPENAME typename

// C++ issue workarounds
#define GO_BOOST_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1
#define GO_BOOST_CHAR16_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1
#define GO_BOOST_CHAR32_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1

// C++ restrictions
#define GO_BOOST_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7 1

// C++11 support
#if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
#define GO_BOOST_DEFAULT_CONSTRUCTOR {}
#define GO_BOOST_DEFAULT_DESTRUCTOR {}
#else
#define GO_BOOST_DEFAULT_CONSTRUCTOR = default;
#define GO_BOOST_DEFAULT_DESTRUCTOR = default;
#endif  // #if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)

#endif  // #if defined(BOOST_GCC)

#endif  // #ifndef GO_BOOST_CONFIG_COMPILER_GCC_HPP_INCLUDED
