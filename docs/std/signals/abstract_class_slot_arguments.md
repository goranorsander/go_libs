---
layout: std_lib_signals
---

```c++
namespace go::signals
```

# abstract class slot_arguments

```c++
<go/signals/slot_arguments.hpp>
```

**Abstract slot_arguments class**

The **slot_arguments** is a base class for slot arguments.

It is declared as:

```c++
class slot_arguments
{
public:
    virtual ~slot_arguments();

protected:
    slot_arguments();
};
```

## Member types

Member type | Definition
-|-
this_type | slot_arguments
ptr | std\::shared_ptr\<this_type>
wptr | std\::weak_ptr\<this_type>

## Member functions

### (destructor)

*public virtual member function*

Destroys the **slot_arguments** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*protected member function*

Constructor | Signature
-|-
*default constructor (1)* | **slot_arguments**()

1. Constructs a **slot_arguments** object.
