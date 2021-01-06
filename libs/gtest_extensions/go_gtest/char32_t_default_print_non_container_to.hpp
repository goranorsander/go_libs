#ifndef GO_GTEST_CHAR32_T_DEFAULT_PRINT_NON_CONTAINER_TO_HPP_INCLUDED
#define GO_GTEST_CHAR32_T_DEFAULT_PRINT_NON_CONTAINER_TO_HPP_INCLUDED

//
//  char32_t_default_print_non_container_to.hpp
//
//  Copyright 2020-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>

namespace testing_internal
{

#if !(defined(GO_NO_CXX11_CHAR32_T) || defined(GO_BOOST_NO_CXX11_CHAR32_T))

template <>
inline void DefaultPrintNonContainerTo(const char32_t& value, ::std::ostream* os)
{
    if (value == (value & 0x000000FF))
    {
        const char& c = static_cast<const char&>(value);
        *os << c;
    }
    else
    {
        const char c1 = static_cast<const char>(value & 0x000000FF);
        const char c2 = static_cast<const char>((value & 0x0000FF00) >> 8);
        const char c3 = static_cast<const char>((value & 0x00FF0000) >> 16);
        const char c4 = static_cast<const char>((value & 0xFF000000) >> 24);
        *os << c1;
        if (c2 != 0)
        {
            *os << c2;
        }
        if (c3 != 0)
        {
            *os << c3;
        }
        if (c4 != 0)
        {
            *os << c4;
        }
    }
}

#endif  // #if !(defined(GO_NO_CXX11_CHAR32_T) || defined(GO_BOOST_NO_CXX11_CHAR32_T))

}

#endif  // #ifndef GO_GTEST_CHAR32_T_DEFAULT_PRINT_NON_CONTAINER_TO_HPP_INCLUDED
