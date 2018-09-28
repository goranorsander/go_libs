---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class basic_notify_property_changed_interface

```c++
<go_boost/mvvm.hpp>
```

**basic_notify_property_changed_interface class**

The **basic_notify_property_changed_interface** is implemented to receive notifications
when a [property](../property/property.html) is changed if the object having the property
implements the [object observer interface](./class_template_basic_object_observer_interface.html)
and the property *setter* calls **on_property_changed** when necessary.

It is declared as:

```c++
template<class S>
class basic_notify_property_changed_interface
    : public go_boost::signals::slot
{
public:
    virtual ~basic_notify_property_changed_interface() = 0;

protected:
    basic_notify_property_changed_interface();

public:
    property_changed_signal property_changed;
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
this_type | basic_notify_property_changed_interface<S>
property_changed_signal | go_boost\::signals\::signal<boost\::function<void(const boost\::shared_ptr<object>&, const boost\::shared_ptr<basic_property_changed_arguments<S>>&)>>

## Member signals

Signal | Description
-|-
property_changed | Emitted when a property changed.

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **basic_notify_property_changed_interface** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_notify_property_changed_interface**()

1. Constructs a **basic_notify_property_changed_interface** object.

# class template basic_notify_property_changed_interface specializations

## typedef nnn

The **notify_property_changed_interface** is a type definition for observing properties
using **std::string** type being changed.

It is defined as:

```c++
typedef basic_notify_property_changed_interface<std::string> notify_property_changed_interface;
```

## typedef notify_wproperty_changed_interface

The **notify_wproperty_changed_interface** is a type definition for observing properties
using **std::wstring** type being changed.

It is defined as:

```c++
typedef basic_notify_property_changed_interface<std::wstring> notify_wproperty_changed_interface;
```
