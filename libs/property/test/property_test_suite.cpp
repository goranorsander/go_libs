//
//  properties_test_suite.cpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <functional>
#include <string>

#include <gtest/gtest.h>

#include <go/property.hpp>

namespace p = go::property;
namespace ph = std::placeholders;

// Test value_scalar_property
class spaceship
{
public:
    p::value_scalar_property<int> crew_complement;
    p::value_scalar_property<double> max_speed;
    p::value_scalar_property<std::string> name;

    spaceship()
        : crew_complement(std::string("crew_complement"), 1012)
        , max_speed(std::string("max_speed"), 9.8)
        , name(std::string("name"), std::string("USS Enterprise (NCC-1701-D)"))
    {
    }

    spaceship(const spaceship& v)
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
    }
};

TEST(properties_test_suite, value_scalar_properties)
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

// Test ro_value_scalar_property
class ro_spaceship
{
public:
    p::ro_value_scalar_property<int> crew_complement;
    p::ro_value_scalar_property<double> max_speed;
    p::ro_value_scalar_property<std::string> name;

    ro_spaceship()
        : crew_complement(std::string("crew_complement"), 1012)
        , max_speed(std::string("max_speed"), 9.8)
        , name(std::string("name"), std::string("USS Enterprise (NCC-1701-D)"))
    {
    }
};

TEST(properties_test_suite, ro_scalar_properties)
{
    ro_spaceship s;

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
    ro_spaceship s2(s);
    EXPECT_EQ(1012, s2.crew_complement());
    EXPECT_EQ(9.8, s2.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s2.name());
}

// Test wo_value_scalar_property
class wo_spaceship
{
public:
    p::wo_value_scalar_property<int> crew_complement;
    p::wo_value_scalar_property<double> max_speed;
    p::wo_value_scalar_property<std::string> name;

    wo_spaceship()
        : crew_complement(std::string("crew_complement"), 1012)
        , max_speed(std::string("max_speed"), 9.8)
        , name(std::string("name"), std::string("USS Enterprise (NCC-1701-D)"))
    {
    }
};

TEST(properties_test_suite, wo_scalar_properties)
{
    wo_spaceship s;

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
    wo_spaceship s2(s);
}

// Test ref_scalar_property
class ref_spaceship
{
public:
    p::ref_scalar_property<int> crew_complement;
    p::ref_scalar_property<double> max_speed;
    p::ref_scalar_property<std::string> name;

    ref_spaceship()
        : crew_complement(std::string("crew_complement"))
        , max_speed(std::string("max_speed"))
        , name(std::string("name"))
    {
    }
};

TEST(properties_test_suite, ref_scalar_properties)
{
    ref_spaceship s;

    // Verify default values
    EXPECT_TRUE(s.crew_complement.empty() == true);
    EXPECT_TRUE(s.max_speed.empty() == true);
    EXPECT_TRUE(s.name.empty() == true);

    // Method oriented get
    int s_cc_1 = 1012;
    double s_ms_1 = 9.8;
    std::string s_n_1("USS Enterprise (NCC-1701-D)");
    s.crew_complement.set(s_cc_1);
    s.max_speed.set(s_ms_1);
    s.name.set(s_n_1);
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
    int s_cc_2 = 647;
    double s_ms_2 = 9.975;
    std::string s_n_2("USS Enterprise (NCC-1701-E)");
    s.crew_complement(s_cc_2);
    s.max_speed(s_ms_2);
    s.name(s_n_2);
    EXPECT_EQ(647, s.crew_complement());
    EXPECT_EQ(9.975, s.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-E)"), s.name());

    // Assign operator oriented set
    int s_cc_3 = 430;
    double s_ms_3 = 9.0;
    std::string s_n_3("USS Enterprise (NCC-1701)");
    s.crew_complement = s_cc_3;
    s.max_speed = s_ms_3;
    s.name = s_n_3;
    EXPECT_EQ(430, s.crew_complement);
    EXPECT_EQ(9.0, s.max_speed);
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701)"), s.name());

    // Traditional set
    int s_cc_4 = 574;
    double s_ms_4 = 9.7;
    std::string s_n_4("USS Enterprise (NCC-1701-B)");
    s.crew_complement.set(s_cc_4);
    s.max_speed.set(s_ms_4);
    s.name.set(s_n_4);
    EXPECT_EQ(574, s.crew_complement.get());
    EXPECT_EQ(9.7, s.max_speed.get());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-B)"), s.name());

    // Assign referenced object oriented set
    s_cc_4 = 600;
    s_ms_4 = 9.75;
    s_n_4 = "USS Enterprise (NCC-1701-C)";
    EXPECT_EQ(600, s.crew_complement.get());
    EXPECT_EQ(9.75, s.max_speed.get());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-C)"), s.name());

    // Copy construction
    ref_spaceship s2(s);
    EXPECT_EQ(600, s2.crew_complement());
    EXPECT_EQ(9.75, s2.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-C)"), s2.name());
}

// Test ro_ref_scalar_property
class ro_ref_spaceship
{
public:
    p::ro_ref_scalar_property<int> crew_complement;
    p::ro_ref_scalar_property<double> max_speed;
    p::ro_ref_scalar_property<std::string> name;

    ro_ref_spaceship()
        : crew_complement(std::string("crew_complement"), m_crew_complement)
        , max_speed(std::string("max_speed"), m_speed)
        , name(std::string("name"), m_name)
        , m_crew_complement(1012)
        , m_speed(9.8)
        , m_name(std::string("USS Enterprise (NCC-1701-D)"))
    {
    }

private:
    int m_crew_complement;
    double m_speed;
    std::string m_name;
};

TEST(properties_test_suite, ro_ref_scalar_properties)
{
    ro_ref_spaceship s;

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

    // Copy construction
    ro_ref_spaceship s2(s);
    EXPECT_TRUE(s2.crew_complement.empty() == false);
    EXPECT_TRUE(s2.max_speed.empty() == false);
    EXPECT_TRUE(s2.name.empty() == false);
    EXPECT_EQ(1012, s2.crew_complement());
    EXPECT_EQ(9.8, s2.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s2.name());
}

// Test wo_ref_scalar_property
class wo_ref_spaceship
{
public:
    p::wo_ref_scalar_property<int> crew_complement;
    p::wo_ref_scalar_property<double> max_speed;
    p::wo_ref_scalar_property<std::string> name;

    wo_ref_spaceship()
        : crew_complement(std::string("crew_complement"))
        , max_speed(std::string("max_speed"))
        , name(std::string("name"))
    {
    }
};

TEST(properties_test_suite, wo_ref_scalar_properties)
{
    wo_ref_spaceship s;

    // Verify default values
    EXPECT_TRUE(s.crew_complement.empty() == true);
    EXPECT_TRUE(s.max_speed.empty() == true);
    EXPECT_TRUE(s.name.empty() == true);

    // Method oriented set
    int s_cc_2 = 647;
    double s_ms_2 = 9.975;
    std::string s_n_2("USS Enterprise (NCC-1701-E)");
    s.crew_complement(s_cc_2);
    s.max_speed(s_ms_2);
    s.name(s_n_2);

    // Assign operator oriented set
    int s_cc_3 = 430;
    double s_ms_3 = 9.0;
    std::string s_n_3("USS Enterprise (NCC-1701)");
    s.crew_complement = s_cc_3;
    s.max_speed = s_ms_3;
    s.name = s_n_3;

    // Traditional set
    int s_cc_4 = 574;
    double s_ms_4 = 9.7;
    std::string s_n_4("USS Enterprise (NCC-1701-B)");
    s.crew_complement.set(s_cc_4);
    s.max_speed.set(s_ms_4);
    s.name.set(s_n_4);

    // Assign referenced object oriented set
    s_cc_4 = 600;
    s_ms_4 = 9.75;
    s_n_4 = "USS Enterprise (NCC-1701-C)";

    // Copy construction
    wo_ref_spaceship s2(s);
}

// Test property
class armament
{
// Spaceship armament, not modifyable, provided by third-party
public:
    ~armament()
    {
    }

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
    p::property<int> phaser_arrays;

    armed_spaceship()
        : spaceship()
        , phaser_arrays(std::string("phaser_arrays"))
        , _armament()
    {
        update_bindings();
    }

    armed_spaceship(const armed_spaceship& v)
        : spaceship(v)
        , phaser_arrays(v.phaser_arrays)
        , _armament(v._armament)
    {
        update_bindings();
    }

    armed_spaceship& operator=(const armed_spaceship& v)
    {
        spaceship::operator=(v);
        phaser_arrays = v.phaser_arrays;
        _armament = v._armament;
        update_bindings();
    }

private:
    void update_bindings()
    {
        phaser_arrays.getter(std::bind(&armament::get_phaser_arrays, &_armament));
        phaser_arrays.setter(std::bind(&armament::set_phaser_arrays, &_armament, ph::_1));
    }

private:
    armament _armament;
};

TEST(properties_test_suite, value_properties)
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

// Test ro_property
class ro_armed_spaceship
    : public ro_spaceship
{
public:
    p::ro_property<int> phaser_arrays;

    ro_armed_spaceship()
        : ro_spaceship()
        , phaser_arrays(std::string("phaser_arrays"))
        , _armament()
    {
        _armament.set_phaser_arrays(8);
        update_bindings();
    }

    ro_armed_spaceship(const ro_armed_spaceship& v)
        : ro_spaceship(v)
        , phaser_arrays(v.phaser_arrays)
        , _armament(v._armament)
    {
        update_bindings();
    }

private:
    void update_bindings()
    {
        phaser_arrays.getter(std::bind(&armament::get_phaser_arrays, &_armament));
    }

private:
    armament _armament;
};

TEST(properties_test_suite, ro_value_properties)
{
    ro_armed_spaceship s;

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
    ro_spaceship s2(s);
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
    ro_armed_spaceship s3(s);
    EXPECT_EQ(1012, s3.crew_complement());
    EXPECT_EQ(9.8, s3.max_speed());
    EXPECT_EQ(std::string("USS Enterprise (NCC-1701-D)"), s3.name());
    EXPECT_EQ(8, s3.phaser_arrays());
}

// Test wo_property
class wo_armed_spaceship
    : public wo_spaceship
{
public:
    p::wo_property<int> phaser_arrays;

    wo_armed_spaceship()
        : wo_spaceship()
        , phaser_arrays(std::string("phaser_arrays"))
        , _armament()
    {
        update_bindings();
    }

    wo_armed_spaceship(const wo_armed_spaceship& v)
        : wo_spaceship(v)
        , phaser_arrays(v.phaser_arrays)
        , _armament(v._armament)
    {
        update_bindings();
    }

private:
    void update_bindings()
    {
        phaser_arrays.setter(std::bind(&armament::set_phaser_arrays, &_armament, ph::_1));
    }

private:
    armament _armament;
};

TEST(properties_test_suite, wo_value_properties)
{
    wo_armed_spaceship s;

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
    wo_spaceship s2(s);

    // PROXY

    // Method oriented set
    s.phaser_arrays(10);

    // Assign operator oriented set
    s.phaser_arrays = 12;

    // Traditional set
    s.phaser_arrays.set(14);

    // Copy construction
    wo_armed_spaceship s3(s);
}
