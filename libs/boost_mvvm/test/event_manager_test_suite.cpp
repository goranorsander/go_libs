//
//  event_manager_test_suite.cpp
//
//  Copyright 2015-2021 Göran Orsander
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
typedef std::string string_type;
typedef go_boost_test::fleet_commander<m::basic_event_manager<string_type>, p::property<string_type>, p::value_property<string_type>, pro::value_property<string_type>> fleet_commander_type;
typedef go_boost_test::bind_function::observable_spaceship<go_boost_test::spaceship_traits<string_type>> spaceship_type;

const string_type fleet_commander_changed_event_type = go_boost_test::spaceship_event_type<string_type>::fleet_commander_changed();

#define TEST_CASE_SHIPYARD \
    m::event_manager::ptr event_mgr = m::event_manager::create(); \
\
    fleet_commander_type::ptr fleet_cmdr = fleet_commander_type::create(event_mgr, "General Jan Dodonna", "Battle of Yavin"); \
\
    boost::shared_ptr<spaceship_type> ship1 = spaceship_type::create("Millennium Falcon", "Han Solo", "General Jan Dodonna"); \
    boost::shared_ptr<spaceship_type> ship2 = spaceship_type::create("X-Wing Red Leader", "Garven Dreis", "General Jan Dodonna"); \
    boost::shared_ptr<spaceship_type> ship3 = spaceship_type::create("X-Wing Red Two", "Wedge Antilles", "General Jan Dodonna"); \
    boost::shared_ptr<spaceship_type> ship4 = spaceship_type::create("X-Wing Red Three", "Biggs Darklighter", "General Jan Dodonna"); \
    boost::shared_ptr<spaceship_type> ship5 = spaceship_type::create("X-Wing Red Four", "John D. Branon", "General Jan Dodonna"); \
    boost::shared_ptr<spaceship_type> ship6 = spaceship_type::create("X-Wing Red Five", "Luke Skywalker", "General Jan Dodonna"); \
    boost::shared_ptr<spaceship_type> ship7 = spaceship_type::create("Y-Wing Gold Leader", "Jon 'Dutch' Vander", "General Jan Dodonna"); \
    boost::shared_ptr<spaceship_type> ship8 = spaceship_type::create("Y-Wing Gold Two", "Dex Tiree", "General Jan Dodonna"); \
\
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship1, boost::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship2, boost::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship3, boost::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship4, boost::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship5, boost::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship6, boost::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship7, boost::placeholders::_1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship_type::on_fleet_commander_changed, ship8, boost::placeholders::_1));

TEST(boost_event_manager_test_suite, test_command_manager)
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

}
