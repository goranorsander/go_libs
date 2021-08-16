//
//  placebo_lockable_observable_object_lambda_test_suite.cpp
//
//  Copyright 2018-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_observable_object_lambda_placebo_lockable_test_suite, required_cpp11_feature_not_supported) {}
#else

GO_MESSAGE("std_observable_object_lambda_placebo_lockable_test_suite is disabled")
TEST(std_observable_object_lambda_placebo_lockable_test_suite, test_suite_disabled) {}

//#include <go/async/placebo_lockable.hpp>
//#include <go_test/spaceship_observer.hpp>
//#include <go_test/spaceship_traits.hpp>
//
//namespace
//{
//
//// Test observable_object
//using string_type = std::string;
//using lockable_type = a::placebo_lockable;
//using spaceship_type = go_test::lambda::single_threaded::observable_spaceship<go_test::spaceship_traits<string_type, lockable_type>>;
//using spaceship_ptr = std::shared_ptr<spaceship_type>;
//using spaceship_wptr = std::weak_ptr<spaceship_type>;
//
//using spaceship_observer = go_test::spaceship_observer<spaceship_type>;
//
//TEST(std_observable_object_lambda_placebo_lockable_test_suite, test_observable_object)
//{
//    const string_type spaceship_name = s::create<string_type>("USS Voyager");
//
//    spaceship_ptr m = spaceship_type::create(spaceship_name);
//    spaceship_observer o;
//
//    const bool connected = o.try_connect(m);
//
//    // After connect
//    EXPECT_EQ(connected, true);
//    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->crew_complement.name()));
//    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->name.name()));
//    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->max_speed.name()));
//
//    m->crew_complement = 141;
//
//    // After one assignment
//    EXPECT_EQ(1u, o.get_property_changed_count(spaceship_name, m->crew_complement.name()));
//    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->name.name()));
//    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->max_speed.name()));
//
//    int pid = m->crew_complement;
//
//    // After one access
//    EXPECT_EQ(141, pid);
//    EXPECT_EQ(1u, o.get_property_changed_count(spaceship_name, m->crew_complement.name()));
//    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->name.name()));
//    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->max_speed.name()));
//
//    m->crew_complement = 141;
//    pid = m->crew_complement;
//
//    // After assignment of same value
//    EXPECT_EQ(141, pid);
//    EXPECT_EQ(1u, o.get_property_changed_count(spaceship_name, m->crew_complement.name()));
//    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->name.name()));
//    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->max_speed.name()));
//
//    const bool disconnected = o.try_disconnect(m);
//
//    // After disconnect
//    EXPECT_EQ(disconnected, true);
//
//    m->crew_complement = 147;
//    pid = m->crew_complement;
//
//    // After disconnect and assignment of new value
//    EXPECT_EQ(147, pid);
//    EXPECT_EQ(1u, o.get_property_changed_count(spaceship_name, m->crew_complement.name()));
//    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->name.name()));
//    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->max_speed.name()));
//}
//
//}

#endif  // #if defined(GO_NO_CXX11)
