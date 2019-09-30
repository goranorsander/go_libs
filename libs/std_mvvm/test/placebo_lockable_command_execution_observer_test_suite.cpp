//
//  placebo_lockable_command_execution_observer_test_suite.cpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_command_execution_observer_placebo_lockable_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>

namespace m = go::mvvm;
namespace mst = go::mvvm::single_threaded;
namespace ph = std::placeholders;
namespace u = go::utility;

namespace
{

const std::string TEST_COMMAND_NAME("test command");

class test_command
    : public mst::command_interface
{
public:
    virtual ~test_command() GO_DEFAULT_DESTRUCTOR

    test_command()
        : mst::command_interface(TEST_COMMAND_NAME, nullptr)
        , _allow_execute(false)
        , _executed(false)
    {
    }

    virtual bool can_execute(const std::shared_ptr<m::command_parameters>& /*params*/) override
    {
        return _allow_execute && !_executed;
    }

    virtual void execute(const std::shared_ptr<m::command_parameters>& params) override
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
        const bool can_execute_ = can_execute(nullptr);
        _allow_execute = v;
        if(can_execute_ != can_execute(nullptr))
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
    virtual ~test_command_execution_observer() GO_DEFAULT_DESTRUCTOR

    test_command_execution_observer()
        : _number_of_executed_commands(0)
        , _number_of_not_executed_commands(0)
    {
    }

    virtual void on_command_executed(const std::shared_ptr<mst::command_interface>& /*c*/) override
    {
        ++_number_of_executed_commands;
    }

    virtual void on_command_not_executed(const std::shared_ptr<mst::command_interface>& /*c*/) override
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
    virtual ~test_command_observer() GO_DEFAULT_DESTRUCTOR

        test_command_observer()
        : _number_of_can_execute_changes(0)
    {
    }

    void on_can_execute_changed(const std::shared_ptr<mst::command_interface>& /*c*/)
    {
        ++_number_of_can_execute_changes;
    }

    unsigned int number_of_can_execute_changes() const { return _number_of_can_execute_changes; }

private:
    unsigned int _number_of_can_execute_changes;
};

TEST(std_command_execution_observer_placebo_lockable_test_suite, test_execute_command)
{
    mst::command_manager::ptr command_mgr = mst::command_manager::create();

    EXPECT_TRUE(command_mgr != nullptr);
    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_TRUE(command_mgr->command_executed.empty());
    EXPECT_TRUE(command_mgr->command_not_executed.empty());

    test_command_execution_observer command_execution_observer;

    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->command_executed.connect(std::bind(&test_command_execution_observer::on_command_executed, &command_execution_observer, ph::_1));
    command_mgr->command_not_executed.connect(std::bind(&test_command_execution_observer::on_command_not_executed, &command_execution_observer, ph::_1));

    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_FALSE(command_mgr->command_executed.empty());
    EXPECT_FALSE(command_mgr->command_not_executed.empty());
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0u, command_execution_observer.number_of_not_executed_commands());

    test_command_observer command_observer;

    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());

    std::shared_ptr<test_command> command(new test_command());

    EXPECT_TRUE(command != nullptr);
    EXPECT_EQ(TEST_COMMAND_NAME, command->command_name());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));
    EXPECT_TRUE(command->can_execute_changed.empty());

    command->can_execute_changed.connect(std::bind(&test_command_observer::on_can_execute_changed, &command_observer, ph::_1));

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));

    command_mgr->execute(command);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command->allow_execute(true);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(1u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_TRUE(command->can_execute(nullptr));
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->execute(command);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));
    EXPECT_EQ(1u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command->execute(nullptr);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));
    EXPECT_EQ(1u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());
}

TEST(std_command_execution_observer_placebo_lockable_test_suite, test_post_command)
{
    mst::command_manager::ptr command_mgr = mst::command_manager::create();

    EXPECT_TRUE(command_mgr != nullptr);
    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_TRUE(command_mgr->command_executed.empty());
    EXPECT_TRUE(command_mgr->command_not_executed.empty());

    test_command_execution_observer command_execution_observer;

    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->command_executed.connect(std::bind(&test_command_execution_observer::on_command_executed, &command_execution_observer, ph::_1));
    command_mgr->command_not_executed.connect(std::bind(&test_command_execution_observer::on_command_not_executed, &command_execution_observer, ph::_1));

    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_FALSE(command_mgr->command_executed.empty());
    EXPECT_FALSE(command_mgr->command_not_executed.empty());
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0u, command_execution_observer.number_of_not_executed_commands());

    test_command_observer command_observer;

    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());

    std::shared_ptr<test_command> command(new test_command());

    EXPECT_TRUE(command != nullptr);
    EXPECT_EQ(TEST_COMMAND_NAME, command->command_name());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));
    EXPECT_TRUE(command->can_execute_changed.empty());

    command->can_execute_changed.connect(std::bind(&test_command_observer::on_can_execute_changed, &command_observer, ph::_1));

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));

    command_mgr->post(command);

    EXPECT_EQ(1u, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->execute_commands();

    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command->allow_execute(true);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(1u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_TRUE(command->can_execute(nullptr));
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->post(command);

    EXPECT_EQ(1u, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(1u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_TRUE(command->can_execute(nullptr));
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->execute_commands();

    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));
    EXPECT_EQ(1u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->post(command);

    EXPECT_EQ(1u, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));
    EXPECT_EQ(1u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(1u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->execute_commands();

    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));
    EXPECT_EQ(1u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(2u, command_execution_observer.number_of_not_executed_commands());
}

}

#endif  // Required C++11 feature is not supported by this compiler
