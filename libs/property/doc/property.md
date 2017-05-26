# GO Property Library

```c++
<go/property.hpp>
```

## Description

**Properties**

A **property** is a member that looks like an ordinary data member. The most important difference
between a **property** a member and a data member is the *accessors*. The *accessors* provide a
mechanism to associate logic with property *get* and *set* operations. Another important feature of
a **property** member is that it can be identified by name.

## Example

A sample class that implement a spacship with three properties.

```c++
#include <functional>
#include <go/config.hpp>
#include <go/property.hpp>

namespace p = go::property;
namespace ph = std::placeholders;

class spaceship
{
public:
    ~spaceship() = default;

    spaceship()
        : _crew_complement(0)
        , _name()
        , _max_speed(0.0)
        , crew_complement("crew_complement",
            [this]() -> int { return _crew_complement; },
            [this](const int& v) { if(v != _crew_complement) { _crew_complement = v; } })
        , name("name",
            [this]() -> double { return _name; },
            [this](const std::string& v) { if(v != _name) { _name = v; } })
        , max_speed("max_speed",
            [this]() -> std::string { return _max_speed; },
            [this](const double& v) { if(v != _max_speed) { _max_speed = v; } })
    {
    }

public:
    p::property<int> crew_complement;
    p::property<double> max_speed;
    p::property<std::string> name;

private:
    int _crew_complement;
    double _max_speed;
    std::string _name;
};
```

## Reference

### Class reference

**Property class templates**

* go\::property\::**basic_property**
  * go\::property\::**property**
  * go\::property\::**wproperty**
  * go\::property\::**u16property**
  * go\::property\::**u32property**
* go\::property\::**basic_reference_property**
  * go\::property\::**reference_property**
  * go\::property\::**reference_wproperty**
  * go\::property\::**reference_u16property**
  * go\::property\::**reference_u32property**
* go\::property\::**basic_value_property**
  * go\::property\::**value_property**
  * go\::property\::**value_wproperty**
  * go\::property\::**value_u16property**
  * go\::property\::**value_u32property**

**Read-only property class templates**

* go\::property\::read_only\::**basic_property**
  * go\::property\::read_only\::**property**
  * go\::property\::read_only\::**wproperty**
  * go\::property\::read_only\::**u16property**
  * go\::property\::read_only\::**u32property**
* go\::property\::read_only\::**basic_reference_property**
  * go\::property\::read_only\::**reference_property**
  * go\::property\::read_only\::**reference_wproperty**
  * go\::property\::read_only\::**reference_u16property**
  * go\::property\::read_only\::**reference_u32property**
* go\::property\::read_only\::**basic_value_property**
  * go\::property\::read_only\::**value_property**
  * go\::property\::read_only\::**value_wproperty**
  * go\::property\::read_only\::**value_u16property**
  * go\::property\::read_only\::**value_u32property**

**Write-only property class templates**

* go\::property\::write_only\::**basic_property**
  * go\::property\::write_only\::**property**
  * go\::property\::write_only\::**wproperty**
  * go\::property\::write_only\::**u16property**
  * go\::property\::write_only\::**u32property**
* go\::property\::write_only\::**basic_reference_property**
  * go\::property\::write_only\::**reference_property**
  * go\::property\::write_only\::**reference_wproperty**
  * go\::property\::write_only\::**reference_u16property**
  * go\::property\::write_only\::**reference_u32property**
* go\::property\::write_only\::**basic_value_property**
  * go\::property\::write_only\::**value_property**
  * go\::property\::write_only\::**value_wproperty**
  * go\::property\::write_only\::**value_u16property**
  * go\::property\::write_only\::**value_u32property**

**Nameless property class templates**

* go\::property\::nameless\::**property**
* go\::property\::nameless\::**reference_property**
* go\::property\::nameless\::**value_property**

**Nameless read-only property class templates**

* go\::property\::nameless\::read_only\::**property**
* go\::property\::nameless\::read_only\::**reference_property**
* go\::property\::nameless\::read_only\::**value_property**

**Nameless write-onlyproperty class templates**

* go\::property\::nameless\::write_only\::**property**
* go\::property\::nameless\::write_only\::**reference_property**
* go\::property\::nameless\::write_only\::**value_property**

Copyright &copy; 2014-2017 Göran Orsander
