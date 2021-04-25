//
//  command_manager_test_suite.cpp
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

#include <go_boost_test/spaceship_observer.hpp>
#include <go_boost_test/spaceship_traits.hpp>

namespace
{

// Test command_manager
typedef std::string string_type;
typedef go_boost_test::bind_function::observable_spaceship<go_boost_test::spaceship_traits<string_type>> spaceship_type;
typedef boost::shared_ptr<spaceship_type> spaceship_ptr;
typedef boost::weak_ptr<spaceship_type> spaceship_wptr;

typedef go_boost_test::spaceship_observer<spaceship_type> spaceship_observer;

#define TEST_CASE_SHIPYARD \
    m::basic_command_manager<string_type>::ptr command_mgr = m::basic_command_manager<string_type>::create(); \
\
    spaceship_ptr ship1 = spaceship_type::create(s::create<string_type>("USS Enterprise"), s::create<string_type>("Captain James T Kirk")); \
    spaceship_ptr ship2 = spaceship_type::create(s::create<string_type>("Millennium Falcon"), s::create<string_type>("Han Solo")); \
    spaceship_ptr ship3 = spaceship_type::create(s::create<string_type>("Executor"), s::create<string_type>("Lord Darth Vader")); \
    spaceship_ptr ship4 = spaceship_type::create(s::create<string_type>("Battlestar Galactica"), s::create<string_type>("Admiral William Adama")); \
    spaceship_ptr ship5 = spaceship_type::create(s::create<string_type>("Serenity"), s::create<string_type>("Captain Malcolm 'Mal' Reynolds")); \
\
    boost::shared_ptr<spaceship_observer> observer = boost::make_shared<spaceship_observer>(); \
\
    observer->try_connect(ship1); \
    observer->try_connect(ship2); \
    observer->try_connect(ship3); \
    observer->try_connect(ship4); \
    observer->try_connect(ship5);

TEST(boost_command_manager_test_suite, test_command_manager)
{
    TEST_CASE_SHIPYARD

    // After connect
    EXPECT_EQ(false, ship1->at_warp_speed());
    EXPECT_EQ(false, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(false, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    // Give warp speed command to USS Enterprise
    command_mgr->post(ship1->warp_speed_command);

    EXPECT_EQ(false, ship1->at_warp_speed());
    EXPECT_EQ(false, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(false, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    command_mgr->execute_commands();

    EXPECT_EQ(true, ship1->at_warp_speed());
    EXPECT_EQ(false, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(false, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    // Give warp speed command to Millennium Falcon and Battlestar Galactica
    command_mgr->post(ship2->warp_speed_command);
    command_mgr->post(ship4->warp_speed_command);

    EXPECT_EQ(true, ship1->at_warp_speed());
    EXPECT_EQ(false, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(false, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    command_mgr->execute_commands();

    EXPECT_EQ(true, ship1->at_warp_speed());
    EXPECT_EQ(true, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(true, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    // Give impulse speed command to USS Enterprise
    command_mgr->post(ship1->impulse_speed_command);

    EXPECT_EQ(true, ship1->at_warp_speed());
    EXPECT_EQ(false, ship1->at_impulse_speed());
    EXPECT_EQ(true, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(true, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    command_mgr->execute_commands();

    EXPECT_EQ(false, ship1->at_warp_speed());
    EXPECT_EQ(true, ship1->at_impulse_speed());
    EXPECT_EQ(true, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(true, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());
}

TEST(boost_command_manager_test_suite, test_spaceship_observer)
{
    TEST_CASE_SHIPYARD

    // Verify first captain
    EXPECT_EQ(true, ship1->captain() == s::create<string_type>("Captain James T Kirk"));
    EXPECT_EQ(true, ship2->captain() == s::create<string_type>("Han Solo"));
    EXPECT_EQ(true, ship3->captain() == s::create<string_type>("Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain() == s::create<string_type>("Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain() == s::create<string_type>("Captain Malcolm 'Mal' Reynolds"));

    // Verify initial 'on property changed' count
    EXPECT_EQ(0u, observer->get_property_changed_count(s::create<string_type>("USS Enterprise"), s::create<string_type>("captain")));
    EXPECT_EQ(0u, observer->get_property_changed_count(s::create<string_type>("Millennium Falcon"), s::create<string_type>("captain")));
    EXPECT_EQ(0u, observer->get_property_changed_count(s::create<string_type>("Executor"), s::create<string_type>("captain")));
    EXPECT_EQ(0u, observer->get_property_changed_count(s::create<string_type>("Battlestar Galactica"), s::create<string_type>("captain")));
    EXPECT_EQ(0u, observer->get_property_changed_count(s::create<string_type>("Serenity"), s::create<string_type>("captain")));

    // Give Mr Spock command of USS Enterprise
    ship1->captain = s::create<string_type>("Mr Spock");

    EXPECT_EQ(true, ship1->captain() == s::create<string_type>("Mr Spock"));
    EXPECT_EQ(true, ship2->captain() == s::create<string_type>("Han Solo"));
    EXPECT_EQ(true, ship3->captain() == s::create<string_type>("Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain() == s::create<string_type>("Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain() == s::create<string_type>("Captain Malcolm 'Mal' Reynolds"));

    EXPECT_EQ(1u, observer->get_property_changed_count(s::create<string_type>("USS Enterprise"), s::create<string_type>("captain")));
    EXPECT_EQ(0u, observer->get_property_changed_count(s::create<string_type>("Millennium Falcon"), s::create<string_type>("captain")));
    EXPECT_EQ(0u, observer->get_property_changed_count(s::create<string_type>("Executor"), s::create<string_type>("captain")));
    EXPECT_EQ(0u, observer->get_property_changed_count(s::create<string_type>("Battlestar Galactica"), s::create<string_type>("captain")));
    EXPECT_EQ(0u, observer->get_property_changed_count(s::create<string_type>("Serenity"), s::create<string_type>("captain")));

    // Return command of USS Enterprise to Captain Kirk
    ship1->captain = s::create<string_type>("Captain James T Kirk");

    EXPECT_EQ(true, ship1->captain() == s::create<string_type>("Captain James T Kirk"));
    EXPECT_EQ(true, ship2->captain() == s::create<string_type>("Han Solo"));
    EXPECT_EQ(true, ship3->captain() == s::create<string_type>("Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain() == s::create<string_type>("Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain() == s::create<string_type>("Captain Malcolm 'Mal' Reynolds"));

    EXPECT_EQ(2u, observer->get_property_changed_count(s::create<string_type>("USS Enterprise"), s::create<string_type>("captain")));
    EXPECT_EQ(0u, observer->get_property_changed_count(s::create<string_type>("Millennium Falcon"), s::create<string_type>("captain")));
    EXPECT_EQ(0u, observer->get_property_changed_count(s::create<string_type>("Executor"), s::create<string_type>("captain")));
    EXPECT_EQ(0u, observer->get_property_changed_count(s::create<string_type>("Battlestar Galactica"), s::create<string_type>("captain")));
    EXPECT_EQ(0u, observer->get_property_changed_count(s::create<string_type>("Serenity"), s::create<string_type>("captain")));
}

}
