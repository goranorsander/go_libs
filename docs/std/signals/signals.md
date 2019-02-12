---
layout: std_lib_signals
---

```c++
namespace go::signals
```

# GO Std Signals Library

```c++
<go/signals.hpp>
```

## Description

**Signals**

A **signal** represent a callback with multiple targets. Signals are connected to 
some set of slots, which are callback receivers. The slots are called when the 
**signal** is *"emitted"*.

The signals in the **Boost.Signals2** library provide a good framework for 
implementing C#-style events and delegates. Unfortunately the C++ Standard 
Library have no alternative to **Boost.Signals2**. 

The **GO Signals Library** implementation of signals is much inspired by the 
**Boost.Signals2** library. It try to use the same terminology as 
**Boost.Signals2**. The implementation use **std::function** to define **signal** 
signatures and a variadic template based call function to emit signals.

## Example

This example is intended to show how signals can be used. It implements a 
simple fire lasers command that the fleet commander can give to the ships.

```c++
#include <functional>
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
    typedef go::signals::signal<std::function<void(const bool&)>> fire_lasers_signal;

    virtual ~fleet_commander() = default;

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
    typedef std::shared_ptr<spaceship> ptr;

    virtual ~spaceship()
    {
        fleet_commander::ptr commander = _fleet_commander.lock();
        if (commander)
            commander->fire_lasers.disconnect(_fire_lasers_slot_key);
    }

    spaceship(const fleet_commander::ptr& fleet_commander_,
        const std::string& name_, const std::string& captain_)
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

    bool _lasers_firing;
    fleet_commander::wptr _fleet_commander;
    s::slot_key_type _fire_lasers_slot_key;
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
```

Output

```
Millennium Falcon start firing lasers
X-Wing Red Two start firing lasers
X-Wing Red Five start firing lasers
Millennium Falcon stop firing lasers
X-Wing Red Two stop firing lasers
X-Wing Red Five stop firing lasers
```

## Reference

### Class reference

* [signal](./class_template_signal.html)
* [slot_key](./class_slot_key.html)
