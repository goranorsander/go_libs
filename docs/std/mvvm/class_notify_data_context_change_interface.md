---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class notify_data_context_change_interface

```c++
<go/mvvm.hpp>
```

The **notify_data_context_change_interface** is implemented to receive notifications
when a [data context](./class_template_data_context_interface.html) is changing.

It is declared as:

```c++
class notify_data_context_change_interface
    : public go::signals::slot
{
public:
    virtual ~notify_data_context_change_interface() = 0;

protected:
    notify_data_context_change_interface() = default;

public:
    data_context_will_change_signal data_context_will_change;
    data_context_changed_signal data_context_changed;
};
```

## Member types

Member type | Definition
-|-
this_type | notify_data_context_change_interface
data_context_changed_signal | go\::signals\::signal<std\::function<void(const std\::shared_ptr<data_context_changed_arguments>&)>>
data_context_will_change_signal | go\::signals\::signal<std\::function<void(const std\::shared_ptr<data_context_will_change_arguments>&)>>

## Member signals

Signal | Description
-|-
data_context_changed | Emitted when a data context have changed.
data_context_will_change | Emitted when a data context is about to change.

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **notify_data_context_change_interface** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **notify_data_context_change_interface**()

1. Constructs a **notify_data_context_change_interface** object.
