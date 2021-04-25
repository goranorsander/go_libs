#ifndef GO_TEST_FRAMEWORK_GO_BOOST_TEST_TEST_COMMAND_OBSERVER_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_BOOST_TEST_TEST_COMMAND_OBSERVER_HPP_INCLUDED

//
//  test_command_observer.hpp
//
//  Copyright 2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#include <go_boost/mvvm.hpp>
#include <go_boost/namespace_alias.hpp>
#include <go_boost/string.hpp>

namespace go_boost_test
{

template <class Traits>
class test_command_observer
{
public:
    typedef test_command_observer<Traits> this_type;

    typedef Traits traits_type;
    typedef typename traits_type::string_value_type string_value_type;
    typedef typename traits_type::lockable_type lockable_type;
    typedef typename traits_type::string_identifier_type string_identifier_type;
    typedef typename traits_type::command_interface_type command_interface_type;

public:
    virtual ~test_command_observer() GO_BOOST_DEFAULT_DESTRUCTOR

    test_command_observer()
        : _number_of_can_execute_changes(0)
    {
    }

    void on_can_execute_changed(const boost::shared_ptr<command_interface_type>& /*c*/)
    {
        ++_number_of_can_execute_changes;
    }

    unsigned int number_of_can_execute_changes() const { return _number_of_can_execute_changes; }

private:
    unsigned int _number_of_can_execute_changes;
};

}

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_BOOST_TEST_TEST_COMMAND_OBSERVER_HPP_INCLUDED
