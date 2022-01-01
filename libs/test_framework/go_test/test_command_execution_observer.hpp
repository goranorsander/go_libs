#ifndef GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_EXECUTION_OBSERVER_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_EXECUTION_OBSERVER_HPP_INCLUDED

//
//  test_command_execution_observer.hpp
//
//  Copyright 2021-2022 Göran Orsander
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
class test_command_execution_observer
    : public m::basic_command_execution_observer_interface<typename Traits::string_identifier_type, typename Traits::lockable_type>
{
public:
    using this_type = test_command_execution_observer<Traits>;
    using base_type = typename m::basic_command_execution_observer_interface<typename Traits::string_identifier_type, typename Traits::lockable_type>;

    using traits_type = Traits;
    using string_value_type = typename traits_type::string_value_type;
    using lockable_type = typename traits_type::lockable_type;
    using string_identifier_type = typename traits_type::string_identifier_type;
    using command_interface_type = typename traits_type::command_interface_type;

public:
    virtual ~test_command_execution_observer() GO_DEFAULT_DESTRUCTOR

    test_command_execution_observer()
        : _number_of_executed_commands(0)
        , _number_of_not_executed_commands(0)
    {
    }

    virtual void on_command_executed(const std::shared_ptr<command_interface_type>& /*c*/) GO_OVERRIDE
    {
        ++this->_number_of_executed_commands;
    }

    virtual void on_command_not_executed(const std::shared_ptr<command_interface_type>& /*c*/) GO_OVERRIDE
    {
        ++this->_number_of_not_executed_commands;
    }

    unsigned int number_of_executed_commands() const { return this->_number_of_executed_commands; }
    unsigned int number_of_not_executed_commands() const { return this->_number_of_not_executed_commands; }

private:
    unsigned int _number_of_executed_commands;
    unsigned int _number_of_not_executed_commands;
};

}

#endif  // #if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_MUTEX))

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_EXECUTION_OBSERVER_HPP_INCLUDED
