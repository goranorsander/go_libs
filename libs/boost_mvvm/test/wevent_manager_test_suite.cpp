//
//  wevent_manager_test_suite.cpp
//
//  Copyright 2015-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#include <go_boost/mvvm.hpp>
#include <go_boost/property.hpp>

namespace m = go_boost::mvvm;
namespace p = go_boost::property;
namespace rop = go_boost::property::read_only;
namespace u = go_boost::utility;

namespace
{

// Test event_manager
const std::wstring fleet_commander_changed_event_type(L"fleet commander changed");

class fleet_commander_changed_event
    : public m::wevent
{
public:
    typedef fleet_commander_changed_event this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<fleet_commander_changed_event> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<fleet_commander_changed_event> wptr;

public:
    virtual ~fleet_commander_changed_event() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
    explicit fleet_commander_changed_event(const std::wstring& fleet_commander_)
        : m::wevent(fleet_commander_changed_event_type)
        , fleet_commander(L"fleet_commander", fleet_commander_)
    {
    }

public:
    rop::value_wproperty<std::wstring> fleet_commander;

public:
    static ptr create(const std::wstring& fleet_commander_)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const std::wstring& fleet_commander_) : this_type(fleet_commander_) {}
        };
        return boost::make_shared<make_shared_enabler, const std::wstring&>(fleet_commander_);
#else
        return boost::shared_ptr<this_type>(new this_type(fleet_commander_));
#endif // BOOST_MSVC > 1500
    }
};

class fleet_commander
    : private u::noncopyable_nonmovable
{
public:
    typedef fleet_commander this_type;
    typedef boost::shared_ptr<fleet_commander> ptr;
    typedef boost::weak_ptr<fleet_commander> wptr;

public:
    virtual ~fleet_commander() GO_BOOST_DEFAULT_DESTRUCTOR

private:
    fleet_commander(const m::wevent_manager::ptr& event_manager_, const std::wstring& commander_, const std::wstring& battle_)
        : u::noncopyable_nonmovable()
        , commander(std::wstring(L"commander"))
        , battle(std::wstring(L"battle"), battle_)
        , _event_manager(event_manager_)
        , _commander(commander_)
    {
    }

public:
    static ptr create(const m::wevent_manager::ptr& event_manager_, const std::wstring& commander_, const std::wstring& battle_)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            make_shared_enabler(const m::wevent_manager::ptr& event_manager_, const std::wstring& commander_, const std::wstring& battle_) : this_type(event_manager_, commander_, battle_) {}
        };
        ptr fleet_cmdr = boost::make_shared<make_shared_enabler, const m::wevent_manager::ptr&, const std::wstring&, const std::wstring&>(event_manager_, commander_, battle_);
#else
        ptr fleet_cmdr = boost::shared_ptr<this_type>(new this_type(event_manager_, commander_, battle_));
#endif // BOOST_MSVC > 1500
        fleet_cmdr->bind_properties();
        return fleet_cmdr;
    }

public:
    p::wproperty<std::wstring> commander;
    p::value_wproperty<std::wstring> battle;

private:
    std::wstring get_commander() const
    {
        return _commander;
    }

    void set_commander(const std::wstring& v)
    {
        if(v != _commander)
        {
            _commander = v;
            _event_manager->post(fleet_commander_changed_event::create(v));
        }
    }

    void bind_properties()
    {
        commander.getter(boost::bind(&fleet_commander::get_commander, this));
        commander.setter(boost::bind(&fleet_commander::set_commander, this, _1));
    }

private:
    m::wevent_manager::ptr _event_manager;
    std::wstring _commander;
};

class spaceship
    : private u::noncopyable_nonmovable
{
public:
    virtual ~spaceship() GO_BOOST_DEFAULT_DESTRUCTOR

private:
    spaceship(const std::wstring& name_, const std::wstring& captain_, const std::wstring& fleet_commander_)
        : u::noncopyable_nonmovable()
        , fleet_commander(std::wstring(L"fleet_commander"))
        , name(std::wstring(L"name"), name_)
        , captain(std::wstring(L"captain"), captain_)
        , _fleet_commander(fleet_commander_)
    {
    }

public:
    static boost::shared_ptr<spaceship> create(const std::wstring& name_, const std::wstring& captain_, const std::wstring& fleet_commander_)
    {
        boost::shared_ptr<spaceship> ship(new spaceship(name_, captain_, fleet_commander_));
        ship->bind_properties();
        return ship;
    }

public:
    rop::wproperty<std::wstring> fleet_commander;
    p::value_wproperty<std::wstring> name;
    p::value_wproperty<std::wstring> captain;

public:
    void on_fleet_commander_changed(const m::wevent::ptr& e)
    {
        fleet_commander_changed_event::ptr fleet_commander_changed = boost::dynamic_pointer_cast<fleet_commander_changed_event>(e);
        if(fleet_commander_changed)
        {
            _fleet_commander = fleet_commander_changed->fleet_commander();
        }
    }

private:
    std::wstring get_fleet_commander() const
    {
        return _fleet_commander;
    }

    void bind_properties()
    {
        fleet_commander.getter(boost::bind(&spaceship::get_fleet_commander, this));
    }

private:
    std::wstring _fleet_commander;
};

#define TEST_CASE_SHIPYARD \
    m::wevent_manager::ptr event_mgr = m::wevent_manager::create(); \
\
    fleet_commander::ptr fleet_cmdr = fleet_commander::create(event_mgr, L"General Jan Dodonna", L"Battle of Yavin"); \
\
    boost::shared_ptr<spaceship> ship1 = spaceship::create(L"Millennium Falcon", L"Han Solo", L"General Jan Dodonna"); \
    boost::shared_ptr<spaceship> ship2 = spaceship::create(L"X-Wing Red Leader", L"Garven Dreis", L"General Jan Dodonna"); \
    boost::shared_ptr<spaceship> ship3 = spaceship::create(L"X-Wing Red Two", L"Wedge Antilles", L"General Jan Dodonna"); \
    boost::shared_ptr<spaceship> ship4 = spaceship::create(L"X-Wing Red Three", L"Biggs Darklighter", L"General Jan Dodonna"); \
    boost::shared_ptr<spaceship> ship5 = spaceship::create(L"X-Wing Red Four", L"John D. Branon", L"General Jan Dodonna"); \
    boost::shared_ptr<spaceship> ship6 = spaceship::create(L"X-Wing Red Five", L"Luke Skywalker", L"General Jan Dodonna"); \
    boost::shared_ptr<spaceship> ship7 = spaceship::create(L"Y-Wing Gold Leader", L"Jon 'Dutch' Vander", L"General Jan Dodonna"); \
    boost::shared_ptr<spaceship> ship8 = spaceship::create(L"Y-Wing Gold Two", L"Dex Tiree", L"General Jan Dodonna"); \
\
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship1, _1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship2, _1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship3, _1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship4, _1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship5, _1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship6, _1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship7, _1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship8, _1));

TEST(boost_event_manager_test_suite, test_command_manager)
{
    TEST_CASE_SHIPYARD

    // After connect
    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship1->fleet_commander());
    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship2->fleet_commander());
    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship3->fleet_commander());
    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship4->fleet_commander());
    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship5->fleet_commander());
    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship6->fleet_commander());
    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship7->fleet_commander());
    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship8->fleet_commander());

    // Change fleet commander
    fleet_cmdr->commander(L"Admiral Gial Ackbar");

    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship1->fleet_commander());
    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship2->fleet_commander());
    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship3->fleet_commander());
    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship4->fleet_commander());
    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship5->fleet_commander());
    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship6->fleet_commander());
    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship7->fleet_commander());
    EXPECT_EQ(std::wstring(L"General Jan Dodonna"), ship8->fleet_commander());

    event_mgr->fire_events();

    EXPECT_EQ(std::wstring(L"Admiral Gial Ackbar"), ship1->fleet_commander());
    EXPECT_EQ(std::wstring(L"Admiral Gial Ackbar"), ship2->fleet_commander());
    EXPECT_EQ(std::wstring(L"Admiral Gial Ackbar"), ship3->fleet_commander());
    EXPECT_EQ(std::wstring(L"Admiral Gial Ackbar"), ship4->fleet_commander());
    EXPECT_EQ(std::wstring(L"Admiral Gial Ackbar"), ship5->fleet_commander());
    EXPECT_EQ(std::wstring(L"Admiral Gial Ackbar"), ship6->fleet_commander());
    EXPECT_EQ(std::wstring(L"Admiral Gial Ackbar"), ship7->fleet_commander());
    EXPECT_EQ(std::wstring(L"Admiral Gial Ackbar"), ship8->fleet_commander());
}

}
