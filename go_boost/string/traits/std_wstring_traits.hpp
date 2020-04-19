#ifndef GO_BOOST_STRING_TRAITS_STD_WSTRING_TRAITS_HPP_INCLUDED
#define GO_BOOST_STRING_TRAITS_STD_WSTRING_TRAITS_HPP_INCLUDED

//
//  std_wstring_traits.hpp
//
//  Copyright 2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_boost/string/convert/convert.hpp>
#include <go_boost/string/traits/conversion_traits.hpp>
#include <go_boost/string/traits/encoding_traits.hpp>
#include <string>

#if defined(GO_BOOST_SIZE_OF_WCHAR_T) && (GO_BOOST_SIZE_OF_WCHAR_T == 2)
#include <go_boost/string/encoding/ucs2.hpp>
#else
#include <go_boost/string/encoding/ucs4.hpp>
#endif  // #if defined(GO_BOOST_SIZE_OF_WCHAR_T) && (GO_BOOST_SIZE_OF_WCHAR_T == 2)

namespace go_boost
{
namespace string
{
namespace traits
{

template <>
struct encoding_traits<std::wstring>
{
    GO_BOOST_USING(this_type, encoding_traits<std::wstring>);
    GO_BOOST_USING(string_type, std::wstring);
    GO_BOOST_USING(char_type, GO_BOOST_TYPENAME std::wstring::value_type);

#if defined(GO_BOOST_SIZE_OF_WCHAR_T) && (GO_BOOST_SIZE_OF_WCHAR_T == 2)
    GO_BOOST_USING(encoding, go_boost::string::encoding::ucs2_tag);
#else
    GO_BOOST_USING(encoding, go_boost::string::encoding::ucs4_tag);
#endif  // #if defined(GO_BOOST_SIZE_OF_WCHAR_T) && (GO_BOOST_SIZE_OF_WCHAR_T == 2)
};

template <>
struct conversion_traits<std::wstring>
{
    GO_BOOST_USING(this_type, conversion_traits<std::wstring>);
    GO_BOOST_USING(string_type, std::wstring);

    static bool try_convert(const std::wstring& from, std::wstring& to)
    {
        to = from;
        return true;
    }

    static bool try_convert(const std::wstring& from, go_boost::string::u8string& to)
    {
        try
        {
            to = go_boost::string::convert::convert_wstring_to_u8string(from);
            return true;
        }
        catch (const std::exception&) {}
        catch (const std::exception_ptr&) {}
        catch (...) {}
        return false;
    }

    static bool try_convert(const go_boost::string::u8string& from, std::wstring& to)
    {
        try
        {
            to = go_boost::string::convert::convert_u8string_to_wstring(from);
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

#endif  // #ifndef GO_BOOST_STRING_TRAITS_STD_WSTRING_TRAITS_HPP_INCLUDED
