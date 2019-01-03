//
//  wobservable_object_lambda_test_suite.cpp
//
//  Copyright 2015-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_LAMBDA_EXPRESSIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_wobservable_object_lambda_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>
#include <go/property.hpp>
#include <go/utility.hpp>

namespace m = go::mvvm;
namespace p = go::property;
namespace ph = std::placeholders;
namespace s = go::signals;
namespace u = go::utility;

namespace
{

// Test observable_object
class spaceship
    : public m::wobservable_object
    , public u::noncopyable_nonmovable
{
public:
    virtual ~spaceship() GO_DEFAULT_DESTRUCTOR

public:
     spaceship()
        : m::wobservable_object()
        , u::noncopyable_nonmovable()
        , crew_complement(L"crew_complement", [this]() { return _crew_complement; }, [this](const int& v) { if(v != _crew_complement) { _crew_complement = v; notify_property_changed(this->shared_from_this(), crew_complement.name()); } })
        , name(L"name", [this]() { return _name; }, [this](const std::wstring& v) { if(v != _name) { _name = v; notify_property_changed(this->shared_from_this(), name.name()); } })
        , max_speed(L"max_speed", [this]() { return _max_speed; }, [this](const double& v) { if(v != _max_speed) { _max_speed = v; notify_property_changed(this->shared_from_this(), max_speed.name()); } })
        , _crew_complement(0)
        , _name()
        , _max_speed(0.0)
    {
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
    virtual ~spaceship_observer() GO_DEFAULT_DESTRUCTOR

     spaceship_observer()
        : _on_property_changed_slot_key()
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
    s::slot_key _on_property_changed_slot_key;
    int _crew_complement_change_count;
    int _name_change_count;
    int _max_speed_change_count;
};

TEST(std_wobservable_object_lambda_test_suite, test_observable_object)
{
    std::shared_ptr<spaceship> m = std::make_shared<spaceship>();
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
