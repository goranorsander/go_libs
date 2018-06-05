---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# class scope_guard

```c++
<go/utility/scope_guard.hpp>
```

Basic scope guard class in the **GO Std C++ Libraries**.

The intent of a scope guard is to ensure that resources are always released when leaving
the scope. Both normal scope exit and exit due to error or exception is handled.

Scope guards are closely related to the Resource Acquisition is Initialization (RAII)
idiom.

It is declared as:

```c++
class scope_guard
    : public noncopyable_nonmovable
{
public:
    typedef std::function<void()> on_scope_exit_function_type;

public:
    virtual ~scope_guard();

    explicit scope_guard(const on_scope_exit_function_type& on_scope_exit);

protected:
    scope_guard();
    void set_on_scope_exit_function(const on_scope_exit_function_type& on_scope_exit);
};
```

## Member types

Member type | Definition
-|-
this_type | scope_guard
base_type | noncopyable_nonmovable
on_scope_exit_function_type | std\::function\<void()>

## Member functions

### (destructor)

*public virtual member function*

Destroys the **scope_guard** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*constructor (1)* | explicit **scope_guard**(const on_scope_exit_function_type& on_scope_exit)

1. Constructs a **scope_guard**.

*protected member function*

Constructor | Signature
-|-
*constructor (2)* | **scope_guard**()

2. Constructs a **scope_guard**.

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

class foo
{
public:
    ~foo()
    {
        std::cout << "Destroy foo" << std::endl;
    }

    foo()
    {
        std::cout << "Create foo" << std::endl;
    }
};

void delete_foo(foo* p)
{
    delete p;
}

int main()
{
    foo* f = new foo;
    u::scope_guard guard(u::scope_guard::on_scope_exit_function_type(std::bind(&delete_foo, f)));
    return 0;
}
```

Output

```
Create foo
Destroy foo
```
