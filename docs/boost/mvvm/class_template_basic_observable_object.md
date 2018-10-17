---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class basic_observable_object

```c++
<go_boost/mvvm.hpp>
```

**basic_observable_object class**

The **basic_observable_object** is a base class for object with properties that are
observable.

It is declared as:

```c++
template<class S>
class basic_observable_object
    : public basic_notify_property_changed_interface<S>
    , public object
{
public:
    typedef S string_type;
    typedef basic_observable_object<string_type> this_type;

public:
    virtual ~basic_observable_object() = 0;

protected:
    basic_observable_object();

protected:
    virtual void notify_property_changed(const string_type& property_name);
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
this_type | basic_observable_object<string_type, container_type>
ptr | boost\::shared_ptr\<this_type>
wptr | boost\::weak_ptr\<this_type>

## Inherited signals

Signal | Description
-|-
property_changed | Emitted when a property changed.

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **basic_observable_object** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_observable_object**()

1. Constructs a **basic_observable_object** object.

### notify_property_changed

Specifiers | Signature
-|-
protected virtual | void **notify_property_changed**(const string_type& property_name)

Called when a property value have changed if the property *setter* implements **basic_notify_property_changed_interface**.
