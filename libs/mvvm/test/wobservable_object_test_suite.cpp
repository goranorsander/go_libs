//
//  wobservable_object_test_suite.cpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
#pragma message("Required C++11 feature is not supported by this compiler")
TEST(std_wobservable_object_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>
#include <go/property.hpp>

namespace m = go::mvvm;
namespace p = go::property;
namespace ph = std::placeholders;
namespace s = go::signals;

namespace
{

// Test observable_object
class spaceship
    : public m::wobservable_object
{
public:
    virtual ~spaceship()
    {
    }

private:
    spaceship(const spaceship&) = delete;
    spaceship(spaceship&&) = delete;

public:
    spaceship()
        : m::wobservable_object()
        , _crew_complement(0)
        , _name()
        , _max_speed(0.0)
        , crew_complement(L"crew_complement")
        , name(L"name")
        , max_speed(L"max_speed")
    {
        bind_properties();
    }

private:
    spaceship& operator=(const spaceship&) = delete;
    spaceship& operator=(spaceship&&) = delete;

private:
    void bind_properties()
    {
        crew_complement.getter(std::bind(&spaceship::get_crew_complement, this));
        crew_complement.setter(std::bind(&spaceship::set_crew_complement, this, ph::_1));
        name.getter(std::bind(&spaceship::get_name, this));
        name.setter(std::bind(&spaceship::set_name, this, ph::_1));
        max_speed.getter(std::bind(&spaceship::get_max_speed, this));
        max_speed.setter(std::bind(&spaceship::set_max_speed, this, ph::_1));
    }

public:
    p::wproperty<int> crew_complement;
    p::wproperty<std::wstring> name;
    p::wproperty<double> max_speed;

private:
    int get_crew_complement() const
    {
        return _crew_complement;
    }

    void set_crew_complement(const int& v)
    {
        if(v != _crew_complement)
        {
            _crew_complement = v;
            on_property_changed(L"crew_complement");
        }
    }

    std::wstring get_name() const
    {
        return _name;
    }

    void set_name(const std::wstring& v)
    {
        if(v != _name)
        {
            _name = v;
            on_property_changed(L"name");
        }
    }

    double get_max_speed() const
    {
        return _max_speed;
    }

    void set_max_speed(const double& v)
    {
        if(v != _max_speed)
        {
            _max_speed = v;
            on_property_changed(L"max_speed");
        }
    }

private:
    int _crew_complement;
    std::wstring _name;
    double _max_speed;
};

class spaceship_observer
{
public:
    virtual ~spaceship_observer()
    {
    }

    spaceship_observer()
        : _on_property_changed_slot_key(0)
        , _crew_complement_change_count(0)
        , _name_change_count(0)
        , _max_speed_change_count(0)
    {
    }

    void connect(spaceship& m)
    {
        _on_property_changed_slot_key = m.property_changed.connect(std::bind(&spaceship_observer::on_property_changed, this, ph::_1, ph::_2));
    }

    void disconnect(spaceship& m)
    {
        m.property_changed.disconnect(_on_property_changed_slot_key);
    }

    void on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a)
    {
        if(o && a)
        {
            if(a->property_name() == L"crew_complement") { ++_crew_complement_change_count; }
            else if(a->property_name() == L"name") { ++_name_change_count; }
            else if(a->property_name() == L"max_speed") { ++_max_speed_change_count; }
        }
    }

    int crew_complement_change_count() const { return _crew_complement_change_count; }
    int name_change_count() const { return _name_change_count; }
    int max_speed_change_count() const { return _max_speed_change_count; }

private:
    s::slot_key_type _on_property_changed_slot_key;
    int _crew_complement_change_count;
    int _name_change_count;
    int _max_speed_change_count;
};

TEST(std_wobservable_object_test_suite, test_observable_object)
{
    std::shared_ptr<spaceship> m(new spaceship);
    spaceship_observer o;

    o.connect(*m);

    // After connect
    EXPECT_EQ(0, o.crew_complement_change_count());
    EXPECT_EQ(0, o.name_change_count());
    EXPECT_EQ(0, o.max_speed_change_count());

    m->crew_complement = 47;

    // After one assignment
    EXPECT_EQ(1, o.crew_complement_change_count());
    EXPECT_EQ(0, o.name_change_count());
    EXPECT_EQ(0, o.max_speed_change_count());

    int pid = m->crew_complement;

    // After one access
    EXPECT_EQ(47, pid);
    EXPECT_EQ(1, o.crew_complement_change_count());
    EXPECT_EQ(0, o.name_change_count());
    EXPECT_EQ(0, o.max_speed_change_count());

    m->crew_complement = 47;
    pid = m->crew_complement;

    // After assignment of same value
    EXPECT_EQ(47, pid);
    EXPECT_EQ(1, o.crew_complement_change_count());
    EXPECT_EQ(0, o.name_change_count());
    EXPECT_EQ(0, o.max_speed_change_count());

    o.disconnect(*m);
    m->crew_complement = 74;
    pid = m->crew_complement;

    // After disconnect and assignment of new value
    EXPECT_EQ(74, pid);
    EXPECT_EQ(1, o.crew_complement_change_count());
    EXPECT_EQ(0, o.name_change_count());
    EXPECT_EQ(0, o.max_speed_change_count());
}

}

#endif  // Required C++11 feature is not supported by this compiler