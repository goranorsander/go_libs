---
layout: boost_lib_mvvm_utility
---

```c++
namespace go_boost::mvvm::utility
```

# functor set_property_value_notify_changed

```c++
<go_boost/mvvm/utility/phoenix_property_value_access_functor.hpp>
```

[Boost.Phoenix](https://www.boost.org/doc/libs/1_68_0/libs/phoenix/doc/html/index.html)
is the most important Boost library for functional programming according to
Boris Schäling, author of [The Boost C++ Libraries](https://theboostcpplibraries.com/boost.phoenix).

The **set_property_value_notify_changed** functor enables lambda style function binding to
the *setter* function of a property to a *functor*, i.e. a
[function object](https://en.wikipedia.org/wiki/Function_object).

It is declared as:

```c++
struct set_property_value_notify_changed_functor
{
    template <typename Arg1, typename Arg2, typename Arg3>
    void operator()(const Arg1& property_name, Arg2 notify_property_changed, Arg3& current_value, const Arg3& new_value) const;
};

static const boost::phoenix::function<set_property_value_notify_changed_functor> set_property_value_notify_changed;
```

## Functor parameters

Parameter | Description
-|-
property_name|Property name
notify_property_changed|Binding to *on property changed* function
current_value|Reference to the member that store the property value
new_value|New value to assign the property

## Example

This example is intended to show how **Boost.Phoenix** functors can be
used to create lambda style function bindings to property *getter* and
*setter* functions. It implements two simple speed commands that set the
speed property on the spaceship object.

```c++
#include <go_boost/config.hpp>
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
    virtual ~spaceship() {}

public:
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
        bind_properties();
    }

private:
    void bind_properties()
    {
        name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_name)));
        captain.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_captain)));
        speed.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_speed)));
        speed.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4)(speed.name(), boost::bind(&spaceship::notify_property_changed, this, _1), bp::ref(_speed), bph::arg1));
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
    virtual ~spaceship_observer() {}

    spaceship_observer() {}

    void connect(const boost::shared_ptr<spaceship>& ship)
    {
        if (ship)
        {
            ship->property_changed.connect(boost::bind(&spaceship_observer::notify_property_changed, this, _1, _2));
        }
    }

    void disconnect(const boost::shared_ptr<spaceship>& ship)
    {
        if (ship)
        {
            ship->property_changed.disconnect(boost::bind(&spaceship_observer::notify_property_changed, this, _1, _2));
        }
    }

    void notify_property_changed(const m::object::ptr& o, const m::property_changed_arguments::ptr& a)
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

    boost::shared_ptr<spaceship> ship1 = boost::make_shared<spaceship, const m::command_manager::ptr&, const std::string&, const std::string&>(command_mgr, "USS Enterprise", "Captain James T Kirk");
    boost::shared_ptr<spaceship> ship2 = boost::make_shared<spaceship, const m::command_manager::ptr&, const std::string&, const std::string&>(command_mgr, "Executor", "Lord Darth Vader");

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
```

Output

```
USS Enterprise cruising at impulse speed
Executor cruising at impulse speed
USS Enterprise changed speed to warp
Executor changed speed to warp
USS Enterprise changed speed to impulse
Executor changed speed to impulse
```
