---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class basic_observable_ordered_associative_container

```c++
<go_boost/mvvm.hpp>
```

**basic_observable_ordered_associative_container class**

The **basic_observable_ordered_associative_container** is a base class for containers
that implement ordered data structures which can be accessed sequentially.

It is declared as:

```c++
template<class S, class C> class basic_observable_ordered_associative_container
    : public basic_observable_associative_container<S, C>
{
public:
    virtual ~basic_observable_ordered_associative_container() = 0;

protected:
    basic_observable_ordered_associative_container();

public:
    reverse_iterator rbegin() throw();
    const_reverse_iterator rbegin() const throw();
    reverse_iterator rend() throw();
    const_reverse_iterator rend() const throw();
    const_reverse_iterator crbegin() const throw();
    const_reverse_iterator crend() const throw();
    iterator lower_bound(const value_type& val);
    const_iterator lower_bound(const value_type& val) const;
    iterator upper_bound(const value_type& val);
    const_iterator upper_bound(const value_type& val) const;
    key_compare key_comp() const;
    value_compare value_comp() const;
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
this_type | basic_observable_ordered_associative_container<string_type, container_type>
ptr | boost\::shared_ptr\<this_type>
wptr | boost\::weak_ptr\<this_type>
key_type | container_type\::key_type
value_type | container_type\::value_type
key_compare | container_type\::key_compare
value_compare | container_type\::value_compare
allocator_type | container_type\::allocator_type
reference | container_type\::reference
const_reference | container_type\::const_reference
pointer | container_type\::pointer
const_pointer | container_type\::const_pointer
iterator | container_type\::iterator
const_iterator | container_type\::const_iterator
reverse_iterator | container_type\::reverse_iterator
const_reverse_iterator | container_type\::const_reverse_iterator
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

Destroys the **basic_observable_ordered_associative_container** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_observable_ordered_associative_container**()

1. Constructs a **basic_observable_ordered_associative_container** object.

### rbegin

Specifiers | Signature
-|-
public | reverse_iterator **rbegin**() throw()
public | const_reverse_iterator **rbegin**() const throw()

Returns a reverse iterator to the first element of the reversed container.

### rend

Specifiers | Signature
-|-
public | reverse_iterator **rend**() throw()
public | const_reverse_iterator **rend**() const throw()

Returns a reverse iterator to the element following the last element of the
reversed container.

### crbegin

Specifiers | Signature
-|-
public | const_reverse_iterator **crbegin**() const throw()

Returns a reverse iterator to the first element of the reversed container.

### crend

Specifiers | Signature
-|-
public | const_reverse_iterator **crend**() const throw()

Returns a reverse iterator to the element following the last element of the
reversed container.

### lower_bound

Specifiers | Signature
-|-
public | iterator **lower_bound**(const value_type& val)
public | const_iterator **lower_bound**(const value_type& val) const

Returns an iterator pointing to the first element that is *not less* than **val**.

### upper_bound

Specifiers | Signature
-|-
public | iterator **upper_bound**(const value_type& val)
public | const_iterator **upper_bound**(const value_type& val) const

Returns an iterator pointing to the first element that is *greater* than **val**.

### key_comp

Specifiers | Signature
-|-
public | key_compare **key_comp**() const

Returns the function object that compares the keys, which is a copy of this container's
constructor argument comp.

### value_comp

Specifiers | Signature
-|-
public | value_compare **value_comp**() const

Returns the function object that compares the values.

## Inherited functions

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

### size

Specifiers | Signature
-|-
public | size_type **size**() const throw()

Returns the number of elements in the container.

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

### emplace_hint

Specifiers | Signature
-|-
public | template <class... Args> iterator **emplace_hint**(const_iterator position, Args&&... args)

Inserts a new element into the container as close as possible to the position just
before hint.

### clear

Specifiers | Signature
-|-
public | void **clear**() throw()

Removes all elements from the container.

### swap

Specifiers | Signature
-|-
public | template<class t, class s> void **swap**(basic_observable_ordered_associative_container<t, s>& x)

Exchanges the contents of the container with those of **x**.

### count

Specifiers | Signature
-|-
public | size_type **count**(const value_type& val) const

Returns the number of elements with key that compares equivalent to **val**.

### find

Specifiers | Signature
-|-
public | const_iterator **find**(const value_type& val) const
public | iterator **find**(const value_type& val)

Finds an element with key equivalent to **val**.

### equal_range

Specifiers | Signature
-|-
public | boost::pair<const_iterator, const_iterator> **equal_range**(const value_type& val) const
public | boost::pair<iterator, iterator> **equal_range**(const value_type& val)

Returns a range containing all elements with the given key in the container.

### get_allocator

Specifiers | Signature
-|-
public | allocator_type **get_allocator**() const throw()

Returns the allocator associated with the container.

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
