#ifndef GO_CONFIG_SELECT_PLATFORM_CONFIG_HPP_INCLUDED
#define GO_CONFIG_SELECT_PLATFORM_CONFIG_HPP_INCLUDED

//
//  select_platform_config.hpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#if defined(__linux__)
#define GO_PLATFORM_CONFIG "go/config/platform/linux.hpp"
#elif defined(_WIN32) || defined(WIN32)
#define GO_PLATFORM_CONFIG "go/config/platform/windows.hpp"
#endif  // #if defined(__linux__)

#if 0
#include "go/config/platform/linux.hpp"
#include "go/config/platform/windows.hpp"
#endif  // #if 0

#endif  // #ifndef GO_CONFIG_SELECT_PLATFORM_CONFIG_HPP_INCLUDED
