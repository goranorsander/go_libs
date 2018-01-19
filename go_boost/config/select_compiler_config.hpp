#ifndef GO_BOOST_CONFIG_SELECT_COMPILER_CONFIG_HPP_INCLUDED
#define GO_BOOST_CONFIG_SELECT_COMPILER_CONFIG_HPP_INCLUDED

//
//  select_compiler_config.hpp
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

#if defined(__clang__)
#define GO_BOOST_COMPILER_CONFIG "go_boost/config/compiler/clang.hpp"
#elif defined(BOOST_GCC)
#define GO_BOOST_COMPILER_CONFIG "go_boost/config/compiler/gcc.hpp"
#elif defined(BOOST_MSVC)
#define GO_BOOST_COMPILER_CONFIG "go_boost/config/compiler/visualc.hpp"
#endif  // #if defined(__clang__)

#if 0
#include "go_boost/config/compiler/gcc.hpp"
#include "go_boost/config/compiler/visualc.hpp"
#endif  // #if 0

#endif  // #ifndef GO_BOOST_CONFIG_SELECT_COMPILER_CONFIG_HPP_INCLUDED
