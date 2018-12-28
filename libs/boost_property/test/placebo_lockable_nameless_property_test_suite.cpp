//
//  placebo_lockable_nameless_property_test_suite.cpp
//
//  Copyright 2018 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go_boost/config.hpp>

#include <boost/bind.hpp>

#include <go_boost/property.hpp>
#include <go_boost/utility.hpp>

namespace p = go_boost::property;
namespace np = go_boost::property::nameless;
namespace roap = go_boost::property::nameless::read_only;
namespace u = go_boost::utility;
namespace woap = go_boost::property::nameless::write_only;

namespace
{

// Test value_property
class spaceship
{
public:
    np::value_property<int, u::placebo_lockable> crew_complement;
    np::value_property<double, u::placebo_lockable> max_speed;
    np::value_property<std::string, u::placebo_lockable> name;

     spaceship()
        : crew_complement(1012)
        , max_speed(9.8)
        , name(std::string("USS Enterprise (NCC-1701-D)"))
    {
    }

    explicit spaceship(const spaceship& v)
        : crew_complement(v.crew_complement)
        , max_speed(v.max_speed)
        , name(v.name)
    {
    }

    spaceship& operator=(const spaceship& v)
    {
        crew_complement = v.crew_complement;
        max_speed = v.max_speed;
        name = v.name;
        return *this;
    }
};

TEST(boost_nameless_property_placebo_lockable_test_suite, value_properties)
{
    spaceship s;

    // Method oriented get
    EXPECT_EQ(1012, s.crew_complement());
    EXPECT_EQ(9.8, s.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s.name());

    // Cast operator oriented get
    EXPECT_EQ(1012, static_cast<int>(s.crew_complement));
    EXPECT_EQ(9.8, static_cast<double>(s.max_speed));
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), static_cast<std::string>(s.name));

    // Implicit cast oriented get
    EXPECT_TRUE(1012 == s.crew_complement);
    EXPECT_TRUE(9.8 == s.max_speed);
    EXPECT_TRUE(std::string("USS Enterprise (NCC-1701-D)") == s.name);

    // Traditional get
    EXPECT_EQ(1012, s.crew_complement.get());
    EXPECT_EQ(9.8, s.max_speed.get());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s.name.get());

    // Method oriented set
    s.crew_complement(647);
    s.max_speed(9.975);
    s.name("USS Enterprise (NCC-1701-E)");
    EXPECT_EQ(647, s.crew_complement());
    EXPECT_EQ(9.975, s.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-E)"), s.name());

    // Assign operator oriented set
    s.crew_complement = 430;
    s.max_speed = 9.0;
    s.name = std::string("USS Enterprise (NCC-1701)");
    EXPECT_EQ(430, s.crew_complement);
    EXPECT_EQ(9.0, s.max_speed);
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701)"), s.name());

    // Traditional set
    s.crew_complement.set(574);
    s.max_speed.set(9.7);
    s.name.set(std::string("USS Enterprise (NCC-1701-B)"));
    EXPECT_EQ(574, s.crew_complement.get());
    EXPECT_EQ(9.7, s.max_speed.get());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-B)"), s.name());

    // Copy construction
    spaceship s2(s);
    EXPECT_EQ(574, s2.crew_complement());
    EXPECT_EQ(9.7, s2.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-B)"), s2.name());
}

// Test read_only::value_property
class read_only_spaceship
{
public:
    roap::value_property<int, u::placebo_lockable> crew_complement;
    roap::value_property<double, u::placebo_lockable> max_speed;
    roap::value_property<std::string, u::placebo_lockable> name;

    read_only_spaceship()
        : crew_complement(1012)
        , max_speed(9.8)
        , name(std::string("USS Enterprise (NCC-1701-D)"))
    {
    }
};

TEST(boost_nameless_property_placebo_lockable_test_suite, read_only_value_properties)
{
    read_only_spaceship s;

    // Method oriented get
    EXPECT_EQ(1012, s.crew_complement());
    EXPECT_EQ(9.8, s.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s.name());

    // Cast operator oriented get
    EXPECT_EQ(1012, static_cast<int>(s.crew_complement));
    EXPECT_EQ(9.8, static_cast<double>(s.max_speed));
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), static_cast<std::string>(s.name));

    // Implicit cast oriented get
    EXPECT_TRUE(1012 == s.crew_complement);
    EXPECT_TRUE(9.8 == s.max_speed);
    EXPECT_TRUE(std::string("USS Enterprise (NCC-1701-D)") == s.name);

    // Traditional get
    EXPECT_EQ(1012, s.crew_complement.get());
    EXPECT_EQ(9.8, s.max_speed.get());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s.name.get());

    // Copy construction
    read_only_spaceship s2(s);
    EXPECT_EQ(1012, s2.crew_complement());
    EXPECT_EQ(9.8, s2.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s2.name());
}

// Test write_only::value_property
class write_only_spaceship
{
public:
    woap::value_property<int, u::placebo_lockable> crew_complement;
    woap::value_property<double, u::placebo_lockable> max_speed;
    woap::value_property<std::string, u::placebo_lockable> name;

    write_only_spaceship()
        : crew_complement(1012)
        , max_speed(9.8)
        , name(std::string("USS Enterprise (NCC-1701-D)"))
    {
    }
};

TEST(boost_nameless_property_placebo_lockable_test_suite, write_only_value_properties)
{
    write_only_spaceship s;

    // Method oriented set
    s.crew_complement(647);
    s.max_speed(9.975);
    s.name("USS Enterprise (NCC-1701-E)");

    // Assign operator oriented set
    s.crew_complement = 430;
    s.max_speed = 9.0;
    s.name = std::string("USS Enterprise (NCC-1701)");

    // Traditional set
    s.crew_complement.set(574);
    s.max_speed.set(9.7);
    s.name.set(std::string("USS Enterprise (NCC-1701-B)"));

    // Copy construction
    write_only_spaceship s2(s);
}

// Test reference_property
class reference_spaceship
{
public:
    np::reference_property<int, u::placebo_lockable> crew_complement;
    np::reference_property<double, u::placebo_lockable> max_speed;
    np::reference_property<std::string, u::placebo_lockable> name;

    reference_spaceship()
        : crew_complement()
        , max_speed()
        , name()
    {
    }
};

TEST(boost_nameless_property_placebo_lockable_test_suite, reference_properties)
{
    reference_spaceship s;

    // Verify default values
    EXPECT_TRUE(s.crew_complement.empty() == true);
    EXPECT_TRUE(s.max_speed.empty() == true);
    EXPECT_TRUE(s.name.empty() == true);

    // Verify unbound references
    EXPECT_THROW(s.crew_complement.get(), p::exception);
    EXPECT_THROW(s.max_speed.get(), p::exception);
    EXPECT_THROW(s.name.get(), p::exception);
    EXPECT_THROW(s.crew_complement.set(0), p::exception);
    EXPECT_THROW(s.max_speed.set(0.0), p::exception);
    EXPECT_THROW(s.name.set(""), p::exception);

    // Bind references
    int store_crew_complement = 1012;
    double store_max_speed = 9.8;
    std::string store_name("USS Enterprise (NCC-1701-D)");
    s.crew_complement.bind(store_crew_complement);
    s.max_speed.bind(store_max_speed);
    s.name.bind(store_name);
    EXPECT_TRUE(s.crew_complement.empty() == false);
    EXPECT_TRUE(s.max_speed.empty() == false);
    EXPECT_TRUE(s.name.empty() == false);

    // Verify storage values
    EXPECT_EQ(1012, store_crew_complement);
    EXPECT_EQ(9.8, store_max_speed);
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), store_name);

    // Method oriented get
    EXPECT_EQ(1012, s.crew_complement());
    EXPECT_EQ(9.8, s.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s.name());

    // Cast operator oriented get
    EXPECT_EQ(1012, static_cast<int>(s.crew_complement));
    EXPECT_EQ(9.8, static_cast<double>(s.max_speed));
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), static_cast<std::string>(s.name));

    // Implicit cast oriented get
    EXPECT_TRUE(1012 == s.crew_complement);
    EXPECT_TRUE(9.8 == s.max_speed);
    EXPECT_TRUE(std::string("USS Enterprise (NCC-1701-D)") == s.name);

    // Traditional get
    EXPECT_EQ(1012, s.crew_complement.get());
    EXPECT_EQ(9.8, s.max_speed.get());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s.name.get());

    // Verify storage values
    EXPECT_EQ(1012, store_crew_complement);
    EXPECT_EQ(9.8, store_max_speed);
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), store_name);

    // Method oriented set
    const int s_cc_2 = 647;
    const double s_ms_2 = 9.975;
    const std::string s_n_2("USS Enterprise (NCC-1701-E)");
    s.crew_complement(s_cc_2);
    s.max_speed(s_ms_2);
    s.name(s_n_2);
    EXPECT_EQ(647, s.crew_complement());
    EXPECT_EQ(9.975, s.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-E)"), s.name());

    // Assign operator oriented set
    const int s_cc_3 = 430;
    const double s_ms_3 = 9.0;
    const std::string s_n_3("USS Enterprise (NCC-1701)");
    s.crew_complement = s_cc_3;
    s.max_speed = s_ms_3;
    s.name = s_n_3;
    EXPECT_EQ(430, s.crew_complement);
    EXPECT_EQ(9.0, s.max_speed);
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701)"), s.name());

    // Traditional set
    const int s_cc_4 = 574;
    const double s_ms_4 = 9.7;
    const std::string s_n_4("USS Enterprise (NCC-1701-B)");
    s.crew_complement.set(s_cc_4);
    s.max_speed.set(s_ms_4);
    s.name.set(s_n_4);
    EXPECT_EQ(574, s.crew_complement.get());
    EXPECT_EQ(9.7, s.max_speed.get());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-B)"), s.name());

    // Assign referenced object oriented set
    store_crew_complement = 600;
    store_max_speed = 9.75;
    store_name = "USS Enterprise (NCC-1701-C)";
    EXPECT_EQ(600, store_crew_complement);
    EXPECT_EQ(9.75, store_max_speed);
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-C)"), store_name);
    EXPECT_EQ(600, s.crew_complement.get());
    EXPECT_EQ(9.75, s.max_speed.get());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-C)"), s.name());

    // Copy construction
    reference_spaceship s2(s);
    EXPECT_EQ(600, s2.crew_complement());
    EXPECT_EQ(9.75, s2.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-C)"), s2.name());

    // Reset
    s.crew_complement.reset();
    s.max_speed.reset();
    s.name.reset();
    EXPECT_TRUE(s.crew_complement.empty() == true);
    EXPECT_TRUE(s.max_speed.empty() == true);
    EXPECT_TRUE(s.name.empty() == true);
    EXPECT_TRUE(s2.crew_complement.empty() == false);
    EXPECT_TRUE(s2.max_speed.empty() == false);
    EXPECT_TRUE(s2.name.empty() == false);
}

// Test read_only::reference_property
class read_only_reference_spaceship
{
public:
    roap::reference_property<int, u::placebo_lockable> crew_complement;
    roap::reference_property<double, u::placebo_lockable> max_speed;
    roap::reference_property<std::string, u::placebo_lockable> name;

    read_only_reference_spaceship(const int& _crew_complement, const double& _max_speed, const std::string& _name)
        : crew_complement(_crew_complement)
        , max_speed(_max_speed)
        , name(_name)
    {
    }
};

TEST(boost_nameless_property_placebo_lockable_test_suite, read_only_reference_properties)
{
    int store_crew_complement = 1012;
    double store_max_speed = 9.8;
    std::string store_name("USS Enterprise (NCC-1701-D)");

    read_only_reference_spaceship s(store_crew_complement, store_max_speed, store_name);

    // Verify storage values
    EXPECT_EQ(1012, store_crew_complement);
    EXPECT_EQ(9.8, store_max_speed);
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), store_name);

    // Verify default values
    EXPECT_TRUE(s.crew_complement.empty() == false);
    EXPECT_TRUE(s.max_speed.empty() == false);
    EXPECT_TRUE(s.name.empty() == false);

    // Method oriented get
    EXPECT_EQ(1012, s.crew_complement());
    EXPECT_EQ(9.8, s.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s.name());

    // Cast operator oriented get
    EXPECT_EQ(1012, static_cast<int>(s.crew_complement));
    EXPECT_EQ(9.8, static_cast<double>(s.max_speed));
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), static_cast<std::string>(s.name));

    // Implicit cast oriented get
    EXPECT_TRUE(1012 == s.crew_complement);
    EXPECT_TRUE(9.8 == s.max_speed);
    EXPECT_TRUE(std::string("USS Enterprise (NCC-1701-D)") == s.name);

    // Traditional get
    EXPECT_EQ(1012, s.crew_complement.get());
    EXPECT_EQ(9.8, s.max_speed.get());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s.name.get());

    // Verify storage values
    EXPECT_EQ(1012, store_crew_complement);
    EXPECT_EQ(9.8, store_max_speed);
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), store_name);

    // Copy construction
    read_only_reference_spaceship s2(s);
    EXPECT_TRUE(s2.crew_complement.empty() == false);
    EXPECT_TRUE(s2.max_speed.empty() == false);
    EXPECT_TRUE(s2.name.empty() == false);
    EXPECT_EQ(1012, s2.crew_complement());
    EXPECT_EQ(9.8, s2.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s2.name());

    // Verify storage values
    EXPECT_EQ(1012, store_crew_complement);
    EXPECT_EQ(9.8, store_max_speed);
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), store_name);

    // Assign referenced object oriented set
    store_crew_complement = 600;
    store_max_speed = 9.75;
    store_name = "USS Enterprise (NCC-1701-C)";
    EXPECT_EQ(600, store_crew_complement);
    EXPECT_EQ(9.75, store_max_speed);
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-C)"), store_name);
    EXPECT_EQ(600, s.crew_complement.get());
    EXPECT_EQ(9.75, s.max_speed.get());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-C)"), s.name());

    // Reset
    s.crew_complement.reset();
    s.max_speed.reset();
    s.name.reset();
    EXPECT_TRUE(s.crew_complement.empty() == true);
    EXPECT_TRUE(s.max_speed.empty() == true);
    EXPECT_TRUE(s.name.empty() == true);
    EXPECT_TRUE(s2.crew_complement.empty() == false);
    EXPECT_TRUE(s2.max_speed.empty() == false);
    EXPECT_TRUE(s2.name.empty() == false);
}

// Test write_only::reference_property
class write_only_reference_spaceship
{
public:
    woap::reference_property<int, u::placebo_lockable> crew_complement;
    woap::reference_property<double, u::placebo_lockable> max_speed;
    woap::reference_property<std::string, u::placebo_lockable> name;

    write_only_reference_spaceship()
        : crew_complement()
        , max_speed()
        , name()
    {
    }
};

TEST(boost_nameless_property_placebo_lockable_test_suite, write_only_reference_properties)
{
    int store_crew_complement = 1012;
    double store_max_speed = 9.8;
    std::string store_name("USS Enterprise (NCC-1701-D)");

    read_only_reference_spaceship s(store_crew_complement, store_max_speed, store_name);

    // Verify storage values
    EXPECT_EQ(1012, store_crew_complement);
    EXPECT_EQ(9.8, store_max_speed);
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), store_name);

    // Verify default values
    EXPECT_TRUE(s.crew_complement.empty() == false);
    EXPECT_TRUE(s.max_speed.empty() == false);
    EXPECT_TRUE(s.name.empty() == false);

    // Method oriented get
    EXPECT_EQ(1012, s.crew_complement());
    EXPECT_EQ(9.8, s.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s.name());

    // Cast operator oriented get
    EXPECT_EQ(1012, static_cast<int>(s.crew_complement));
    EXPECT_EQ(9.8, static_cast<double>(s.max_speed));
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), static_cast<std::string>(s.name));

    // Implicit cast oriented get
    EXPECT_TRUE(1012 == s.crew_complement);
    EXPECT_TRUE(9.8 == s.max_speed);
    EXPECT_TRUE(std::string("USS Enterprise (NCC-1701-D)") == s.name);

    // Traditional get
    EXPECT_EQ(1012, s.crew_complement.get());
    EXPECT_EQ(9.8, s.max_speed.get());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s.name.get());

    // Verify storage values
    EXPECT_EQ(1012, store_crew_complement);
    EXPECT_EQ(9.8, store_max_speed);
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), store_name);

    // Copy construction
    read_only_reference_spaceship s2(s);
    EXPECT_TRUE(s2.crew_complement.empty() == false);
    EXPECT_TRUE(s2.max_speed.empty() == false);
    EXPECT_TRUE(s2.name.empty() == false);
    EXPECT_EQ(1012, s2.crew_complement());
    EXPECT_EQ(9.8, s2.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s2.name());

    // Verify storage values
    EXPECT_EQ(1012, store_crew_complement);
    EXPECT_EQ(9.8, store_max_speed);
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), store_name);

    // Assign referenced object oriented set
    store_crew_complement = 600;
    store_max_speed = 9.75;
    store_name = "USS Enterprise (NCC-1701-C)";
    EXPECT_EQ(600, store_crew_complement);
    EXPECT_EQ(9.75, store_max_speed);
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-C)"), store_name);
    EXPECT_EQ(600, s.crew_complement.get());
    EXPECT_EQ(9.75, s.max_speed.get());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-C)"), s.name());

    // Reset
    s.crew_complement.reset();
    s.max_speed.reset();
    s.name.reset();
    EXPECT_TRUE(s.crew_complement.empty() == true);
    EXPECT_TRUE(s.max_speed.empty() == true);
    EXPECT_TRUE(s.name.empty() == true);
    EXPECT_TRUE(s2.crew_complement.empty() == false);
    EXPECT_TRUE(s2.max_speed.empty() == false);
    EXPECT_TRUE(s2.name.empty() == false);
}

// Test property
class armament
{
    // Spaceship armament, not modifyable, provided by third-party
public:
    virtual ~armament() GO_BOOST_DEFAULT_DESTRUCTOR

    armament()
        : _phaser_arrays(0)
    {
    }

    void set_phaser_arrays(int phaser_arrays)
    {
        _phaser_arrays = phaser_arrays;
    }

    int get_phaser_arrays() const
    {
        return _phaser_arrays;
    }

private:
    int _phaser_arrays;
};

class armed_spaceship
    : public spaceship
{
public:
    np::property<int, u::placebo_lockable> phaser_arrays;

    armed_spaceship()
        : spaceship()
        , phaser_arrays()
        , _armament()
    {
        bind_properties();
    }

    armed_spaceship(const armed_spaceship& v)
        : spaceship(v)
        , phaser_arrays(v.phaser_arrays)
        , _armament(v._armament)
    {
        bind_properties();
    }

    armed_spaceship& operator=(const armed_spaceship& v)
    {
        spaceship::operator=(v);
        phaser_arrays = v.phaser_arrays;
        _armament = v._armament;
        bind_properties();
        return *this;
    }

private:
    void bind_properties()
    {
        phaser_arrays.getter(boost::bind(&armament::get_phaser_arrays, &_armament));
        phaser_arrays.setter(boost::bind(&armament::set_phaser_arrays, &_armament, _1));
    }

private:
    armament _armament;
};

TEST(boost_nameless_property_placebo_lockable_test_suite, proxy_properties)
{
    armed_spaceship s;

    // INHERITED PROPERTIES

    // Method oriented get
    EXPECT_EQ(1012, s.crew_complement());
    EXPECT_EQ(9.8, s.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s.name());

    // Cast operator oriented get
    EXPECT_EQ(1012, static_cast<int>(s.crew_complement));
    EXPECT_EQ(9.8, static_cast<double>(s.max_speed));
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), static_cast<std::string>(s.name));

    // Implicit cast oriented get
    EXPECT_TRUE(1012 == s.crew_complement);
    EXPECT_TRUE(9.8 == s.max_speed);
    EXPECT_TRUE(std::string("USS Enterprise (NCC-1701-D)") == s.name);

    // Traditional get
    EXPECT_EQ(1012, s.crew_complement.get());
    EXPECT_EQ(9.8, s.max_speed.get());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s.name.get());

    // Method oriented set
    s.crew_complement(647);
    s.max_speed(9.975);
    s.name("USS Enterprise (NCC-1701-E)");
    EXPECT_EQ(647, s.crew_complement());
    EXPECT_EQ(9.975, s.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-E)"), s.name());

    // Assign operator oriented set
    s.crew_complement = 430;
    s.max_speed = 9.0;
    s.name = std::string("USS Enterprise (NCC-1701)");
    EXPECT_EQ(430, s.crew_complement);
    EXPECT_EQ(9.0, s.max_speed);
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701)"), s.name());

    // Traditional set
    s.crew_complement.set(574);
    s.max_speed.set(9.7);
    s.name.set(std::string("USS Enterprise (NCC-1701-B)"));
    EXPECT_EQ(574, s.crew_complement.get());
    EXPECT_EQ(9.7, s.max_speed.get());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-B)"), s.name());

    // Copy construction
    spaceship s2(s);
    EXPECT_EQ(574, s2.crew_complement());
    EXPECT_EQ(9.7, s2.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-B)"), s2.name());

    // PROXY

    s.phaser_arrays(8);

    // Method oriented get
    EXPECT_EQ(8, s.phaser_arrays());

    // Cast operator oriented get
    EXPECT_EQ(8, static_cast<int>(s.phaser_arrays));

    // Implicit cast oriented get
    EXPECT_TRUE(8 == s.phaser_arrays);

    // Traditional get
    EXPECT_EQ(8, s.phaser_arrays.get());

    // Method oriented set
    s.phaser_arrays(10);
    EXPECT_EQ(10, s.phaser_arrays());

    // Assign operator oriented set
    s.phaser_arrays = 12;
    EXPECT_EQ(12, s.phaser_arrays);

    // Traditional set
    s.phaser_arrays.set(14);
    EXPECT_EQ(14, s.phaser_arrays.get());

    // Copy construction
    armed_spaceship s3(s);
    EXPECT_EQ(574, s3.crew_complement());
    EXPECT_EQ(9.7, s3.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-B)"), s3.name());
    EXPECT_EQ(14, s3.phaser_arrays());
}

// Test read_only::property
class read_only_armed_spaceship
    : public read_only_spaceship
{
public:
    roap::property<int, u::placebo_lockable> phaser_arrays;

    read_only_armed_spaceship()
        : read_only_spaceship()
        , phaser_arrays()
        , _armament()
    {
        _armament.set_phaser_arrays(8);
        bind_properties();
    }

    read_only_armed_spaceship(const read_only_armed_spaceship& v)
        : read_only_spaceship(v)
        , phaser_arrays(v.phaser_arrays)
        , _armament(v._armament)
    {
        bind_properties();
    }

private:
    void bind_properties()
    {
        phaser_arrays.getter(boost::bind(&armament::get_phaser_arrays, &_armament));
    }

private:
    armament _armament;
};

TEST(boost_nameless_property_placebo_lockable_test_suite, read_only_proxy_properties)
{
    read_only_armed_spaceship s;

    // INHERITED PROPERTIES

    // Method oriented get
    EXPECT_EQ(1012, s.crew_complement());
    EXPECT_EQ(9.8, s.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s.name());

    // Cast operator oriented get
    EXPECT_EQ(1012, static_cast<int>(s.crew_complement));
    EXPECT_EQ(9.8, static_cast<double>(s.max_speed));
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), static_cast<std::string>(s.name));

    // Implicit cast oriented get
    EXPECT_TRUE(1012 == s.crew_complement);
    EXPECT_TRUE(9.8 == s.max_speed);
    EXPECT_TRUE(std::string("USS Enterprise (NCC-1701-D)") == s.name);

    // Traditional get
    EXPECT_EQ(1012, s.crew_complement.get());
    EXPECT_EQ(9.8, s.max_speed.get());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s.name.get());

    // Copy construction
    read_only_spaceship s2(s);
    EXPECT_EQ(1012, s2.crew_complement());
    EXPECT_EQ(9.8, s2.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s2.name());

    // PROXY

    // Method oriented get
    EXPECT_EQ(8, s.phaser_arrays());

    // Cast operator oriented get
    EXPECT_EQ(8, static_cast<int>(s.phaser_arrays));

    // Implicit cast oriented get
    EXPECT_TRUE(8 == s.phaser_arrays);

    // Traditional get
    EXPECT_EQ(8, s.phaser_arrays.get());

    // Copy construction
    read_only_armed_spaceship s3(s);
    EXPECT_EQ(1012, s3.crew_complement());
    EXPECT_EQ(9.8, s3.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s3.name());
    EXPECT_EQ(8, s3.phaser_arrays());
}

// Test write_only::property
class write_only_armed_spaceship
    : public write_only_spaceship
{
public:
    woap::property<int, u::placebo_lockable> phaser_arrays;

    write_only_armed_spaceship()
        : write_only_spaceship()
        , phaser_arrays()
        , _armament()
    {
        bind_properties();
    }

    write_only_armed_spaceship(const write_only_armed_spaceship& v)
        : write_only_spaceship(v)
        , phaser_arrays(v.phaser_arrays)
        , _armament(v._armament)
    {
        bind_properties();
    }

private:
    void bind_properties()
    {
        phaser_arrays.setter(boost::bind(&armament::set_phaser_arrays, &_armament, _1));
    }

private:
    armament _armament;
};

TEST(boost_nameless_property_placebo_lockable_test_suite, write_only_proxy_properties)
{
    write_only_armed_spaceship s;

    // INHERITED PROPERTIES

    // Method oriented set
    s.crew_complement(647);
    s.max_speed(9.975);
    s.name("USS Enterprise (NCC-1701-E)");

    // Assign operator oriented set
    s.crew_complement = 430;
    s.max_speed = 9.0;
    s.name = std::string("USS Enterprise (NCC-1701)");

    // Traditional set
    s.crew_complement.set(574);
    s.max_speed.set(9.7);
    s.name.set(std::string("USS Enterprise (NCC-1701-B)"));

    // Copy construction
    write_only_spaceship s2(s);

    // PROXY

    // Method oriented set
    s.phaser_arrays(10);

    // Assign operator oriented set
    s.phaser_arrays = 12;

    // Traditional set
    s.phaser_arrays.set(14);

    // Copy construction
    write_only_armed_spaceship s3(s);
}

}