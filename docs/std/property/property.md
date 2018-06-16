---
layout: std_lib_property
---

```c++
namespace go::property
```

# GO Std Property Library

```c++
<go/property.hpp>
```

## Description

**Properties**

A **property** is a member that looks like an ordinary data member. The most important
difference between a **property** member and a data member is the *accessors*. The
*accessors* provide a mechanism to associate logic with property *get* and *set*
operations. Another important feature of a **property** member is that it can be
identified by name.

## Example

A sample class that implement a spacship with three properties.

```c++
#include <functional>
#include <go/config.hpp>
#include <go/property.hpp>

namespace p = go::property;

class spaceship
{
public:
    ~spaceship() = default;

    spaceship()
        : crew_complement("crew_complement")
        , max_speed("max_speed")
        , name("name", "USS Enterprise (NCC-1701-D)")
        , _crew_complement(1012)
        , _max_speed(9.8)
    {
        crew_complement.getter([this]() -> int { return _crew_complement; });
        crew_complement.setter([this](const int& other) { if(other != _crew_complement) { _crew_complement = other; } });
        max_speed.bind(_max_speed);
    }

public:
    p::property<int> crew_complement;
    p::reference_property<double> max_speed;
    p::value_property<std::string> name;

private:
    int _crew_complement;
    double _max_speed;
};

int main()
{
    spaceship s;
    std::cout << "Name: " << s.name().c_str() << ", crew: " << s.crew_complement << ", speed: " << s.max_speed << std::endl;

    s.crew_complement = 430;
    s.max_speed = 9.0;
    s.name = "USS Enterprise (NCC-1701)";
    std::cout << "Name: " << s.name().c_str() << ", crew: " << s.crew_complement << ", speed: " << s.max_speed << std::endl;

    return 0;
}
```

Output

```
Name: USS Enterprise (NCC-1701-D), crew: 1012, speed: 9.8
Name: USS Enterprise (NCC-1701), crew: 430, speed: 9
```

## Reference

### Class reference

* [go\::property\::**basic_property**](./class_template_basic_property.html)
  * [go\::property\::**property**](./class_template_basic_property.html)
  * [go\::property\::**wproperty**](./class_template_basic_property.html)
  * [go\::property\::**u16property**](./class_template_basic_property.html)
  * [go\::property\::**u32property**](./class_template_basic_property.html)
* [go\::property\::**basic_reference_property**](./class_template_basic_reference_property.html)
  * [go\::property\::**reference_property**](./class_template_basic_reference_property.html)
  * [go\::property\::**reference_wproperty**](./class_template_basic_reference_property.html)
  * [go\::property\::**reference_u16property**](./class_template_basic_reference_property.html)
  * [go\::property\::**reference_u32property**](./class_template_basic_reference_property.html)
* [go\::property\::**basic_value_property**](./class_template_basic_value_property.html)
  * [go\::property\::**value_property**](./class_template_basic_value_property.html)
  * [go\::property\::**value_wproperty**](./class_template_basic_value_property.html)
  * [go\::property\::**value_u16property**](./class_template_basic_value_property.html)
  * [go\::property\::**value_u32property**](./class_template_basic_value_property.html)
