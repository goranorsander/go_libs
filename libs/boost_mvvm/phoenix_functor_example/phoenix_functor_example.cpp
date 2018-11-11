//
//  boost_phoenix_functor_example.cpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#if defined(GO_BOOST_NO_BOOST_PHOENIX)

GO_BOOST_MESSAGE("Boost.Phoenix is not supported by this compiler")

int main()
{
    return 0;
}

#else

#include <go_boost/mvvm.hpp>
#include <go_boost/mvvm/utility.hpp>
#include <go_boost/property.hpp>

namespace bp = boost::phoenix;
namespace bph = boost::phoenix::placeholders;
namespace m = go_boost::mvvm;
namespace mu = go_boost::mvvm::utility;
namespace p = go_boost::property;
namespace rop = go_boost::property::read_only;
namespace u = go_boost::utility;

const std::string fleet_commander_changed_event_type("fleet commander changed");

class spaceship
    : public m::observable_object
    , private u::noncopyable_nonmovable
{
public:
    virtual ~spaceship() GO_BOOST_DEFAULT_DESTRUCTOR

private:
    spaceship(const m::command_manager::ptr& command_manager_, const std::string& name_, const std::string& captain_)
        : m::observable_object()
        , u::noncopyable_nonmovable()
        , name("name")
        , captain("captain")
        , speed("speed")
        , impulse_speed_command("impulse_speed_command")
        , warp_speed_command("warp_speed_command")
        , _command_manager(command_manager_)
        , _name(name_)
        , _captain(captain_)
        , _speed("impulse")
        , _impulse_speed_command()
        , _warp_speed_command()
    {
    }

public:
    static boost::shared_ptr<spaceship> create(const m::command_manager::ptr& command_manager_, const std::string& name_, const std::string& captain_)
    {
        boost::shared_ptr<spaceship> ship(new spaceship(command_manager_, name_, captain_));
        ship->bind_properties();
        return ship;
    }

private:
    void bind_properties()
    {
        name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_name)));
        captain.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_captain)));
        speed.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_speed)));
        speed.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), speed.name(), boost::bind(&spaceship::notify_property_changed, this, _1, _2), bp::ref(_speed), bph::arg1, bph::arg2));
        impulse_speed_command.getter(bp::bind(mu::get_property_relay_command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(std::string("impulse_speed"), boost::bind(&spaceship::go_to_impulse, this, _1), boost::bind(&spaceship::can_go_to_impulse, this, _1), m::command_parameters::create(), bp::ref(_impulse_speed_command)));
        warp_speed_command.getter(bp::bind(mu::get_property_relay_command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(std::string("warp_speed"), boost::bind(&spaceship::go_to_warp, this, _1), boost::bind(&spaceship::can_go_to_warp, this, _1), m::command_parameters::create(), bp::ref(_warp_speed_command)));
    }

public:
    rop::property<std::string> name;
    rop::property<std::string> captain;
    p::property<std::string> speed;
    rop::property<m::command_interface::ptr> impulse_speed_command;
    rop::property<m::command_interface::ptr> warp_speed_command;

private:
    // impulse_speed_command property
    void go_to_impulse(const m::command_parameters::ptr& /*params*/)
    {
        speed = "impulse";
        if (_impulse_speed_command) { _impulse_speed_command->notify_can_execute_changed(); }
        if (_warp_speed_command) { _warp_speed_command->notify_can_execute_changed(); }
    }

    bool can_go_to_impulse(const m::command_parameters::ptr& /*params*/)
    {
        return _speed != "impulse";
    }

    // warp_speed_command property
    void go_to_warp(const m::command_parameters::ptr& /*params*/)
    {
        speed = "warp";
        if (_impulse_speed_command) { _impulse_speed_command->notify_can_execute_changed(); }
        if (_warp_speed_command) { _warp_speed_command->notify_can_execute_changed(); }
    }

    bool can_go_to_warp(const m::command_parameters::ptr& /*params*/)
    {
        return _speed != "warp";
    }

private:
    m::command_manager::ptr _command_manager;
    std::string _name;
    std::string _captain;
    std::string _speed;
    m::command_interface::ptr _impulse_speed_command;
    m::command_interface::ptr _warp_speed_command;
};

class spaceship_observer
{
public:
    virtual ~spaceship_observer() GO_BOOST_DEFAULT_DESTRUCTOR

    spaceship_observer()
    {
    }

    void connect(const boost::shared_ptr<spaceship>& ship)
    {
        if (ship)
        {
            ship->property_changed.connect(boost::bind(&spaceship_observer::on_property_changed, this, _1, _2));
        }
    }

    void disconnect(const boost::shared_ptr<spaceship>& ship)
    {
        if (ship)
        {
            ship->property_changed.disconnect(boost::bind(&spaceship_observer::on_property_changed, this, _1, _2));
        }
    }

    void on_property_changed(const m::object::ptr& o, const m::property_changed_arguments::ptr& a)
    {
        if (o && a)
        {
            boost::shared_ptr<spaceship> ship = boost::dynamic_pointer_cast<spaceship>(o);
            if (ship && a->property_name() == "speed")
            {
                std::cout << ship->name() << " changed speed to " << ship->speed() << std::endl;
            }
        }
    }
};

int main()
{
    m::command_manager::ptr command_mgr = m::command_manager::create();

    boost::shared_ptr<spaceship> ship1 = spaceship::create(command_mgr, "USS Enterprise", "Captain James T Kirk");
    boost::shared_ptr<spaceship> ship2 = spaceship::create(command_mgr, "Executor", "Lord Darth Vader");

    boost::shared_ptr<spaceship_observer> observer = boost::make_shared<spaceship_observer>();
    observer->connect(ship1);
    observer->connect(ship2);

    std::cout << ship1->name() << " cruising at " << ship1->speed() << " speed" << std::endl;
    std::cout << ship2->name() << " cruising at " << ship2->speed() << " speed" << std::endl;

    command_mgr->post(ship1->warp_speed_command);
    command_mgr->post(ship2->warp_speed_command);
    command_mgr->execute_commands();

    command_mgr->post(ship1->impulse_speed_command);
    command_mgr->post(ship2->impulse_speed_command);
    command_mgr->execute_commands();

    return 0;
}

#endif  // #if defined(GO_BOOST_NO_BOOST_PHOENIX)
