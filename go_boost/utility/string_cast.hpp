#ifndef GO_BOOST_UTILITY_STRING_CAST_HPP_INCLUDED
#define GO_BOOST_UTILITY_STRING_CAST_HPP_INCLUDED

//
//  string_cast.hpp
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

#include <go_boost/utility/string/string_cast.hpp>

namespace go_boost
{
namespace utility
{

template <typename to_string, typename from_string>
to_string string_cast(const from_string& from)
{
    return string::detail::string_cast<to_string, from_string>::cast(from);
}

}
}

#endif  // #ifndef GO_BOOST_UTILITY_STRING_CAST_HPP_INCLUDED
