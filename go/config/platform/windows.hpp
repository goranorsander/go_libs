#ifndef GO_CONFIG_PLATFORM_WINDOWS_HPP_INCLUDED
#define GO_CONFIG_PLATFORM_WINDOWS_HPP_INCLUDED

//
//  windows.hpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64)

#define GO_PLATFORM_WINDOWS 1

#if defined(_WIN64)

#define GO_ADDRESS_MODEL_64 1

#else

#define GO_ADDRESS_MODEL_32 1

#endif  // #if defined(_WIN64)

#endif  // #if defined(_WIN32) || defined(WIN32) || defined(_WIN64)

#endif  // #ifndef GO_CONFIG_PLATFORM_WINDOWS_HPP_INCLUDED
