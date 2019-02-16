---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class basic_observable_multimap

```c++
<go/mvvm.hpp>
```

**basic_observable_multimap class**

The **basic_observable_multimap** is a container that encapsulates collections of key-value
pairs, sorted by keys. It wraps the [**std\::multimap**](https://en.cppreference.com/w/cpp/container/multimap)
and adds notifications when items get added, removed, or when the whole multimap is reset
or swapped.

It is declared as:

```c++
template<class K, class T, class S> class basic_observable_multimap
    : public basic_observable_ordered_associative_container<S, std::multimap<K, T>>
{
public:
    virtual ~basic_observable_multimap() = default;

protected:
    basic_observable_multimap();
    template <class InputIterator> basic_observable_multimap(InputIterator first, InputIterator last);
    explicit basic_observable_multimap(const this_type& x);
    explicit basic_observable_multimap(this_type&& x);
    explicit basic_observable_multimap(const std::initializer_list<value_type>& il);

public:
    static ptr create();
    template <class InputIterator> static ptr create(InputIterator first, InputIterator last);
    static ptr create(const this_type& x);
    static ptr create(this_type&& x);
    static ptr create(const std::initializer_list<value_type>& il);

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
    void insert(const std::initializer_list<value_type>& il);
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
container_type | std\::map<K, T>
this_type | basic_observable_multimap<K, T, S>
ptr | std\::shared_ptr\<this_type>
wptr | std\::weak_ptr\<this_type>
key_type | container_type\::key_type
mapped_type | container_type\::mapped_type
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
public static | ptr **create**(const std::initializer_list<value_type>& il)

Constructs a new **basic_observable_multimap<key_type, value_type, string_type>** object and return it as a
**basic_observable_multimap<key_type, value_type, string_type>\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_observable_multimap** object.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/~multimap)

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_observable_multimap**()
*constructor (2)* | protected | template <class InputIterator> **basic_observable_multimap**(InputIterator first, InputIterator last)
*copy constructor (3)* | protected explicit | **basic_observable_multimap**(const this_type& x)
*move constructor (4)* | protected explicit | **basic_observable_multimap**(this_type&& x)
*constructor (5)* | protected explicit | **basic_observable_multimap**(const std::initializer_list<value_type>& il)

1. Constructs a **basic_observable_multimap** object with an empty container.
2. Constructs a **basic_observable_multimap** object with the contents of the range **[first, last)**.
3. Constructs a **basic_observable_multimap** object with the copy of the contents of **x**.
4. Constructs a **basic_observable_multimap** object with the contents of **x** using move semantics.
5. Constructs a **basic_observable_multimap** object with the contents of the initializer list **il**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/multimap)

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | public | this_type& **operator=**(const this_type& x)
*assign move (2)* | public | this_type& **operator=**(this_type&& x)

1. Copy assignment operator. Replaces the contents with a copy of the contents of **x**.
2. Move assignment operator. Replaces the contents with those of **x** using move semantics.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/operator%3D)

### emplace

Specifiers | Signature
-|-
public | template <class... Args> iterator **emplace**(Args&&... args)

Inserts a new element into the container constructed in-place with the given **args**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/emplace)

### insert

Specifiers | Signature
-|-
public | iterator **insert**(const value_type& val)
public | template <class P> iterator **insert**(P&& val)
public | iterator **insert**(const_iterator position, const value_type& val)
public | iterator **insert**(const_iterator position, value_type&& val)
public | template <class InputIterator> void **insert**(InputIterator first, InputIterator last)
public | void **insert**(const std\::initializer_list<value_type>& il)

Inserts element(s) into the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/insert)

### erase

Specifiers | Signature
-|-
public | iterator **erase**(const_iterator position)
public | size_type **erase**(const key_type& k)
public | iterator **erase**(const_iterator first, const_iterator last)

Removes specified elements from the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/erase)

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
public | reverse_iterator **rbegin**() noexcept
public constexpr | const_reverse_iterator **rbegin**() const noexcept

Returns a reverse iterator to the first element of the reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/rbegin)

### rend

Specifiers | Signature
-|-
public | reverse_iterator **rend**() noexcept
public constexpr | const_reverse_iterator **rend**() const noexcept

Returns a reverse iterator to the element following the last element of the
reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/rend)

### crbegin

Specifiers | Signature
-|-
public constexpr | const_reverse_iterator **crbegin**() const noexcept

Returns a reverse iterator to the first element of the reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/crbegin)

### crend

Specifiers | Signature
-|-
public constexpr | const_reverse_iterator **crend**() const noexcept

Returns a reverse iterator to the element following the last element of the
reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/crend)

### lower_bound

Specifiers | Signature
-|-
public | iterator **lower_bound**(const value_type& val)
public constexpr | const_iterator **lower_bound**(const value_type& val) const

Returns an iterator pointing to the first element that is *not less* than **val**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/lower_bound)

### upper_bound

Specifiers | Signature
-|-
public | iterator **upper_bound**(const value_type& val)
public constexpr | const_iterator **upper_bound**(const value_type& val) const

Returns an iterator pointing to the first element that is *greater* than **val**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/upper_bound)

### key_comp

Specifiers | Signature
-|-
public constexpr | key_compare **key_comp**() const

Returns the function object that compares the keys, which is a copy of this container's
constructor argument comp.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/key_comp)

### value_comp

Specifiers | Signature
-|-
public constexpr | value_compare **value_comp**() const

Returns the function object that compares the values.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/value_comp)

### begin

Specifiers | Signature
-|-
public | iterator **begin**() noexcept
public constexpr | const_iterator **begin**() const noexcept

Returns an iterator to the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/begin)

### end

Specifiers | Signature
-|-
public | iterator **end**() noexcept
public constexpr | const_iterator **end**() const noexcept

Returns an iterator to the element following the last element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/end)

### cbegin

Specifiers | Signature
-|-
public constexpr | const_iterator **cbegin**() const noexcept

Returns an iterator to the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/cbegin)

### cend

Specifiers | Signature
-|-
public constexpr | const_iterator **cend**() const noexcept

Returns an iterator to the element following the last element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/cend)

### size

Specifiers | Signature
-|-
public constexpr | size_type **size**() const noexcept

Returns the number of elements in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/size)

### max_size

Specifiers | Signature
-|-
public constexpr | size_type **max_size**() const noexcept

Returns the maximum number of elements the container is able to hold.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/max_size)

### empty

Specifiers | Signature
-|-
public constexpr | bool **empty**() const noexcept

Checks if the container has no elements, i.e. whether **begin() == end()**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/empty)

### emplace_hint

Specifiers | Signature
-|-
public | template <class... Args> iterator **emplace_hint**(const_iterator position, Args&&... args)

Inserts a new element into the container as close as possible to the position just
before hint.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/emplace_hint)

### clear

Specifiers | Signature
-|-
public | void **clear**() noexcept

Removes all elements from the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/clear)

### swap

Specifiers | Signature
-|-
public | template<class t, class s> void **swap**(basic_observable_multimap<t, s>& x)

Exchanges the contents of the container with those of **x**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/swap)

### count

Specifiers | Signature
-|-
public constexpr | size_type **count**(const value_type& val) const

Returns the number of elements with key that compares equivalent to **val**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/count)

### find

Specifiers | Signature
-|-
public constexpr | const_iterator **find**(const value_type& val) const
public | iterator **find**(const value_type& val)

Finds an element with key equivalent to **val**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/find)

### equal_range

Specifiers | Signature
-|-
public constexpr | std::pair<const_iterator, const_iterator> **equal_range**(const value_type& val) const
public | std::pair<iterator, iterator> **equal_range**(const value_type& val)

Returns a range containing all elements with the given key in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/equal_range)

### get_allocator

Specifiers | Signature
-|-
public constexpr | allocator_type **get_allocator**() const noexcept

Returns the allocator associated with the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/multimap/get_allocator)

### notify_insert

Specifiers | Signature
-|-
protected | void **notify_insert**(const std\::size_t& before, const std\::size_t& after)

Emit signal to notify that new elements have been inserted into the container.

### notify_erase

Specifiers | Signature
-|-
protected | void **notify_erase**(const std\::size_t& before, const std\::size_t& after)

Emit signal to notify that elements have been erased from the container.

# class template basic_property specializations

## class template observable_multimap

The **observable_multimap** is a generalization class for observable maps with any value
type and size using **std\::string**.

It is declared as:

```c++
template<class K, class T> class observable_multimap : public basic_observable_multimap<K, T, std\::string>
{
public:
    static ptr create();
    template <class InputIterator> static ptr create(InputIterator first, InputIterator last);
    static ptr create(const this_type& x);
    static ptr create(this_type&& x);
    static ptr create(const std::initializer_list<value_type>& il);
};
```

## class template wobservable_multimap

The **wobservable_multimap** is a generalization class for observable maps with any value
type and size using **std\::wstring**.

It is declared as:

```c++
template<class K, class T> class wobservable_multimap : public basic_observable_multimap<K, T, std\::wstring>
{
public:
    static ptr create();
    template <class InputIterator> static ptr create(InputIterator first, InputIterator last);
    static ptr create(const this_type& x);
    static ptr create(this_type&& x);
    static ptr create(const std::initializer_list<value_type>& il);
};
```
