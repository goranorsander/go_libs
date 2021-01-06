//
//  basic_event_manager_test_suite.cpp
//
//  Copyright 2018-2021 Göran Orsander
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
TEST(std_basic_event_manager_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>
#include <go/namespace_alias.hpp>
#include <go/property.hpp>
#include <go/string.hpp>

namespace
{

// Test event_manager
const s::u8string fleet_commander_changed_event_type(s::create<s::u8string>("fleet commander changed"));

class fleet_commander_changed_event
    : public m::basic_event<s::u8string>
{
public:
    typedef fleet_commander_changed_event this_type;
    typedef std::shared_ptr<fleet_commander_changed_event> ptr;
    typedef std::weak_ptr<fleet_commander_changed_event> wptr;

public:
    virtual ~fleet_commander_changed_event() GO_DEFAULT_DESTRUCTOR

protected:
    explicit fleet_commander_changed_event(const s::u8string& fleet_commander_)
        : m::basic_event<s::u8string>(fleet_commander_changed_event_type)
        , fleet_commander(s::create<s::u8string>("fleet_commander"), fleet_commander_)
    {
    }

public:
    pro::value_u8property<s::u8string> fleet_commander;

public:
    static ptr create(const s::u8string& fleet_commander_)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const s::u8string& fleet_commander_) : this_type(fleet_commander_) {}
        };

        return std::make_shared<make_shared_enabler, const s::u8string&>(fleet_commander_);
    }
};

class fleet_commander
    : public tt::noncopyable_nonmovable
{
public:
    typedef std::shared_ptr<fleet_commander> ptr;
    typedef std::weak_ptr<fleet_commander> wptr;

public:
    virtual ~fleet_commander() GO_DEFAULT_DESTRUCTOR

private:
    fleet_commander(const m::basic_event_manager<s::u8string>::ptr& event_manager_, const s::u8string& commander_, const s::u8string& battle_)
        : tt::noncopyable_nonmovable()
        , commander(s::create<s::u8string>("commander"))
        , battle(s::create<s::u8string>("battle"), battle_)
        , _event_manager(event_manager_)
        , _commander(commander_)
    {
    }

public:
    static ptr create(const m::basic_event_manager<s::u8string>::ptr& event_manager_, const s::u8string& commander_, const s::u8string& battle_)
    {
        struct make_shared_enabler
            : public fleet_commander
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(const m::basic_event_manager<s::u8string>::ptr& event_manager_, const s::u8string& commander_, const s::u8string& battle_) : fleet_commander(event_manager_, commander_, battle_) {}
        };

        ptr fleet_cmdr = std::make_shared<make_shared_enabler, const m::basic_event_manager<s::u8string>::ptr&, const s::u8string&, const s::u8string&>(event_manager_, commander_, battle_);
        fleet_cmdr->bind_properties();
        return fleet_cmdr;
    }

private:
    void bind_properties()
    {
        commander.getter([this]() -> s::u8string { return _commander; });
        commander.setter(
            [this](const s::u8string& commander_)
            {
                if(commander_ != _commander)
                {
                    _commander = commander_;
                    _event_manager->post(fleet_commander_changed_event::create(commander_));
                }
            });
    }

public:
    p::u8property<s::u8string> commander;
    p::value_u8property<s::u8string> battle;

private:
    m::basic_event_manager<s::u8string>::ptr _event_manager;
    s::u8string _commander;
};

class spaceship
    : public tt::noncopyable_nonmovable
{
public:
    virtual ~spaceship() GO_DEFAULT_DESTRUCTOR

private:
    spaceship(const s::u8string& name_, const s::u8string& captain_, const s::u8string& fleet_commander_)
        : tt::noncopyable_nonmovable()
        , fleet_commander(s::create<s::u8string>("fleet_commander"))
        , name(s::create<s::u8string>("name"), name_)
        , captain(s::create<s::u8string>("captain"), captain_)
        , _fleet_commander(fleet_commander_)
    {
    }

public:
    static std::shared_ptr<spaceship> create(const s::u8string& name_, const s::u8string& captain_, const s::u8string& fleet_commander_)
    {
        std::shared_ptr<spaceship> ship(new spaceship(name_, captain_, fleet_commander_));
        ship->bind_properties();
        return ship;
    }

public:
    pro::u8property<s::u8string> fleet_commander;
    p::value_u8property<s::u8string> name;
    p::value_u8property<s::u8string> captain;

public:
    void on_fleet_commander_changed(const m::basic_event<s::u8string>::ptr& e)
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
        fleet_commander.getter([this]() -> s::u8string { return _fleet_commander; });
    }

private:
    s::u8string _fleet_commander;
};

#define TEST_CASE_SHIPYARD \
    m::basic_event_manager<s::u8string>::ptr event_mgr = m::basic_event_manager<s::u8string>::create(); \
\
    fleet_commander::ptr fleet_cmdr = fleet_commander::create(event_mgr, s::create<s::u8string>("General Jan Dodonna"), s::create<s::u8string>("Battle of Yavin")); \
\
    std::shared_ptr<spaceship> ship1 = spaceship::create(s::create<s::u8string>("Millennium Falcon"), s::create<s::u8string>("Han Solo"), s::create<s::u8string>("General Jan Dodonna")); \
    std::shared_ptr<spaceship> ship2 = spaceship::create(s::create<s::u8string>("X-Wing Red Leader"), s::create<s::u8string>("Garven Dreis"), s::create<s::u8string>("General Jan Dodonna")); \
    std::shared_ptr<spaceship> ship3 = spaceship::create(s::create<s::u8string>("X-Wing Red Two"), s::create<s::u8string>("Wedge Antilles"), s::create<s::u8string>("General Jan Dodonna")); \
    std::shared_ptr<spaceship> ship4 = spaceship::create(s::create<s::u8string>("X-Wing Red Three"), s::create<s::u8string>("Biggs Darklighter"), s::create<s::u8string>("General Jan Dodonna")); \
    std::shared_ptr<spaceship> ship5 = spaceship::create(s::create<s::u8string>("X-Wing Red Four"), s::create<s::u8string>("John D. Branon"), s::create<s::u8string>("General Jan Dodonna")); \
    std::shared_ptr<spaceship> ship6 = spaceship::create(s::create<s::u8string>("X-Wing Red Five"), s::create<s::u8string>("Luke Skywalker"), s::create<s::u8string>("General Jan Dodonna")); \
    std::shared_ptr<spaceship> ship7 = spaceship::create(s::create<s::u8string>("Y-Wing Gold Leader"), s::create<s::u8string>("Jon 'Dutch' Vander"), s::create<s::u8string>("General Jan Dodonna")); \
    std::shared_ptr<spaceship> ship8 = spaceship::create(s::create<s::u8string>("Y-Wing Gold Two"), s::create<s::u8string>("Dex Tiree"), s::create<s::u8string>("General Jan Dodonna")); \
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

TEST(std_basic_event_manager_test_suite, test_command_manager)
{
    TEST_CASE_SHIPYARD

    // After connect
    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship1->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship2->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship3->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship4->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship5->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship6->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship7->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship8->fleet_commander());

    // Change fleet commander
    fleet_cmdr->commander(s::create<s::u8string>("Admiral Gial Ackbar"));

    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship1->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship2->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship3->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship4->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship5->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship6->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship7->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("General Jan Dodonna"), ship8->fleet_commander());

    event_mgr->fire_events();

    EXPECT_EQ(s::create<s::u8string>("Admiral Gial Ackbar"), ship1->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("Admiral Gial Ackbar"), ship2->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("Admiral Gial Ackbar"), ship3->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("Admiral Gial Ackbar"), ship4->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("Admiral Gial Ackbar"), ship5->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("Admiral Gial Ackbar"), ship6->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("Admiral Gial Ackbar"), ship7->fleet_commander());
    EXPECT_EQ(s::create<s::u8string>("Admiral Gial Ackbar"), ship8->fleet_commander());

    TEST_CASE_SCRAP_HEAP
}

}

#endif  // Required C++11 feature is not supported by this compiler
