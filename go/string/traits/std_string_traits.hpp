#ifndef GO_STRING_TRAITS_STD_STRING_TRAITS_HPP_INCLUDED
#define GO_STRING_TRAITS_STD_STRING_TRAITS_HPP_INCLUDED

//
//  std_string_traits.hpp
//
//  Copyright 2020-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/string/convert/convert.hpp>
#include <go/string/traits/conversion_traits.hpp>
#include <go/string/traits/encoding_traits.hpp>

#if defined(GO_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE)
#include <go/string/encoding/ascii.hpp>
#else
#if defined(GO_PLATFORM_WINDOWS)
#include <go/string/encoding/windows_1252.hpp>
#else
#include <go/string/encoding/iso_8859_1.hpp>
#endif  // #if defined(GO_PLATFORM_WINDOWS)
#endif  // #if defined(GO_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE)

namespace go
{
namespace string
{
namespace traits
{

template <>
struct encoding_traits<std::string>
{
    GO_USING(this_type, encoding_traits<std::string>);
    GO_USING(string_type, std::string);
    GO_USING(char_type, GO_TYPENAME std::string::value_type);

#if defined(GO_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE)
    GO_USING(encoding, go::string::encoding::ascii_tag);
#else
#if defined(GO_PLATFORM_WINDOWS)
    GO_USING(encoding, go::string::encoding::windows_1252_tag);
#else
    GO_USING(encoding, go::string::encoding::iso_8859_1_tag);
#endif  // #if defined(GO_PLATFORM_WINDOWS)
#endif  // #if defined(GO_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE)
};

template <>
struct conversion_traits<std::string>
{
    GO_USING(this_type, conversion_traits<std::string>);
    GO_USING(string_type, std::string);

    static bool try_convert(const std::string& from, std::string& to)
    {
        to = from;
        return true;
    }

    static bool try_convert(const std::string& from, go::string::u8string& to)
    {
        try
        {
            to = go::string::convert::convert_string_to_u8string(from);
            return true;
        }
        catch (const std::exception&) {}
        catch (const std::exception_ptr&) {}
        catch (...) {}
        return false;
    }

    static bool try_convert(const go::string::u8string& from, std::string& to)
    {
        try
        {
            to = go::string::convert::convert_u8string_to_string(from);
            return true;
        }
        catch (const std::exception&) {}
        catch (const std::exception_ptr&) {}
        catch (...) {}
        return false;
    }

private:
    // cppcheck-suppress unusedPrivateFunction
    template <typename T1, typename T2> static bool try_convert(const T1&, T2&)
    {
        // Make public try_convert functions explicit
        return false;
    }
};

}
}
}

#endif  // #ifndef GO_STRING_TRAITS_STD_STRING_TRAITS_HPP_INCLUDED
