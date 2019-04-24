//
//  basic_command_test_suite.cpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go_boost/config.hpp>
#include <go_boost/mvvm.hpp>
#include <go_boost/utility.hpp>

namespace m = go_boost::mvvm;
namespace u = go_boost::utility;
namespace us = go_boost::utility::string;

namespace
{

const u::u8string TEST_COMMAND_NAME(us::create<u::u8string>("test command"));

class test_command
    : public m::basic_command_interface<u::u8string>
{
public:
    virtual ~test_command() GO_BOOST_DEFAULT_DESTRUCTOR

    test_command()
        : m::basic_command_interface<u::u8string>(TEST_COMMAND_NAME, m::basic_command_interface<u::u8string>::command_parameters_type())
        , _allow_execute(false)
        , _executed(false)
    {
    }

    virtual bool can_execute(const boost::shared_ptr<m::command_parameters>& /*params*/) GO_BOOST_OVERRIDE
    {
        return _allow_execute && !_executed;
    }

    virtual void execute(const boost::shared_ptr<m::command_parameters>& params) GO_BOOST_OVERRIDE
    {
        if(can_execute(params))
        {
            _executed = true;
            if(!can_execute(params))
            {
                can_execute_changed(this->shared_from_this());
            }
        }
    }

    bool allow_execute() const { return _allow_execute; }

    void allow_execute(const bool v)
    {
        const bool can_execute_ = can_execute(m::basic_command_interface<u::u8string>::command_parameters_type());
        _allow_execute = v;
        if(can_execute_ != can_execute(m::basic_command_interface<u::u8string>::command_parameters_type()))
        {
            can_execute_changed(this->shared_from_this());
        }
    }

    bool executed() const { return _executed; }

private:
    bool _allow_execute;
    bool _executed;
};

class test_command_observer
{
public:
    virtual ~test_command_observer() GO_BOOST_DEFAULT_DESTRUCTOR

    test_command_observer()
        : _number_of_can_execute_changes(0)
    {
    }

    void on_can_execute_changed(const boost::shared_ptr<m::basic_command_interface<u::u8string>>& /*c*/)
    {
        ++_number_of_can_execute_changes;
    }

    unsigned int number_of_can_execute_changes() const { return _number_of_can_execute_changes; }

private:
    unsigned int _number_of_can_execute_changes;
};

TEST(boost_basic_command_test_suite, test_command)
{
    boost::shared_ptr<test_command> command(new test_command());

    EXPECT_TRUE(command != NULL);
    EXPECT_EQ(TEST_COMMAND_NAME, command->command_name());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<u::u8string>::command_parameters_type()));
    EXPECT_TRUE(command->can_execute_changed.empty());

    test_command_observer command_observer;

    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());

    command->can_execute_changed.connect(boost::bind(&test_command_observer::on_can_execute_changed, &command_observer, _1));

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<u::u8string>::command_parameters_type()));

    command->execute(m::basic_command_interface<u::u8string>::command_parameters_type());

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<u::u8string>::command_parameters_type()));

    command->allow_execute(true);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(1u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_TRUE(command->can_execute(m::basic_command_interface<u::u8string>::command_parameters_type()));

    command->execute(m::basic_command_interface<u::u8string>::command_parameters_type());

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<u::u8string>::command_parameters_type()));

    command->execute(m::basic_command_interface<u::u8string>::command_parameters_type());

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<u::u8string>::command_parameters_type()));
}

}
