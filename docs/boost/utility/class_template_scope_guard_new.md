---
layout: boost_lib_utility
---

```c++
namespace go_boost::utility
```

# class template scope_guard_new

```c++
<go_boost/utility/scope_guard_new.hpp>
```

The **scope_guard_new** is a class template that specialize the basic scope guard
class **scope_guard** to handle memory allocation using **new**.

It is declared as:

```c++
template<class T> class scope_guard_new
    : public scope_guard
{
public:
    virtual ~scope_guard_new();
    explicit scope_guard_new(pointer px);
    pointer operator->() const;
    reference operator*() const;
    explicit operator bool() const;
    pointer detach();
    pointer get() const;
};
```

## Template parameters

Parameter | Description
-|-
T | The guarded value type

## Member types

Member type | Definition
-|-
this_type | scope_guard_new\<T>
base_type | scope_guard
value_type | T
reference | T&
pointer | T*

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **scope_guard_new** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*constructor (1)* | public explicit | **scope_guard_new**(pointer px)

1. Constructs a **scope_guard**.

### Member of pointer operator

Specifiers | Signature
-|-
public | pointer operator->() const

Returns a raw pointer to the guarded object.

### Indirection operator

Specifiers | Signature
-|-
public | reference operator*() const

Returns a reference to the guarded object.

### operator bool

Specifiers | Signature
-|-
public explicit | operator bool() const

Returns true if the guarded object pointer is not nullptr, false otherwise.

### detach

Specifiers | Signature
-|-
public | pointer detach()

Returns a pointer to the guarded object and relesees the object from the scoped guard.

### get

Specifiers | Signature
-|-
public | pointer get() const

Returns a pointer to the guarded object.

## Inherited functions

### set_on_scope_exit_function

Specifiers | Signature
-|-
protected virtual | void set_on_scope_exit_function(const on_scope_exit_function_type& on_scope_exit)

Set the callback function called by the **scope_guard** destructor.

## Example

This example is intended to show how scope guards can be used.

```c++
#include <iostream>
#include <go_boost/utility.hpp>

namespace u = go_boost::utility;

class foo
{
public:
    ~foo()
    {
        boost::cout << "Destroy foo" << boost::endl;
    }

    foo()
    {
        boost::cout << "Create foo" << boost::endl;
    }
};

int main()
{
    u::scope_guard_new<foo> guard(new foo);
    return 0;
}
```

Output

```
Create foo
Destroy foo
```
