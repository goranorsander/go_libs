#ifndef GO_BOOST_UTILITY_STRING_DETAIL_STRING_CAST_FWD_HPP_INCLUDED
#define GO_BOOST_UTILITY_STRING_DETAIL_STRING_CAST_FWD_HPP_INCLUDED

//
//  string_cast_fwd.hpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/utility/u2string.hpp>
#include <go_boost/utility/u8string.hpp>
#include <go_boost/utility/u16string.hpp>
#include <go_boost/utility/u32string.hpp>
#include <string>
#include <boost/function.hpp>

namespace go_boost
{
namespace utility
{
namespace string
{
namespace detail
{

template <typename to_string, typename from_string>
struct string_cast;

std::string convert_wstring_to_string(const std::wstring&);
std::string convert_u2string_to_string(const u2string&);
std::string convert_u8string_to_string(const u8string&);
std::string convert_u16string_to_string(const u16string&);
std::string convert_u32string_to_string(const u32string&);
std::wstring convert_string_to_wstring(const std::string&);
std::wstring convert_u2string_to_wstring(const u2string&);
std::wstring convert_u8string_to_wstring(const u8string&);
std::wstring convert_u16string_to_wstring(const u16string&);
std::wstring convert_u32string_to_wstring(const u32string&);
u2string convert_string_to_u2string(const std::string&);
u2string convert_wstring_to_u2string(const std::wstring&);
u2string convert_u8string_to_u2string(const u8string&);
u2string convert_u16string_to_u2string(const u16string&);
u2string convert_u32string_to_u2string(const u32string&);
u8string convert_string_to_u8string(const std::string&);
u8string convert_wstring_to_u8string(const std::wstring&);
u8string convert_u2string_to_u8string(const u2string&);
u8string convert_u16string_to_u8string(const u16string&);
u8string convert_u32string_to_u8string(const u32string&);
u16string convert_string_to_u16string(const std::string&);
u16string convert_wstring_to_u16string(const std::wstring&);
u16string convert_u2string_to_u16string(const u2string&);
u16string convert_u8string_to_u16string(const u8string&);
u16string convert_u32string_to_u16string(const u32string&);
u32string convert_string_to_u32string(const std::string&);
u32string convert_wstring_to_u32string(const std::wstring&);
u32string convert_u2string_to_u32string(const u2string&);
u32string convert_u8string_to_u32string(const u8string&);
u32string convert_u16string_to_u32string(const u16string&);

bool is_little_endian_system();

}

// to std::string

typedef GO_BOOST_TYPENAME boost::function<std::string(const std::wstring&)> convert_wstring_to_string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<std::string(const u2string&)> convert_u2string_to_string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<std::string(const u8string&)> convert_u8string_to_string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<std::string(const u16string&)> convert_u16string_to_string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<std::string(const u32string&)> convert_u32string_to_string_function_signature;

convert_wstring_to_string_function_signature& convert_wstring_to_string();
convert_u2string_to_string_function_signature& convert_u2string_to_string();
convert_u8string_to_string_function_signature& convert_u8string_to_string();
convert_u16string_to_string_function_signature& convert_u16string_to_string();
convert_u32string_to_string_function_signature& convert_u32string_to_string();

// to std::wstring

typedef GO_BOOST_TYPENAME boost::function<std::wstring(const std::string&)> convert_string_to_wstring_function_signature;
typedef GO_BOOST_TYPENAME boost::function<std::wstring(const u2string&)> convert_u2string_to_wstring_function_signature;
typedef GO_BOOST_TYPENAME boost::function<std::wstring(const u8string&)> convert_u8string_to_wstring_function_signature;
typedef GO_BOOST_TYPENAME boost::function<std::wstring(const u16string&)> convert_u16string_to_wstring_function_signature;
typedef GO_BOOST_TYPENAME boost::function<std::wstring(const u32string&)> convert_u32string_to_wstring_function_signature;

convert_string_to_wstring_function_signature& convert_string_to_wstring();
convert_u2string_to_wstring_function_signature& convert_u2string_to_wstring();
convert_u8string_to_wstring_function_signature& convert_u8string_to_wstring();
convert_u16string_to_wstring_function_signature& convert_u16string_to_wstring();
convert_u32string_to_wstring_function_signature& convert_u32string_to_wstring();

// to go::utility::u2string

typedef GO_BOOST_TYPENAME boost::function<u2string(const std::string&)> convert_string_to_u2string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u2string(const std::wstring&)> convert_wstring_to_u2string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u2string(const u8string&)> convert_u8string_to_u2string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u2string(const u16string&)> convert_u16string_to_u2string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u2string(const u32string&)> convert_u32string_to_u2string_function_signature;

convert_string_to_u2string_function_signature& convert_string_to_u2string();
convert_wstring_to_u2string_function_signature& convert_wstring_to_u2string();
convert_u8string_to_u2string_function_signature& convert_u8string_to_u2string();
convert_u16string_to_u2string_function_signature& convert_u16string_to_u2string();
convert_u32string_to_u2string_function_signature& convert_u32string_to_u2string();

// to go::utility::u8string

typedef GO_BOOST_TYPENAME boost::function<u8string(const std::string&)> convert_string_to_u8string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u8string(const std::wstring&)> convert_wstring_to_u8string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u8string(const u2string&)> convert_u2string_to_u8string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u8string(const u16string&)> convert_u16string_to_u8string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u8string(const u32string&)> convert_u32string_to_u8string_function_signature;

convert_string_to_u8string_function_signature& convert_string_to_u8string();
convert_wstring_to_u8string_function_signature& convert_wstring_to_u8string();
convert_u2string_to_u8string_function_signature& convert_u2string_to_u8string();
convert_u16string_to_u8string_function_signature& convert_u16string_to_u8string();
convert_u32string_to_u8string_function_signature& convert_u32string_to_u8string();

// to u16string

typedef GO_BOOST_TYPENAME boost::function<u16string(const std::string&)> convert_string_to_u16string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u16string(const std::wstring&)> convert_wstring_to_u16string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u16string(const u2string&)> convert_u2string_to_u16string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u16string(const u8string&)> convert_u8string_to_u16string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u16string(const u32string&)> convert_u32string_to_u16string_function_signature;

convert_string_to_u16string_function_signature& convert_string_to_u16string();
convert_wstring_to_u16string_function_signature& convert_wstring_to_u16string();
convert_u2string_to_u16string_function_signature& convert_u2string_to_u16string();
convert_u8string_to_u16string_function_signature& convert_u8string_to_u16string();
convert_u32string_to_u16string_function_signature& convert_u32string_to_u16string();

// to u32string

typedef GO_BOOST_TYPENAME boost::function<u32string(const std::string&)> convert_string_to_u32string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u32string(const std::wstring&)> convert_wstring_to_u32string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u32string(const u2string&)> convert_u2string_to_u32string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u32string(const u8string&)> convert_u8string_to_u32string_function_signature;
typedef GO_BOOST_TYPENAME boost::function<u32string(const u16string&)> convert_u16string_to_u32string_function_signature;

convert_string_to_u32string_function_signature& convert_string_to_u32string();
convert_wstring_to_u32string_function_signature& convert_wstring_to_u32string();
convert_u2string_to_u32string_function_signature& convert_u2string_to_u32string();
convert_u8string_to_u32string_function_signature& convert_u8string_to_u32string();
convert_u16string_to_u32string_function_signature& convert_u16string_to_u32string();

}
}
}

#endif  // #ifndef GO_BOOST_UTILITY_STRING_DETAIL_STRING_CAST_FWD_HPP_INCLUDED
