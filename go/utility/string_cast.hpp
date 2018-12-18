#ifndef GO_UTILITY_STRING_CAST_HPP_INCLUDED
#define GO_UTILITY_STRING_CAST_HPP_INCLUDED

//
//  string_cast.hpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11_CODECVT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/utility/string/string_cast.hpp>

namespace go
{
namespace utility
{

template <typename to_string, typename from_string>
GO_CONSTEXPR to_string string_cast(const from_string& from)
{
    return string::detail::string_cast<to_string, from_string>::cast(from);
}

}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_UTILITY_STRING_CAST_HPP_INCLUDED
