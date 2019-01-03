//
//  event_manager_example.cpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
int main() { return -1; }
#else

#include <iostream>
#include <go/mvvm.hpp>
#include <go/property.hpp>
#include <go/signals.hpp>

namespace m = go::mvvm;
namespace p = go::property;
namespace s = go::signals;
namespace ph = std::placeholders;
namespace rop = go::property::read_only;

const std::string fleet_commander_changed_event_type("fleet commander changed");

class fleet_commander_changed_event
    : public m::event
{
public:
    typedef fleet_commander_changed_event this_type;
    typedef std::shared_ptr<fleet_commander_changed_event> ptr;

public:
    virtual ~fleet_commander_changed_event() GO_DEFAULT_DESTRUCTOR

    fleet_commander_changed_event()
        : m::event(fleet_commander_changed_event_type)
    {
    }
};

class fleet_commander
{
public:
    typedef std::shared_ptr<fleet_commander> ptr;

    virtual ~fleet_commander() GO_DEFAULT_DESTRUCTOR

    fleet_commander(const m::event_manager::ptr& event_manager_, const std::string& commander_)
        : commander("commander")
        , _event_manager(event_manager_)
        , _commander(commander_)
    {
        commander.getter([this]() -> std::string { return _commander; });
        commander.setter(
            [this](const std::string& commander_)
            {
                if (commander_ != _commander)
                {
                    _commander = commander_;
                    _event_manager->post(fleet_commander_changed_event::ptr(new fleet_commander_changed_event()));
                }
            });
    }

    p::property<std::string> commander;

private:
    m::event_manager::ptr _event_manager;
    std::string _commander;
};

class spaceship
{
public:
    typedef std::shared_ptr<spaceship> ptr;

    virtual ~spaceship() GO_DEFAULT_DESTRUCTOR

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
        fleet_commander_changed_event::ptr fleet_commander_changed = std::dynamic_pointer_cast<fleet_commander_changed_event>(e);
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

    const m::event_subscription_key_type ship1_key = event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship::on_fleet_commander_changed, ship1, ph::_1));
    const m::event_subscription_key_type ship2_key = event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship::on_fleet_commander_changed, ship2, ph::_1));
    const m::event_subscription_key_type ship3_key = event_mgr->subscribe(fleet_commander_changed_event_type, std::bind(&spaceship::on_fleet_commander_changed, ship3, ph::_1));

    commander->commander("General Jan Dodonna");
    event_mgr->fire_events();
    commander->commander("Admiral Gial Ackbar");
    event_mgr->fire_events();

    return 0;
}

#endif  // Required C++11 feature is not supported by this compiler
