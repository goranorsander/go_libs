---
layout: boost_lib_utility
---

```c++
namespace go_boost::utility
```

# class template value_guard

```c++
<go_boost/utility/value_guard.hpp>
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

### Destructor

Specifiers |
-|
public virtual |

Destroys the **value_guard** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*constructor (1)* | public | **value_guard**(value_type& value, const value_type& new_value)
*constructor (2)* | public | **value_guard**(value_type& value, value_type&& new_value)

1. Constructs a **value_guard**.
2. Constructs a **value_guard**.

## Example

This example is intended to show how value guards can be used.

```c++
#include <iostream>
#include <go_boost/utility.hpp>

namespace u = go_boost::utility;

int main()
{
    std::string value("First scope");
    boost::cout << value << boost::endl;
    {
        const u::value_guard<std::string> guard(value, std::string("Second scope"));
        boost::cout << value << boost::endl;
    }
    boost::cout << value << boost::endl;
    return 0;
}
```

Output

```
First scope
Second scope
First scope
```