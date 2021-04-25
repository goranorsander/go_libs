#ifndef GO_TEST_FRAMEWORK_GO_BOOST_TEST_SPACESHIP_TRAITS_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_BOOST_TEST_SPACESHIP_TRAITS_HPP_INCLUDED

//
//  spaceship_traits.hpp
//
//  Copyright 2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#include <go_boost/mvvm/property_changed_arguments.hpp>
#include <go_boost/property.hpp>
#include <go_boost_test/fleet_commander_changed_event.hpp>

namespace go_boost_test
{

template <class StrVal, class Lock = boost::recursive_mutex>
struct spaceship_traits
{
    typedef spaceship_traits<StrVal, Lock> this_type;
    typedef StrVal string_value_type;
    typedef Lock lockable_type;
    typedef std::string string_identifier_type;

    // Property types
    typedef p::property<double, lockable_type> double_property_type;
    typedef p::property<int, lockable_type> int_property_type;
    typedef p::property<string_value_type, lockable_type> string_property_type;
    typedef p::value_property<string_value_type, lockable_type> string_value_property_type;
    typedef pro::property<typename m::basic_command_interface<string_identifier_type, lockable_type>::ptr, lockable_type> read_only_command_property_type;
    typedef pro::property<string_value_type, lockable_type> read_only_string_property_type;
    typedef pro::value_property<string_value_type, lockable_type> read_only_string_value_property_type;

    // Observable object types
    typedef m::basic_observable_object<string_identifier_type, lockable_type> observable_object_base_type;
    typedef typename m::basic_property_changed_arguments<string_identifier_type> property_changed_arguments_type;
    typedef typename property_changed_arguments_type::ptr property_changed_arguments_ptr;

    // Command types
    typedef typename read_only_command_property_type::value_type command_value_type;
    typedef typename command_value_type command_ptr;

    // Event types
    typedef m::basic_event_manager<string_identifier_type, lockable_type> event_manager_type;
    typedef typename event_manager_type::ptr event_manager_ptr;
    typedef typename event_manager_type::wptr event_manager_wptr;
    typedef m::basic_event<string_identifier_type> event_type;
    typedef typename event_type::ptr event_ptr;
    typedef typename event_type::wptr event_wptr;
    typedef fleet_commander_changed_event<string_identifier_type, read_only_string_value_property_type> fleet_commander_changed_event_type;
    typedef typename fleet_commander_changed_event_type::ptr fleet_commander_changed_event_ptr;
};

template <class StrVal, class Lock = boost::recursive_mutex>
struct wspaceship_traits
{
    typedef wspaceship_traits<StrVal, Lock> this_type;
    typedef StrVal string_value_type;
    typedef Lock lockable_type;
    typedef std::wstring string_identifier_type;

    // Property types
    typedef p::wproperty<double, lockable_type> double_property_type;
    typedef p::wproperty<int, lockable_type> int_property_type;
    typedef p::wproperty<string_value_type, lockable_type> string_property_type;
    typedef p::value_wproperty<string_value_type, lockable_type> string_value_property_type;
    typedef pro::wproperty<typename m::basic_command_interface<string_identifier_type, lockable_type>::ptr, lockable_type> read_only_command_property_type;
    typedef pro::wproperty<string_value_type, lockable_type> read_only_string_property_type;
    typedef pro::value_wproperty<string_value_type, lockable_type> read_only_string_value_property_type;

    // Observable object types
    typedef m::basic_observable_object<string_identifier_type, lockable_type> observable_object_base_type;
    typedef typename m::basic_property_changed_arguments<string_identifier_type> property_changed_arguments_type;
    typedef typename property_changed_arguments_type::ptr property_changed_arguments_ptr;

    // Command types
    typedef typename read_only_command_property_type::value_type command_value_type;
    typedef typename command_value_type command_ptr;

    // Event types
    typedef m::basic_event_manager<string_identifier_type, lockable_type> event_manager_type;
    typedef typename event_manager_type::ptr event_manager_ptr;
    typedef typename event_manager_type::wptr event_manager_wptr;
    typedef m::basic_event<string_identifier_type> event_type;
    typedef typename event_type::ptr event_ptr;
    typedef typename event_type::wptr event_wptr;
    typedef fleet_commander_changed_event<string_identifier_type, read_only_string_value_property_type> fleet_commander_changed_event_type;
    typedef typename fleet_commander_changed_event_type::ptr fleet_commander_changed_event_ptr;
};

template <class StrVal, class Lock = boost::recursive_mutex>
struct u8spaceship_traits
{
    typedef u8spaceship_traits<StrVal, Lock> this_type;
    typedef StrVal string_value_type;
    typedef Lock lockable_type;
    typedef s::u8string string_identifier_type;

    // Property types
    typedef p::u8property<double, lockable_type> double_property_type;
    typedef p::u8property<int, lockable_type> int_property_type;
    typedef p::u8property<string_value_type, lockable_type> string_property_type;
    typedef p::value_u8property<string_value_type, lockable_type> string_value_property_type;
    typedef pro::u8property<typename m::basic_command_interface<string_identifier_type, lockable_type>::ptr, lockable_type> read_only_command_property_type;
    typedef pro::u8property<string_value_type, lockable_type> read_only_string_property_type;
    typedef pro::value_u8property<string_value_type, lockable_type> read_only_string_value_property_type;

    // Observable object types
    typedef m::basic_observable_object<string_identifier_type, lockable_type> observable_object_base_type;
    typedef typename m::basic_property_changed_arguments<string_identifier_type> property_changed_arguments_type;
    typedef typename property_changed_arguments_type::ptr property_changed_arguments_ptr;

    // Command types
    typedef typename read_only_command_property_type::value_type command_value_type;
    typedef typename command_value_type command_ptr;

    // Event types
    typedef m::basic_event_manager<string_identifier_type, lockable_type> event_manager_type;
    typedef typename event_manager_type::ptr event_manager_ptr;
    typedef typename event_manager_type::wptr event_manager_wptr;
    typedef m::basic_event<string_identifier_type> event_type;
    typedef typename event_type::ptr event_ptr;
    typedef typename event_type::wptr event_wptr;
    typedef fleet_commander_changed_event<string_identifier_type, read_only_string_value_property_type> fleet_commander_changed_event_type;
    typedef typename fleet_commander_changed_event_type::ptr fleet_commander_changed_event_ptr;
};

}

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_BOOST_TEST_SPACESHIP_TRAITS_HPP_INCLUDED
