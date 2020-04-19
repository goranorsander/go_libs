#ifndef GO_BOOST_STRING_TRAITS_STD_STRING_TRAITS_HPP_INCLUDED
#define GO_BOOST_STRING_TRAITS_STD_STRING_TRAITS_HPP_INCLUDED

//
//  std_string_traits.hpp
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

#if defined(GO_BOOST_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE)
#include <go_boost/string/encoding/ascii.hpp>
#else
#if defined(GO_BOOST_PLATFORM_WINDOWS)
#include <go_boost/string/encoding/windows_1252.hpp>
#else
#include <go_boost/string/encoding/iso_8859_1.hpp>
#endif  // #if defined(GO_BOOST_PLATFORM_WINDOWS)
#endif  // #if defined(GO_BOOST_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE)

namespace go_boost
{
namespace string
{
namespace traits
{

template <>
struct encoding_traits<std::string>
{
    GO_BOOST_USING(this_type, encoding_traits<std::string>);
    GO_BOOST_USING(string_type, std::string);
    GO_BOOST_USING(char_type, GO_BOOST_TYPENAME std::string::value_type);

#if defined(GO_BOOST_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE)
    GO_BOOST_USING(encoding, go_boost::string::encoding::ascii_tag);
#else
#if defined(GO_BOOST_PLATFORM_WINDOWS)
    GO_BOOST_USING(encoding, go_boost::string::encoding::windows_1252_tag);
#else
    GO_BOOST_USING(encoding, go_boost::string::encoding::iso_8859_1_tag);
#endif  // #if defined(GO_BOOST_PLATFORM_WINDOWS)
#endif  // #if defined(GO_BOOST_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE)
};

template <>
struct conversion_traits<std::string>
{
    GO_BOOST_USING(this_type, conversion_traits<std::string>);
    GO_BOOST_USING(string_type, std::string);

    static bool try_convert(const std::string& from, std::string& to)
    {
        to = from;
        return true;
    }

    static bool try_convert(const std::string& from, go_boost::string::u8string& to)
    {
        try
        {
            to = go_boost::string::convert::convert_string_to_u8string(from);
            return true;
        }
        catch (const std::exception&) {}
        catch (const std::exception_ptr&) {}
        catch (...) {}
        return false;
    }

    static bool try_convert(const go_boost::string::u8string& from, std::string& to)
    {
        try
        {
            to = go_boost::string::convert::convert_u8string_to_string(from);
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

#endif  // #ifndef GO_BOOST_STRING_TRAITS_STD_STRING_TRAITS_HPP_INCLUDED
