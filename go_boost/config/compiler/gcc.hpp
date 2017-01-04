#ifndef GO_BOOST_CONFIG_COMPILER_GCC_HPP_INCLUDED
#define GO_BOOST_CONFIG_COMPILER_GCC_HPP_INCLUDED

//
//  gcc.hpp
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

// Compiler message
#define GO_BOOST_MESSAGE(_message_) \
__warning _message_

// C++ keyword typename support
#define GO_BOOST_TYPENAME typename

#endif  // #if defined(BOOST_GCC)

#endif  // #ifndef GO_BOOST_CONFIG_COMPILER_GCC_HPP_INCLUDED
