//
//  basic_command_execution_observer_test_suite.cpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#include <go_boost/mvvm.hpp>
#include <go_boost/namespace_alias.hpp>
#include <go_boost/string.hpp>

namespace
{

const s::u8string TEST_COMMAND_NAME(s::create<s::u8string>("test command"));

class test_command
    : public m::basic_command_interface<s::u8string>
{
public:
    virtual ~test_command() GO_BOOST_DEFAULT_DESTRUCTOR

    test_command()
        : m::basic_command_interface<s::u8string>(TEST_COMMAND_NAME, m::basic_command_interface<s::u8string>::command_parameters_type())
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
        const bool can_execute_ = can_execute(m::basic_command_interface<s::u8string>::command_parameters_type());
        _allow_execute = v;
        if(can_execute_ != can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()))
        {
            can_execute_changed(this->shared_from_this());
        }
    }

    bool executed() const { return _executed; }

private:
    bool _allow_execute;
    bool _executed;
};

class test_command_execution_observer
    : public m::basic_command_execution_observer_interface<s::u8string>
{
public:
    virtual ~test_command_execution_observer() GO_BOOST_DEFAULT_DESTRUCTOR

    test_command_execution_observer()
        : _number_of_executed_commands(0)
        , _number_of_not_executed_commands(0)
    {
    }

    virtual void on_command_executed(const boost::shared_ptr<m::basic_command_interface<s::u8string>>& /*c*/) GO_BOOST_OVERRIDE
    {
        ++_number_of_executed_commands;
    }

    virtual void on_command_not_executed(const boost::shared_ptr<m::basic_command_interface<s::u8string>>& /*c*/) GO_BOOST_OVERRIDE
    {
        ++_number_of_not_executed_commands;
    }

    unsigned int number_of_executed_commands() const { return _number_of_executed_commands; }
    unsigned int number_of_not_executed_commands() const { return _number_of_not_executed_commands; }

private:
    unsigned int _number_of_executed_commands;
    unsigned int _number_of_not_executed_commands;
};

class test_command_observer
{
public:
    virtual ~test_command_observer() GO_BOOST_DEFAULT_DESTRUCTOR

        test_command_observer()
        : _number_of_can_execute_changes(0)
    {
    }

    void on_can_execute_changed(const boost::shared_ptr<m::basic_command_interface<s::u8string>>& /*c*/)
    {
        ++_number_of_can_execute_changes;
    }

    unsigned int number_of_can_execute_changes() const { return _number_of_can_execute_changes; }

private:
    unsigned int _number_of_can_execute_changes;
};

TEST(boost_basic_command_execution_observer_test_suite, test_execute_command)
{
    m::basic_command_manager<s::u8string>::ptr command_mgr = m::basic_command_manager<s::u8string>::create();

    EXPECT_TRUE(command_mgr != NULL);
    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_TRUE(command_mgr->command_executed.empty());
    EXPECT_TRUE(command_mgr->command_not_executed.empty());

    test_command_execution_observer command_execution_observer;

    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->command_executed.connect(boost::bind(&test_command_execution_observer::on_command_executed, &command_execution_observer, boost::placeholders::_1));
    command_mgr->command_not_executed.connect(boost::bind(&test_command_execution_observer::on_command_not_executed, &command_execution_observer, boost::placeholders::_1));

    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_FALSE(command_mgr->command_executed.empty());
    EXPECT_FALSE(command_mgr->command_not_executed.empty());
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0u, command_execution_observer.number_of_not_executed_commands());

    test_command_observer command_observer;

    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());

    boost::shared_ptr<test_command> command(new test_command());

    EXPECT_TRUE(command != NULL);
    EXPECT_EQ(TEST_COMMAND_NAME, command->command_name());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()));
    EXPECT_TRUE(command->can_execute_changed.empty());

    command->can_execute_changed.connect(boost::bind(&test_command_observer::on_can_execute_changed, &command_observer, boost::placeholders::_1));

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()));

    command_mgr->execute(command);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()));
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command->allow_execute(true);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(1u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_TRUE(command->can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()));
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->execute(command);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()));
    EXPECT_EQ(1u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command->execute(m::basic_command_interface<s::u8string>::command_parameters_type());

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()));
    EXPECT_EQ(1u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());
}

TEST(boost_basic_command_execution_observer_test_suite, test_post_command)
{
    m::basic_command_manager<s::u8string>::ptr command_mgr = m::basic_command_manager<s::u8string>::create();

    EXPECT_TRUE(command_mgr != NULL);
    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_TRUE(command_mgr->command_executed.empty());
    EXPECT_TRUE(command_mgr->command_not_executed.empty());

    test_command_execution_observer command_execution_observer;

    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->command_executed.connect(boost::bind(&test_command_execution_observer::on_command_executed, &command_execution_observer, boost::placeholders::_1));
    command_mgr->command_not_executed.connect(boost::bind(&test_command_execution_observer::on_command_not_executed, &command_execution_observer, boost::placeholders::_1));

    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_FALSE(command_mgr->command_executed.empty());
    EXPECT_FALSE(command_mgr->command_not_executed.empty());
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0u, command_execution_observer.number_of_not_executed_commands());

    test_command_observer command_observer;

    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());

    boost::shared_ptr<test_command> command(new test_command());

    EXPECT_TRUE(command != NULL);
    EXPECT_EQ(TEST_COMMAND_NAME, command->command_name());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()));
    EXPECT_TRUE(command->can_execute_changed.empty());

    command->can_execute_changed.connect(boost::bind(&test_command_observer::on_can_execute_changed, &command_observer, boost::placeholders::_1));

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()));

    command_mgr->post(command);

    EXPECT_EQ(1u, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()));
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->execute_commands();

    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()));
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command->allow_execute(true);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(1u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_TRUE(command->can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()));
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->post(command);

    EXPECT_EQ(1u, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(1u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_TRUE(command->can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()));
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->execute_commands();

    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()));
    EXPECT_EQ(1u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->post(command);

    EXPECT_EQ(1u, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()));
    EXPECT_EQ(1u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->execute_commands();

    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(m::basic_command_interface<s::u8string>::command_parameters_type()));
    EXPECT_EQ(1u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(2u, command_execution_observer.number_of_not_executed_commands());
}

}
