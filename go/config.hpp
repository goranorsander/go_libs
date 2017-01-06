#ifndef GO_CONFIG_HPP_INCLUDED
#define GO_CONFIG_HPP_INCLUDED

//
//  config.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#if !defined(GO_COMPILER_CONFIG) && !defined(GO_NO_COMPILER_CONFIG) && !defined(GO_NO_CONFIG)
#include "go/config/select_compiler_config.hpp"
#endif

#ifdef GO_COMPILER_CONFIG
#include GO_COMPILER_CONFIG
#endif

#endif  // #ifndef GO_CONFIG_HPP_INCLUDED
