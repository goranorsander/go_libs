//
//  placebo_lockable_observable_object_phoenix_test_suite.cpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_BOOST_NO_BOOST_PHOENIX)
GO_BOOST_MESSAGE("Boost.Phoenix is not supported by this compiler")
TEST(boost_observable_object_phoenix_placebo_lockable_test_suite, boost_phoenix_not_supported) {}
#else

#include <go_boost/mvvm.hpp>
#include <go_boost/mvvm/utility.hpp>
#include <go_boost/namespace_alias.hpp>
#include <go_boost/property.hpp>
#include <go_boost/utility.hpp>

namespace
{

// Test observable_object
class spaceship
    : public mst::observable_object
    , private tt::noncopyable_nonmovable
{
public:
    virtual ~spaceship() GO_BOOST_DEFAULT_DESTRUCTOR

private:
    spaceship()
        : mst::observable_object()
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
    static boost::shared_ptr<spaceship> create()
    {
        boost::shared_ptr<spaceship> ship(new spaceship());
        ship->bind_properties();
        return ship;
    }

private:
    void bind_properties()
    {
        crew_complement.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_crew_complement)));
        crew_complement.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), crew_complement.name(), boost::bind(&spaceship::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(_crew_complement), bph::arg1, bph::arg2));
        name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_name)));
        name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), name.name(), boost::bind(&spaceship::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(_name), bph::arg1, bph::arg2));
        max_speed.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_max_speed)));
        max_speed.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), max_speed.name(), boost::bind(&spaceship::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(_max_speed), bph::arg1, bph::arg2));
    }

public:
    p::property<int> crew_complement;
    p::property<std::string> name;
    p::property<double> max_speed;

private:
    int _crew_complement;
    std::string _name;
    double _max_speed;
};

class spaceship_observer
{
public:
    virtual ~spaceship_observer() GO_BOOST_DEFAULT_DESTRUCTOR

     spaceship_observer()
        : _on_property_changed_connections()
        , _crew_complement_change_count(0u)
        , _name_change_count(0u)
        , _max_speed_change_count(0u)
    {
    }

    void connect(spaceship& m)
    {
        _on_property_changed_connections[&m] = m.property_changed.connect(boost::bind(&spaceship_observer::on_property_changed, this, boost::placeholders::_1, boost::placeholders::_2));
    }

    void disconnect(spaceship& m)
    {
        spaceship_connection_map_type::iterator it = _on_property_changed_connections.find(&m);
        if (it != _on_property_changed_connections.end())
        {
            m.property_changed.disconnect(it->second);
            _on_property_changed_connections.erase(it);
        }
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
    typedef std::map<boost::shared_ptr<spaceship>::element_type*, boost::signals2::connection> spaceship_connection_map_type;

    spaceship_connection_map_type _on_property_changed_connections;
    unsigned int _crew_complement_change_count;
    unsigned int _name_change_count;
    unsigned int _max_speed_change_count;
};

TEST(boost_observable_object_phoenix_placebo_lockable_test_suite, test_observable_object)
{
    boost::shared_ptr<spaceship> m = spaceship::create();
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

#endif  // #if defined(GO_BOOST_NO_BOOST_PHOENIX)
