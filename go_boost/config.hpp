#ifndef GO_BOOST_CONFIG_HPP_INCLUDED
#define GO_BOOST_CONFIG_HPP_INCLUDED

//
//  config.hpp
//
//  Copyright 2016-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <boost/config.hpp>
#include <boost/predef.h>
#include <boost/version.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#if !defined(GO_BOOST_PLATFORM_CONFIG) && !defined(GO_BOOST_NO_PLATFORM_CONFIG) && !defined(GO_BOOST_NO_CONFIG)
#include "go_boost/config/select_platform_config.hpp"
#endif  // #if !defined(GO_BOOST_PLATFORM_CONFIG) && !defined(GO_BOOST_NO_PLATFORM_CONFIG) && !defined(GO_BOOST_NO_CONFIG)

#ifdef GO_BOOST_PLATFORM_CONFIG
#include GO_BOOST_PLATFORM_CONFIG
#endif  // #ifdef GO_BOOST_PLATFORM_CONFIG

#if !defined(GO_BOOST_COMPILER_CONFIG) && !defined(GO_BOOST_NO_COMPILER_CONFIG) && !defined(GO_BOOST_NO_CONFIG)
#include "go_boost/config/select_compiler_config.hpp"
#endif  // #if !defined(GO_BOOST_COMPILER_CONFIG) && !defined(GO_BOOST_NO_COMPILER_CONFIG) && !defined(GO_BOOST_NO_CONFIG)

#ifdef GO_BOOST_COMPILER_CONFIG
#include GO_BOOST_COMPILER_CONFIG
#endif  // #ifdef GO_BOOST_COMPILER_CONFIG

#include "go_boost/config/preprocessor.hpp"

#endif  // #ifndef GO_BOOST_CONFIG_HPP_INCLUDED
