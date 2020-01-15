//
//  observable_object_test_suite.cpp
//
//  Copyright 2015-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_observable_object_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>
#include <go/namespace_alias.hpp>
#include <go/property.hpp>
#include <go/utility.hpp>

namespace
{

// Test observable_object
class spaceship
    : public m::observable_object
    , public tt::noncopyable_nonmovable
{
public:
    virtual ~spaceship() GO_DEFAULT_DESTRUCTOR

private:
     spaceship()
        : m::observable_object()
        , tt::noncopyable_nonmovable()
        , crew_complement("crew_complement")
        , name("name")
        , max_speed("max_speed")
        , _crew_complement(0)
        , _name()
        , _max_speed(0.0)
    {
    }

public:
    static std::shared_ptr<spaceship> create()
    {
        std::shared_ptr<spaceship> ship(new spaceship());
        ship->bind_properties();
        return ship;
    }

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
    p::property<int> crew_complement;
    p::property<std::string> name;
    p::property<double> max_speed;

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
            notify_property_changed(this->shared_from_this(), crew_complement.name());
        }
    }

    std::string get_name() const
    {
        return _name;
    }

    void set_name(const std::string& v)
    {
        if(v != _name)
        {
            _name = v;
            notify_property_changed(this->shared_from_this(), name.name());
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
            notify_property_changed(this->shared_from_this(), max_speed.name());
        }
    }

private:
    int _crew_complement;
    std::string _name;
    double _max_speed;
};

class spaceship_observer
{
public:
    virtual ~spaceship_observer() GO_DEFAULT_DESTRUCTOR

     spaceship_observer()
        : _on_property_changed_slot_key()
        , _crew_complement_change_count(0u)
        , _name_change_count(0u)
        , _max_speed_change_count(0u)
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

    void on_property_changed(const m::object::ptr& o, const m::property_changed_arguments::ptr& a)
    {
        if(o && a)
        {
            if(a->property_name() == "crew_complement") { ++_crew_complement_change_count; }
            else if(a->property_name() == "name") { ++_name_change_count; }
            else if(a->property_name() == "max_speed") { ++_max_speed_change_count; }
        }
    }

    unsigned int crew_complement_change_count() const { return _crew_complement_change_count; }
    unsigned int name_change_count() const { return _name_change_count; }
    unsigned int max_speed_change_count() const { return _max_speed_change_count; }

private:
    si::slot_key _on_property_changed_slot_key;
    unsigned int _crew_complement_change_count;
    unsigned int _name_change_count;
    unsigned int _max_speed_change_count;
};

TEST(std_observable_object_test_suite, test_observable_object)
{
    std::shared_ptr<spaceship> m = spaceship::create();
    spaceship_observer o;

    o.connect(*m);

    // After connect
    EXPECT_EQ(0u, o.crew_complement_change_count());
    EXPECT_EQ(0u, o.name_change_count());
    EXPECT_EQ(0u, o.max_speed_change_count());

    m->crew_complement = 47;

    // After one assignment
    EXPECT_EQ(1u, o.crew_complement_change_count());
    EXPECT_EQ(0u, o.name_change_count());
    EXPECT_EQ(0u, o.max_speed_change_count());

    int pid = m->crew_complement;

    // After one access
    EXPECT_EQ(47, pid);
    EXPECT_EQ(1u, o.crew_complement_change_count());
    EXPECT_EQ(0u, o.name_change_count());
    EXPECT_EQ(0u, o.max_speed_change_count());

    m->crew_complement = 47;
    pid = m->crew_complement;

    // After assignment of same value
    EXPECT_EQ(47, pid);
    EXPECT_EQ(1u, o.crew_complement_change_count());
    EXPECT_EQ(0u, o.name_change_count());
    EXPECT_EQ(0u, o.max_speed_change_count());

    o.disconnect(*m);
    m->crew_complement = 74;
    pid = m->crew_complement;

    // After disconnect and assignment of new value
    EXPECT_EQ(74, pid);
    EXPECT_EQ(1u, o.crew_complement_change_count());
    EXPECT_EQ(0u, o.name_change_count());
    EXPECT_EQ(0u, o.max_speed_change_count());
}

}

#endif  // Required C++11 feature is not supported by this compiler
