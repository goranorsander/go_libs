#ifndef GO_BOOST_CONFIG_PLATFORM_WINDOWS_HPP_INCLUDED
#define GO_BOOST_CONFIG_PLATFORM_WINDOWS_HPP_INCLUDED

//
//  windows.hpp
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

#if defined(_WIN32) || defined(WIN32)

#define GO_BOOST_PLATFORM_WINDOWS 1

#endif  // #if defined(_WIN32) || defined(WIN32)

#endif  // #ifndef GO_BOOST_CONFIG_PLATFORM_WINDOWS_HPP_INCLUDED
