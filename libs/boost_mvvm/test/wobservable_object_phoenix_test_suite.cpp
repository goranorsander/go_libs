//
//  wobservable_object_phoenix_test_suite.cpp
//
//  Copyright 2015-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_BOOST_NO_BOOST_PHOENIX)
GO_BOOST_MESSAGE("Boost.Phoenix is not supported by this compiler")
TEST(boost_wobservable_object_phoenix_test_suite, boost_phoenix_not_supported) {}
#else

#include <go_boost_test/spaceship_observer.hpp>
#include <go_boost_test/spaceship_traits.hpp>

namespace
{

// Test observable_object
typedef std::wstring string_type;
typedef go_boost_test::phoenix::observable_spaceship<go_boost_test::wspaceship_traits<string_type>> spaceship_type;
typedef boost::shared_ptr<spaceship_type> spaceship_ptr;
typedef boost::weak_ptr<spaceship_type> spaceship_wptr;

typedef go_boost_test::spaceship_observer<spaceship_type> spaceship_observer;

TEST(boost_wobservable_object_phoenix_test_suite, test_wobservable_object)
{
    const string_type spaceship_name = s::create<string_type>("USS Voyager");

    spaceship_ptr m = spaceship_type::create(spaceship_name);
    spaceship_observer o;

    const bool connected = o.try_connect(m);

    // After connect
    EXPECT_EQ(connected, true);
    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->crew_complement.name()));
    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->name.name()));
    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->max_speed.name()));

    m->crew_complement = 141;

    // After one assignment
    EXPECT_EQ(1u, o.get_property_changed_count(spaceship_name, m->crew_complement.name()));
    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->name.name()));
    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->max_speed.name()));

    int pid = m->crew_complement;

    // After one access
    EXPECT_EQ(141, pid);
    EXPECT_EQ(1u, o.get_property_changed_count(spaceship_name, m->crew_complement.name()));
    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->name.name()));
    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->max_speed.name()));

    m->crew_complement = 141;
    pid = m->crew_complement;

    // After assignment of same value
    EXPECT_EQ(141, pid);
    EXPECT_EQ(1u, o.get_property_changed_count(spaceship_name, m->crew_complement.name()));
    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->name.name()));
    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->max_speed.name()));

    const bool disconnected = o.try_disconnect(m);

    // After disconnect
    EXPECT_EQ(disconnected, true);

    m->crew_complement = 147;
    pid = m->crew_complement;

    // After disconnect and assignment of new value
    EXPECT_EQ(147, pid);
    //EXPECT_EQ(1u, o.get_property_changed_count(spaceship_name, m->crew_complement.name()));
    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->name.name()));
    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->max_speed.name()));
}

}

#endif  // #if defined(GO_BOOST_NO_BOOST_PHOENIX)
