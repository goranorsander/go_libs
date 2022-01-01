//
//  placebo_lockable_event_manager_test_suite.cpp
//
//  Copyright 2018-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#include <go/async/placebo_lockable.hpp>
#include <go_test/fleet_commander.hpp>
#include <go_test/observable_spaceship.hpp>
#include <go_test/spaceship_traits.hpp>

namespace
{

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT)
TEST(std_event_manager_placebo_lockable_test_suite, required_cpp11_feature_not_supported) {}
#else

// Test event_manager
using string_type = std::string;
using lockable_type = a::placebo_lockable;
using fleet_commander_type = go_test::fleet_commander<m::basic_event_manager<string_type, lockable_type>, p::property<string_type, lockable_type>, p::value_property<string_type, lockable_type>, pro::value_property<string_type, lockable_type>>;
using spaceship_type = go_test::bind_function::observable_spaceship<go_test::spaceship_traits<string_type, lockable_type>>;

const string_type fleet_commander_changed_event_type = go_test::spaceship_event_type<string_type>::fleet_commander_changed();

#define TEST_CASE_SHIPYARD \
    m::basic_event_manager<string_type, lockable_type>::ptr event_mgr = m::basic_event_manager<string_type, lockable_type>::create(); \
\
    fleet_commander_type::ptr fleet_cmdr = fleet_commander_type::create(event_mgr, s::create<string_type>("General Jan Dodonna"), s::create<string_type>("Battle of Yavin")); \
\
    std::shared_ptr<spaceship_type> ship1 = spaceship_type::create(s::create<string_type>("Millennium Falcon"), s::create<string_type>("Han Solo"), s::create<string_type>("General Jan Dodonna")); \
    std::shared_ptr<spaceship_type> ship2 = spaceship_type::create(s::create<string_type>("X-Wing Red Leader"), s::create<string_type>("Garven Dreis"), s::create<string_type>("General Jan Dodonna")); \
    std::shared_ptr<spaceship_type> ship3 = spaceship_type::create(s::create<string_type>("X-Wing Red Two"), s::create<string_type>("Wedge Antilles"), s::create<string_type>("General Jan Dodonna")); \
    std::shared_ptr<spaceship_type> ship4 = spaceship_type::create(s::create<string_type>("X-Wing Red Three"), s::create<string_type>("Biggs Darklighter"), s::create<string_type>("General Jan Dodonna")); \
    std::shared_ptr<spaceship_type> ship5 = spaceship_type::create(s::create<string_type>("X-Wing Red Four"), s::create<string_type>("John D. Branon"), s::create<string_type>("General Jan Dodonna")); \
    std::shared_ptr<spaceship_type> ship6 = spaceship_type::create(s::create<string_type>("X-Wing Red Five"), s::create<string_type>("Luke Skywalker"), s::create<string_type>("General Jan Dodonna")); \
    std::shared_ptr<spaceship_type> ship7 = spaceship_type::create(s::create<string_type>("Y-Wing Gold Leader"), s::create<string_type>("Jon 'Dutch' Vander"), s::create<string_type>("General Jan Dodonna")); \
    std::shared_ptr<spaceship_type> ship8 = spaceship_type::create(s::create<string_type>("Y-Wing Gold Two"), s::create<string_type>("Dex Tiree"), s::create<string_type>("General Jan Dodonna")); \
\
    event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship_type::on_fleet_commander_changed, ship1, std::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship_type::on_fleet_commander_changed, ship2, std::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship_type::on_fleet_commander_changed, ship3, std::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship_type::on_fleet_commander_changed, ship4, std::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship_type::on_fleet_commander_changed, ship5, std::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship_type::on_fleet_commander_changed, ship6, std::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship_type::on_fleet_commander_changed, ship7, std::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship_type::on_fleet_commander_changed, ship8, std::placeholders::_1));

TEST(std_event_manager_placebo_lockable_test_suite, test_command_manager)
{
    TEST_CASE_SHIPYARD

    // After connect
    EXPECT_EQ(std::string("General Jan Dodonna"), ship1->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship2->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship3->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship4->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship5->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship6->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship7->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship8->fleet_commander());

    // Change fleet commander
    fleet_cmdr->commander("Admiral Gial Ackbar");

    EXPECT_EQ(std::string("General Jan Dodonna"), ship1->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship2->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship3->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship4->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship5->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship6->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship7->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship8->fleet_commander());

    event_mgr->fire_events();

    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship1->fleet_commander());
    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship2->fleet_commander());
    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship3->fleet_commander());
    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship4->fleet_commander());
    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship5->fleet_commander());
    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship6->fleet_commander());
    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship7->fleet_commander());
    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship8->fleet_commander());
}

#endif  // Required C++11 feature is not supported by this compiler

}
