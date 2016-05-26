#ifndef GO_CONFIG_COMPILER_VISUALC_HPP_INCLUDED
#define GO_CONFIG_COMPILER_VISUALC_HPP_INCLUDED

//
//  visualc.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#define GO_COMP_MSVC 1

#define GO_MSVC_VER _MSC_VER

#if _MSC_FULL_VER > 100000000
#define GO_MSVC_FULL_VER _MSC_FULL_VER
#else
#define GO_MSVC_FULL_VER (_MSC_FULL_VER * 10)
#endif

#define GO_COMP_GCC 0

#endif  // #ifndef GO_CONFIG_COMPILER_VISUALC_HPP_INCLUDED
