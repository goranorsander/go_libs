#ifndef GO_BOOST_CONFIG_COMPILER_CLANG_HPP_INCLUDED
#define GO_BOOST_CONFIG_COMPILER_CLANG_HPP_INCLUDED

//
//  clang.hpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#if defined(__clang__)

#define GO_BOOST_COMP_CLANG 1

#define GO_BOOST_CLANG_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)

// Compiler message
#define GO_BOOST_MESSAGE(_message_) \
__warning _message_

// C++ keyword typename support
#define GO_BOOST_TYPENAME typename
#define GO_BOOST_TYPENAME_REQUIRED 1

// C++ issue workarounds
#define GO_BOOST_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE 1
#define GO_BOOST_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1
#define GO_BOOST_CHAR16_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1
#define GO_BOOST_CHAR32_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1

// C++11 support
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

#endif  // #if defined(__clang__)

#endif  // #ifndef GO_BOOST_CONFIG_COMPILER_CLANG_HPP_INCLUDED
