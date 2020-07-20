#ifndef GO_BOOST_STRING_STRING_CAST_HPP_INCLUDED
#define GO_BOOST_STRING_STRING_CAST_HPP_INCLUDED

//
//  string_cast.hpp
//
//  Copyright 2017-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/string/string_cast_exception.hpp>
#include <go_boost/string/traits/traits.hpp>

#include <boost/core/enable_if.hpp>
#include <boost/core/is_same.hpp>

#if defined(GO_BOOST_NO_CXX14_EXTENDED_CONSTEXPR) || defined(GO_BOOST_COMP_CLANG)
#define GO_BOOST_STRING_CAST_CONSTEXPR
#else
#define GO_BOOST_STRING_CAST_CONSTEXPR constexpr
#endif  // #if defined(GO_NO_CXX11_CONSTEXPR) || defined(GO_BOOST_COMP_CLANG)

namespace go_boost
{
namespace string
{

template <typename to_string, typename from_string>
inline GO_BOOST_STRING_CAST_CONSTEXPR typename boost::enable_if_c<boost::is_same<to_string, from_string>::value, from_string>::type string_cast(const from_string& from)
{
    return from;
}

template <typename to_string, typename from_string>
inline GO_BOOST_STRING_CAST_CONSTEXPR typename boost::enable_if_c<!boost::is_same<to_string, from_string>::value, to_string>::type string_cast(const from_string& from)
{
    u8string intermediate;
    if (!traits::conversion_traits<from_string>::try_convert(from, intermediate))
    {
        const std::string message = std::string("Cannot cast from ") + std::string(typeid(from_string).name()) + std::string(" to intermediate ") + std::string(typeid(u8string).name());
        throw string_cast_exception(message);
    }
    to_string to;
    if (!traits::conversion_traits<to_string>::try_convert(intermediate, to))
    {
        const std::string message = std::string("Cannot cast intermediate ") + std::string(typeid(u8string).name()) + std::string(" to ") + std::string(typeid(to_string).name());
        throw string_cast_exception(message);
    }
    return to;
}

}
}

#endif  // #ifndef GO_BOOST_STRING_STRING_CAST_HPP_INCLUDED