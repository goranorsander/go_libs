//
//  event_manager_test_suite.cpp
//
//  Copyright 2015-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <gtest/gtest.h>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_event_manager_test_suite, cpp11_not_supported) {}
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
const std::string fleet_commander_changed_event_type("fleet commander changed");

class fleet_commander_changed_event
    : public m::event
{
public:
    typedef fleet_commander_changed_event this_type;
    typedef std::shared_ptr<fleet_commander_changed_event> ptr;
    typedef std::weak_ptr<fleet_commander_changed_event> wptr;

public:
    virtual ~fleet_commander_changed_event() GO_DEFAULT_DESTRUCTOR

protected:
    explicit fleet_commander_changed_event(const std::string& fleet_commander_)
        : m::event(fleet_commander_changed_event_type)
        , fleet_commander("fleet_commander", fleet_commander_)
    {
    }

public:
    rop::value_property<std::string> fleet_commander;

public:
    static ptr create(const std::string& fleet_commander_)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const std::string& fleet_commander_) : this_type(fleet_commander_) {}
        };

        return std::make_shared<make_shared_enabler, const std::string&>(fleet_commander_);
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
    fleet_commander(const m::event_manager::ptr& event_manager_, const std::string& commander_, const std::string& battle_)
        : u::noncopyable_nonmovable()
        , commander("commander")
        , battle("battle", battle_)
        , _event_manager(event_manager_)
        , _commander(commander_)
    {
    }

public:
    static ptr create(const m::event_manager::ptr& event_manager_, const std::string& commander_, const std::string& battle_)
    {
        struct make_shared_enabler
            : public fleet_commander
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(const m::event_manager::ptr& event_manager_, const std::string& commander_, const std::string& battle_) : fleet_commander(event_manager_, commander_, battle_) {}
        };

        ptr fleet_cmdr = std::make_shared<make_shared_enabler, const m::event_manager::ptr&, const std::string&, const std::string&>(event_manager_, commander_, battle_);
        fleet_cmdr->bind_properties();
        return fleet_cmdr;
    }

private:
    void bind_properties()
    {
        commander.getter([this]() -> std::string { return _commander; });
        commander.setter(
            [this](const std::string& commander_)
            {
                if(commander_ != _commander)
                {
                    _commander = commander_;
                    _event_manager->post(fleet_commander_changed_event::create(commander_));
                }
            });
    }

public:
    p::property<std::string> commander;
    p::value_property<std::string> battle;

private:
    m::event_manager::ptr _event_manager;
    std::string _commander;
};

class spaceship
    : public u::noncopyable_nonmovable
{
public:
    virtual ~spaceship() GO_DEFAULT_DESTRUCTOR

private:
    spaceship(const std::string& name_, const std::string& captain_, const std::string& fleet_commander_)
        : u::noncopyable_nonmovable()
        , fleet_commander("fleet_commander")
        , name("name", name_)
        , captain("captain", captain_)
        , _fleet_commander(fleet_commander_)
    {
    }

public:
    static std::shared_ptr<spaceship> create(const std::string& name_, const std::string& captain_, const std::string& fleet_commander_)
    {
        std::shared_ptr<spaceship> ship(new spaceship(name_, captain_, fleet_commander_));
        ship->bind_properties();
        return ship;
    }

public:
    rop::property<std::string> fleet_commander;
    p::value_property<std::string> name;
    p::value_property<std::string> captain;

public:
    void on_fleet_commander_changed(const m::event::ptr& e)
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
        fleet_commander.getter([this]() -> std::string { return _fleet_commander; });
    }

private:
    std::string _fleet_commander;
};

#define TEST_CASE_SHIPYARD \
    m::event_manager::ptr event_mgr = m::event_manager::create(); \
\
    fleet_commander::ptr fleet_cmdr = fleet_commander::create(event_mgr, "General Jan Dodonna", "Battle of Yavin"); \
\
    std::shared_ptr<spaceship> ship1 = spaceship::create("Millennium Falcon", "Han Solo", "General Jan Dodonna"); \
    std::shared_ptr<spaceship> ship2 = spaceship::create("X-Wing Red Leader", "Garven Dreis", "General Jan Dodonna"); \
    std::shared_ptr<spaceship> ship3 = spaceship::create("X-Wing Red Two", "Wedge Antilles", "General Jan Dodonna"); \
    std::shared_ptr<spaceship> ship4 = spaceship::create("X-Wing Red Three", "Biggs Darklighter", "General Jan Dodonna"); \
    std::shared_ptr<spaceship> ship5 = spaceship::create("X-Wing Red Four", "John D. Branon", "General Jan Dodonna"); \
    std::shared_ptr<spaceship> ship6 = spaceship::create("X-Wing Red Five", "Luke Skywalker", "General Jan Dodonna"); \
    std::shared_ptr<spaceship> ship7 = spaceship::create("Y-Wing Gold Leader", "Jon 'Dutch' Vander", "General Jan Dodonna"); \
    std::shared_ptr<spaceship> ship8 = spaceship::create("Y-Wing Gold Two", "Dex Tiree", "General Jan Dodonna"); \
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

TEST(std_event_manager_test_suite, test_command_manager)
{
    TEST_CASE_SHIPYARD

    // After connect
    EXPECT_EQ(std::string("General Jan Dodonna"), ship1->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship2->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship3->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship4->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship5->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship6->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship7->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship8->fleet_commander());

    // Change fleet commander
    fleet_cmdr->commander("Admiral Gial Ackbar");

    EXPECT_EQ(std::string("General Jan Dodonna"), ship1->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship2->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship3->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship4->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship5->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship6->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship7->fleet_commander());
    EXPECT_EQ(std::string("General Jan Dodonna"), ship8->fleet_commander());

    event_mgr->fire_events();

    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship1->fleet_commander());
    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship2->fleet_commander());
    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship3->fleet_commander());
    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship4->fleet_commander());
    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship5->fleet_commander());
    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship6->fleet_commander());
    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship7->fleet_commander());
    EXPECT_EQ(std::string("Admiral Gial Ackbar"), ship8->fleet_commander());

    TEST_CASE_SCRAP_HEAP
}

}

#endif  // Required C++11 feature is not supported by this compiler
