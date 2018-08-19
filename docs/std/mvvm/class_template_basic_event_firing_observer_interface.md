---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class template basic_event_firing_observer_interface

```c++
<go/mvvm.hpp>
```

**Generic event firing observer interface**

The **basic_event_firing_observer_interface** is a generalization class for
observing [events](./class_template_basic_event.html) being fired.

It is declared as:

```c++
template<class S>
class basic_event_firing_observer_interface
{
public:
    typedef S string_type;
    typedef basic_event_firing_observer_interface<S> this_type;

public:
    virtual ~basic_event_firing_observer_interface() = 0;

protected:
    basic_event_firing_observer_interface() = default;

public:
    virtual void on_event_fired(const std::shared_ptr<basic_event<S>>& /*e*/) = 0;
};
```

## Template parameters

Parameter | Description
-|-
S | The observer string class

## Member types

Member type | Definition
-|-
string_type | S
this_type | basic_event_firing_observer_interface<S>

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **basic_event_firing_observer_interface** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_event_firing_observer_interface**()

1. Constructs a **basic_event_firing_observer_interface** object.

### on_event_fired

Specifiers | Signature
-|-
public abstract | **void on_event_fired**(const std\::shared_ptr<basic_event<S>>& e) = 0

The [event manager](./class_template_basic_event_manager.html) call this member
function as a signal that an [event](./class_template_basic_event.html)
have been fired.

# class template basic_event_firing_observer_interface specializations

## typedef event_firing_observer_interface

The **event_firing_observer_interface** is a type definition for observing events
using **std::string** type being fired.

It is defined as:

```c++
typedef basic_event_firing_observer_interface<std::string> event_firing_observer_interface;
```

## typedef wevent_firing_observer_interface

The **wevent_firing_observer_interface** is a type definition for observing events
using **std::wstring** type being fired.

It is defined as:

```c++
typedef basic_event_firing_observer_interface<std::wstring> wevent_firing_observer_interface;
```
