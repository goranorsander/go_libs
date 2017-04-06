//
//  event_manager_test_suite.cpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <gtest/gtest.h>
#include <go_boost/config.hpp>

#include <go_boost/mvvm.hpp>
#include <go_boost/property.hpp>

namespace m = go_boost::mvvm;
namespace p = go_boost::property;
namespace rop = go_boost::property::read_only;
namespace s = go_boost::signals;
namespace u = go_boost::utility;

namespace
{

// Test event_manager
const std::string fleet_commander_changed_event_type("fleet commander changed");

class fleet_commander_changed_event
    : public m::event
{
public:
    typedef fleet_commander_changed_event this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<fleet_commander_changed_event> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<fleet_commander_changed_event> wptr;

public:
    virtual ~fleet_commander_changed_event()
    {
    }

protected:
    explicit fleet_commander_changed_event(const std::string& flt_cmd)
        : m::event(fleet_commander_changed_event_type)
        , fleet_commander("fleet_commander", flt_cmd)
    {
    }

public:
    rop::value_property<std::string> fleet_commander;

public:
    static ptr create(const std::string& flt_cmd)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() {}
            explicit make_shared_enabler(const std::string& flt_cmd) : this_type(flt_cmd) {}
        };
        return boost::make_shared<make_shared_enabler, const std::string&>(flt_cmd);
#else
        return boost::shared_ptr<this_type>(new this_type(flt_cmd));
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
    virtual ~fleet_commander()
    {
    }

private:
    fleet_commander(const m::event_manager::ptr& event_mgr, const std::string& cmd, const std::string& btl)
        : u::noncopyable_nonmovable()
        , commander("commander")
        , battle("battle", btl)
        , _event_manager(event_mgr)
        , _commander(cmd)
    {
        bind_properties();
    }

public:
    static ptr create(const m::event_manager::ptr& event_mgr, const std::string& cmd, const std::string& btl)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() {}
            make_shared_enabler(const m::event_manager::ptr& event_mgr, const std::string& cmd, const std::string& btl) : this_type(event_mgr, cmd, btl) {}
        };
        return boost::make_shared<make_shared_enabler, const m::event_manager::ptr&, const std::string&, const std::string&>(event_mgr, cmd, btl);
#else
        return boost::shared_ptr<this_type>(new this_type(event_mgr, cmd, btl));
#endif // BOOST_MSVC > 1500
    }

public:
    p::property<std::string> commander;
    p::value_property<std::string> battle;

private:
    std::string get_commander() const
    {
        return _commander;
    }

    void set_commander(const std::string& v)
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
    m::event_manager::ptr _event_manager;
    std::string _commander;
};

class spaceship
    : private u::noncopyable_nonmovable
{
public:
    virtual ~spaceship() {}

public:
    spaceship(const std::string& nme, const std::string& cpt, const std::string& flt_cmd)
        : u::noncopyable_nonmovable()
        , fleet_commander("fleet_commander")
        , name("name", nme)
        , captain("captain", cpt)
        , _fleet_commander(flt_cmd)
    {
        bind_properties();
    }

public:
    rop::property<std::string> fleet_commander;
    p::value_property<std::string> name;
    p::value_property<std::string> captain;

public:
    void on_fleet_commander_changed(const m::event::ptr& e)
    {
        fleet_commander_changed_event::ptr fleet_commander_changed = boost::dynamic_pointer_cast<fleet_commander_changed_event>(e);
        if(fleet_commander_changed)
        {
            _fleet_commander = fleet_commander_changed->fleet_commander();
        }
    }

private:
    std::string get_fleet_commander() const
    {
        return _fleet_commander;
    }

    void bind_properties()
    {
        fleet_commander.getter(boost::bind(&spaceship::get_fleet_commander, this));
    }

private:
    std::string _fleet_commander;
};

#if BOOST_MSVC > 1500
#define TEST_CASE_SHIPYARD \
    m::event_manager::ptr event_mgr = m::event_manager::create(); \
\
    fleet_commander::ptr flt_cmd = fleet_commander::create(event_mgr, "General Jan Dodonna", "Battle of Yavin"); \
\
    boost::shared_ptr<spaceship> ship1 = boost::make_shared<spaceship, const std::string&, const std::string&, const std::string&>("Millennium Falcon", "Han Solo", "General Jan Dodonna"); \
    boost::shared_ptr<spaceship> ship2 = boost::make_shared<spaceship, const std::string&, const std::string&, const std::string&>("X-Wing Red Leader", "Garven Dreis", "General Jan Dodonna"); \
    boost::shared_ptr<spaceship> ship3 = boost::make_shared<spaceship, const std::string&, const std::string&, const std::string&>("X-Wing Red Two", "Wedge Antilles", "General Jan Dodonna"); \
    boost::shared_ptr<spaceship> ship4 = boost::make_shared<spaceship, const std::string&, const std::string&, const std::string&>("X-Wing Red Three", "Biggs Darklighter", "General Jan Dodonna"); \
    boost::shared_ptr<spaceship> ship5 = boost::make_shared<spaceship, const std::string&, const std::string&, const std::string&>("X-Wing Red Four", "John D. Branon", "General Jan Dodonna"); \
    boost::shared_ptr<spaceship> ship6 = boost::make_shared<spaceship, const std::string&, const std::string&, const std::string&>("X-Wing Red Five", "Luke Skywalker", "General Jan Dodonna"); \
    boost::shared_ptr<spaceship> ship7 = boost::make_shared<spaceship, const std::string&, const std::string&, const std::string&>("Y-Wing Gold Leader", "Jon 'Dutch' Vander", "General Jan Dodonna"); \
    boost::shared_ptr<spaceship> ship8 = boost::make_shared<spaceship, const std::string&, const std::string&, const std::string&>("Y-Wing Gold Two", "Dex Tiree", "General Jan Dodonna"); \
\
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship1, _1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship2, _1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship3, _1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship4, _1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship5, _1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship6, _1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship7, _1)); \
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship8, _1));
#else
#define TEST_CASE_SHIPYARD \
    m::event_manager::ptr event_mgr = m::event_manager::create(); \
\
    fleet_commander::ptr flt_cmd = fleet_commander::create(event_mgr, "General Jan Dodonna", "Battle of Yavin"); \
\
    boost::shared_ptr<spaceship> ship1(new spaceship("Millennium Falcon", "Han Solo", "General Jan Dodonna")); \
    boost::shared_ptr<spaceship> ship2(new spaceship("X-Wing Red Leader", "Garven Dreis", "General Jan Dodonna")); \
    boost::shared_ptr<spaceship> ship3(new spaceship("X-Wing Red Two", "Wedge Antilles", "General Jan Dodonna")); \
    boost::shared_ptr<spaceship> ship4(new spaceship("X-Wing Red Three", "Biggs Darklighter", "General Jan Dodonna")); \
    boost::shared_ptr<spaceship> ship5(new spaceship("X-Wing Red Four", "John D. Branon", "General Jan Dodonna")); \
    boost::shared_ptr<spaceship> ship6(new spaceship("X-Wing Red Five", "Luke Skywalker", "General Jan Dodonna")); \
    boost::shared_ptr<spaceship> ship7(new spaceship("Y-Wing Gold Leader", "Jon 'Dutch' Vander", "General Jan Dodonna")); \
    boost::shared_ptr<spaceship> ship8(new spaceship("Y-Wing Gold Two", "Dex Tiree", "General Jan Dodonna")); \
\
    const m::event_subscription_key_type ship1_key = event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship1, _1)); \
    const m::event_subscription_key_type ship2_key = event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship2, _1)); \
    const m::event_subscription_key_type ship3_key = event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship3, _1)); \
    const m::event_subscription_key_type ship4_key = event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship4, _1)); \
    const m::event_subscription_key_type ship5_key = event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship5, _1)); \
    const m::event_subscription_key_type ship6_key = event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship6, _1)); \
    const m::event_subscription_key_type ship7_key = event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship7, _1)); \
    const m::event_subscription_key_type ship8_key = event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship8, _1));
#endif  // BOOST_MSVC > 1500

TEST(boost_event_manager_test_suite, test_command_manager)
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
    flt_cmd->commander("Admiral Gial Ackbar");

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
}

}
