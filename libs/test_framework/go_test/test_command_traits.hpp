#ifndef GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_TRAITS_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_TRAITS_HPP_INCLUDED

//
//  test_command_traits.hpp
//
//  Copyright 2021-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_MUTEX))

#include <mutex>

#include <go/string/u8string.hpp>

namespace go_test
{

template <class StrVal, class Lock = std::recursive_mutex>
struct test_command_traits
{
    using this_type = test_command_traits<StrVal, Lock>;
    using string_value_type = StrVal;
    using lockable_type = Lock;
    using string_identifier_type = std::string;
    using command_interface_type = m::basic_command_interface<string_identifier_type, lockable_type>;
};

template <class StrVal, class Lock = std::recursive_mutex>
struct wtest_command_traits
{
    using this_type = wtest_command_traits<StrVal, Lock>;
    using string_value_type = StrVal;
    using lockable_type = Lock;
    using string_identifier_type = std::wstring;
    using command_interface_type = m::basic_command_interface<string_identifier_type, lockable_type>;
};

template <class StrVal, class Lock = std::recursive_mutex>
struct u8test_command_traits
{
    using this_type = u8test_command_traits<StrVal, Lock>;
    using string_value_type = StrVal;
    using lockable_type = Lock;
    using string_identifier_type = s::u8string;
    using command_interface_type = m::basic_command_interface<string_identifier_type, lockable_type>;
};

}

#endif  // #if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_MUTEX))

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_TRAITS_HPP_INCLUDED
