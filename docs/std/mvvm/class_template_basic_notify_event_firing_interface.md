---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class basic_notify_event_firing_interface

```c++
<go/mvvm.hpp>
```

**basic_notify_event_firing_interface class**

The **basic_notify_event_firing_interface** is implemented to receive notifications
when an [event](./class_template_basic_event.html) is fired.

It is declared as:

```c++
template<class S>
class basic_notify_event_firing_interface
    : public go::signals::slot
{
public:
    virtual ~basic_notify_event_firing_interface() = 0;

protected:
    basic_notify_event_firing_interface() = default;

public:
    event_fired_signal event_fired;
};
```

## Template parameters

Parameter | Description
-|-
S | The string class

## Member types

Member type | Definition
-|-
string_type | S
this_type | basic_notify_event_firing_interface<S>
event_fired_signal | go\::signals\::signal<std\::function<void(const std\::shared_ptr<basic_event<string_type>>&)>>

## Member signals

Signal | Description
-|-
event_fired | Emitted after an event was fired.

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **basic_notify_event_firing_interface** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_notify_event_firing_interface**()

1. Constructs a **basic_notify_event_firing_interface** object.

# class template basic_notify_event_firing_interface specializations

## typedef notify_event_firing_interface

The **notify_event_firing_interface** is a type definition for observing events
using **std::string** type being fired.

It is defined as:

```c++
typedef basic_notify_event_firing_interface<std::string> notify_event_firing_interface;
```

## typedef notify_wevent_firing_interface

The **notify_wevent_firing_interface** is a type definition for observing events
using **std::wstring** type being fired.

It is defined as:

```c++
typedef basic_notify_event_firing_interface<std::wstring> notify_wevent_firing_interface;
```
