---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class object

```c++
<go_boost/mvvm.hpp>
```

The **object** class is the base class for most classes in the 
[GO Boost MVVM Library](./mvvm.html).

It is declared as:

```c++
class object
    : public boost::enable_shared_from_this<object>
{
public:
    typedef object this_type;
    typedef boost::shared_ptr<this_type> ptr;
    typedef boost::weak_ptr<this_type> wptr;

public:
    virtual ~object() = 0;

protected:
    object();
};
```

## Member types

Member type | Definition
-|-
this_type | object
ptr | boost\::shared_ptr\<this_type>
wptr | boost\::weak_ptr\<this_type>

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
