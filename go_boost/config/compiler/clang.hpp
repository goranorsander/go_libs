#ifndef GO_BOOST_CONFIG_COMPILER_CLANG_HPP_INCLUDED
#define GO_BOOST_CONFIG_COMPILER_CLANG_HPP_INCLUDED

//
//  clang.hpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#if defined(BOOST_CLANG)

// Compiler message
#define GO_BOOST_MESSAGE(_message_) \
__warning _message_

// C++ keyword typename support
#define GO_BOOST_TYPENAME typename

// C++ issue workarounds
#define GO_BOOST_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE 1
#define GO_BOOST_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1
#define GO_BOOST_CHAR16_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1
#define GO_BOOST_CHAR32_T_ILLEGAL_BYTE_SEQUENCE_ISSUE 1

#endif  // #if defined(BOOST_CLANG)

#endif  // #ifndef GO_BOOST_CONFIG_COMPILER_CLANG_HPP_INCLUDED
