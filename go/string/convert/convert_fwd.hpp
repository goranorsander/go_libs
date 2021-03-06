#ifndef GO_STRING_CONVERT_CONVERT_FWD_HPP_INCLUDED
#define GO_STRING_CONVERT_CONVERT_FWD_HPP_INCLUDED

//
//  convert_fwd.hpp
//
//  Copyright 2017-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/string/u2string.hpp>
#include <go/string/u8string.hpp>
#include <string>

namespace go
{
namespace string
{
namespace convert
{

std::string convert_wstring_to_string(const std::wstring&);
std::string convert_u2string_to_string(const u2string&);
std::string convert_u8string_to_string(const u8string&);
std::string convert_u16string_to_string(const std::u16string&);
std::string convert_u32string_to_string(const std::u32string&);
std::wstring convert_string_to_wstring(const std::string&);
std::wstring convert_u2string_to_wstring(const u2string&);
std::wstring convert_u8string_to_wstring(const u8string&);
std::wstring convert_u16string_to_wstring(const std::u16string&);
std::wstring convert_u32string_to_wstring(const std::u32string&);
u2string convert_string_to_u2string(const std::string&);
u2string convert_wstring_to_u2string(const std::wstring&);
u2string convert_u8string_to_u2string(const u8string&);
u2string convert_u16string_to_u2string(const std::u16string&);
u2string convert_u32string_to_u2string(const std::u32string&);
u8string convert_string_to_u8string(const std::string&);
u8string convert_wstring_to_u8string(const std::wstring&);
u8string convert_u2string_to_u8string(const u2string&);
u8string convert_u16string_to_u8string(const std::u16string&);
u8string convert_u32string_to_u8string(const std::u32string&);
std::u16string convert_string_to_u16string(const std::string&);
std::u16string convert_wstring_to_u16string(const std::wstring&);
std::u16string convert_u2string_to_u16string(const u2string&);
std::u16string convert_u8string_to_u16string(const u8string&);
std::u16string convert_u32string_to_u16string(const std::u32string&);
std::u32string convert_string_to_u32string(const std::string&);
std::u32string convert_wstring_to_u32string(const std::wstring&);
std::u32string convert_u2string_to_u32string(const u2string&);
std::u32string convert_u8string_to_u32string(const u8string&);
std::u32string convert_u16string_to_u32string(const std::u16string&);

}
}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_STRING_CONVERT_CONVERT_FWD_HPP_INCLUDED
