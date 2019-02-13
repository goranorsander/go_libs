---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class basic_observable_object

```c++
<go/mvvm.hpp>
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
    basic_observable_object() = default;

protected:
    virtual void notify_property_changed(const string_type& property_name);

    template<class T> T get_property_value(const T& value);
    template<class P> void set_property_value(const P& prop, typename P::value_type& value, const typename P::value_type& new_value);
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
this_type | basic_observable_object<string_type, container_type, lockable_type>
ptr | std\::shared_ptr\<this_type>
wptr | std\::weak_ptr\<this_type>

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

### get_property_value

Specifiers | Signature
-|-
protected | template\<class T\> T **get_property_value**(const T& value)

A template function that provide a basic property *getter* function.

The template parameter **T** is the property value type.

### set_property_value

Specifiers | Signature
-|-
protected | template\<class T\> void **set_property_value**(const P& prop, typename P\::value_type& value, const typename P\::value_type& new_value)

A template function that provide a basic property *setter* function that will
call **notify_property_changed** if necessary.

The template parameter **P** is the property type.
