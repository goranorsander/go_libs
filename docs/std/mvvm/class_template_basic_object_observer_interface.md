---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class basic_object_observer_interface

```c++
<go/mvvm.hpp>
```

**basic_object_observer_interface class**

The **basic_object_observer_interface** is a generalization class for
observing object [properties](../property/property.html) and
[containers](./class_template_basic_observable_container.html).

It is declared as:

```c++
template<class S>
class basic_object_observer_interface
{
public:
    typedef S string_type;
    typedef basic_object_observer_interface<S> this_type;

public:
    virtual ~basic_object_observer_interface() = 0;

protected:
    basic_object_observer_interface() = default;

public:
    virtual void on_container_changed(const std::shared_ptr<object>& /*o*/, const std::shared_ptr<container_changed_arguments>& /*a*/) = 0;
    virtual void on_property_changed(const std::shared_ptr<object>& /*o*/, const std::shared_ptr<basic_property_changed_arguments<S>>& /*a*/) = 0;
};
```

## Template parameters

Parameter | Description
-|-
S | The observer string class

## Member types

Member type | Definition
-|-
this_type | basic_object_observer_interface
ptr | std\::shared_ptr\<this_type>
wptr | std\::weak_ptr\<this_type>

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_object_observer_interface** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_object_observer_interface**()

1. Constructs a **basic_object_observer_interface** object.

# class template basic_object_observer_interface specializations

## typedef object_observer_interface

The **object_observer_interface** is a type definition for observing objects
using **std::string** [properties](../property/property.html) and
[containers](./class_template_basic_observable_container.html).

It is defined as:

```c++
typedef basic_object_observer_interface<std::string> object_observer_interface;
```

## typedef object_wobserver_interface

The **object_wobserver_interface** is a type definition for observing objects
using **std::wstring** [properties](../property/property.html) and
[containers](./class_template_basic_observable_container.html).

It is defined as:

```c++
typedef basic_object_observer_interface<std::wstring> object_wobserver_interface;
```
