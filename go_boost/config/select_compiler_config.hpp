#ifndef GO_BOOST_CONFIG_SELECT_COMPILER_CONFIG_HPP_INCLUDED
#define GO_BOOST_CONFIG_SELECT_COMPILER_CONFIG_HPP_INCLUDED

//
//  select_compiler_config.hpp
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

#if defined(BOOST_GCC)
#define GO_BOOST_COMPILER_CONFIG "go_boost/config/compiler/gcc.hpp"
#elif defined(BOOST_MSVC)
#define GO_BOOST_COMPILER_CONFIG "go_boost/config/compiler/visualc.hpp"
#endif

#if 0
#include "go_boost/config/compiler/gcc.hpp"
#include "go_boost/config/compiler/visualc.hpp"
#endif

#endif  // #ifndef GO_BOOST_CONFIG_SELECT_COMPILER_CONFIG_HPP_INCLUDED
