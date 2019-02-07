---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# abstract class arguments

```c++
<go_boost/mvvm/arguments.hpp>
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
ptr | boost\::shared_ptr\<this_type>
wptr | boost\::weak_ptr\<this_type>

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
