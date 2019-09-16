---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class basic_observable_set

```c++
<go_boost/mvvm.hpp>
```

**basic_observable_set class**

The **basic_observable_set** is a container that encapsulates collections of unique
keys, sorted by keys. It wraps the [**boost\::set**](https://en.cppreference.com/w/cpp/container/set)
and adds notifications when items get added, removed, or when the whole set is reset
or swapped.

It is declared as:

```c++
template<class K, class S> class basic_observable_set
    : public basic_observable_ordered_associative_container<S, boost::set<K>>
{
public:
    virtual ~basic_observable_set();

protected:
    basic_observable_set();
    template <class InputIterator> basic_observable_set(InputIterator first, InputIterator last);
    explicit basic_observable_set(const this_type& x);
    explicit basic_observable_set(this_type&& x);
    explicit basic_observable_set(const boost::initializer_list<value_type>& il);

public:
    static ptr create();
    template <class InputIterator> static ptr create(InputIterator first, InputIterator last);
    static ptr create(const this_type& x);
    static ptr create(this_type&& x);
    static ptr create(const boost::initializer_list<value_type>& il);

public:
    this_type& operator=(const this_type& x) noexcept;
    this_type& operator=(this_type&& x) noexcept;

public:
    template <class... Args> boost::pair<iterator, bool> emplace(Args&&... args);
    boost::pair<iterator, bool> insert(const value_type& val);
    boost::pair<iterator, bool> insert(value_type&& val);
    iterator insert(const_iterator position, const value_type& val);
    iterator insert(const_iterator position, value_type&& val);
    template <class InputIterator> void insert(InputIterator first, InputIterator last);
    void insert(const boost::initializer_list<value_type>& il);
    iterator erase(const_iterator position);
    size_type erase(const value_type& val);
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
S | The string class

## Member types

Member type | Definition
-|-
string_type | S
container_type | boost\::set<K>
this_type | basic_observable_set<K, S>
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

## Static member functions

### create

Specifiers | Signature
-|-
public static | ptr **create**()
public static | template <class InputIterator> ptr **create**(InputIterator first, InputIterator last)
public static | ptr **create**(const this_type& x)
public static | ptr **create**(this_type&& x)
public static | ptr **create**(const boost::initializer_list<value_type>& il)

Constructs a new **basic_observable_set<key_type, string_type>** object and return it as a
**basic_observable_set<key_type, string_type>\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_observable_set** object.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/~set)

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_observable_set**()
*constructor (2)* | protected | template <class InputIterator> **basic_observable_set**(InputIterator first, InputIterator last)
*copy constructor (3)* | protected explicit | **basic_observable_set**(const this_type& x)
*move constructor (4)* | protected explicit | **basic_observable_set**(this_type&& x)
*constructor (5)* | protected explicit | **basic_observable_set**(const boost::initializer_list<value_type>& il)

1. Constructs a **basic_observable_set** object with an empty container.
2. Constructs a **basic_observable_set** object with the contents of the range **[first, last)**.
3. Constructs a **basic_observable_set** object with the copy of the contents of **x**.
4. Constructs a **basic_observable_set** object with the contents of **x** using move semantics.
5. Constructs a **basic_observable_set** object with the contents of the initializer list **il**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/set)

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | public | this_type& **operator=**(const this_type& x) noexcept
*assign move (2)* | public | this_type& **operator=**(this_type&& x) noexcept

1. Copy assignment operator. Replaces the contents with a copy of the contents of **x**.
2. Move assignment operator. Replaces the contents with those of **x** using move semantics.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/operator%3D)

### emplace

Specifiers | Signature
-|-
public | template <class... Args> boost\::pair<iterator, bool> **emplace**(Args&&... args)

Inserts a new element into the container constructed in-place with the given **args** if
there is no element with the key in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/emplace)

### insert

Specifiers | Signature
-|-
public | boost\::pair<iterator, bool> **insert**(const value_type& val)
public | boost\::pair<iterator, bool> **insert**(value_type&& val)
public | iterator **insert**(const_iterator position, const value_type& val)
public | iterator **insert**(const_iterator position, value_type&& val)
public | template <class InputIterator> void **insert**(InputIterator first, InputIterator last)
public | void **insert**(const boost\::initializer_list<value_type>& il)

Inserts element(s) into the container, if the container doesn't already contain an
element with an equivalent key.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/insert)

### erase

Specifiers | Signature
-|-
public | iterator **erase**(const_iterator position)
public | size_type **erase**(const value_type& val)
public | iterator **erase**(const_iterator first, const_iterator last)

Removes specified elements from the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/erase)

### container

Specifiers | Signature
-|-
protected abstract | container_type& **container**()
protected abstract | const container_type& **container**() const

Return a referense to the underlying container storage.

## Inherited functions

### rbegin

Specifiers | Signature
-|-
public | reverse_iterator **rbegin**() throw()
public | const_reverse_iterator **rbegin**() const throw()

Returns a reverse iterator to the first element of the reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/rbegin)

### rend

Specifiers | Signature
-|-
public | reverse_iterator **rend**() throw()
public | const_reverse_iterator **rend**() const throw()

Returns a reverse iterator to the element following the last element of the
reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/rend)

### crbegin

Specifiers | Signature
-|-
public | const_reverse_iterator **crbegin**() const throw()

Returns a reverse iterator to the first element of the reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/crbegin)

### crend

Specifiers | Signature
-|-
public | const_reverse_iterator **crend**() const throw()

Returns a reverse iterator to the element following the last element of the
reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/crend)

### lower_bound

Specifiers | Signature
-|-
public | iterator **lower_bound**(const value_type& val)
public | const_iterator **lower_bound**(const value_type& val) const

Returns an iterator pointing to the first element that is *not less* than **val**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/lower_bound)

### upper_bound

Specifiers | Signature
-|-
public | iterator **upper_bound**(const value_type& val)
public | const_iterator **upper_bound**(const value_type& val) const

Returns an iterator pointing to the first element that is *greater* than **val**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/upper_bound)

### key_comp

Specifiers | Signature
-|-
public | key_compare **key_comp**() const

Returns the function object that compares the keys, which is a copy of this container's
constructor argument comp.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/key_comp)

### value_comp

Specifiers | Signature
-|-
public | value_compare **value_comp**() const

Returns the function object that compares the values.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/value_comp)

### begin

Specifiers | Signature
-|-
public | iterator **begin**() throw()
public | const_iterator **begin**() const throw()

Returns an iterator to the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/begin)

### end

Specifiers | Signature
-|-
public | iterator **end**() throw()
public | const_iterator **end**() const throw()

Returns an iterator to the element following the last element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/end)

### cbegin

Specifiers | Signature
-|-
public | const_iterator **cbegin**() const throw()

Returns an iterator to the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/cbegin)

### cend

Specifiers | Signature
-|-
public | const_iterator **cend**() const throw()

Returns an iterator to the element following the last element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/cend)

### size

Specifiers | Signature
-|-
public | size_type **size**() const throw()

Returns the number of elements in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/size)

### max_size

Specifiers | Signature
-|-
public | size_type **max_size**() const throw()

Returns the maximum number of elements the container is able to hold.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/max_size)

### empty

Specifiers | Signature
-|-
public | bool **empty**() const throw()

Checks if the container has no elements, i.e. whether **begin() == end()**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/empty)

### emplace_hint

Specifiers | Signature
-|-
public | template <class... Args> iterator **emplace_hint**(const_iterator position, Args&&... args)

Inserts a new element into the container as close as possible to the position just
before hint.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/emplace_hint)

### clear

Specifiers | Signature
-|-
public | void **clear**() throw()

Removes all elements from the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/clear)

### swap

Specifiers | Signature
-|-
public | template<class t, class s> void **swap**(basic_observable_set<t, s>& x)

Exchanges the contents of the container with those of **x**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/swap)

### count

Specifiers | Signature
-|-
public | size_type **count**(const value_type& val) const

Returns the number of elements with key that compares equivalent to **val**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/count)

### find

Specifiers | Signature
-|-
public | const_iterator **find**(const value_type& val) const
public | iterator **find**(const value_type& val)

Finds an element with key equivalent to **val**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/find)

### equal_range

Specifiers | Signature
-|-
public | boost::pair<const_iterator, const_iterator> **equal_range**(const value_type& val) const
public | boost::pair<iterator, iterator> **equal_range**(const value_type& val)

Returns a range containing all elements with the given key in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/equal_range)

### get_allocator

Specifiers | Signature
-|-
public | allocator_type **get_allocator**() const throw()

Returns the allocator associated with the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/set/get_allocator)

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

## class template observable_set

The **observable_set** is a generalization class for observable maps with any value
type and size using **std\::string**.

It is declared as:

```c++
template<class K> class observable_set : public basic_observable_set<T, std\::string>
{
public:
    static ptr create();
    template <class InputIterator> static ptr create(InputIterator first, InputIterator last);
    static ptr create(const this_type& x);
    static ptr create(this_type&& x);
    static ptr create(const boost::initializer_list<value_type>& il);
};
```

## class template wobservable_set

The **wobservable_set** is a generalization class for observable maps with any value
type and size using **std\::wstring**.

It is declared as:

```c++
template<class K> class wobservable_set : public basic_observable_set<T, std\::wstring>
{
public:
    static ptr create();
    template <class InputIterator> static ptr create(InputIterator first, InputIterator last);
    static ptr create(const this_type& x);
    static ptr create(this_type&& x);
    static ptr create(const boost::initializer_list<value_type>& il);
};
```
