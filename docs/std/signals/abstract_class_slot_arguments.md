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

### Destructor

Specifiers |
-|
public virtual |

Destroys the **slot_arguments** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **slot_arguments**()

1. Constructs a **slot_arguments** object.
