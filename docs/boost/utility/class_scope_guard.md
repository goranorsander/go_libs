---
layout: boost_lib_utility
---

```c++
namespace go_boost::utility
```

# class scope_guard

```c++
<go_boost/utility/scope_guard.hpp>
```

Basic scope guard class in the **GO Boost C++ Libraries**.

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
    typedef boost::function<void()> on_scope_exit_function_type;

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
on_scope_exit_function_type | boost\::function\<void()>

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **scope_guard** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*constructor (1)* | public explicit | **scope_guard**(const on_scope_exit_function_type& on_scope_exit)
*constructor (2)* | protected | **scope_guard**()

1. Constructs a **scope_guard**.
2. Constructs a **scope_guard**.

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

void delete_foo(foo* p)
{
    delete p;
}

int main()
{
    foo* f = new foo;
    u::scope_guard guard(u::scope_guard::on_scope_exit_function_type(boost::bind(&delete_foo, f)));
    return 0;
}
```

Output

```
Create foo
Destroy foo
```