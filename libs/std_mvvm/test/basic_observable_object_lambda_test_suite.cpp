//
//  basic_observable_object_lambda_test_suite.cpp
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

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_basic_observable_object_lambda_test_suite, required_cpp11_feature_not_supported) {}
#else

#include <go_test/spaceship_observer.hpp>
#include <go_test/spaceship_traits.hpp>

namespace
{

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT)
TEST(std_basic_observable_object_lambda_test_suite, required_cpp11_feature_not_supported) {}
#else

// Test observable_object
using string_type = s::u8string;
using spaceship_type = go_test::lambda::observable_spaceship<go_test::u8spaceship_traits<string_type>>;
using spaceship_ptr = std::shared_ptr<spaceship_type>;
using spaceship_wptr = std::weak_ptr<spaceship_type>;

using spaceship_observer = go_test::spaceship_observer<spaceship_type>;

TEST(std_basic_observable_object_lambda_test_suite, test_observable_object)
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
    EXPECT_EQ(1u, o.get_property_changed_count(spaceship_name, m->crew_complement.name()));
    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->name.name()));
    EXPECT_EQ(0u, o.get_property_changed_count(spaceship_name, m->max_speed.name()));
}

#endif  // Required C++11 feature is not supported by this compiler

}

#endif  // #if defined(GO_NO_CXX11)
