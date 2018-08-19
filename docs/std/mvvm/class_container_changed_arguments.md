---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class container_changed_arguments

```c++
<go/mvvm.hpp>
```

The class **container_changed_arguments** hold the arguments asociated wtih the
**container_changed** signal on
[notify_container_changed_interface](./class_notify_container_changed_interface.html).

It is declared as:

```c++
class container_changed_arguments
    : public go::signals::slot_arguments
{
public:
    virtual ~container_changed_arguments() = default;

protected:
    container_changed_arguments(const notify_container_changed_action& action_, const std::size_t& added_elements_, const std::size_t& removed_elements_, const std::size_t& new_size_);

public:
    go::property::nameless::read_only::value_property<notify_container_changed_action> action;
    go::property::nameless::read_only::value_property<std::size_t> added_elements;
    go::property::nameless::read_only::value_property<std::size_t> removed_elements;
    go::property::nameless::read_only::value_property<std::size_t> new_size;

    static std::shared_ptr<container_changed_arguments> create(const notify_container_changed_action& action_, const std::size_t& added_elements_, const std::size_t& removed_elements_, const std::size_t& new_size_);
};
```

## Member types

Member type | Definition
-|-
this_type | container_changed_arguments
ptr | std\::shared_ptr\<this_type>
wptr | std\::weak_ptr\<this_type>

## Member properties

Property type | Property name
-|-
go\::property\::nameless\::read_only\::value_property<notify_container_changed_action> | action
go\::property\::nameless\::read_only\::value_property<std\::size_t> | added_element
go\::property\::nameless\::read_only\::value_property<std\::size_t> | removed_elements
go\::property\::nameless\::read_only\::value_property<std\::size_t> | new_size

### Property action

Gets the type of change. The actions are defined by the emuneration
[notify_container_changed_action](./enum_notify_container_changed_action.html).

### Property added_element

Gets the number of elements added to the container.

### Property removed_elements

Gets the number of elements removed from the container.

### Property new_size

Gets the new size of the container.

## Static member functions

### create

Specifiers | Signature
-|-
public static | std\::shared_ptr<container_changed_arguments> **create**(const notify_container_changed_action& action_, const std\::size_t& added_elements_, const std\::size_t& removed_elements_, const std\::size_t& new_size_)

Constructs a new **container_changed_arguments** object and return it as a
**container_changed_arguments\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **container_changed_arguments** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **container_changed_arguments**()

1. Constructs a **container_changed_arguments** object.
