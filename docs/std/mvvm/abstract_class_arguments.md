---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# abstract class arguments

```c++
<go/mvvm/arguments.hpp>
```

**Abstract arguments class**

The **arguments** is a base class for event arguments.

It is declared as:

```c++
class arguments
{
public:
    virtual ~arguments();

protected:
    arguments();
};
```

## Member types

Member type | Definition
-|-
this_type | arguments
ptr | std\::shared_ptr\<this_type>
wptr | std\::weak_ptr\<this_type>

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **arguments** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **arguments**()

1. Constructs a **arguments** object.
