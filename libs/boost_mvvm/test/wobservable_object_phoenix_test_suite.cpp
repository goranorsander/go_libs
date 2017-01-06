//
//  wobservable_object_phoenix_test_suite.cpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <gtest/gtest.h>
#include <go_boost/config.hpp>

#if (BOOST_COMP_MSVC) && (BOOST_MSVC <= 1700)
GO_BOOST_MESSAGE("Boost.Phoenix is not supported by this compiler")
TEST(boost_wobservable_object_phoenix_test_suite, boost_phoenix_not_supported) {}
#else

#include <go_boost/mvvm.hpp>
#include <go_boost/mvvm/utility.hpp>
#include <go_boost/property.hpp>

namespace bp = boost::phoenix;
namespace bph = boost::phoenix::placeholders;
namespace m = go_boost::mvvm;
namespace mu = go_boost::mvvm::utility;
namespace p = go_boost::property;
namespace s = go_boost::signals;
namespace u = go_boost::utility;

namespace
{

// Test observable_object
class spaceship
    : public m::wobservable_object
    , private u::noncopyable_nonmovable
{
public:
    virtual ~spaceship()
    {
    }

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
    void bind_properties()
    {
        crew_complement.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_crew_complement)));
        crew_complement.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4)(crew_complement.name(), boost::bind(&spaceship::on_property_changed, this, _1), bp::ref(_crew_complement), bph::arg1));
        name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_name)));
        name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4)(name.name(), boost::bind(&spaceship::on_property_changed, this, _1), bp::ref(_name), bph::arg1));
        max_speed.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_max_speed)));
        max_speed.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4)(max_speed.name(), boost::bind(&spaceship::on_property_changed, this, _1), bp::ref(_max_speed), bph::arg1));
    }

public:
    p::wproperty<int> crew_complement;
    p::wproperty<std::wstring> name;
    p::wproperty<double> max_speed;

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
    int _crew_complement_change_count;
    int _name_change_count;
    int _max_speed_change_count;
};

TEST(boost_wobservable_object_phoenix_test_suite, test_wobservable_object)
{
    boost::shared_ptr<spaceship> m = boost::make_shared<spaceship>();
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

#endif  // Boost.Phoenix is not supported by this compiler
