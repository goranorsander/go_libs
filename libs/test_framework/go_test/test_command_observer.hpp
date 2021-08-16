#ifndef GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_OBSERVER_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_OBSERVER_HPP_INCLUDED

//
//  test_command_observer.hpp
//
//  Copyright 2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <go/mvvm.hpp>
#include <go/namespace_alias.hpp>
#include <go/string.hpp>

#if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_MUTEX))

namespace go_test
{

template <class Traits>
class test_command_observer
{
public:
    using this_type = test_command_observer<Traits>;

    using traits_type = Traits;
    using string_value_type = typename traits_type::string_value_type;
    using lockable_type = typename traits_type::lockable_type;
    using string_identifier_type = typename traits_type::string_identifier_type;
    using command_interface_type = typename traits_type::command_interface_type;

public:
    virtual ~test_command_observer() GO_DEFAULT_DESTRUCTOR

    test_command_observer()
        : _number_of_can_execute_changes(0)
    {
    }

    void on_can_execute_changed(const std::shared_ptr<command_interface_type>& /*c*/)
    {
        ++_number_of_can_execute_changes;
    }

    unsigned int number_of_can_execute_changes() const { return _number_of_can_execute_changes; }

private:
    unsigned int _number_of_can_execute_changes;
};

}

#endif  // #if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_MUTEX))

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_OBSERVER_HPP_INCLUDED
