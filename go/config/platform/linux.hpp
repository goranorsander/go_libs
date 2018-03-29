#ifndef GO_CONFIG_PLATFORM_LINUX_HPP_INCLUDED
#define GO_CONFIG_PLATFORM_LINUX_HPP_INCLUDED

//
//  linux.hpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#if defined(__linux__)

#define GO_PLATFORM_LINUX 1

#endif  // defined(__linux__)

#if defined(__x86_64__) || defined(__ppc64__)

#define GO_ADDRESS_MODEL_64 1

#else

#define GO_ADDRESS_MODEL_32 1

#endif  // #if defined(__x86_64__) || defined(__ppc64__)

#endif  // #ifndef GO_CONFIG_PLATFORM_LINUX_HPP_INCLUDED
