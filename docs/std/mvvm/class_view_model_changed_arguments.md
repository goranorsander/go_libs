---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class view_model_changed_arguments

```c++
<go/mvvm.hpp>
```

The **view_model_changed_arguments** hold the arguments asociated wtih the
**view_model_changed** signal on
[notify_view_model_interface](./class_notify_view_model_change_interface.html).

It is declared as:

```c++
class view_model_changed_arguments
    : public go::signals::slot_arguments
{
public:
    virtual ~view_model_changed_arguments() = default;

protected:
    view_model_changed_arguments();

public:
    static std::shared_ptr<view_model_changed_arguments> create();
};
```

## Member types

Member type | Definition
-|-
this_type | view_model_changed_arguments
ptr | std\::shared_ptr\<this_type>
wptr | std\::weak_ptr\<this_type>

## Static member functions

### create

Specifiers | Signature
-|-
public static | std\::shared_ptr<view_model_changed_arguments> create()

Constructs a new **view_model_changed_arguments** object and return it as a
**view_model_changed_arguments\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **view_model_changed_arguments** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **view_model_changed_arguments**()

1. Constructs a **view_model_changed_arguments** object.
