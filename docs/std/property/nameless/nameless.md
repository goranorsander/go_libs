---
layout: std_lib_property_nameless
---

```c++
namespace go::property::nameless
```

# GO Std Property Library

```c++
<go/property.hpp>
```

## Description

**Nameless properties**

A nameless **property** member cannot be identified by name.

## Example

A sample class that implement a spacship with three properties.

```c++
#include <functional>
#include <go/config.hpp>
#include <go/property.hpp>

namespace np = go::property::nameless;

class spaceship
{
public:
    ~spaceship() = default;

    spaceship()
        : crew_complement()
        , max_speed()
        , name("USS Enterprise (NCC-1701-D)")
        , _crew_complement(1012)
        , _max_speed(9.8)
    {
        crew_complement.getter([this]() -> int { return _crew_complement; });
        crew_complement.setter([this](const int& other) { if(other != _crew_complement) { _crew_complement = other; } });
        max_speed.bind(_max_speed);
    }

public:
    np::property<int> crew_complement;
    np::reference_property<double> max_speed;
    np::value_property<std::string> name;

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

* [go\::property\::nameless\::**property**](./class_template_property.html)
* [go\::property\::nameless\::**reference_property**](./class_template_reference_property.html)
* [go\::property\::nameless\::**value_property**](./class_template_value_property.html)

**Read-only property class templates**

* [go\::property\::nameless\::read_only\::**property**](./read_only/class_template_read_only_property.html)
* [go\::property\::nameless\::read_only\::**reference_property**](./read_only/class_template_read_only_reference_property.html)
* [go\::property\::nameless\::read_only\::**value_property**](./read_only/class_template_read_only_value_property.html)

**Write-only property class templates**

* [go\::property\::nameless\::write_only\::**property**](./write_only/class_template_write_only_property.html)
* [go\::property\::nameless\::write_only\::**reference_property**](./write_only/class_template_write_only_reference_property.html)
* [go\::property\::nameless\::write_only\::**value_property**](./write_only/class_template_write_only_value_property.html)
