#ifndef GO_CONFIG_HPP_INCLUDED
#define GO_CONFIG_HPP_INCLUDED

//
//  config.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#if !defined(GO_COMPILER_CONFIG) && !defined(GO_NO_COMPILER_CONFIG) && !defined(GO_NO_CONFIG)
#include "go/config/select_compiler_config.hpp"
#endif  // #if !defined(GO_COMPILER_CONFIG) && !defined(GO_NO_COMPILER_CONFIG) && !defined(GO_NO_CONFIG)

#ifdef GO_COMPILER_CONFIG
#include GO_COMPILER_CONFIG
#endif  // #ifdef GO_COMPILER_CONFIG

#if !defined(GO_PLATFORM_CONFIG) && !defined(GO_NO_PLATFORM_CONFIG) && !defined(GO_NO_CONFIG)
#include "go/config/select_platform_config.hpp"
#endif  // #if !defined(GO_PLATFORM_CONFIG) && !defined(GO_NO_PLATFORM_CONFIG) && !defined(GO_NO_CONFIG)

#ifdef GO_PLATFORM_CONFIG
#include GO_PLATFORM_CONFIG
#endif  // #ifdef GO_PLATFORM_CONFIG

#include "go/config/preprocessor.hpp"

#endif  // #ifndef GO_CONFIG_HPP_INCLUDED
