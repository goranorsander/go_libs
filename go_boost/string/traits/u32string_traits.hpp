#ifndef GO_BOOST_STRING_TRAITS_U32STRING_TRAITS_HPP_INCLUDED
#define GO_BOOST_STRING_TRAITS_U32STRING_TRAITS_HPP_INCLUDED

//
//  u32string_traits.hpp
//
//  Copyright 2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_boost/string/convert/convert.hpp>
#include <go_boost/string/encoding/utf32.hpp>
#include <go_boost/string/traits/conversion_traits.hpp>
#include <go_boost/string/traits/encoding_traits.hpp>

namespace go_boost
{
namespace string
{
namespace traits
{

template <>
struct encoding_traits<go_boost::string::u32string>
{
    GO_BOOST_USING(this_type, encoding_traits<go_boost::string::u32string>);
    GO_BOOST_USING(string_type, go_boost::string::u32string);
    GO_BOOST_USING(char_type, GO_BOOST_TYPENAME go_boost::string::u32string::value_type);
    GO_BOOST_USING(encoding, go_boost::string::encoding::utf32_tag);
};

template <>
struct conversion_traits<go_boost::string::u32string>
{
    GO_BOOST_USING(this_type, conversion_traits<go_boost::string::u32string>);
    GO_BOOST_USING(string_type, go_boost::string::u32string);

    static bool try_convert(const go_boost::string::u32string& from, go_boost::string::u32string& to)
    {
        to = from;
        return true;
    }

    static bool try_convert(const go_boost::string::u32string& from, go_boost::string::u8string& to)
    {
        try
        {
            to = go_boost::string::convert::convert_u32string_to_u8string(from);
            return true;
        }
        catch (const std::exception&) {}
#if defined(GO_BOOST_MSVC_VER) && (GO_BOOST_MSVC_VER > 1500)
        catch (const std::exception_ptr&) {}
#endif
        catch (...) {}
        return false;
    }

    static bool try_convert(const go_boost::string::u8string& from, go_boost::string::u32string& to)
    {
        try
        {
            to = go_boost::string::convert::convert_u8string_to_u32string(from);
            return true;
        }
        catch (const std::exception&) {}
#if defined(GO_BOOST_MSVC_VER) && (GO_BOOST_MSVC_VER > 1500)
        catch (const std::exception_ptr&) {}
#endif
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

#endif  // #ifndef GO_BOOST_STRING_TRAITS_U32STRING_TRAITS_HPP_INCLUDED
