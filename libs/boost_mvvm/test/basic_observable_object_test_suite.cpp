//
//  basic_observable_object_test_suite.cpp
//
//  Copyright 2018 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go_boost/config.hpp>
#include <go_boost/mvvm.hpp>
#include <go_boost/property.hpp>
#include <go_boost/utility.hpp>

namespace m = go_boost::mvvm;
namespace p = go_boost::property;
namespace s = go_boost::signals;
namespace u = go_boost::utility;
namespace us = go_boost::utility::string;

namespace
{

// Test observable_object
class spaceship
    : public m::basic_observable_object<u::u8string>
    , private u::noncopyable_nonmovable
{
public:
    virtual ~spaceship() GO_BOOST_DEFAULT_DESTRUCTOR

private:
     spaceship()
        : m::basic_observable_object<u::u8string>()
        , u::noncopyable_nonmovable()
        , crew_complement(us::create<u::u8string>("crew_complement"))
        , name(us::create<u::u8string>("name"))
        , max_speed(us::create<u::u8string>("max_speed"))
        , _crew_complement(0)
        , _name()
        , _max_speed(0.0)
    {
    }

public:
    static boost::shared_ptr<spaceship> create()
    {
        boost::shared_ptr<spaceship> ship(new spaceship());
        ship->bind_properties();
        return ship;
    }

private:
    void bind_properties()
    {
        crew_complement.getter(boost::bind(&spaceship::get_crew_complement, this));
        crew_complement.setter(boost::bind(&spaceship::set_crew_complement, this, _1));
        name.getter(boost::bind(&spaceship::get_name, this));
        name.setter(boost::bind(&spaceship::set_name, this, _1));
        max_speed.getter(boost::bind(&spaceship::get_max_speed, this));
        max_speed.setter(boost::bind(&spaceship::set_max_speed, this, _1));
    }

public:
    p::u8property<int> crew_complement;
    p::u8property<u::u8string> name;
    p::u8property<double> max_speed;

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

    u::u8string get_name() const
    {
        return _name;
    }

    void set_name(const u::u8string& v)
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
    u::u8string _name;
    double _max_speed;
};

class spaceship_observer
{
public:
    virtual ~spaceship_observer() GO_BOOST_DEFAULT_DESTRUCTOR

     spaceship_observer()
        : _crew_complement_change_count(0)
        , _name_change_count(0)
        , _max_speed_change_count(0)
    {
    }

    void connect(spaceship& m)
    {
        m.property_changed.connect(boost::bind(&spaceship_observer::on_property_changed, this, _1, _2));
    }

    void disconnect(spaceship& m)
    {
        m.property_changed.disconnect(boost::bind(&spaceship_observer::on_property_changed, this, _1, _2));
    }

    void on_property_changed(const m::object::ptr& o, const m::basic_property_changed_arguments<u::u8string>::ptr& a)
    {
        if(o && a)
        {
            if(a->property_name() == us::create<u::u8string>("crew_complement")) { ++_crew_complement_change_count; }
            else if(a->property_name() == us::create<u::u8string>("name")) { ++_name_change_count; }
            else if(a->property_name() == us::create<u::u8string>("max_speed")) { ++_max_speed_change_count; }
        }
    }

    int crew_complement_change_count() const { return _crew_complement_change_count; }
    int name_change_count() const { return _name_change_count; }
    int max_speed_change_count() const { return _max_speed_change_count; }

private:
    int _crew_complement_change_count;
    int _name_change_count;
    int _max_speed_change_count;
};

TEST(boost_basic_observable_object_test_suite, test_observable_object)
{
    boost::shared_ptr<spaceship> m = spaceship::create();
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