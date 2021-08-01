#ifndef GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_TRAITS_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_TRAITS_HPP_INCLUDED

//
//  test_command_traits.hpp
//
//  Copyright 2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <mutex>

#include <go/string/u8string.hpp>

namespace go_test
{

template <class StrVal, class Lock = std::recursive_mutex>
struct test_command_traits
{
    typedef test_command_traits<StrVal, Lock> this_type;
    typedef StrVal string_value_type;
    typedef Lock lockable_type;
    typedef std::string string_identifier_type;
    typedef m::basic_command_interface<string_identifier_type, lockable_type> command_interface_type;
};

template <class StrVal, class Lock = std::recursive_mutex>
struct wtest_command_traits
{
    typedef wtest_command_traits<StrVal, Lock> this_type;
    typedef StrVal string_value_type;
    typedef Lock lockable_type;
    typedef std::wstring string_identifier_type;
    typedef m::basic_command_interface<string_identifier_type, lockable_type> command_interface_type;
};

template <class StrVal, class Lock = std::recursive_mutex>
struct u8test_command_traits
{
    typedef u8test_command_traits<StrVal, Lock> this_type;
    typedef StrVal string_value_type;
    typedef Lock lockable_type;
    typedef s::u8string string_identifier_type;
    typedef m::basic_command_interface<string_identifier_type, lockable_type> command_interface_type;
};

}

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_TRAITS_HPP_INCLUDED
