---
layout: std_lib_utility_container
---

```c++
namespace go::utility::container
```

# class template circular_buffer

```c++
<go/utility/container/circular_buffer.hpp>
```

The **circular_buffer** is a class template that implement
a [circular buffer](https://en.wikipedia.org/wiki/Circular_buffer)
(also called a *ring buffer* or *cyclic buffer*). It refers
to an area in the memory which is used to store data. When
the buffer is filled, new data is written starting at the
beginning of the buffer and overwriting the old.

It is declared as:

```c++
template<class T, class A = std::allocator<T>> class circular_buffer
{
public:
    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

public:
    virtual ~circular_buffer() = default;
    explicit circular_buffer(const allocator_type& alloc = allocator_type()) noexcept;
    explicit circular_buffer(capacity_type cap, const allocator_type& alloc = allocator_type());
    circular_buffer(size_type count, param_value_type value, const allocator_type& alloc = allocator_type());
    circular_buffer(capacity_type cap, size_type count, param_value_type value, const allocator_type& alloc = allocator_type());
    circular_buffer(const this_type&) = default;
    circular_buffer(this_type&&) noexcept = default;
    template<typename InputIt> circular_buffer(InputIt first, InputIt last, const allocator_type& alloc = allocator_type());
    template<typename InputIt> circular_buffer(capacity_type cap, InputIt first, InputIt last, const allocator_type& alloc = allocator_type());
    circular_buffer(const std::initializer_list<T>& il, const allocator_type& alloc = allocator_type());
    circular_buffer(capacity_type cap, const std::initializer_list<T>& il, const allocator_type& alloc = allocator_type());

    this_type& operator=(const this_type&) = default;
    this_type& operator=(this_type&&) noexcept = default;
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;

    allocator_type get_allocator() const noexcept;
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;
    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference front();
    reference back();
    const_reference front() const;
    const_reference back() const;
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    bool empty() const noexcept;
    bool full() const noexcept;
    capacity_type capacity() const noexcept;
    void resize(capacity_type new_cap);
    void assign(size_type count, param_value_type value);
    void assign(capacity_type cap, size_type count, param_value_type value);
    template<typename InputIt> void assign(InputIt first, InputIt last);
    template<typename InputIt> void assign(capacity_type cap, InputIt first, InputIt last);
    void assign(const std::initializer_list<T>& il);
    void assign(capacity_type cap, const std::initializer_list<T>& il);
    void swap(this_type& other) noexcept;
    void push_back(param_value_type value);
    void push_back(rvalue_type value);
    void push_front(param_value_type value);
    void push_front(rvalue_type value);
    void pop_back();
    void pop_front();
    iterator insert(iterator it, param_value_type value);
    iterator insert(iterator it, rvalue_type value);
    iterator insert(iterator it);
    iterator erase(iterator it);
    void clear() noexcept;
};
```

## Template parameters

template<class T, class A = std::allocator<T>> class circular_buffer
Parameter | Description
-|-
T | The element type
A | The allocator type

## Member types

Member type | Definition
-|-
this_type | circular_buffer\<T, A>
element_type | T
allocator_type | A
buffer_container_type | typename std\::vector\<T, A>
value_type | typename buffer_container_type\::value_type
capacity_type | typename buffer_container_type\::size_type
reference | typename buffer_container_type\::reference
const_reference | typename buffer_container_type\::const_reference
pointer | typename buffer_container_type\::pointer
const_pointer | typename buffer_container_type\::const_pointer
difference_type | typename buffer_container_type\::difference_type
size_type | typename buffer_container_type\::size_type
param_value_type | typename buffer_container_type\::const_reference
rvalue_type | typename buffer_container_type\::value_type&&

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **circular_buffer** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*constructor (1)* | public explicit noexcept | **circular_buffer**(const allocator_type& alloc = allocator_type())
*constructor (2)* | public explicit noexcept | **circular_buffer**(capacity_type cap, const allocator_type& alloc = allocator_type())
*constructor (3)* | public | **circular_buffer**(size_type count, param_value_type value, const allocator_type& alloc = allocator_type())
*constructor (4)* | public | **circular_buffer**(capacity_type cap, size_type count, param_value_type value, const allocator_type& alloc = allocator_type())
*constructor (5)* | public | **circular_buffer**(const this_type&)
*constructor (6)* | public noexcept | **circular_buffer**(this_type&&)
*constructor (7)* | public | template<typename InputIt> **circular_buffer**(InputIt first, InputIt last, const allocator_type& alloc = allocator_type())
*constructor (8)* | public | template<typename InputIt> **circular_buffer**(capacity_type cap, InputIt first, InputIt last, const allocator_type& alloc = allocator_type())
*constructor (9)* | public | **circular_buffer**(const std::initializer_list<T>& il, const allocator_type& alloc = allocator_type())
*constructor (10)* | public | **circular_buffer**(capacity_type cap, const std::initializer_list<T>& il, const allocator_type& alloc = allocator_type())

1. Default constructor. Constructs an empty **circular_buffer** with a default-constructed allocator or the given allocator.
2. Constructs an empty **circular_buffer** with a default-constructed allocator or the given allocator and capacity *cap*.
3. Constructs the **circular_buffer** with count copies of elements with value *value*.
4. Constructs the **circular_buffer** with count copies of elements with value *value* and capacity *cap*.
5. Copy constructor.
6. Move constructor.
7. Constructs the **circular_buffer** with the contents of the range [first, last).
8. Constructs the **circular_buffer** with the contents of the range [first, last) and capacity *cap*.
9. Constructs the **circular_buffer** with the contents of the initializer list *il*.
10. Constructs the **circular_buffer** with the contents of the initializer list *il* and capacity *cap*.

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | public | this_type& **operator=**(const this_type& x)
*assign move (2)* | public | this_type& **operator=**(this_type&& x)

1. Copy assignment operator. Replaces the contents with a copy of the contents of **x**.
2. Move assignment operator. Replaces the contents with those of **x** using move semantics.

### Subscript operator

Specifiers | Signature
-|-
public | const_reference **operator[]**(size_type pos) const
public | reference **operator[]**(size_type pos)

Returns a reference to the element at specified location **pos**.

### get_allocator

Specifiers | Signature
-|-
public | allocator_type **get_allocator**() const noexcept

Returns the allocator associated with the container.

### begin

Specifiers | Signature
-|-
public | iterator **begin**() noexcept
public | const_iterator **begin**() const noexcept

Returns an iterator to the first element of the container.

### end

Specifiers | Signature
-|-
public | iterator **end**() noexcept
public | const_iterator **end**() const noexcept

Returns an iterator to the element following the last element of the container.

### rbegin

Specifiers | Signature
-|-
public | reverse_iterator **rbegin**() noexcept
public | const_reverse_iterator **rbegin**() const noexcept

Returns a reverse iterator to the first element of the reversed container.

### rend

Specifiers | Signature
-|-
public | reverse_iterator **rend**() noexcept
public | const_reverse_iterator **rend**() const noexcept

Returns a reverse iterator to the element following the last element of the
reversed container.

### at

Specifiers | Signature
-|-
public | const_reference *at**(size_type pos) const
public | reference **at**(size_type pos)

Returns a reference to the element at specified location **pos**.

### front

Specifiers | Signature
-|-
public | reference **front**()
public constexpr | const_reference **front**() const

Returns reference to the first element in the container.

### back

Specifiers | Signature
-|-
public | reference **back**()
public constexpr | const_reference **back**() const

Returns reference to the last element in the container.

### size

Specifiers | Signature
-|-
public | size_type **size**() const noexcept

Returns the number of elements in the container.

### max_size

Specifiers | Signature
-|-
public | size_type **max_size**() const noexcept

Returns the maximum number of elements the container is
able to hold due to system or library implementation
limitations.

### empty

Specifiers | Signature
-|-
public | bool **empty**() const noexcept

Checks if the container has no elements, i.e. whether **size() == 0**.

### full

Specifiers | Signature
-|-
public | bool **full**() const noexcept

Checks if the container is full to capacity, i.e. whether **size() == capacity()**.

### capacity

Specifiers | Signature
-|-
public | capacity_type **capacity**() const noexcept

Returns the number of elements that the container has currently allocated space for.

### resize

Specifiers | Signature
-|-
public | void **resize**(capacity_type new_cap)

Change the capacity of the circular buffer to to **new_cap**.

### assign

Specifiers | Signature
-|-
public | void **assign**(size_type count, param_value_type value)
public | void **assign**(capacity_type cap, size_type count, param_value_type value)
public | template<typename InputIt> void **assign**(InputIt first, InputIt last)
public | template<typename InputIt> void **assign**(capacity_type cap, InputIt first, InputIt last)
public | void **assign**(const std::initializer_list<T>& il)
public | void **assign**(capacity_type cap, const std::initializer_list<T>& il)

Replaces the contents of the container.

### swap

Specifiers | Signature
-|-
public | void **swap**(this_type& other) noexcept

Exchanges the contents of the container with those of other.

### push_back

Specifiers | Signature
-|-
public | void **push_back**(param_value_type val)
public | void **push_back**(rvalue_type val)

Appends the given element value to the end of the container.
If the container is full it will create space for the new
element by doing a **pop_front**.


### push_front

Specifiers | Signature
-|-
public | void **push_front**(param_value_type val)
public | void **push_front**(rvalue_type val)

Prepends the given element value to the beginning of the container.
If the container is full it will create space for the new
element by doing a **pop_back**.

### pop_back

Specifiers | Signature
-|-
public | void **pop_back**()

Removes the last element of the container.

### pop_front

Specifiers | Signature
-|-
public | void **pop_front**()

Removes the first element of the container.

### insert

Specifiers | Signature
-|-
public | iterator **insert**(iterator it, param_value_type value)
public | iterator **insert**(iterator it, rvalue_type value)
public | iterator **insert**(iterator it)

Inserts elements at the specified location in the container.
If the container becomes full it will create space for new
elements by doing **pop_front**.

### erase

Specifiers | Signature
-|-
public | iterator **erase**(iterator it)

Removes specified elements from the container.

### clear

Specifiers | Signature
-|-
public | void **clear**() noexcept

Removes all elements from the container.

##  Nested classes

### iterator_base

Base class for **circular_buffer** random access iterators.

```c++
class iterator_base : public std::iterator<std::random_access_iterator_tag, value_type>
{
protected:
    virtual ~iterator_base() = default;
    iterator_base() = default;
    iterator_base(const iterator_base&) = default;
    iterator_base(iterator_base&&) = default;
    explicit iterator_base(this_type* container, size_t pos = 0);

    iterator_base& operator=(const iterator_base&) = default;
    iterator_base& operator=(iterator_base&&) = default;
    bool operator==(const iterator_base& other) const;
    bool operator!=(const iterator_base& other) const;
    bool operator<(const iterator_base& other) const;
    bool operator>(const iterator_base& other) const;
    bool operator<=(const iterator_base& other) const;
    bool operator>=(const iterator_base& other) const;
    reference operator*();
    const_reference operator*() const;
    pointer operator->();
    const_pointer operator->() const;

public:
    constexpr bool is_at_end() const;
    constexpr bool is_in_valid_range() const;
    constexpr bool is_valid() const;

protected:
    void increment();
    void decrement();
};
```

### iterator

Class implementing a **circular_buffer** random access iterator.

```c++
class iterator : public iterator_base
{
public:
    virtual ~iterator() = default;
    iterator() = default;
    iterator(const iterator&) = default;
    iterator(iterator&&) = default;
    explicit iterator(this_type* container, size_t pos = 0);

    iterator& operator=(const iterator&) = default;
    iterator& operator=(iterator&&) = default;
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
    bool operator<(const iterator& other) const;
    bool operator>(const iterator& other) const;
    bool operator<=(const iterator& other) const;
    bool operator>=(const iterator& other) const;
    reference operator*();
    const_reference operator*() const;
    pointer operator->();
    const_pointer operator->() const;
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
};
```

### const_iterator

Class implementing a **circular_buffer** constant random access iterator.

```c++
class const_iterator : public iterator_base
{
public:
    virtual ~const_iterator() = default;
    const_iterator() = default;
    const_iterator(const const_iterator&) = default;
    const_iterator(const_iterator&&) = default;
    explicit const_iterator(this_type* container, size_t pos = 0);
    const_iterator& operator=(const const_iterator&) = default;
    const_iterator& operator=(const_iterator&&) = default;

    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;
    bool operator<(const const_iterator& other) const;
    bool operator>(const const_iterator& other) const;
    bool operator<=(const const_iterator& other) const;
    bool operator>=(const const_iterator& other) const;
    const_reference operator*() const;
    const_pointer operator->() const;
    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator& operator--();
    const_iterator operator--(int);
};
```

### reverse_iterator

Class implementing a **circular_buffer** reverse random access iterator.

```c++
class reverse_iterator : public iterator_base
{
public:
    virtual ~reverse_iterator() = default;
    reverse_iterator() = default;
    reverse_iterator(const reverse_iterator&) = default;
    reverse_iterator(reverse_iterator&&) = default;
    explicit reverse_iterator(this_type* container, size_t pos = 0);
    reverse_iterator& operator=(const reverse_iterator&) = default;
    reverse_iterator& operator=(reverse_iterator&&) = default;

    bool operator==(const reverse_iterator& other) const;
    bool operator!=(const reverse_iterator& other) const;
    bool operator<(const reverse_iterator& other) const;
    bool operator>(const reverse_iterator& other) const;
    bool operator<=(const reverse_iterator& other) const;
    bool operator>=(const reverse_iterator& other) const;
    reference operator*();
    const_reference operator*() const;
    pointer operator->();
    const_pointer operator->() const;
    reverse_iterator& operator++();
    reverse_iterator operator++(int);
    reverse_iterator& operator--();
    reverse_iterator operator--(int);
};
```

### const_reverse_iterator

Class implementing a **circular_buffer** constant reverse random access iterator.

```c++
class const_reverse_iterator : public iterator_base
{
public:
    virtual ~const_reverse_iterator() = default;
    const_reverse_iterator() = default;
    const_reverse_iterator(const const_reverse_iterator&) = default;
    const_reverse_iterator(const_reverse_iterator&&) = default;
    explicit const_reverse_iterator(this_type* container, size_t pos = 0);

    const_reverse_iterator& operator=(const const_reverse_iterator&) = default;
    const_reverse_iterator& operator=(const_reverse_iterator&&) = default;
    bool operator==(const const_reverse_iterator& other) const;
    bool operator!=(const const_reverse_iterator& other) const;
    bool operator<(const const_reverse_iterator& other) const;
    bool operator>(const const_reverse_iterator& other) const;
    bool operator<=(const const_reverse_iterator& other) const;
    bool operator>=(const const_reverse_iterator& other) const;
    const_reference operator*() const;
    const_pointer operator->() const;
    const_reverse_iterator& operator++();
    const_reverse_iterator operator++(int);
    const_reverse_iterator& operator--();
    const_reverse_iterator operator--(int);
};
```
