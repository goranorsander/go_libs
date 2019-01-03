#ifndef GO_BOOST_UTILITY_STRING_ALGORITHM_FWD_HPP_INCLUDED
#define GO_BOOST_UTILITY_STRING_ALGORITHM_FWD_HPP_INCLUDED

//
//  algorithm_fwd.hpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <string>

namespace go_boost
{
namespace utility
{

class u2string;
class u8string;
class u16string;
class u32string;

namespace string
{

template<class S>
bool equals(const S&, const S&);

std::string copy_to_multibyte_string(const std::wstring&);
std::string copy_to_multibyte_string(const u2string&);
std::string copy_to_multibyte_string(const u8string&);
std::string copy_to_multibyte_string(const u16string&);
std::string copy_to_multibyte_string(const u32string&);

bool try_copy_from_multibyte_string(const std::string&, std::wstring&);
bool try_copy_from_multibyte_string(const std::string&, u2string&);
bool try_copy_from_multibyte_string(const std::string&, u8string&);
bool try_copy_from_multibyte_string(const std::string&, u16string&);
bool try_copy_from_multibyte_string(const std::string&, u32string&);

}
}
}

#endif  // #ifndef GO_BOOST_UTILITY_STRING_ALGORITHM_FWD_HPP_INCLUDED
