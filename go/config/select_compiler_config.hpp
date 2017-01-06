#ifndef GO_CONFIG_SELECT_COMPILER_CONFIG_HPP_INCLUDED
#define GO_CONFIG_SELECT_COMPILER_CONFIG_HPP_INCLUDED

//
//  select_compiler_config.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#if defined(__clang__)
#define GO_COMPILER_CONFIG "go/config/compiler/clang.hpp"
#elif defined(__GNUC__)
#define GO_COMPILER_CONFIG "go/config/compiler/gcc.hpp"
#elif defined(_MSC_VER)
#define GO_COMPILER_CONFIG "go/config/compiler/visualc.hpp"
#endif

#if 0
#include "go/config/compiler/gcc.hpp"
#include "go/config/compiler/visualc.hpp"
#endif

#endif  // #ifndef GO_CONFIG_SELECT_COMPILER_CONFIG_HPP_INCLUDED
