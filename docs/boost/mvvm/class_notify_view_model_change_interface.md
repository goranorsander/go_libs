---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class notify_view_model_change_interface

```c++
<go_boost/mvvm.hpp>
```

The **notify_view_model_change_interface** is implemented to receive notifications
when a [view model](./class_view_model_interface.html) is changing.

It is declared as:

```c++
class notify_view_model_change_interface
    : public go_boost::signals::slot
{
public:
    virtual ~notify_view_model_change_interface() = 0;

protected:
    notify_view_model_change_interface();

public:
    view_model_will_change_signal view_model_will_change;
    view_model_changed_signal view_model_changed;
};
```

## Member types

Member type | Definition
-|-
this_type | notify_view_model_change_interface
view_model_changed_signal | go_boost\::signals\::signal<boost\::function<void(const boost\::shared_ptr<view_model_changed_arguments>&)>>
view_model_will_change_signal | go_boost\::signals\::signal<boost\::function<void(const boost\::shared_ptr<view_model_will_change_arguments>&)>>

## Member signals

Signal | Description
-|-
view_model_changed | Emitted when a view model have changed.
view_model_will_change | Emitted when a view model is about to change.

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **notify_view_model_change_interface** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **notify_view_model_change_interface**()

1. Constructs a **notify_view_model_change_interface** object.
