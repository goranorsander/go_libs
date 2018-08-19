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

### Destructor

Specifiers |
-|
public virtual |

Destroys the **slot** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **slot**()

1. Constructs a **slot** object.
