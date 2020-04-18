#ifndef GO_STRING_TRAITS_U8STRING_TRAITS_HPP_INCLUDED
#define GO_STRING_TRAITS_U8STRING_TRAITS_HPP_INCLUDED

//
//  u8string_traits.hpp
//
//  Copyright 2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/string/convert/convert.hpp>
#include <go/string/encoding/utf8.hpp>
#include <go/string/traits/conversion_traits.hpp>
#include <go/string/traits/encoding_traits.hpp>

namespace go
{
namespace string
{
namespace traits
{

template <>
struct encoding_traits<go::string::u8string>
{
    using this_type = encoding_traits<go::string::u8string>;
    using string_type = go::string::u8string;
    using char_type = GO_TYPENAME go::string::u8string::value_type;
    using encoding = go::string::encoding::utf8_tag;
};

template <>
struct conversion_traits<go::string::u8string>
{
    using this_type = conversion_traits<go::string::u8string>;
    using string_type = go::string::u8string;

    static bool try_convert(const go::string::u8string& from, go::string::u8string& to)
    {
        to = from;
        return true;
    }

private:
    template <typename T1, typename T2>
    static bool try_convert(const T1&, T2&)
    {
        // Make public try_convert functions explicit
        return false;
    }
};

}
}
}

#endif  // #ifndef GO_STRING_TRAITS_U8STRING_TRAITS_HPP_INCLUDED
