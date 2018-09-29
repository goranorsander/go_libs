---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class basic_observable_sequence_container

```c++
<go_boost/mvvm.hpp>
```

**basic_observable_sequence_container class**

The **basic_observable_sequence_container** is a base class for containers that
implement data structures which can be accessed sequentially.

It is declared as:

```c++
template<class S, class C> class basic_observable_sequence_container
    : public basic_observable_container<S, C>
{
public:
    virtual ~basic_observable_sequence_container() = 0;

protected:
    basic_observable_sequence_container();

public:
    iterator begin() throw();
    const_iterator begin() const throw();
    iterator end() throw();
    const_iterator end() const throw();
    const_iterator cbegin() const throw();
    const_iterator cend() const throw();
    size_type max_size() const throw();
    bool empty() const throw();
    reference front();
    const_reference front() const;

protected:
    void notify_assign(const boost::size_t& before, const boost::size_t& after);
    void notify_insert(const boost::size_t& before, const boost::size_t& after);
    void notify_erase(const boost::size_t& before, const boost::size_t& after);
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
this_type | basic_observable_sequence_container<string_type, container_type>
ptr | boost\::shared_ptr\<this_type>
wptr | boost\::weak_ptr\<this_type>
value_type | container_type\::value_type
reference | container_type\::reference
const_reference | container_type\::const_reference
pointer | container_type\::pointer
const_pointer | container_type\::const_pointer
iterator | container_type\::iterator
const_iterator | container_type\::const_iterator
difference_type | container_type\::difference_type
size_type | container_type\::size_type

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

Destroys the **basic_observable_sequence_container** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_observable_sequence_container**()

1. Constructs a **basic_observable_sequence_container** object.

### begin

Specifiers | Signature
-|-
public | iterator **begin**() throw()
public | const_iterator **begin**() const throw()

Returns an iterator to the first element of the container.

### end

Specifiers | Signature
-|-
public | iterator **end**() throw()
public | const_iterator **end**() const throw()

Returns an iterator to the element following the last element of the container.

### cbegin

Specifiers | Signature
-|-
public | const_iterator **cbegin**() const throw()

Returns an iterator to the first element of the container.

### cend

Specifiers | Signature
-|-
public | const_iterator **cend**() const throw()

Returns an iterator to the element following the last element of the container.

### max_size

Specifiers | Signature
-|-
public | size_type **max_size**() const throw()

Returns the maximum number of elements the container is able to hold.

### empty

Specifiers | Signature
-|-
public | bool **empty**() const throw()

Checks if the container has no elements, i.e. whether **begin() == end()**.

### front

Specifiers | Signature
-|-
public | reference front()
public | const_reference **front**() const

Returns a reference to the first element in the container.

### notify_assign

Specifiers | Signature
-|-
protected | void **notify_assign**(const boost\::size_t& before, const boost\::size_t& after)

Emit signal to notify that the container have been assigned new elements.

### notify_insert

Specifiers | Signature
-|-
protected | void **notify_insert**(const boost\::size_t& before, const boost\::size_t& after)

Emit signal to notify that new elements have been inserted into the container.

### notify_erase

Specifiers | Signature
-|-
protected | void **notify_erase**(const boost\::size_t& before, const boost\::size_t& after)

Emit signal to notify that elements have been erased from the container.

## Inherited functions

### container

Specifiers | Signature
-|-
protected abstract | container_type& **container**()
protected abstract | const container_type& **container**() const

Return a referense to the underlying container storage.

### on_container_changed

Specifiers | Signature
-|-
protected virtual | void **on_container_changed**(const notify_container_changed_action& action, const boost::size_t& added_elements, const boost::size_t& removed_elements, const boost::size_t& new_size)

Called when the container have changed.

### on_property_changed

Specifiers | Signature
-|-
protected virtual | void **on_property_changed**(const string_type& property_name)

Called when a property value have changed if the property *setter* implements **basic_notify_property_changed_interface**.
