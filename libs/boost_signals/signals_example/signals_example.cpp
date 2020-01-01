//
//  signals_example.cpp
//
//  Copyright 2017-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_boost/namespace_alias.hpp>
#include <go_boost/property.hpp>
#include <go_boost/signals.hpp>
#include <iostream>

class fleet_commander
{
public:
    typedef boost::shared_ptr<fleet_commander> ptr;
    typedef boost::weak_ptr<fleet_commander> wptr;
    typedef GO_BOOST_TYPENAME boost::signals2::signal<void(const bool&)> fire_lasers_signal;

    virtual ~fleet_commander() {}

    fleet_commander(const std::string& commander_)
        : commander("commander", commander_)
        , fire_lasers()
    {
    }

    p::value_property<std::string> commander;

    fire_lasers_signal fire_lasers;
};

class spaceship
{
public:
    typedef boost::shared_ptr<spaceship> ptr;

    virtual ~spaceship()
    {
        fleet_commander::ptr commander = _fleet_commander.lock();
        if (commander)
            commander->fire_lasers.disconnect(boost::bind(&p::property<bool>::set, &lasers_firing, _1));
    }

    spaceship(const fleet_commander::ptr& fleet_commander_, const std::string& name_, const std::string& captain_)
        : name("name", name_)
        , captain("captain", captain_)
        , lasers_firing("lasers_firing")
        , _lasers_firing(false)
        , _fleet_commander(fleet_commander_)
    {
        lasers_firing.getter(boost::bind(&spaceship::get_lasers_firing, this));
        lasers_firing.setter(boost::bind(&spaceship::set_lasers_firing, this, _1));
        fleet_commander_->fire_lasers.connect(boost::bind(&p::property<bool>::set, &lasers_firing, _1));
    }

    p::value_property<std::string> name;
    p::value_property<std::string> captain;
    p::property<bool> lasers_firing;

private:
    bool get_lasers_firing() const { return _lasers_firing; }

    void set_lasers_firing(const bool& lasers_firing_)
    {
        if (lasers_firing_ != _lasers_firing)
        {
            _lasers_firing = lasers_firing_;
            std::cout << name.get() << (_lasers_firing ? " start " : " stop ") << "firing lasers" << std::endl;
        }
    }

private:
    bool _lasers_firing;
    fleet_commander::wptr _fleet_commander;
};

int main()
{
    fleet_commander::ptr commander(new fleet_commander("Admiral Gial Ackbar"));

    spaceship::ptr ship1(new spaceship(commander, "Millennium Falcon", "Han Solo"));
    spaceship::ptr ship2(new spaceship(commander, "X-Wing Red Two", "Wedge Antilles"));
    spaceship::ptr ship3(new spaceship(commander, "X-Wing Red Five", "Luke Skywalker"));

    commander->fire_lasers(true);
    commander->fire_lasers(false);

    return 0;
}
