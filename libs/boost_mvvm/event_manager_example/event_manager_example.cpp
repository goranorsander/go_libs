//
//  event_manager_example.cpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_boost/mvvm.hpp>
#include <go_boost/property.hpp>
#include <go_boost/signals.hpp>
#include <iostream>

namespace m = go_boost::mvvm;
namespace p = go_boost::property;
namespace s = go_boost::signals;
namespace rop = go_boost::property::read_only;

const std::string fleet_commander_changed_event_type("fleet commander changed");

class fleet_commander_changed_event
    : public m::event
{
public:
    typedef fleet_commander_changed_event this_type;
    typedef boost::shared_ptr<fleet_commander_changed_event> ptr;

public:
    virtual ~fleet_commander_changed_event() {}

    fleet_commander_changed_event()
        : m::event(fleet_commander_changed_event_type)
    {
    }
};

class fleet_commander
{
public:
    typedef boost::shared_ptr<fleet_commander> ptr;

    virtual ~fleet_commander() {}

    fleet_commander(const m::event_manager::ptr& event_manager_, const std::string& commander_)
        : commander("commander")
        , _event_manager(event_manager_)
        , _commander(commander_)
    {
        commander.getter(boost::bind(&fleet_commander::get_commander, this));
        commander.setter(boost::bind(&fleet_commander::set_commander, this, _1));
    }

    p::property<std::string> commander;

private:
    std::string get_commander() const { return _commander; }

    void set_commander(const std::string& v)
    {
        if (v != _commander)
        {
            _commander = v;
            _event_manager->post(fleet_commander_changed_event::ptr(new fleet_commander_changed_event()));
        }
    }

private:
    m::event_manager::ptr _event_manager;
    std::string _commander;
};

class spaceship
{
public:
    typedef boost::shared_ptr<spaceship> ptr;

    virtual ~spaceship() {}

    spaceship(const fleet_commander::ptr& fleet_commander_, const std::string& name_, const std::string& captain_)
        : fleet_commander("fleet_commander", fleet_commander_)
        , name("name", name_)
        , captain("captain", captain_)
    {
    }

    rop::value_property<fleet_commander::ptr> fleet_commander;
    p::value_property<std::string> name;
    p::value_property<std::string> captain;

    void on_fleet_commander_changed(const m::event::ptr& e)
    {
        fleet_commander_changed_event::ptr fleet_commander_changed = boost::dynamic_pointer_cast<fleet_commander_changed_event>(e);
        if (fleet_commander_changed)
        {
            std::cout << name.get() << " acknowledge " << fleet_commander.get()->commander() << " as new fleet commander" << std::endl;
        }
    }
};

int main()
{
    m::event_manager::ptr event_mgr = m::event_manager::create();

    fleet_commander::ptr commander(new fleet_commander(event_mgr, "Admiral Gial Ackbar"));

    spaceship::ptr ship1(new spaceship(commander, "Millennium Falcon", "Han Solo"));
    spaceship::ptr ship2(new spaceship(commander, "X-Wing Red Two", "Wedge Antilles"));
    spaceship::ptr ship3(new spaceship(commander, "X-Wing Red Five", "Luke Skywalker"));

    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship1, _1));
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship2, _1));
    event_mgr->subscribe(fleet_commander_changed_event_type, boost::bind(&spaceship::on_fleet_commander_changed, ship3, _1));

    commander->commander("General Jan Dodonna");
    event_mgr->fire_events();
    commander->commander("Admiral Gial Ackbar");
    event_mgr->fire_events();

    event_mgr->unsubscribe_all();

    return 0;
}
