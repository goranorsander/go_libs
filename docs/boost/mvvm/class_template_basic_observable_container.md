---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class basic_observable_container

```c++
<go_boost/mvvm.hpp>
```

**basic_observable_container class**

The **basic_observable_container** is a base class for containers that are observable.

It is declared as:

```c++
template<class S, class C> class basic_observable_container
    : public notify_container_changed_interface
    , public basic_observable_object<S>
{
public:
    typedef S string_type;
    typedef C container_type;
    typedef basic_observable_container<string_type, container_type> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~basic_observable_container() = 0;

protected:
    basic_observable_container();

protected:
    virtual void notify_container_changed(const notify_container_changed_action& action, const boost::size_t& added_elements, const boost::size_t& removed_elements, const boost::size_t& new_size);
    virtual void notify_property_changed(const string_type& property_name);
    virtual container_type& container() = 0;
    virtual const container_type& container() const = 0;
};
```

## Template parameters

Parameter | Description
-|-
S | The string class
C | The container class

## Member types

Member type | Definition
-|-
string_type | S
container_type | C
this_type | basic_observable_container<string_type, container_type>
ptr | boost\::shared_ptr\<this_type>
wptr | boost\::weak_ptr\<this_type>

## Inherited signals

Signal | Description
-|-
container_changed | Emitted when the collection is changed.
property_changed | Emitted when a property changed.

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **basic_observable_container** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_observable_container**()

1. Constructs a **basic_observable_container** object.

### container

Specifiers | Signature
-|-
protected abstract | container_type& **container**()
protected abstract | const container_type& **container**() const

Return a referense to the underlying container storage.

## Inherited functions

### notify_container_changed

Specifiers | Signature
-|-
protected virtual | void **notify_container_changed**(const notify_container_changed_action& action, const boost::size_t& added_elements, const boost::size_t& removed_elements, const boost::size_t& new_size)

Called when the container have changed.

### notify_property_changed

Specifiers | Signature
-|-
protected virtual | void **notify_property_changed**(const string_type& property_name)

Called when a property value have changed if the property *setter* implements **basic_notify_property_changed_interface**.
