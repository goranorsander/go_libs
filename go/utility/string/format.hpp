#ifndef GO_UTILITY_STRING_FORMAT_HPP_INCLUDED
#define GO_UTILITY_STRING_FORMAT_HPP_INCLUDED

//
//  format.hpp
//
//  Copyright 2016-2019 Göran Orsander
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

//
// IMPLEMENTATION NOTE #1
//
// error C2338: va_start argument must not have reference type and must not be parenthesized
//

namespace go
{
namespace utility
{
namespace string
{

inline std::string format(const std::string::value_type* fmt_str, ...)  // See implementation note #1
{
	if (fmt_str == nullptr)
	{
		return std::string();
	}
    int n = static_cast<int>(strlen(fmt_str)) * 2; // Reserve two times as much as the length of the fmt_str
    std::unique_ptr<char[]> formatted;
    va_list ap = nullptr;
    for(;;)
    {
        formatted.reset(new char[n]); // Wrap the plain char array into the unique_ptr
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
	if (fmt_str == nullptr)
	{
		return std::wstring();
	}
	int n = static_cast<int>(wcslen(fmt_str)) * 2; // Reserve two times as much as the length of the fmt_str
    std::unique_ptr<wchar_t[]> formatted;
    va_list ap = nullptr;
    for(;;)
    {
        formatted.reset(new wchar_t[n]); // Wrap the plain char array into the unique_ptr
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
}

#endif  // #ifndef GO_UTILITY_STRING_FORMAT_HPP_INCLUDED
