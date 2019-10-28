---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class command_parameters

```c++
<go_boost/mvvm.hpp>
```

The class **command_parameters** is base class for parameters asociated with
[commands](./class_template_basic_command_interface.html).

It is declared as:

```c++
class command_parameters
    : public go_boost::type_traits::noncopyable_nonmovable
{
public:
    virtual ~command_parameters();

protected:
    command_parameters();

public:
    static ptr create()
 };
```

## Member types

Member type | Definition
-|-
this_type | command_parameters
ptr | boost\::shared_ptr\<this_type>
wptr | boost\::weak_ptr\<this_type>

## Static member functions

### create

Specifiers | Signature
-|-
public static | ptr **create**()

Constructs a new **command_parameters** object and return it as a
**command_parameters\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **command_parameters** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **command_parameters**()

1. Constructs a **command_parameters** object.
