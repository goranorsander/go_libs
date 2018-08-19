---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class notify_container_changed_interface

```c++
<go/mvvm.hpp>
```

The **notify_container_changed_interface** is implemented to receive notifications
when an [observable container](./class_template_basic_observable_container.html)
is changed.

It is declared as:

```c++
class notify_container_changed_interface
    : public go::signals::slot
{
public:
    virtual ~notify_container_changed_interface() = 0;

protected:
    notify_container_changed_interface() = default;

public:
    container_changed_signal container_changed;
};
```

## Member types

Member type | Definition
-|-
this_type | notify_container_changed_interface
container_changed_arguments_type | container_changed_arguments
container_changed_signal | go\::signals\::signal<std\::function<void(const std\::shared_ptr<object>&, const std\::shared_ptr<container_changed_arguments_type>&)>>

## Member signals

Signal | Description
-|-
container_changed | Emitted when an observable collection is changed.

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **notify_container_changed_interface** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **notify_container_changed_interface**()

1. Constructs a **notify_container_changed_interface** object.
