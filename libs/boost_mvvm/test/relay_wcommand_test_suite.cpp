//
//  relay_wcommand_test_suite.cpp
//
//  Copyright 2018-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#include <go_boost/mvvm.hpp>
#include <go_boost/namespace_alias.hpp>

namespace
{

const std::wstring TEST_RELAY_COMMAND_NAME(L"test relay wcommand");

class test_relay_wcommand
    : public m::relay_wcommand
{
public:
    virtual ~test_relay_wcommand() GO_BOOST_DEFAULT_DESTRUCTOR

        test_relay_wcommand(const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command)
        : m::relay_wcommand(TEST_RELAY_COMMAND_NAME, execute_command, can_execute_command, m::relay_wcommand::command_parameters_type())
    {
    }

    virtual bool can_execute(const boost::shared_ptr<m::command_parameters>& params) GO_BOOST_OVERRIDE
    {
        return m::relay_wcommand::can_execute(params);
    }

    virtual void execute(const boost::shared_ptr<m::command_parameters>& params) GO_BOOST_OVERRIDE
    {
        m::relay_wcommand::execute(params);
    }
};

class test_relay_wcommand_exection_context
{
public:
    typedef GO_BOOST_TYPENAME boost::signals2::signal<void(const boost::shared_ptr<m::wcommand_interface>&)> can_execute_changed_signal;

    virtual ~test_relay_wcommand_exection_context() GO_BOOST_DEFAULT_DESTRUCTOR

    test_relay_wcommand_exection_context()
        : _allow_execute(false)
        , _executed(false)
    {
    }

    virtual bool can_execute(const boost::shared_ptr<m::command_parameters>& /*params*/)
    {
        return _allow_execute && !_executed;
    }

    virtual void execute(const boost::shared_ptr<m::command_parameters>& params)
    {
        if(can_execute(params))
        {
            _executed = true;
            if(!can_execute(params))
            {
                can_execute_changed(m::relay_wcommand::ptr());
            }
        }
    }

    bool allow_execute() const { return _allow_execute; }

    void allow_execute(const bool v)
    {
        const bool can_execute_ = can_execute(m::relay_wcommand::command_parameters_type());
        _allow_execute = v;
        if(can_execute_ != can_execute(m::relay_wcommand::command_parameters_type()))
        {
            can_execute_changed(m::relay_wcommand::ptr());
        }
    }

    bool executed() const { return _executed; }

    can_execute_changed_signal can_execute_changed;

private:
    bool _allow_execute;
    bool _executed;
};

class test_relay_wcommand_observer
{
public:
    virtual ~test_relay_wcommand_observer() GO_BOOST_DEFAULT_DESTRUCTOR

    test_relay_wcommand_observer()
        : _number_of_can_execute_changes(0)
    {
    }

    void on_can_execute_changed(const boost::shared_ptr<m::wcommand_interface>& /*c*/)
    {
        ++_number_of_can_execute_changes;
    }

    unsigned int number_of_can_execute_changes() const { return _number_of_can_execute_changes; }

private:
    unsigned int _number_of_can_execute_changes;
};

TEST(boost_relay_wcommand_test_suite, test_relay_wcommand)
{
    test_relay_wcommand_exection_context command_exection_context;

    EXPECT_FALSE(command_exection_context.allow_execute());
    EXPECT_FALSE(command_exection_context.executed());
    EXPECT_FALSE(command_exection_context.can_execute(m::relay_wcommand::command_parameters_type()));

    boost::shared_ptr<test_relay_wcommand> command(new test_relay_wcommand(boost::bind(&test_relay_wcommand_exection_context::execute, &command_exection_context, boost::placeholders::_1),
        boost::bind(&test_relay_wcommand_exection_context::can_execute, &command_exection_context, boost::placeholders::_1)));

    EXPECT_TRUE(command != NULL);
    EXPECT_EQ(TEST_RELAY_COMMAND_NAME, command->command_name());
    EXPECT_FALSE(command_exection_context.allow_execute());
    EXPECT_FALSE(command_exection_context.executed());
    EXPECT_FALSE(command_exection_context.can_execute(m::relay_wcommand::command_parameters_type()));
    EXPECT_FALSE(command->can_execute(m::relay_wcommand::command_parameters_type()));
    EXPECT_TRUE(command->can_execute_changed.empty());

    test_relay_wcommand_observer command_observer;

    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());

    command->can_execute_changed.connect(boost::bind(&test_relay_wcommand_observer::on_can_execute_changed, &command_observer, boost::placeholders::_1));

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command_exection_context.allow_execute());
    EXPECT_FALSE(command_exection_context.executed());
    EXPECT_FALSE(command_exection_context.can_execute(m::relay_wcommand::command_parameters_type()));
    EXPECT_FALSE(command->can_execute(m::relay_wcommand::command_parameters_type()));

    command->execute(m::relay_wcommand::command_parameters_type());

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command_exection_context.allow_execute());
    EXPECT_FALSE(command_exection_context.executed());
    EXPECT_FALSE(command_exection_context.can_execute(m::relay_wcommand::command_parameters_type()));
    EXPECT_FALSE(command->can_execute(m::relay_wcommand::command_parameters_type()));

    command_exection_context.allow_execute(true);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command_exection_context.allow_execute());
    EXPECT_FALSE(command_exection_context.executed());
    EXPECT_TRUE(command_exection_context.can_execute(m::relay_wcommand::command_parameters_type()));
    EXPECT_TRUE(command->can_execute(m::relay_wcommand::command_parameters_type()));

    command->execute(m::relay_wcommand::command_parameters_type());

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command_exection_context.allow_execute());
    EXPECT_TRUE(command_exection_context.executed());
    EXPECT_FALSE(command_exection_context.can_execute(m::relay_wcommand::command_parameters_type()));
    EXPECT_FALSE(command->can_execute(m::relay_wcommand::command_parameters_type()));

    command->execute(m::relay_wcommand::command_parameters_type());

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command_exection_context.allow_execute());
    EXPECT_TRUE(command_exection_context.executed());
    EXPECT_FALSE(command_exection_context.can_execute(m::relay_wcommand::command_parameters_type()));
    EXPECT_FALSE(command->can_execute(m::relay_wcommand::command_parameters_type()));
}

}
