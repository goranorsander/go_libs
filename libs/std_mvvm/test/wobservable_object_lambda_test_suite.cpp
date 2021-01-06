//
//  wobservable_object_lambda_test_suite.cpp
//
//  Copyright 2015-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_LAMBDA_EXPRESSIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_wobservable_object_lambda_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>
#include <go/namespace_alias.hpp>
#include <go/property.hpp>
#include <go/utility.hpp>

namespace
{

// Test observable_object
class spaceship
    : public m::wobservable_object
    , public tt::noncopyable_nonmovable
{
public:
    virtual ~spaceship() GO_DEFAULT_DESTRUCTOR

public:
     spaceship()
        : m::wobservable_object()
        , tt::noncopyable_nonmovable()
        , crew_complement(L"crew_complement")
        , name(L"name")
        , max_speed(L"max_speed")
        , _crew_complement(0)
        , _name()
        , _max_speed(0.0)
    {
		 crew_complement.getter([this]() { return _crew_complement; });
		 crew_complement.setter([this](const int& v) { if (v != _crew_complement) { _crew_complement = v; notify_property_changed(this->shared_from_this(), crew_complement.name()); } });
		 name.getter([this]() { return _name; });
		 name.setter([this](const std::wstring & v) { if (v != _name) { _name = v; notify_property_changed(this->shared_from_this(), name.name()); } });
		 max_speed.getter([this]() { return _max_speed; });
		 max_speed.setter([this](const double& v) { if (v != _max_speed) { _max_speed = v; notify_property_changed(this->shared_from_this(), max_speed.name()); } });
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
        : _on_property_changed_connections()
        , _crew_complement_change_count(0u)
        , _name_change_count(0u)
        , _max_speed_change_count(0u)
    {
    }

    void connect(spaceship& m)
    {
        _on_property_changed_connections[&m] = m.property_changed.connect(std::bind(&spaceship_observer::on_property_changed, this, ph::_1, ph::_2));
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

    void on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a)
    {
        if(o && a)
        {
            if(a->property_name() == L"crew_complement") { ++_crew_complement_change_count; }
            else if(a->property_name() == L"name") { ++_name_change_count; }
            else if(a->property_name() == L"max_speed") { ++_max_speed_change_count; }
        }
    }

    unsigned int crew_complement_change_count() const { return _crew_complement_change_count; }
    unsigned int name_change_count() const { return _name_change_count; }
    unsigned int max_speed_change_count() const { return _max_speed_change_count; }

private:
    typedef std::map<std::shared_ptr<spaceship>::element_type*, si::slot_key> spaceship_connection_map_type;

    spaceship_connection_map_type _on_property_changed_connections;
    unsigned int _crew_complement_change_count;
    unsigned int _name_change_count;
    unsigned int _max_speed_change_count;
};

TEST(std_wobservable_object_lambda_test_suite, test_observable_object)
{
    std::shared_ptr<spaceship> m = std::make_shared<spaceship>();
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
