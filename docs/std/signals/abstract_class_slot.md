---
layout: std_lib_signals
---

```c++
namespace go::signals
```

# abstract class slot

```c++
<go/signals/slot.hpp>
```

**Abstract slot class**

The **slot** is a base class for slots.

It is declared as:

```c++
class slot
{
public:
    virtual ~slot();

protected:
    slot();
};
```

## Member types

Member type | Definition
-|-
this_type | slot
ptr | std\::shared_ptr\<this_type>
wptr | std\::weak_ptr\<this_type>

## Member functions

### (destructor)

*public virtual member function*

Destroys the **slot** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*protected member function*

Constructor | Signature
-|-
*default constructor (1)* | **slot**()

1. Constructs a **slot** object.