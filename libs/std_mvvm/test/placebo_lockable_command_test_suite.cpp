//
//  placebo_lockable_command_test_suite.cpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#include <go_test/test_command.hpp>
#include <go_test/test_command_observer.hpp>
#include <go_test/test_command_traits.hpp>

namespace
{

GO_USING(string_type, std::string);
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
typedef go_test::test_command_traits<string_type, a::placebo_lockable> test_command_traits;
#else
using test_command_traits = go_test::test_command_traits<string_type, a::placebo_lockable>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
GO_USING(test_command, go_test::test_command<test_command_traits>);
GO_USING(test_command_observer, go_test::test_command_observer<test_command_traits>);

const std::string TEST_COMMAND_NAME(s::create<string_type>("test command"));

TEST(std_command_placebo_lockable_test_suite, test_command)
{
    std::shared_ptr<test_command> command(new test_command());

    EXPECT_TRUE(command != NULL);
    EXPECT_EQ(TEST_COMMAND_NAME, command->command_name());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));
    EXPECT_TRUE(command->can_execute_changed.empty());

    test_command_observer command_observer;

    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());

    command->can_execute_changed.connect(std::bind(&test_command_observer::on_can_execute_changed, &command_observer, std::placeholders::_1));

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));

    command->execute(mst::command_interface::command_parameters_type());

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(0u, command_observer.number_of_can_execute_changes());
    EXPECT_FALSE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));

    command->allow_execute(true);

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(1u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_FALSE(command->executed());
    EXPECT_TRUE(command->can_execute(mst::command_interface::command_parameters_type()));

    command->execute(mst::command_interface::command_parameters_type());

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));

    command->execute(mst::command_interface::command_parameters_type());

    EXPECT_FALSE(command->can_execute_changed.empty());
    EXPECT_EQ(2u, command_observer.number_of_can_execute_changes());
    EXPECT_TRUE(command->allow_execute());
    EXPECT_TRUE(command->executed());
    EXPECT_FALSE(command->can_execute(mst::command_interface::command_parameters_type()));
}

}
