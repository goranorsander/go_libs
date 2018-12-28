#ifndef GO_BOOST_CONFIG_PREPROCESSOR_HPP_INCLUDED
#define GO_BOOST_CONFIG_PREPROCESSOR_HPP_INCLUDED

//
//  preprocessor.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <boost/current_function.hpp>
#include <boost/preprocessor/stringize.hpp>

#define GO_BOOST_TO_STRING_HELPER(s) #s
#define GO_BOOST_TO_STRING(s) GO_BOOST_TO_STRING_HELPER(s)

#define GO_BOOST_APPEND_L(s) L## #s
#define GO_BOOST_TO_WSTRING(s) GO_BOOST_APPEND_L(s)

#define GO_BOOST_APPEND_U8(s) u8## #s
#define GO_BOOST_TO_U8STRING(s) GO_BOOST_APPEND_U8(s)

#define GO_BOOST_APPEND_U16(s) u## #s
#define GO_BOOST_TO_U16STRING(s) GO_BOOST_APPEND_U16(s)

#define GO_BOOST_APPEND_U32(s) U## #s
#define GO_BOOST_TO_U32STRING(s) GO_BOOST_APPEND_U32(s)

#define GO_BOOST_WFILE GO_BOOST_APPEND_L(__FILE__)

#if defined(_MSC_VER)
#define GO_BOOST_FUNC BOOST_CURRENT_FUNCTION
#else
#define GO_BOOST_FUNC BOOST_PP_STRINGIZE(BOOST_CURRENT_FUNCTION)
#endif  // #if defined(_MSC_VER)

#define GO_BOOST_WFUNC GO_BOOST_APPEND_L(GO_BOOST_FUNC)

#endif  // #ifndef GO_BOOST_CONFIG_PREPROCESSOR_HPP_INCLUDED
