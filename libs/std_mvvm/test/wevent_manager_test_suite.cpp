//
//  wevent_manager_test_suite.cpp
//
//  Copyright 2015-2019 Göran Orsander
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
TEST(std_wevent_manager_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>
#include <go/property.hpp>
#include <go/utility.hpp>

namespace m = go::mvvm;
namespace p = go::property;
namespace ph = std::placeholders;
namespace rop = go::property::read_only;
namespace s = go::signals;
namespace u = go::utility;

namespace
{

// Test event_manager
const std::wstring fleet_commander_changed_event_type(L"fleet commander changed");

class fleet_commander_changed_event
    : public m::wevent
{
public:
    typedef fleet_commander_changed_event this_type;
    typedef GO_TYPENAME std::shared_ptr<fleet_commander_changed_event> ptr;
    typedef GO_TYPENAME std::weak_ptr<fleet_commander_changed_event> wptr;

public:
    virtual ~fleet_commander_changed_event() GO_DEFAULT_DESTRUCTOR

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
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const std::wstring& fleet_commander_) : this_type(fleet_commander_) {}
        };

        return std::make_shared<make_shared_enabler, const std::wstring&>(fleet_commander_);
    }
};

class fleet_commander
    : public u::noncopyable_nonmovable
{
public:
    typedef std::shared_ptr<fleet_commander> ptr;
    typedef std::weak_ptr<fleet_commander> wptr;

public:
    virtual ~fleet_commander() GO_DEFAULT_DESTRUCTOR

private:
    fleet_commander(const m::wevent_manager::ptr& event_manager_, const std::wstring& commander_, const std::wstring& battle_)
        : u::noncopyable_nonmovable()
        , commander(L"commander")
        , battle(L"battle", battle_)
        , _event_manager(event_manager_)
        , _commander(commander_)
    {
    }

public:
    static ptr create(const m::wevent_manager::ptr& event_manager_, const std::wstring& commander_, const std::wstring& battle_)
    {
        struct make_shared_enabler
            : public fleet_commander
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(const m::wevent_manager::ptr& event_manager_, const std::wstring& commander_, const std::wstring& battle_) : fleet_commander(event_manager_, commander_, battle_) {}
        };

        ptr fleet_cmdr = std::make_shared<make_shared_enabler, const m::wevent_manager::ptr&, const std::wstring&, const std::wstring&>(event_manager_, commander_, battle_);
        fleet_cmdr->bind_properties();
        return fleet_cmdr;
    }

private:
    void bind_properties()
    {
        commander.getter([this]() -> std::wstring { return _commander; });
        commander.setter(
            [this](const std::wstring& commander_)
        {
            if(commander_ != _commander)
            {
                _commander = commander_;
                _event_manager->post(fleet_commander_changed_event::create(commander_));
            }
        });
    }

public:
    p::wproperty<std::wstring> commander;
    p::value_wproperty<std::wstring> battle;

private:
    m::wevent_manager::ptr _event_manager;
    std::wstring _commander;
};

class spaceship
    : public u::noncopyable_nonmovable
{
public:
    virtual ~spaceship() GO_DEFAULT_DESTRUCTOR

private:
    spaceship(const std::wstring& name_, const std::wstring& captain_, const std::wstring& fleet_commander_)
        : u::noncopyable_nonmovable()
        , fleet_commander(L"fleet_commander")
        , name(L"name", name_)
        , captain(L"captain", captain_)
        , _fleet_commander(fleet_commander_)
    {
    }

public:
    static std::shared_ptr<spaceship> create(const std::wstring& name_, const std::wstring& captain_, const std::wstring& fleet_commander_)
    {
        std::shared_ptr<spaceship> ship(new spaceship(name_, captain_, fleet_commander_));
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
        fleet_commander_changed_event::ptr fleet_commander_changed = std::dynamic_pointer_cast<fleet_commander_changed_event>(e);
        if(fleet_commander_changed)
        {
            _fleet_commander = fleet_commander_changed->fleet_commander();
        }
    }

private:
    void bind_properties()
    {
        fleet_commander.getter([this]() -> std::wstring { return _fleet_commander; });
    }

private:
    std::wstring _fleet_commander;
};

#define TEST_CASE_SHIPYARD \
    m::wevent_manager::ptr event_mgr = m::wevent_manager::create(); \
\
    fleet_commander::ptr fleet_cmdr = fleet_commander::create(event_mgr, L"General Jan Dodonna", L"Battle of Yavin"); \
\
    std::shared_ptr<spaceship> ship1 = spaceship::create(L"Millennium Falcon", L"Han Solo", L"General Jan Dodonna"); \
    std::shared_ptr<spaceship> ship2 = spaceship::create(L"X-Wing Red Leader", L"Garven Dreis", L"General Jan Dodonna"); \
    std::shared_ptr<spaceship> ship3 = spaceship::create(L"X-Wing Red Two", L"Wedge Antilles", L"General Jan Dodonna"); \
    std::shared_ptr<spaceship> ship4 = spaceship::create(L"X-Wing Red Three", L"Biggs Darklighter", L"General Jan Dodonna"); \
    std::shared_ptr<spaceship> ship5 = spaceship::create(L"X-Wing Red Four", L"John D. Branon", L"General Jan Dodonna"); \
    std::shared_ptr<spaceship> ship6 = spaceship::create(L"X-Wing Red Five", L"Luke Skywalker", L"General Jan Dodonna"); \
    std::shared_ptr<spaceship> ship7 = spaceship::create(L"Y-Wing Gold Leader", L"Jon 'Dutch' Vander", L"General Jan Dodonna"); \
    std::shared_ptr<spaceship> ship8 = spaceship::create(L"Y-Wing Gold Two", L"Dex Tiree", L"General Jan Dodonna"); \
\
    const m::event_subscription_key ship1_key = event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship::on_fleet_commander_changed, ship1, ph::_1)); \
    const m::event_subscription_key ship2_key = event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship::on_fleet_commander_changed, ship2, ph::_1)); \
    const m::event_subscription_key ship3_key = event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship::on_fleet_commander_changed, ship3, ph::_1)); \
    const m::event_subscription_key ship4_key = event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship::on_fleet_commander_changed, ship4, ph::_1)); \
    const m::event_subscription_key ship5_key = event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship::on_fleet_commander_changed, ship5, ph::_1)); \
    const m::event_subscription_key ship6_key = event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship::on_fleet_commander_changed, ship6, ph::_1)); \
    const m::event_subscription_key ship7_key = event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship::on_fleet_commander_changed, ship7, ph::_1)); \
    const m::event_subscription_key ship8_key = event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship::on_fleet_commander_changed, ship8, ph::_1));

#define TEST_CASE_SCRAP_HEAP \
    event_mgr->unsubscribe(fleet_commander_changed_event_type, ship1_key); \
    event_mgr->unsubscribe(fleet_commander_changed_event_type, ship2_key); \
    event_mgr->unsubscribe(fleet_commander_changed_event_type, ship3_key); \
    event_mgr->unsubscribe(fleet_commander_changed_event_type, ship4_key); \
    event_mgr->unsubscribe(fleet_commander_changed_event_type, ship5_key); \
    event_mgr->unsubscribe(fleet_commander_changed_event_type, ship6_key); \
    event_mgr->unsubscribe(fleet_commander_changed_event_type, ship7_key); \
    event_mgr->unsubscribe(fleet_commander_changed_event_type, ship8_key);

TEST(std_wevent_manager_test_suite, test_command_manager)
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

    TEST_CASE_SCRAP_HEAP
}

}

#endif  // Required C++11 feature is not supported by this compiler
