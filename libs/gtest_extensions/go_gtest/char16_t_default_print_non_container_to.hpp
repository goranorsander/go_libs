#ifndef GO_GTEST_CHAR16_T_DEFAULT_PRINT_NON_CONTAINER_TO_HPP_INCLUDED
#define GO_GTEST_CHAR16_T_DEFAULT_PRINT_NON_CONTAINER_TO_HPP_INCLUDED

//
//  char16_t_default_print_non_container_to.hpp
//
//  Copyright 2020-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>

namespace testing_internal
{

#if defined(GO_GTEST_FOR_CPP03) && !(defined(GO_NO_CXX11_CHAR16_T) || defined(GO_BOOST_NO_CXX11_CHAR16_T))

template <>
inline void DefaultPrintNonContainerTo(const char16_t& value, ::std::ostream* os)
{
    if (value == (value & 0x00FF))
    {
        const char& c = static_cast<const char&>(value);
        *os << c;
    }
    else
    {
        const char c1 = static_cast<const char>(value & 0x00FF);
        const char c2 = static_cast<const char>((value & 0xFF00) >> 8);
        *os << c1;
        if (c2 != 0)
        {
            *os << c2;
        }
    }
}

#endif  // #if defined(GO_GTEST_FOR_CPP03) && !(defined(GO_NO_CXX11_CHAR16_T) || defined(GO_BOOST_NO_CXX11_CHAR16_T))

}

#endif  // #ifndef GO_GTEST_CHAR16_T_DEFAULT_PRINT_NON_CONTAINER_TO_HPP_INCLUDED
