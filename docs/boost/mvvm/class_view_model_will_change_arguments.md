---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class view_model_will_change_arguments

```c++
<go_boost/mvvm.hpp>
```

The **view_model_will_change_arguments** hold the arguments asociated wtih the
**view_model_will_change** signal on
[notify_view_model_interface](./class_notify_view_model_change_interface.html).

It is declared as:

```c++
class view_model_will_change_arguments
    : public go_boost::signals::slot_arguments
{
public:
    virtual ~view_model_will_change_arguments();

protected:
    view_model_will_change_arguments();

public:
    static boost::shared_ptr<view_model_will_change_arguments> create();
};
```

## Member types

Member type | Definition
-|-
this_type | view_model_will_change_arguments
ptr | boost\::shared_ptr\<this_type>
wptr | boost\::weak_ptr\<this_type>

## Static member functions

### create

Specifiers | Signature
-|-
public static | boost\::shared_ptr<view_model_will_change_arguments> create()

Constructs a new **view_model_will_change_arguments** object and return it as a
**view_model_will_change_arguments\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **view_model_will_change_arguments** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **view_model_will_change_arguments**()

1. Constructs a **view_model_will_change_arguments** object.
