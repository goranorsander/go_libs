---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class template view_model_interface

```c++
<go/mvvm.hpp>
```

**Generic view model interface**

The **view_model_interface** is a generalization class for view models.

It is declared as:

```c++
class view_model_interface
    : public notify_view_model_change_interface
{
public:
    typedef view_model_interface this_type;

public:
    virtual ~view_model_interface() = 0;

protected:
    view_model_interface() = default;

protected:
    virtual void on_view_model_will_change();
    virtual void on_view_model_changed();
};
```

## Member types

Member type | Definition
-|-
this_type | view_model_interface

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **view_model_interface** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*constructor (1)* | protected | **view_model_interface**()

1. Constructs a **view_model_interface** object.

### on_view_model_will_change

Specifiers | Signature
-|-
protected virtual | void **on_view_model_will_change**()

Called when the view model is about to change.

### on_view_model_changed

Specifiers | Signature
-|-
protected virtual | void **on_view_model_changed**()

Called when the view model have changed.
