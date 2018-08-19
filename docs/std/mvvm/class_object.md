---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class object

```c++
<go/mvvm.hpp>
```

The **object** class is the base class for most classes in the 
[GO Std MVVM Library](./mvvm.html).

It is declared as:

```c++
class object
    : public std::enable_shared_from_this<object>
{
public:
    typedef object this_type;
    typedef std::shared_ptr<this_type> ptr;
    typedef std::weak_ptr<this_type> wptr;

public:
    virtual ~object() = 0;

protected:
    object() = default;
};
```

## Member types

Member type | Definition
-|-
this_type | object
ptr | std\::shared_ptr\<this_type>
wptr | std\::weak_ptr\<this_type>

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **object** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **object**()

1. Constructs a **object** object.
