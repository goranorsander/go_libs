#ifndef GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_EXECUTION_OBSERVER_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_EXECUTION_OBSERVER_HPP_INCLUDED

//
//  test_command_execution_observer.hpp
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

namespace go_test
{

template <class Traits>
class test_command_execution_observer
    : public m::basic_command_execution_observer_interface<typename Traits::string_identifier_type, typename Traits::lockable_type>
{
public:
    typedef test_command_execution_observer<Traits> this_type;
    typedef typename m::basic_command_execution_observer_interface<typename Traits::string_identifier_type, typename Traits::lockable_type> base_type;

    typedef Traits traits_type;
    typedef typename traits_type::string_value_type string_value_type;
    typedef typename traits_type::lockable_type lockable_type;
    typedef typename traits_type::string_identifier_type string_identifier_type;
    typedef typename traits_type::command_interface_type command_interface_type;

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

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_EXECUTION_OBSERVER_HPP_INCLUDED
