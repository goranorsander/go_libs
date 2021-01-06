#ifndef GO_STRING_TRAITS_STD_U32STRING_TRAITS_HPP_INCLUDED
#define GO_STRING_TRAITS_STD_U32STRING_TRAITS_HPP_INCLUDED

//
//  std_u32string_traits.hpp
//
//  Copyright 2020-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/string/convert/convert.hpp>
#include <go/string/encoding/utf32.hpp>
#include <go/string/traits/conversion_traits.hpp>
#include <go/string/traits/encoding_traits.hpp>

namespace go
{
namespace string
{
namespace traits
{

template <>
struct encoding_traits<std::u32string>
{
    GO_USING(this_type, encoding_traits<std::u32string>);
    GO_USING(string_type, std::u32string);
    GO_USING(char_type, GO_TYPENAME std::u32string::value_type);
    GO_USING(encoding, go::string::encoding::utf32_tag);
};

template <>
struct conversion_traits<std::u32string>
{
    GO_USING(this_type, conversion_traits<std::u32string>);
    GO_USING(string_type, std::u32string);

    static bool try_convert(const std::u32string& from, std::u32string& to)
    {
        to = from;
        return true;
    }

    static bool try_convert(const std::u32string& from, go::string::u8string& to)
    {
        try
        {
            to = go::string::convert::convert_u32string_to_u8string(from);
            return true;
        }
        catch (const std::exception&) {}
        catch (const std::exception_ptr&) {}
        catch (...) {}
        return false;
    }

    static bool try_convert(const go::string::u8string& from, std::u32string& to)
    {
        try
        {
            to = go::string::convert::convert_u8string_to_u32string(from);
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

#endif  // #ifndef GO_STRING_TRAITS_STD_U32STRING_TRAITS_HPP_INCLUDED
