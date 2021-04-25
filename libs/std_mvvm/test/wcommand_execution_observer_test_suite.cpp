//
//  wcommand_execution_observer_test_suite.cpp
//
//  Copyright 2017-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_wcommand_execution_observer_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>
#include <go/namespace_alias.hpp>

namespace
{

const std::wstring TEST_COMMAND_NAME(L"test wcommand");

class test_wcommand
    : public m::wcommand_interface
{
public:
    virtual ~test_wcommand() GO_DEFAULT_DESTRUCTOR

    test_wcommand()
        : m::wcommand_interface(TEST_COMMAND_NAME, nullptr)
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

class test_wcommand_execution_wobserver
    : public m::wcommand_execution_wobserver_interface
{
public:
    virtual ~test_wcommand_execution_wobserver() GO_DEFAULT_DESTRUCTOR

    test_wcommand_execution_wobserver()
        : _number_of_executed_commands(0)
        , _number_of_not_executed_commands(0)
    {
    }

    virtual void on_command_executed(const std::shared_ptr<m::wcommand_interface>& /*c*/) override
    {
        ++_number_of_executed_commands;
    }

    virtual void on_command_not_executed(const std::shared_ptr<m::wcommand_interface>& /*c*/) override
    {
        ++_number_of_not_executed_commands;
    }

    unsigned int number_of_executed_commands() const { return _number_of_executed_commands; }
    unsigned int number_of_not_executed_commands() const { return _number_of_not_executed_commands; }

private:
    unsigned int _number_of_executed_commands;
    unsigned int _number_of_not_executed_commands;
};

class test_wcommand_observer
{
public:
    virtual ~test_wcommand_observer() GO_DEFAULT_DESTRUCTOR

        test_wcommand_observer()
        : _number_of_can_execute_changes(0)
    {
    }

    void on_can_execute_changed(const std::shared_ptr<m::wcommand_interface>& /*c*/)
    {
        ++_number_of_can_execute_changes;
    }

    unsigned int number_of_can_execute_changes() const { return _number_of_can_execute_changes; }

private:
    unsigned int _number_of_can_execute_changes;
};

TEST(std_wcommand_execution_observer_test_suite, test_execute_wcommand)
{
    m::wcommand_manager::ptr command_mgr = m::wcommand_manager::create();

    EXPECT_TRUE(command_mgr != nullptr);
    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_TRUE(command_mgr->command_executed.empty());
    EXPECT_TRUE(command_mgr->command_not_executed.empty());

    test_wcommand_execution_wobserver command_execution_observer;

    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->command_executed.connect(std::bind(&test_wcommand_execution_wobserver::on_command_executed, &command_execution_observer, ph::_1));
    command_mgr->command_not_executed.connect(std::bind(&test_wcommand_execution_wobserver::on_command_not_executed, &command_execution_observer, ph::_1));

    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_FALSE(command_mgr->command_executed.empty());
    EXPECT_FALSE(command_mgr->command_not_executed.empty());
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0u, command_execution_observer.number_of_not_executed_commands());

    test_wcommand_observer command_observer;

    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());

    std::shared_ptr<test_wcommand> command(new test_wcommand());

    EXPECT_TRUE(command != nullptr);
    EXPECT_EQ(TEST_COMMAND_NAME, command->command_name());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));
    EXPECT_TRUE(command->can_execute_changed.empty());

    command->can_execute_changed.connect(std::bind(&test_wcommand_observer::on_can_execute_changed, &command_observer, ph::_1));

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

TEST(std_wcommand_execution_observer_test_suite, test_post_wcommand)
{
    m::wcommand_manager::ptr command_mgr = m::wcommand_manager::create();

    EXPECT_TRUE(command_mgr != nullptr);
    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_TRUE(command_mgr->command_executed.empty());
    EXPECT_TRUE(command_mgr->command_not_executed.empty());

    test_wcommand_execution_wobserver command_execution_observer;

    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0u, command_execution_observer.number_of_not_executed_commands());

    command_mgr->command_executed.connect(std::bind(&test_wcommand_execution_wobserver::on_command_executed, &command_execution_observer, ph::_1));
    command_mgr->command_not_executed.connect(std::bind(&test_wcommand_execution_wobserver::on_command_not_executed, &command_execution_observer, ph::_1));

    EXPECT_EQ(0u, command_mgr->commands());
    EXPECT_FALSE(command_mgr->command_executed.empty());
    EXPECT_FALSE(command_mgr->command_not_executed.empty());
    EXPECT_EQ(0u, command_execution_observer.number_of_executed_commands());
    EXPECT_EQ(0u, command_execution_observer.number_of_not_executed_commands());

    test_wcommand_observer command_observer;

    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());

    std::shared_ptr<test_wcommand> command(new test_wcommand());

    EXPECT_TRUE(command != nullptr);
    EXPECT_EQ(TEST_COMMAND_NAME, command->command_name());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));
    EXPECT_TRUE(command->can_execute_changed.empty());

    command->can_execute_changed.connect(std::bind(&test_wcommand_observer::on_can_execute_changed, &command_observer, ph::_1));

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
