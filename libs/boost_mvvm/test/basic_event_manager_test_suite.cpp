//
//  basic_event_manager_test_suite.cpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#include <go_boost_test/fleet_commander.hpp>
#include <go_boost_test/observable_spaceship.hpp>
#include <go_boost_test/spaceship_traits.hpp>

namespace
{

// Test event_manager
typedef s::u8string string_type;
typedef go_boost_test::fleet_commander<m::basic_event_manager<string_type>, p::u8property<string_type>, p::value_u8property<string_type>, pro::value_u8property<string_type>> fleet_commander_type;
typedef go_boost_test::bind_function::observable_spaceship<go_boost_test::u8spaceship_traits<string_type>> spaceship_type;

const string_type fleet_commander_changed_event_type = go_boost_test::spaceship_event_type<string_type>::fleet_commander_changed();

#define TEST_CASE_SHIPYARD \
    m::basic_event_manager<string_type>::ptr event_mgr = m::basic_event_manager<string_type>::create(); \
\
    fleet_commander_type::ptr fleet_cmdr = fleet_commander_type::create(event_mgr, s::create<string_type>("General Jan Dodonna"), s::create<string_type>("Battle of Yavin")); \
\
    boost::shared_ptr<spaceship_type> ship1 = spaceship_type::create(s::create<string_type>("Millennium Falcon"), s::create<string_type>("Han Solo"), s::create<string_type>("General Jan Dodonna")); \
    boost::shared_ptr<spaceship_type> ship2 = spaceship_type::create(s::create<string_type>("X-Wing Red Leader"), s::create<string_type>("Garven Dreis"), s::create<string_type>("General Jan Dodonna")); \
    boost::shared_ptr<spaceship_type> ship3 = spaceship_type::create(s::create<string_type>("X-Wing Red Two"), s::create<string_type>("Wedge Antilles"), s::create<string_type>("General Jan Dodonna")); \
    boost::shared_ptr<spaceship_type> ship4 = spaceship_type::create(s::create<string_type>("X-Wing Red Three"), s::create<string_type>("Biggs Darklighter"), s::create<string_type>("General Jan Dodonna")); \
    boost::shared_ptr<spaceship_type> ship5 = spaceship_type::create(s::create<string_type>("X-Wing Red Four"), s::create<string_type>("John D. Branon"), s::create<string_type>("General Jan Dodonna")); \
    boost::shared_ptr<spaceship_type> ship6 = spaceship_type::create(s::create<string_type>("X-Wing Red Five"), s::create<string_type>("Luke Skywalker"), s::create<string_type>("General Jan Dodonna")); \
    boost::shared_ptr<spaceship_type> ship7 = spaceship_type::create(s::create<string_type>("Y-Wing Gold Leader"), s::create<string_type>("Jon 'Dutch' Vander"), s::create<string_type>("General Jan Dodonna")); \
    boost::shared_ptr<spaceship_type> ship8 = spaceship_type::create(s::create<string_type>("Y-Wing Gold Two"), s::create<string_type>("Dex Tiree"), s::create<string_type>("General Jan Dodonna")); \
\
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship1, boost::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship2, boost::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship3, boost::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship4, boost::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship5, boost::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship6, boost::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship7, boost::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship8, boost::placeholders::_1));

TEST(boost_basic_event_manager_test_suite, test_command_manager)
{
    TEST_CASE_SHIPYARD

    // After connect
    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship1->fleet_commander());
    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship2->fleet_commander());
    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship3->fleet_commander());
    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship4->fleet_commander());
    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship5->fleet_commander());
    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship6->fleet_commander());
    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship7->fleet_commander());
    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship8->fleet_commander());

    // Change fleet commander
    fleet_cmdr->commander(s::create<string_type>("Admiral Gial Ackbar"));

    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship1->fleet_commander());
    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship2->fleet_commander());
    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship3->fleet_commander());
    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship4->fleet_commander());
    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship5->fleet_commander());
    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship6->fleet_commander());
    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship7->fleet_commander());
    EXPECT_EQ(s::create<string_type>("General Jan Dodonna"), ship8->fleet_commander());

    event_mgr->fire_events();

    EXPECT_EQ(s::create<string_type>("Admiral Gial Ackbar"), ship1->fleet_commander());
    EXPECT_EQ(s::create<string_type>("Admiral Gial Ackbar"), ship2->fleet_commander());
    EXPECT_EQ(s::create<string_type>("Admiral Gial Ackbar"), ship3->fleet_commander());
    EXPECT_EQ(s::create<string_type>("Admiral Gial Ackbar"), ship4->fleet_commander());
    EXPECT_EQ(s::create<string_type>("Admiral Gial Ackbar"), ship5->fleet_commander());
    EXPECT_EQ(s::create<string_type>("Admiral Gial Ackbar"), ship6->fleet_commander());
    EXPECT_EQ(s::create<string_type>("Admiral Gial Ackbar"), ship7->fleet_commander());
    EXPECT_EQ(s::create<string_type>("Admiral Gial Ackbar"), ship8->fleet_commander());
}

}
