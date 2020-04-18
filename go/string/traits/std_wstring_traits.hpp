#ifndef GO_STRING_TRAITS_STD_WSTRING_TRAITS_HPP_INCLUDED
#define GO_STRING_TRAITS_STD_WSTRING_TRAITS_HPP_INCLUDED

//
//  std_wstring_traits.hpp
//
//  Copyright 2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/string/convert/convert.hpp>
#include <go/string/traits/conversion_traits.hpp>
#include <go/string/traits/encoding_traits.hpp>

#if defined(GO_SIZE_OF_WCHAR_T) && (GO_SIZE_OF_WCHAR_T == 2)
#include <go/string/encoding/ucs2.hpp>
#else
#include <go/string/encoding/ucs4.hpp>
#endif  // #if defined(GO_SIZE_OF_WCHAR_T) && (GO_SIZE_OF_WCHAR_T == 2)

namespace go
{
namespace string
{
namespace traits
{

template <>
struct encoding_traits<std::wstring>
{
    using this_type = encoding_traits<std::wstring>;
    using string_type = std::wstring;
    using char_type = GO_TYPENAME std::wstring::value_type;

#if defined(GO_SIZE_OF_WCHAR_T) && (GO_SIZE_OF_WCHAR_T == 2)
    using encoding = go::string::encoding::ucs2_tag;
#else
    using encoding = go::string::encoding::ucs4_tag;
#endif  // #if defined(GO_SIZE_OF_WCHAR_T) && (GO_SIZE_OF_WCHAR_T == 2)
};

template <>
struct conversion_traits<std::wstring>
{
    using this_type = conversion_traits<std::wstring>;
    using string_type = std::wstring;

    static bool try_convert(const std::wstring& from, std::wstring& to)
    {
        to = from;
        return true;
    }

    static bool try_convert(const std::wstring& from, go::string::u8string& to)
    {
        try
        {
            to = go::string::convert::convert_wstring_to_u8string(from);
            return true;
        }
        catch (const std::exception&) {}
        catch (const std::exception_ptr&) {}
        catch (...) {}
        return false;
    }

    static bool try_convert(const go::string::u8string& from, std::wstring& to)
    {
        try
        {
            to = go::string::convert::convert_u8string_to_wstring(from);
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

#endif  // #ifndef GO_STRING_TRAITS_STD_WSTRING_TRAITS_HPP_INCLUDED
