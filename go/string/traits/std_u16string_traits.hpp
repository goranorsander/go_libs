#ifndef GO_STRING_TRAITS_STD_U16STRING_TRAITS_HPP_INCLUDED
#define GO_STRING_TRAITS_STD_U16STRING_TRAITS_HPP_INCLUDED

//
//  std_u16string_traits.hpp
//
//  Copyright 2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/string/convert/convert.hpp>
#include <go/string/encoding/utf16.hpp>
#include <go/string/traits/conversion_traits.hpp>
#include <go/string/traits/encoding_traits.hpp>

namespace go
{
namespace string
{
namespace traits
{

template <>
struct encoding_traits<std::u16string>
{
    using this_type = encoding_traits<std::u16string>;
    using string_type = std::u16string;
    using char_type = GO_TYPENAME std::u16string::value_type;
    using encoding = go::string::encoding::utf16_tag;
};

template <>
struct conversion_traits<std::u16string>
{
    using this_type = conversion_traits<std::u16string>;
    using string_type = std::u16string;

    static bool try_convert(const std::u16string& from, std::u16string& to)
    {
        to = from;
        return true;
    }

    static bool try_convert(const std::u16string& from, go::string::u8string& to)
    {
        try
        {
            to = go::string::convert::convert_u16string_to_u8string(from);
            return true;
        }
        catch (const std::exception&) {}
        catch (const std::exception_ptr&) {}
        catch (...) {}
        return false;
    }

    static bool try_convert(const go::string::u8string& from, std::u16string& to)
    {
        try
        {
            to = go::string::convert::convert_u8string_to_u16string(from);
            return true;
        }
        catch (const std::exception&) {}
        catch (const std::exception_ptr&) {}
        catch (...) {}
        return false;
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

#endif  // #ifndef GO_STRING_TRAITS_STD_U16STRING_TRAITS_HPP_INCLUDED
