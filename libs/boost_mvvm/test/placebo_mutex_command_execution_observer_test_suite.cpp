//
//  placebo_mutex_command_execution_observer_test_suite.cpp
//
//  Copyright 2018 Göran Orsander
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
namespace mst = go_boost::mvvm::single_threaded;
namespace u = go_boost::utility;

namespace
{

const std::string TEST_COMMAND_NAME("test command");

class test_command
    : public mst::command_interface
{
public:
    virtual ~test_command() GO_BOOST_DEFAULT_DESTRUCTOR

    test_command()
        : mst::command_interface(TEST_COMMAND_NAME, mst::command_interface::command_parameters_type())
        , _allow_execute(false)
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
                can_execute_changed(this->shared_from_this());
            }
        }
    }

    bool allow_execute() const { return _allow_execute; }

    void allow_execute(const bool v)
    {
        const bool can_execute_ = can_execute(mst::command_interface::command_parameters_type());
        _allow_execute = v;
        if(can_execute_ != can_execute(mst::command_interface::command_parameters_type()))
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
    : public mst::command_execution_observer_interface
{
public:
    virtual ~test_command_execution_observer() GO_BOOST_DEFAULT_DESTRUCTOR

    test_command_execution_observer()
        : _number_of_executed_commands(0)
        , _number_of_not_executed_commands(0)
    {
    }

    virtual void on_command_executed(const boost::shared_ptr<mst::command_interface>& /*c*/)
    {
        ++_number_of_executed_commands;
    }

    virtual void on_command_not_executed(const boost::shared_ptr<mst::command_interface>& /*c*/)
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

    void on_can_execute_changed(const boost::shared_ptr<mst::command_interface>& /*c*/)
    {
        ++_number_of_can_execute_changes;
    }

    unsigned int number_of_can_execute_changes() const { return _number_of_can_execute_changes; }

private:
    unsigned int _number_of_can_execute_changes;
};

TEST(boost_command_execution_observer_placebo_mutex_test_suite, test_execute_command)
{
    mst::command_manager::ptr command_mgr = mst::command_manager::create();

    EXPECT_TRUE(command_mgr != NULL);
    EXPECT_EQ(0, command_mgr->commands());
    EXPECT_TRUE(command_mgr->command_executed.empty());
    EXPECT_TRUE(command_mgr->command_not_executed.empty());

    test_command_execution_observer command_execution_observer;

    EXPECT_EQ(0, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0, command_execution_observer.number_of_not_executed_commands());

    command_mgr->command_executed.connect(boost::bind(&test_command_execution_observer::on_command_executed, &command_execution_observer, _1));
    command_mgr->command_not_executed.connect(boost::bind(&test_command_execution_observer::on_command_not_executed, &command_execution_observer, _1));

    EXPECT_EQ(0, command_mgr->commands());
    EXPECT_FALSE(command_mgr->command_executed.empty());
    EXPECT_FALSE(command_mgr->command_not_executed.empty());
    EXPECT_EQ(0, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0, command_execution_observer.number_of_not_executed_commands());

    test_command_observer command_observer;

    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());

    boost::shared_ptr<test_command> command(new test_command());

    EXPECT_TRUE(command != NULL);
    EXPECT_EQ(TEST_COMMAND_NAME, command->command_name());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));
    EXPECT_TRUE(command->can_execute_changed.empty());

    command->can_execute_changed.connect(boost::bind(&test_command_observer::on_can_execute_changed, &command_observer, _1));

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));

    command_mgr->execute(command);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));
    EXPECT_EQ(0, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1, command_execution_observer.number_of_not_executed_commands());

    command->allow_execute(true);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(1, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_TRUE(command->can_execute(mst::command_interface::command_parameters_type()));
    EXPECT_EQ(0, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1, command_execution_observer.number_of_not_executed_commands());

    command_mgr->execute(command);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));
    EXPECT_EQ(1, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1, command_execution_observer.number_of_not_executed_commands());

    command->execute(mst::command_interface::command_parameters_type());

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));
    EXPECT_EQ(1, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1, command_execution_observer.number_of_not_executed_commands());
}

TEST(boost_command_execution_observer_placebo_mutex_test_suite, test_post_command)
{
    mst::command_manager::ptr command_mgr = mst::command_manager::create();

    EXPECT_TRUE(command_mgr != NULL);
    EXPECT_EQ(0, command_mgr->commands());
    EXPECT_TRUE(command_mgr->command_executed.empty());
    EXPECT_TRUE(command_mgr->command_not_executed.empty());

    test_command_execution_observer command_execution_observer;

    EXPECT_EQ(0, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0, command_execution_observer.number_of_not_executed_commands());

    command_mgr->command_executed.connect(boost::bind(&test_command_execution_observer::on_command_executed, &command_execution_observer, _1));
    command_mgr->command_not_executed.connect(boost::bind(&test_command_execution_observer::on_command_not_executed, &command_execution_observer, _1));

    EXPECT_EQ(0, command_mgr->commands());
    EXPECT_FALSE(command_mgr->command_executed.empty());
    EXPECT_FALSE(command_mgr->command_not_executed.empty());
    EXPECT_EQ(0, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0, command_execution_observer.number_of_not_executed_commands());

    test_command_observer command_observer;

    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());

    boost::shared_ptr<test_command> command(new test_command());

    EXPECT_TRUE(command != NULL);
    EXPECT_EQ(TEST_COMMAND_NAME, command->command_name());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));
    EXPECT_TRUE(command->can_execute_changed.empty());

    command->can_execute_changed.connect(boost::bind(&test_command_observer::on_can_execute_changed, &command_observer, _1));

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));

    command_mgr->post(command);

    EXPECT_EQ(1, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));
    EXPECT_EQ(0, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0, command_execution_observer.number_of_not_executed_commands());

    command_mgr->execute_commands();

    EXPECT_EQ(0, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));
    EXPECT_EQ(0, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1, command_execution_observer.number_of_not_executed_commands());

    command->allow_execute(true);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(1, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_TRUE(command->can_execute(mst::command_interface::command_parameters_type()));
    EXPECT_EQ(0, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1, command_execution_observer.number_of_not_executed_commands());

    command_mgr->post(command);

    EXPECT_EQ(1, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(1, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_TRUE(command->can_execute(mst::command_interface::command_parameters_type()));
    EXPECT_EQ(0, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1, command_execution_observer.number_of_not_executed_commands());

    command_mgr->execute_commands();

    EXPECT_EQ(0, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));
    EXPECT_EQ(1, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1, command_execution_observer.number_of_not_executed_commands());

    command_mgr->post(command);

    EXPECT_EQ(1, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));
    EXPECT_EQ(1, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1, command_execution_observer.number_of_not_executed_commands());

    command_mgr->execute_commands();

    EXPECT_EQ(0, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));
    EXPECT_EQ(1, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(2, command_execution_observer.number_of_not_executed_commands());
}

}
