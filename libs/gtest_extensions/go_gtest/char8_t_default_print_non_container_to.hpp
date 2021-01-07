#ifndef GO_GTEST_CHAR8_T_DEFAULT_PRINT_NON_CONTAINER_TO_HPP_INCLUDED
#define GO_GTEST_CHAR8_T_DEFAULT_PRINT_NON_CONTAINER_TO_HPP_INCLUDED

//
//  char8_t_default_print_non_container_to.hpp
//
//  Copyright 2019-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>

namespace testing_internal
{

#if !(defined(GO_NO_CXX20_CHAR8_T) || defined(GO_BOOST_NO_CXX20_CHAR8_T))

template <>
inline void DefaultPrintNonContainerTo(const char8_t& value, ::std::ostream* os)
{
    const char& v = static_cast<const char&>(value);
    *os << v;
}

#endif  // #if !(defined(GO_NO_CXX20_CHAR8_T) || defined(GO_BOOST_NO_CXX20_CHAR8_T))

}

#endif  // #ifndef GO_GTEST_CHAR8_T_DEFAULT_PRINT_NON_CONTAINER_TO_HPP_INCLUDED
