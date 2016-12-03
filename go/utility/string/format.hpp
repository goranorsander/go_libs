#ifndef GO_UTILITY_ITERATOR_ITERATOR_HPP_INCLUDED
#define GO_UTILITY_ITERATOR_ITERATOR_HPP_INCLUDED

//
//  format.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <cstdarg>
#include <memory>
#include <string>

namespace go
{
namespace utility
{
namespace string
{

inline std::string format(const std::string fmt_str, ...)
{
    // Implementation from StackOverflow, see
    // http://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf

    int n = ((int)fmt_str.size()) * 2; // Reserve two times as much as the length of the fmt_str
    int final_n = 0;
    std::string str;
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(true)
    {
        formatted.reset(new char[n]); // Wrap the plain char array into the unique_ptr
        strcpy_s(&formatted[0], n, fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
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

inline std::wstring format(const std::wstring fmt_str, ...)
{
    // Implementation from StackOverflow modified for std::wstring, see
    // http://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf

    int n = ((int)fmt_str.size()) * 2; // Reserve two times as much as the length of the fmt_str
    int final_n = 0;
    std::wstring str;
    std::unique_ptr<wchar_t[]> formatted;
    va_list ap;
    while(true)
    {
        formatted.reset(new wchar_t[n]); // Wrap the plain char array into the unique_ptr
        wcscpy_s(&formatted[0], n, fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vswprintf(&formatted[0], n, fmt_str.c_str(), ap);
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

#endif  // #ifndef GO_UTILITY_ITERATOR_ITERATOR_HPP_INCLUDED
