#ifndef GO_STRING_TRAITS_U2STRING_TRAITS_HPP_INCLUDED
#define GO_STRING_TRAITS_U2STRING_TRAITS_HPP_INCLUDED

//
//  u2string_traits.hpp
//
//  Copyright 2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/string/convert/convert.hpp>
#include <go/string/encoding/ucs2.hpp>
#include <go/string/traits/conversion_traits.hpp>
#include <go/string/traits/encoding_traits.hpp>

namespace go
{
namespace string
{
namespace traits
{

template <>
struct encoding_traits<go::string::u2string>
{
    GO_USING(this_type, encoding_traits<go::string::u2string>);
    GO_USING(string_type, go::string::u2string);
    GO_USING(char_type, GO_TYPENAME go::string::u2string::value_type);
    GO_USING(encoding, go::string::encoding::ucs2_tag);
};

template <>
struct conversion_traits<go::string::u2string>
{
    GO_USING(this_type, conversion_traits<go::string::u2string>);
    GO_USING(string_type, go::string::u2string);

    static bool try_convert(const go::string::u2string& from, go::string::u2string& to)
    {
        to = from;
        return true;
    }

    static bool try_convert(const go::string::u2string& from, go::string::u8string& to)
    {
        try
        {
            to = go::string::convert::convert_u2string_to_u8string(from);
            return true;
        }
        catch (const std::exception&) {}
        catch (const std::exception_ptr&) {}
        catch (...) {}
        return false;
    }

    static bool try_convert(const go::string::u8string& from, go::string::u2string& to)
    {
        try
        {
            to = go::string::convert::convert_u8string_to_u2string(from);
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

#endif  // #ifndef GO_STRING_TRAITS_U2STRING_TRAITS_HPP_INCLUDED
