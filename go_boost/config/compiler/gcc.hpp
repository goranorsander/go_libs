#ifndef GO_BOOST_CONFIG_COMPILER_GCC_HPP_INCLUDED
#define GO_BOOST_CONFIG_COMPILER_GCC_HPP_INCLUDED

//
//  gcc.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#if defined(BOOST_GCC)

// Compiler message
#define GO_BOOST_MESSAGE(_message_) \
__warning _message_

// C++ keyword typename support
#define GO_BOOST_TYPENAME typename

#endif  // #if defined(BOOST_GCC)

#endif  // #ifndef GO_BOOST_CONFIG_COMPILER_GCC_HPP_INCLUDED
