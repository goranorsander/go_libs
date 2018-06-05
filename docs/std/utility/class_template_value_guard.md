---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# class template value_guard

```c++
<go/utility/value_guard.hpp>
```

The **value_guard** is a class template restore a variables original value on scope exit.

It is declared as:

```c++
template<class T> class value_guard
{
public:
    virtual ~value_guard();
    value_guard(value_type& value, const value_type& new_value);
    value_guard(value_type& value, value_type&& new_value);
};
```

## Template parameters

Parameter | Description
-|-
T | The guarded value type

## Member types

Member type | Definition
-|-
this_type | value_guard\<T>
value_type | T

## Member functions

### (destructor)

*public virtual member function*

Destroys the **value_guard** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*constructor (1)* | **value_guard**(value_type& value, const value_type& new_value)
*constructor (2)* | **value_guard**(value_type& value, value_type&& new_value)

1. Constructs a **value_guard**.
2. Constructs a **value_guard**.

## Inherited functions

### void set_on_scope_exit_function(const on_scope_exit_function_type& on_scope_exit)

*protected virtual member function*

Set the callback function called by the **scope_guard** destructor.

## Example

This example is intended to show how signals can be used. It implements a 
simple fire lasers command that the fleet commander can give to the ships.

```c++
#include <iostream>
#include <go/utility.hpp>

namespace u = go::utility;

int main()
{
    std::string value("First scope");
    std::cout << value << std::endl;
    {
        const u::value_guard<std::string> guard(value, std::string("Second scope"));
        std::cout << value << std::endl;
    }
    std::cout << value << std::endl;
    return 0;
}
```

Output

```
First scope
Second scope
First scope
```
