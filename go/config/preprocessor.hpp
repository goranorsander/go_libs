#ifndef GO_CONFIG_PREPROCESSOR_HPP_INCLUDED
#define GO_CONFIG_PREPROCESSOR_HPP_INCLUDED

//
//  preprocessor.hpp
//
//  Copyright 2017-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#define GO_TO_STRING_HELPER(s) #s
#define GO_TO_STRING(s) GO_TO_STRING_HELPER(s)

#define GO_APPEND_L(s) L## #s
#define GO_TO_WSTRING(s) GO_APPEND_L(s)

#define GO_APPEND_U8(s) u8## #s
#define GO_TO_U8STRING(s) GO_APPEND_U8(s)

#define GO_APPEND_U16(s) u## #s
#define GO_TO_U16STRING(s) GO_APPEND_U16(s)

#define GO_APPEND_U32(s) U## #s
#define GO_TO_U32STRING(s) GO_APPEND_U32(s)

#define GO_WFILE GO_APPEND_L(__FILE__)

#if defined(GO_COMP_MSVC)
#define GO_FUNC __FUNCTION__
#else
#define GO_FUNC __func__
#endif  // #if defined(GO_MSVC)

#define GO_WFUNC GO_APPEND_L(GO_FUNC)

#define GO_CAT_HELPER(a, ...) a ## __VA_ARGS__
#define GO_CAT(a, ...) GO_CAT_HELPER(a, __VA_ARGS__)

#endif  // #ifndef GO_CONFIG_PREPROCESSOR_HPP_INCLUDED
