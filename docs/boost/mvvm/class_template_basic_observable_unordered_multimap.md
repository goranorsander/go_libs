---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class basic_observable_unordered_multimap

```c++
<go_boost/mvvm.hpp>
```

**basic_observable_unordered_multimap class**

The **basic_observable_unordered_multimap** is a container that encapsulates collections of key-value
pairs, hashed by keys. It wraps the [**boost\::unordered_multimap**](https://www.boost.org/doc/libs/1_71_0/doc/html/boost/unordered_multimap.html)
and adds notifications when items get added, removed, or when the whole map is reset
or swapped.

It is declared as:

```c++
template<class K, class T, class S> class basic_observable_unordered_multimap
    : public basic_observable_unordered_associative_container<S, boost::unordered_multimap<K, T>>
{
public:
    virtual ~basic_observable_unordered_multimap();

protected:
    basic_observable_unordered_multimap();
    template <class InputIterator> basic_observable_unordered_multimap(InputIterator first, InputIterator last);
    explicit basic_observable_unordered_multimap(const this_type& x);
    explicit basic_observable_unordered_multimap(this_type&& x);
    explicit basic_observable_unordered_multimap(const boost::initializer_list<value_type>& il);

public:
    static ptr create();
    template <class InputIterator> static ptr create(InputIterator first, InputIterator last);
    static ptr create(const this_type& x);
    static ptr create(this_type&& x);
    static ptr create(const boost::initializer_list<value_type>& il);

public:
    this_type& operator=(const this_type& x);
    this_type& operator=(this_type&& x);

public:
    template <class... Args> iterator emplace(Args&&... args);
    iterator insert(const value_type& val);
    template <class P> iterator insert(P&& val);
    iterator insert(const_iterator position, const value_type& val);
    iterator insert(const_iterator position, value_type&& val);
    template <class InputIterator> void insert(InputIterator first, InputIterator last);
    void insert(const boost::initializer_list<value_type>& il);
    iterator erase(const_iterator position);
    size_type erase(const key_type& k);
    iterator erase(const_iterator first, const_iterator last);

protected:
    virtual container_type& container();
    virtual const container_type& container() const;
};
```

## Template parameters

Parameter | Description
-|-
K | The key type
T | The element type
S | The string class

## Member types

Member type | Definition
-|-
string_type | S
container_type | boost\::unordered_multimap<K, T>
this_type | basic_observable_unordered_multimap<K, T, S>
ptr | boost\::shared_ptr\<this_type>
wptr | boost\::weak_ptr\<this_type>
key_type | container_type\::key_type
mapped_type | container_type\::mapped_type
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

## Static member functions

### create

Specifiers | Signature
-|-
public static | ptr **create**()
public static | template <class InputIterator> ptr **create**(InputIterator first, InputIterator last)
public static | ptr **create**(const this_type& x)
public static | ptr **create**(this_type&& x)
public static | ptr **create**(const boost::initializer_list<value_type>& il)

Constructs a new **basic_observable_unordered_multimap<key_type, value_type, string_type>** object and return it as a
**basic_observable_unordered_multimap<key_type, value_type, string_type>\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_observable_unordered_multimap** object.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/~unordered_multimap)

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_observable_unordered_multimap**()
*constructor (2)* | protected | template <class InputIterator> **basic_observable_unordered_multimap**(InputIterator first, InputIterator last)
*copy constructor (3)* | protected explicit | **basic_observable_unordered_multimap**(const this_type& x)
*move constructor (4)* | protected explicit | **basic_observable_unordered_multimap**(this_type&& x)
*constructor (5)* | protected explicit | **basic_observable_unordered_multimap**(const boost::initializer_list<value_type>& il)

1. Constructs a **basic_observable_unordered_multimap** object with an empty container.
2. Constructs a **basic_observable_unordered_multimap** object with the contents of the range **[first, last)**.
3. Constructs a **basic_observable_unordered_multimap** object with the copy of the contents of **x**.
4. Constructs a **basic_observable_unordered_multimap** object with the contents of **x** using move semantics.
5. Constructs a **basic_observable_unordered_multimap** object with the contents of the initializer list **il**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/unordered_multimap)

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | public | this_type& **operator=**(const this_type& x)
*assign move (2)* | public | this_type& **operator=**(this_type&& x)

1. Copy assignment operator. Replaces the contents with a copy of the contents of **x**.
2. Move assignment operator. Replaces the contents with those of **x** using move semantics.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/operator%3D)

### emplace

Specifiers | Signature
-|-
public | template <class... Args> boost\::pair<iterator, bool> **emplace**(Args&&... args)

Inserts a new element into the container constructed in-place with the given **args**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/emplace)

### insert

Specifiers | Signature
-|-
public | boost\::pair<iterator, bool> **insert**(const value_type& val)
public | template <class P> boost\::pair<iterator, bool> **insert**(P&& val)
public | iterator **insert**(const_iterator position, const value_type& val)
public | iterator **insert**(const_iterator position, value_type&& val)
public | template <class InputIterator> void **insert**(InputIterator first, InputIterator last)
public | void **insert**(const boost\::initializer_list<value_type>& il)

Inserts element(s) into the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/insert)

### erase

Specifiers | Signature
-|-
public | iterator **erase**(const_iterator position)
public | size_type **erase**(const key_type& k)
public | iterator **erase**(const_iterator first, const_iterator last)

Removes specified elements from the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/erase)

### container

Specifiers | Signature
-|-
protected abstract | container_type& **container**()
protected abstract | const container_type& **container**() const

Return a referense to the underlying container storage.

## Inherited functions

### key_eq

Specifiers | Signature
-|-
public | key_equal **key_eq**() const

Returns the function that compares keys for equality.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/key_eq)

### hash_function

Specifiers | Signature
-|-
public | hasher **hash_function**() const

Returns the function that hashes the keys.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/hash_function)

### bucket

Specifiers | Signature
-|-
public | size_type **bucket**(const key_type& k) const

Returns the index of the bucket for key key.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/bucket)

### bucket_count

Specifiers | Signature
-|-
public | size_type **bucket_count**() const throw()

Returns the number of buckets in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/bucket_count)

### bucket_size

Specifiers | Signature
-|-
public | size_type **bucket_size**(size_type n) const

Returns the number of elements in the bucket with index n.

### max_bucket_count

Specifiers | Signature
-|-
public | size_type **max_bucket_count**() const

Returns the maximum number of buckets the container is able to hold.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/bucket_size)

### rehash

Specifiers | Signature
-|-
public | void **rehash**(size_type n)

Sets the number of buckets to count and rehashes the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/rehash)

### load_factor

Specifiers | Signature
-|-
public | float **load_factor**() const

Returns the average number of elements per bucket, that is, **size()** divided by
**bucket_count()**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/load_factor)

### max_load_factor

Specifiers | Signature
-|-
public | float **max_load_factor**() const
public | void **max_load_factor**(float z)

Manages the maximum load factor (number of elements per bucket). The container
automatically increases the number of buckets if the load factor exceeds this threshold.

1. Returns current maximum load factor.
2. Sets the maximum load factor to **z**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/max_load_factor)

### begin

Specifiers | Signature
-|-
public | iterator **begin**() throw()
public | const_iterator **begin**() const throw()

Returns an iterator to the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/begin)

### end

Specifiers | Signature
-|-
public | iterator **end**() throw()
public | const_iterator **end**() const throw()

Returns an iterator to the element following the last element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/end)

### cbegin

Specifiers | Signature
-|-
public | const_iterator **cbegin**() const throw()

Returns an iterator to the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/cbegin)

### cend

Specifiers | Signature
-|-
public | const_iterator **cend**() const throw()

Returns an iterator to the element following the last element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/cend)

### size

Specifiers | Signature
-|-
public | size_type **size**() const throw()

Returns the number of elements in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/size)

### max_size

Specifiers | Signature
-|-
public | size_type **max_size**() const throw()

Returns the maximum number of elements the container is able to hold.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/max_size)

### empty

Specifiers | Signature
-|-
public | bool **empty**() const throw()

Checks if the container has no elements, i.e. whether **begin() == end()**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/empty)

### emplace_hint

Specifiers | Signature
-|-
public | template <class... Args> iterator **emplace_hint**(const_iterator position, Args&&... args)

Inserts a new element into the container as close as possible to the position just
before hint.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/emplace_hint)

### clear

Specifiers | Signature
-|-
public | void **clear**() throw()

Removes all elements from the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/clear)

### swap

Specifiers | Signature
-|-
public | template<class t, class s> void **swap**(basic_observable_unordered_multimap<t, s>& x)

Exchanges the contents of the container with those of **x**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/swap)

### count

Specifiers | Signature
-|-
public | size_type **count**(const value_type& val) const

Returns the number of elements with key that compares equivalent to **val**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/count)

### find

Specifiers | Signature
-|-
public | const_iterator **find**(const value_type& val) const
public | iterator **find**(const value_type& val)

Finds an element with key equivalent to **val**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/find)

### equal_range

Specifiers | Signature
-|-
public | boost::pair<const_iterator, const_iterator> **equal_range**(const value_type& val) const
public | boost::pair<iterator, iterator> **equal_range**(const value_type& val)

Returns a range containing all elements with the given key in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/equal_range)

### get_allocator

Specifiers | Signature
-|-
public | allocator_type **get_allocator**() const throw()

Returns the allocator associated with the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/unordered_multimap/get_allocator)

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

# class template basic_property specializations

## class template observable_unordered_multimap

The **observable_unordered_multimap** is a generalization class for observable maps with any value
type and size using **std\::string**.

It is declared as:

```c++
template<class K, class T> class observable_unordered_multimap : public basic_observable_unordered_multimap<K, T, std\::string>
{
public:
    static ptr create();
    template <class InputIterator> static ptr create(InputIterator first, InputIterator last);
    static ptr create(const this_type& x);
    static ptr create(this_type&& x);
    static ptr create(const boost::initializer_list<value_type>& il);
};
```

## class template wobservable_unordered_multimap

The **wobservable_unordered_multimap** is a generalization class for observable maps with any value
type and size using **std\::wstring**.

It is declared as:

```c++
template<class K, class T> class wobservable_unordered_multimap : public basic_observable_unordered_multimap<K, T, std\::wstring>
{
public:
    static ptr create();
    template <class InputIterator> static ptr create(InputIterator first, InputIterator last);
    static ptr create(const this_type& x);
    static ptr create(this_type&& x);
    static ptr create(const boost::initializer_list<value_type>& il);
};
```
