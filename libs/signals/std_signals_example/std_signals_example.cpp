//
//  std_value_property_example.cpp
//
//  Copyright 2017-2018 Göran Orsander
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
#include <go/property.hpp>
#include <go/signals.hpp>

namespace p = go::property;
namespace s = go::signals;
namespace ph = std::placeholders;

class fleet_commander
{
public:
    typedef std::shared_ptr<fleet_commander> ptr;
    typedef std::weak_ptr<fleet_commander> wptr;
    typedef s::signal<std::function<void(const bool&)>> fire_lasers_signal;

    virtual ~fleet_commander() = default;

    explicit fleet_commander(const std::string& commander_)
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
    typedef std::shared_ptr<spaceship> ptr;

    virtual ~spaceship()
    {
        fleet_commander::ptr commander = _fleet_commander.lock();
        if (commander)
            commander->fire_lasers.disconnect(_fire_lasers_slot_key);
    }

    spaceship(const fleet_commander::ptr& fleet_commander_, const std::string& name_, const std::string& captain_)
        : name("name", name_)
        , captain("captain", captain_)
        , lasers_firing("lasers_firing")
        , _lasers_firing(false)
        , _fleet_commander(fleet_commander_)
        , _fire_lasers_slot_key()
    {
        lasers_firing.getter([this]() { return _lasers_firing; });
        lasers_firing.setter(std::bind(&spaceship::set_lasers_firing, this, ph::_1));
        _fire_lasers_slot_key = fleet_commander_->fire_lasers.connect(std::bind(&p::property<bool>::set, &lasers_firing, ph::_1));
    }

    p::value_property<std::string> name;
    p::value_property<std::string> captain;
    p::property<bool> lasers_firing;

private:
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
    s::slot_key _fire_lasers_slot_key;
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

#endif  // Required C++11 feature is not supported by this compiler
