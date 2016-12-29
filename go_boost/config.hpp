#ifndef GO_BOOST_CONFIG_HPP_INCLUDED
#define GO_BOOST_CONFIG_HPP_INCLUDED

//
//  config.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <boost/config.hpp>
#include <boost/predef.h>
#include <boost/version.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(GO_BOOST_COMPILER_CONFIG) && !defined(GO_BOOST_NO_COMPILER_CONFIG) && !defined(GO_BOOST_NO_CONFIG)
#include "go_boost/config/select_compiler_config.hpp"
#endif

#ifdef GO_BOOST_COMPILER_CONFIG
#include GO_BOOST_COMPILER_CONFIG
#endif

#endif  // #ifndef GO_BOOST_CONFIG_HPP_INCLUDED
