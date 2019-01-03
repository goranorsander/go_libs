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
#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_basic_command_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>
#include <go/utility.hpp>

namespace m = go::mvvm;
namespace ph = std::placeholders;
namespace u = go::utility;
namespace us = go::utility::string;

namespace
{

const u::u8string TEST_COMMAND_NAME(us::create<u::u8string>("test command"));

class test_command
    : public m::basic_command_interface<u::u8string>
{
public:
    virtual ~test_command() GO_DEFAULT_DESTRUCTOR

    test_command()
        : m::basic_command_interface<u::u8string>(TEST_COMMAND_NAME, nullptr)
        , _allow_execute(false)
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

class test_command_observer
{
public:
    virtual ~test_command_observer() GO_DEFAULT_DESTRUCTOR

    test_command_observer()
        : _number_of_can_execute_changes(0)
    {
    }

    void on_can_execute_changed(const std::shared_ptr<m::basic_command_interface<u::u8string>>& /*c*/)
    {
        ++_number_of_can_execute_changes;
    }

    unsigned int number_of_can_execute_changes() const { return _number_of_can_execute_changes; }

private:
    unsigned int _number_of_can_execute_changes;
};

TEST(std_basic_command_test_suite, test_command)
{
    std::shared_ptr<test_command> command(new test_command());

    EXPECT_TRUE(command != nullptr);
    EXPECT_EQ(TEST_COMMAND_NAME, command->command_name());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));
    EXPECT_TRUE(command->can_execute_changed.empty());

    test_command_observer command_observer;

    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());

    command->can_execute_changed.connect(std::bind(&test_command_observer::on_can_execute_changed, &command_observer, ph::_1));

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));

    command->execute(nullptr);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));

    command->allow_execute(true);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(1, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_TRUE(command->can_execute(nullptr));

    command->execute(nullptr);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));

    command->execute(nullptr);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(nullptr));
}

}

#endif  // Required C++11 feature is not supported by this compiler
