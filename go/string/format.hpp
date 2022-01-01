#ifndef GO_STRING_FORMAT_HPP_INCLUDED
#define GO_STRING_FORMAT_HPP_INCLUDED

//
//  format.hpp
//
//  Copyright 2016-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <cstdarg>
#include <cstring>
#include <memory>
#include <string>

#if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
#include <go/utility/scope_guard_new_array.hpp>
#endif

//
// IMPLEMENTATION NOTE #1
//
// error C2338: va_start argument must not have reference type and must not be parenthesized
//

namespace go
{
namespace string
{

inline std::string format(const std::string::value_type* fmt_str, ...)  // See implementation note #1
{
	if (fmt_str == GO_NULLPTR)
	{
		return std::string();
	}
    int n = static_cast<int>(strlen(fmt_str)) * 2; // Reserve two times as much as the length of the fmt_str
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
    go::utility::scope_guard_new_array<char> formatted(GO_NULLPTR, 0);
#else
    std::unique_ptr<char[]> formatted;
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
    va_list ap;
    for(;;)
    {
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
        formatted.reset(new char[n], n); // Wrap the plain char array into the scope_guard_new_array
#else
        formatted.reset(new char[n]); // Wrap the plain char array into the unique_ptr
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
#if !defined(GO_COMP_GCC) && !defined(GO_COMP_CLANG)
        strcpy_s(&formatted[0], n, fmt_str);
#else
        strcpy(&formatted[0], fmt_str);
#endif  // #if !defined(GO_COMP_GCC) && !defined(GO_COMP_CLANG)
		va_start(ap, fmt_str);
#if !defined(GO_COMP_GCC) && !defined(GO_COMP_CLANG)
        const int final_n = vsnprintf_s(&formatted[0], n, n, fmt_str, ap);
#else
        const int final_n = vsnprintf(&formatted[0], n, fmt_str, ap);
#endif  // #if !defined(GO_COMP_GCC) && !defined(GO_COMP_CLANG)
        va_end(ap);
        if(final_n < 0 || final_n >= n)
        {
            n += abs(final_n - n + 1);
        }
        else
        {
            break;
        }
    }
    return std::string(formatted.get());
}

inline std::wstring format(const std::wstring::value_type* fmt_str, ...)  // See implementation note #1
{
	if (fmt_str == GO_NULLPTR)
	{
		return std::wstring();
	}
	int n = static_cast<int>(wcslen(fmt_str)) * 2; // Reserve two times as much as the length of the fmt_str
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
    go::utility::scope_guard_new_array<wchar_t> formatted(GO_NULLPTR, 0);
#else
    std::unique_ptr<wchar_t[]> formatted;
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
    va_list ap;
    for(;;)
    {
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
        formatted.reset(new wchar_t[n], n); // Wrap the plain char array into the scope_guard_new_array
#else
        formatted.reset(new wchar_t[n]); // Wrap the plain char array into the unique_ptr
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
#if !defined(GO_COMP_GCC) && !defined(GO_COMP_CLANG)
        wcscpy_s(&formatted[0], n, fmt_str);
#else
        wcscpy(&formatted[0], fmt_str);
#endif  // #if !defined(GO_COMP_GCC) && !defined(GO_COMP_CLANG)
        va_start(ap, fmt_str);
        const int final_n = vswprintf(&formatted[0], n, fmt_str, ap);
        va_end(ap);
        if(final_n < 0 || final_n >= n)
        {
            n += abs(final_n - n + 1);
        }
        else
        {
            break;
        }
    }
    return std::wstring(formatted.get());
}

}
}

#endif  // #ifndef GO_STRING_FORMAT_HPP_INCLUDED
