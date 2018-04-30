#ifndef GO_BOOST_CONFIG_COMPILER_VISUALC_HPP_INCLUDED
#define GO_BOOST_CONFIG_COMPILER_VISUALC_HPP_INCLUDED

//
//  visualc.hpp
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

#if defined(BOOST_MSVC)

#define GO_BOOST_COMP_MSVC 1

#if (_MSC_VER == 1500)
#define GO_BOOST_COMP_MSVC_VC90 1
#define GO_BOOST_IDE_MS_VS2008 1
#elif (_MSC_VER == 1600)
#define GO_BOOST_COMP_MSVC_VC100 1
#define GO_BOOST_IDE_MS_VS2010 1
#elif (_MSC_VER == 1700)
#define GO_BOOST_COMP_MSVC_VC110 1
#define GO_BOOST_IDE_MS_VS2012 1
#elif (_MSC_VER == 1800)
#define GO_BOOST_COMP_MSVC_VC120 1
#define GO_BOOST_IDE_MS_VS2013 1
#elif (_MSC_VER == 1900)
#define GO_BOOST_COMP_MSVC_VC140 1
#define GO_BOOST_IDE_MS_VS2015 1
#elif (_MSC_VER >= 1910)
#define GO_BOOST_COMP_MSVC_VC141 1
#define GO_BOOST_IDE_MS_VS2017 1
#if (_MSC_VER == 1910)
#define GO_BOOST_IDE_MS_VS2017_15_0 1
#elif (_MSC_VER == 1911)
#define GO_BOOST_IDE_MS_VS2017_15_3 1
#elif (_MSC_VER == 1912)
#define GO_BOOST_IDE_MS_VS2017_15_5 1
#elif (_MSC_VER == 1913)
#define GO_BOOST_IDE_MS_VS2017_15_6 1
#elif (_MSC_VER == 1914)
#define GO_BOOST_IDE_MS_VS2017_15_7 1
#endif  // #if (_MSC_VER == 1910)
#endif  // #if (_MSC_VER == 1500)

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
#define GO_BOOST_TYPENAME_REQUIRED 1
#endif  // #if (_MSC_VER < 1900)

// C++11 support
#if defined(BOOST_NO_CXX11_CONSTEXPR)
#define GO_BOOST_CONSTEXPR
#else
#define GO_BOOST_CONSTEXPR constexpr
#endif  // #if defined(GO_NO_CXX11_CONSTEXPR)

#if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || defined(GO_BOOST_COMP_MSVC_VC120)
#define GO_BOOST_DEFAULT_CONSTRUCTOR {}
#define GO_BOOST_DEFAULT_DESTRUCTOR {}
#else
#define GO_BOOST_DEFAULT_CONSTRUCTOR = default;
#define GO_BOOST_DEFAULT_DESTRUCTOR = default;
#endif  // #if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)

#endif  // #if defined(BOOST_MSVC)

#endif  // #ifndef GO_BOOST_CONFIG_COMPILER_VISUALC_HPP_INCLUDED
