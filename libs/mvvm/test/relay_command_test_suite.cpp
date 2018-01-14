//
//  relay_command_test_suite.cpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_relay_command_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>

namespace m = go::mvvm;
namespace ph = std::placeholders;

namespace
{

const std::string TEST_RELAY_COMMAND_NAME("test relay command");

class test_relay_command
    : public m::relay_command
{
public:
    virtual ~test_relay_command() GO_DEFAULT_DESTRUCTOR

        test_relay_command(const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command)
        : m::relay_command(TEST_RELAY_COMMAND_NAME, execute_command, can_execute_command, nullptr)
    {
    }

    virtual bool can_execute(const std::shared_ptr<m::command_parameters>& params)
    {
        return m::relay_command::can_execute(params);
    }

    virtual void execute(const std::shared_ptr<m::command_parameters>& params)
    {
        m::relay_command::execute(params);
    }
};

class test_relay_command_exection_context
{
public:
    typedef GO_TYPENAME go::signals::signal<std::function<void(const std::shared_ptr<m::command_interface>&)>> can_execute_changed_signal;

    virtual ~test_relay_command_exection_context() GO_DEFAULT_DESTRUCTOR

    test_relay_command_exection_context()
        : _allow_execute(false)
        , _executed(false)
    {
    }

    virtual bool can_execute(const std::shared_ptr<m::command_parameters>& /*params*/)
    {
        return _allow_execute && !_executed;
    }

    virtual void execute(const std::shared_ptr<m::command_parameters>& params)
    {
        if(can_execute(params))
        {
            _executed = true;
            if(!can_execute(params))
            {
                can_execute_changed(nullptr);
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
            can_execute_changed(nullptr);
        }
    }

    bool executed() const { return _executed; }

    can_execute_changed_signal can_execute_changed;

private:
    bool _allow_execute;
    bool _executed;
};

class test_relay_command_observer
{
public:
    virtual ~test_relay_command_observer() GO_DEFAULT_DESTRUCTOR

    test_relay_command_observer()
        : _number_of_can_execute_changes(0)
    {
    }

    void on_can_execute_changed(const std::shared_ptr<m::command_interface>& /*c*/)
    {
        ++_number_of_can_execute_changes;
    }

    unsigned int number_of_can_execute_changes() const { return _number_of_can_execute_changes; }

private:
    unsigned int _number_of_can_execute_changes;
};

TEST(relay_command_test_suite, test_relay_command)
{
    test_relay_command_exection_context command_exection_context;

    EXPECT_FALSE(command_exection_context.allow_execute());
    EXPECT_FALSE(command_exection_context.executed());
    EXPECT_FALSE(command_exection_context.can_execute(nullptr));

    std::shared_ptr<test_relay_command> command(new test_relay_command(std::bind(&test_relay_command_exection_context::execute, &command_exection_context, ph::_1),
        std::bind(&test_relay_command_exection_context::can_execute, &command_exection_context, ph::_1)));

    EXPECT_TRUE(command != nullptr);
    EXPECT_EQ(TEST_RELAY_COMMAND_NAME, command->command_name());
    EXPECT_FALSE(command_exection_context.allow_execute());
    EXPECT_FALSE(command_exection_context.executed());
    EXPECT_FALSE(command_exection_context.can_execute(nullptr));
    EXPECT_FALSE(command->can_execute(nullptr));
    EXPECT_TRUE(command->can_execute_changed.empty());

    test_relay_command_observer command_observer;

    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());

    command->can_execute_changed.connect(std::bind(&test_relay_command_observer::on_can_execute_changed, &command_observer, ph::_1));

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command_exection_context.allow_execute());
    EXPECT_FALSE(command_exection_context.executed());
    EXPECT_FALSE(command_exection_context.can_execute(nullptr));
    EXPECT_FALSE(command->can_execute(nullptr));

    command->execute(nullptr);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command_exection_context.allow_execute());
    EXPECT_FALSE(command_exection_context.executed());
    EXPECT_FALSE(command_exection_context.can_execute(nullptr));
    EXPECT_FALSE(command->can_execute(nullptr));

    command_exection_context.allow_execute(true);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command_exection_context.allow_execute());
    EXPECT_FALSE(command_exection_context.executed());
    EXPECT_TRUE(command_exection_context.can_execute(nullptr));
    EXPECT_TRUE(command->can_execute(nullptr));

    command->execute(nullptr);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command_exection_context.allow_execute());
    EXPECT_TRUE(command_exection_context.executed());
    EXPECT_FALSE(command_exection_context.can_execute(nullptr));
    EXPECT_FALSE(command->can_execute(nullptr));

    command->execute(nullptr);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command_exection_context.allow_execute());
    EXPECT_TRUE(command_exection_context.executed());
    EXPECT_FALSE(command_exection_context.can_execute(nullptr));
    EXPECT_FALSE(command->can_execute(nullptr));
}

}

#endif  // Required C++11 feature is not supported by this compiler
