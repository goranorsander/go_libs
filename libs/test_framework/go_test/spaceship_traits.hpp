#ifndef GO_TEST_FRAMEWORK_GO_TEST_SPACESHIP_TRAITS_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_TEST_SPACESHIP_TRAITS_HPP_INCLUDED

//
//  spaceship_traits.hpp
//
//  Copyright 2021-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <go/mvvm/property_changed_arguments.hpp>
#include <go/property.hpp>
#include <go_test/fleet_commander_changed_event.hpp>

#if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_MUTEX))

namespace go_test
{

template <class StrVal, class Lock = std::recursive_mutex>
struct spaceship_traits
{
    using this_type = spaceship_traits<StrVal, Lock>;
    using string_value_type = StrVal;
    using lockable_type = Lock;
    using string_identifier_type = std::string;

    // Property types
    using double_property_type = p::property<double, lockable_type>;
    using int_property_type = p::property<int, lockable_type>;
    using string_property_type = p::property<string_value_type, lockable_type>;
    using string_value_property_type = p::value_property<string_value_type, lockable_type>;
    using read_only_command_property_type = pro::property<typename m::basic_command_interface<string_identifier_type, lockable_type>::ptr, lockable_type>;
    using read_only_string_property_type = pro::property<string_value_type, lockable_type>;
    using read_only_string_value_property_type = pro::value_property<string_value_type, lockable_type>;

    // Observable object types
    using observable_object_base_type = typename m::basic_observable_object<string_identifier_type, lockable_type>;
    using property_changed_arguments_type = typename m::basic_property_changed_arguments<string_identifier_type>;
    using property_changed_arguments_ptr = typename property_changed_arguments_type::ptr;

    // Command types
    using command_value_type = typename read_only_command_property_type::value_type;
    using command_ptr = command_value_type;

    // Event types
    using event_manager_type = m::basic_event_manager<string_identifier_type, lockable_type>;
    using event_manager_ptr = typename event_manager_type::ptr;
    using event_manager_wptr = typename event_manager_type::wptr;
    using event_type = m::basic_event<string_identifier_type>;
    using event_ptr = typename event_type::ptr;
    using event_wptr = typename event_type::wptr;
    using fleet_commander_changed_event_type = fleet_commander_changed_event<string_identifier_type, read_only_string_value_property_type>;
    using fleet_commander_changed_event_ptr = typename fleet_commander_changed_event_type::ptr;
};

template <class StrVal, class Lock = std::recursive_mutex>
struct wspaceship_traits
{
    using this_type = wspaceship_traits<StrVal, Lock>;
    using string_value_type = StrVal;
    using lockable_type = Lock;
    using string_identifier_type = std::wstring;

    // Property types
    using double_property_type = p::wproperty<double, lockable_type>;
    using int_property_type = p::wproperty<int, lockable_type>;
    using string_property_type = p::wproperty<string_value_type, lockable_type>;
    using string_value_property_type = p::value_wproperty<string_value_type, lockable_type>;
    using read_only_command_property_type = pro::wproperty<typename m::basic_command_interface<string_identifier_type, lockable_type>::ptr, lockable_type>;
    using read_only_string_property_type = pro::wproperty<string_value_type, lockable_type>;
    using read_only_string_value_property_type = pro::value_wproperty<string_value_type, lockable_type>;

    // Observable object types
    using observable_object_base_type = typename m::basic_observable_object<string_identifier_type, lockable_type>;
    using property_changed_arguments_type = typename m::basic_property_changed_arguments<string_identifier_type>;
    using property_changed_arguments_ptr = typename property_changed_arguments_type::ptr;

    // Command types
    using command_value_type = typename read_only_command_property_type::value_type;
    using command_ptr = command_value_type;

    // Event types
    using event_manager_type = m::basic_event_manager<string_identifier_type, lockable_type>;
    using event_manager_ptr = typename event_manager_type::ptr;
    using event_manager_wptr = typename event_manager_type::wptr;
    using event_type = m::basic_event<string_identifier_type>;
    using event_ptr = typename event_type::ptr;
    using event_wptr = typename event_type::wptr;
    using fleet_commander_changed_event_type = fleet_commander_changed_event<string_identifier_type, read_only_string_value_property_type>;
    using fleet_commander_changed_event_ptr = typename fleet_commander_changed_event_type::ptr;
};

template <class StrVal, class Lock = std::recursive_mutex>
struct u8spaceship_traits
{
    using this_type = u8spaceship_traits<StrVal, Lock>;
    using string_value_type = StrVal;
    using lockable_type = Lock;
    using string_identifier_type = s::u8string;

    // Property types
    using double_property_type = p::u8property<double, lockable_type>;
    using int_property_type = p::u8property<int, lockable_type>;
    using string_property_type = p::u8property<string_value_type, lockable_type>;
    using string_value_property_type = p::value_u8property<string_value_type, lockable_type>;
    using read_only_command_property_type = pro::u8property<typename m::basic_command_interface<string_identifier_type, lockable_type>::ptr, lockable_type>;
    using read_only_string_property_type = pro::u8property<string_value_type, lockable_type>;
    using read_only_string_value_property_type = pro::value_u8property<string_value_type, lockable_type>;

    // Observable object types
    using observable_object_base_type = typename m::basic_observable_object<string_identifier_type, lockable_type>;
    using property_changed_arguments_type = typename m::basic_property_changed_arguments<string_identifier_type>;
    using property_changed_arguments_ptr = typename property_changed_arguments_type::ptr;

    // Command types
    using command_value_type = typename read_only_command_property_type::value_type;
    using command_ptr = command_value_type;

    // Event types
    using event_manager_type = m::basic_event_manager<string_identifier_type, lockable_type>;
    using event_manager_ptr = typename event_manager_type::ptr;
    using event_manager_wptr = typename event_manager_type::wptr;
    using event_type = m::basic_event<string_identifier_type>;
    using event_ptr = typename event_type::ptr;
    using event_wptr = typename event_type::wptr;
    using fleet_commander_changed_event_type = fleet_commander_changed_event<string_identifier_type, read_only_string_value_property_type>;
    using fleet_commander_changed_event_ptr = typename fleet_commander_changed_event_type::ptr;
};

}

#endif  // #if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_MUTEX))

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_TEST_SPACESHIP_TRAITS_HPP_INCLUDED
