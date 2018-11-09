---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class basic_observable_unordered_associative_container

```c++
<go_boost/mvvm.hpp>
```

**basic_observable_unordered_associative_container class**

The **basic_observable_unordered_associative_container** is a base class for containers
that implement unordered data structures which can be accessed sequentially.

It is declared as:

```c++
template<class S, class C> class basic_observable_unordered_associative_container
    : public basic_observable_associative_container<S, C>
{
public:
    virtual ~basic_observable_unordered_associative_container() = 0;

protected:
    basic_observable_unordered_associative_container();

public:
    key_equal key_eq() const;
    hasher hash_function() const;
    size_type bucket(const key_type& k) const;
    size_type bucket_count() const throw();
    size_type bucket_size(size_type n) const;
    size_type max_bucket_count() const throw();
    void rehash(size_type n);
    float load_factor() const throw();
    float max_load_factor() const throw();
    void max_load_factor(float z);
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
this_type | basic_observable_unordered_associative_container<string_type, container_type, mutex_type>
ptr | boost\::shared_ptr\<this_type>
wptr | boost\::weak_ptr\<this_type>
key_type | container_type\::key_type
value_type | container_type\::value_type
hasher | container_type\::hasher
key_equal | container_type\::key_equal
allocator_type | container_type\::allocator_type
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

Destroys the **basic_observable_unordered_associative_container** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_observable_unordered_associative_container**()

1. Constructs a **basic_observable_unordered_associative_container** object.

### key_eq

Specifiers | Signature
-|-
public | key_equal **key_eq**() const

Returns the function that compares keys for equality.

### hash_function

Specifiers | Signature
-|-
public | hasher **hash_function**() const

Returns the function that hashes the keys.

### bucket

Specifiers | Signature
-|-
public | size_type **bucket**(const key_type& k) const

Returns the index of the bucket for key key.

### bucket_count

Specifiers | Signature
-|-
public | size_type **bucket_count**() const throw()

Returns the number of buckets in the container.

### bucket_size

Specifiers | Signature
-|-
public | size_type **bucket_size**(size_type n) const

Returns the number of elements in the bucket with index **n**.

### max_bucket_count

Specifiers | Signature
-|-
public | size_type **max_bucket_count**() const

Returns the maximum number of buckets the container is able to hold due to system
or library implementation limitations.

### rehash

Specifiers | Signature
-|-
public | void **rehash**(size_type n)

Sets the number of buckets to **n** and rehashes the container.

### load_factor

Specifiers | Signature
-|-
public | float **load_factor**() const

Returns the average number of elements per bucket, that is, **size()** divided by
**bucket_count()**.

### max_load_factor

Specifiers | Signature
-|-
public | float **max_load_factor**() const
public | void **max_load_factor**(float z)

Manages the maximum load factor (number of elements per bucket). The container
automatically increases the number of buckets if the load factor exceeds this threshold.

1. Returns current maximum load factor.
2. Sets the maximum load factor to **z**.

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
public | template<class t, class s> void **swap**(basic_observable_unordered_associative_container<t, s>& x)

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
