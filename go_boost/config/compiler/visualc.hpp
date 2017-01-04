#ifndef GO_BOOST_CONFIG_COMPILER_VISUALC_HPP_INCLUDED
#define GO_BOOST_CONFIG_COMPILER_VISUALC_HPP_INCLUDED

//
//  visualc.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_MSVC)

// Compiler message
#define GO_BOOST_MESSAGE(_message_) \
__pragma(message(_message_))

// ATL support
#if defined(_ATL_VER)

#define GO_BOOST_MSVC_ATL 1

#define GO_BOOST_MSVC_ATL_VER _MFX_VER

#endif  // if defined(_ATL_VER)

// MFC support
#if defined(_MFC_VER)

#define GO_BOOST_MSVC_MFC 1

#define GO_BOOST_MSVC_MFC_VER _MFX_VER

#endif  // if defined(_MFC_VER)

// Unicode support
#if defined(_UNICODE) || defined(UNICODE)

#define GO_BOOST_UNICODE 1

#endif  // if defined(_UNICODE) || defined(UNICODE)

// C++ keyword typename support
#if (_MSC_VER < 1900)

#define GO_BOOST_TYPENAME

#else

#define GO_BOOST_TYPENAME typename

#endif  // #if (_MSC_VER < 1900)

#endif  // #if defined(BOOST_MSVC)

#endif  // #ifndef GO_BOOST_CONFIG_COMPILER_VISUALC_HPP_INCLUDED
