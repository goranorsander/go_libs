---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class basic_observable_deque

```c++
<go_boost/mvvm.hpp>
```

**basic_observable_deque class**

The **basic_observable_deque** is a container that encapsulates double-ended queues.
It wraps the [**std\::deque**](https://en.cppreference.com/w/cpp/container/deque)
and adds notifications when items get added, removed, or when the whole double-ended
queue is reset or swapped.

It is declared as:

```c++
template<class T, class S> class basic_observable_deque
    : public basic_observable_sequence_container<S, std::deque<T>>
{
public:
    virtual ~basic_observable_deque();

protected:
    basic_observable_deque();
    explicit basic_observable_deque(size_type n);
    basic_observable_deque(size_type n, const value_type& val);
    template <class InputIterator> basic_observable_deque(InputIterator first, InputIterator last);
    explicit basic_observable_deque(const this_type& x);
    explicit basic_observable_deque(this_type&& x);
    explicit basic_observable_deque(const boost::initializer_list<value_type>& il);

public:
    static ptr create();
    static ptr create(size_type n);
    static ptr create(size_type n, const value_type& val);
    template <class InputIterator> static ptr create(InputIterator first, InputIterator last);
    static ptr create(const this_type& x);
    static ptr create(this_type&& x);
    static ptr create(const boost::initializer_list<value_type>& il);

public:
    this_type& operator=(const this_type& x);
    this_type& operator=(this_type&& x);
    this_type& operator=(const boost::initializer_list<value_type>& il);
    const_reference operator[](size_type n) const;
    reference operator[](size_type n);

protected:
    virtual container_type& container();
    virtual const container_type& container() const;

public:
    reverse_iterator rbegin() throw();
    const_reverse_iterator rbegin() const throw();
    reverse_iterator rend() throw();
    const_reverse_iterator rend() const throw();
    const_reverse_iterator crbegin() const throw();
    const_reverse_iterator crend() const throw();
    size_type size() const throw();
    const_reference at(size_type n) const;
    reference at(size_type n);
    reference back();
    const_reference back() const;
    void resize(size_type n);
    void resize(size_type n, const value_type& val);
    void shrink_to_fit();
    template <class InputIterator> void assign(InputIterator first, InputIterator last);
    void assign(size_type n, const value_type& val);
    void assign(const boost::initializer_list<value_type>& il);
    void push_back(const value_type& val);
    void push_back(value_type&& val);
    void push_front(const value_type& val);
    void push_front(value_type&& val);
    void pop_back();
    void pop_front();
    iterator insert(const_iterator position, const value_type& val);
    iterator insert(const_iterator position, size_type n, const value_type& val);
    template <class InputIterator> iterator insert(const_iterator position, InputIterator first, InputIterator last);
    iterator insert(const_iterator position, value_type&& val);
    iterator insert(const_iterator position, boost::initializer_list<value_type> il);
    iterator erase(const_iterator position);
    iterator erase(const_iterator first, const_iterator last);
    template<class t, class s> void swap(basic_observable_deque<t, s>& x);
    void clear() throw();
    template <class... Args> iterator emplace(const_iterator position, Args&&... args);
    template <class... Args> void emplace_back(Args&&... args);
    template <class... Args> void emplace_front(Args&&... args);
    allocator_type get_allocator() const throw();
};
```

## Template parameters

Parameter | Description
-|-
T | The element type
S | The string class

## Member types

Member type | Definition
-|-
string_type | S
container_type | std\::deque<T>
this_type | basic_observable_deque<T, S>
ptr | boost\::shared_ptr\<this_type>
wptr | boost\::weak_ptr\<this_type>
value_type | container_type\::value_type
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
public static | ptr **create**(size_type n)
public static | ptr **create**(size_type n, const value_type& val)
public static | template <class InputIterator> ptr **create**(InputIterator first, InputIterator last)
public static | ptr **create**(const this_type& x)
public static | ptr **create**(this_type&& x)
public static | ptr **create**(const boost::initializer_list<value_type>& il)

Constructs a new **basic_observable_deque<value_type, string_type, lockable_type>** object and return it as a
**basic_observable_deque<value_type, string_type, lockable_type>\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_observable_deque** object.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/~deque)

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_observable_deque**()
*constructor (2)* | protected explicit | **basic_observable_deque**(size_type n)
*constructor (3)* | protected | **basic_observable_deque**(size_type n, const value_type& val)
*constructor (4)* | protected | template <class InputIterator> **basic_observable_deque**(InputIterator first, InputIterator last)
*copy constructor (5)* | protected explicit | **basic_observable_deque**(const this_type& x)
*move constructor (6)* | protected explicit | **basic_observable_deque**(this_type&& x)
*constructor (7)* | protected explicit | **basic_observable_deque**(const boost::initializer_list<value_type>& il)

1. Constructs a **basic_observable_deque** object with an empty container.
2. Constructs a **basic_observable_deque** object with **n** default-inserted instances of **T**.
3. Constructs a **basic_observable_deque** object with **n** copies of elements with value **val**.
4. Constructs a **basic_observable_deque** object with the contents of the range **[first, last)**.
5. Constructs a **basic_observable_deque** object with the copy of the contents of **x**.
6. Constructs a **basic_observable_deque** object with the contents of **x** using move semantics.
7. Constructs a **basic_observable_deque** object with the contents of the initializer list **il**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/deque)

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | public | this_type& **operator=**(const this_type& x)
*assign move (2)* | public | this_type& **operator=**(this_type&& x)
*assign replace (2)* | public | this_type& **operator=**(const boost\::initializer_list<value_type>& il)

1. Copy assignment operator. Replaces the contents with a copy of the contents of **x**.
2. Move assignment operator. Replaces the contents with those of **x** using move semantics.
3. Replaces the contents with those identified by initializer list **il**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/operator%3D)

### Subscript operator

Specifiers | Signature
-|-
public | const_reference **operator[]**(size_type n) const
public | reference **operator[]**(size_type n)

Returns a reference to the element at specified location **n**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/operator_at)

### container

Specifiers | Signature
-|-
protected virtual | container_type& **container**()
protected virtual | const container_type& **container**() const

Return a referense to the underlying container storage.

### rbegin

Specifiers | Signature
-|-
public | reverse_iterator **rbegin**() throw()
public | const_reverse_iterator **rbegin**() const throw()

Returns a reverse iterator to the first element of the reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/rbegin)

### rend

Specifiers | Signature
-|-
public | reverse_iterator **rend**() throw()
public | const_reverse_iterator **rend**() const throw()

Returns a reverse iterator to the element following the last element of the
reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/rend)

### crbegin

Specifiers | Signature
-|-
public | const_reverse_iterator **crbegin**() const throw()

Returns a reverse iterator to the first element of the reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/crbegin)

### crend

Specifiers | Signature
-|-
public | const_reverse_iterator **crend**() const throw()

Returns a reverse iterator to the element following the last element of the
reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/crend)

### size

Specifiers | Signature
-|-
public | size_type **size**() const throw()

Returns the number of elements in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/size)

### at

Specifiers | Signature
-|-
public | const_reference **at**(size_type n) const
public | reference **at**(size_type n)

Returns a reference to the element at specified location **n**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/at)

### back

Specifiers | Signature
-|-
public | reference **back**()
public | const_reference **back**() const

Returns reference to the last element in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/back)

### resize

Specifiers | Signature
-|-
public | void **resize**(size_type n)
public | void **resize**(size_type n, const value_type& val)

Resizes the container to contain **n** elements.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/resize)

### shrink_to_fit

Specifiers | Signature
-|-
public | void **shrink_to_fit**()

Requests the removal of unused capacity.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/shrink_to_fit)

### assign

Specifiers | Signature
-|-
public | template <class InputIterator> void **assign**(InputIterator first, InputIterator last)
public | void **assign**(size_type n, const value_type& val)
public | void **assign**(const boost::initializer_list<value_type>& il)

Replaces the contents of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/assign)

### push_back

Specifiers | Signature
-|-
public | void **push_back**(const value_type& val)
public | void **push_back**(value_type&& val)

Appends the given element value to the end of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/push_back)

### push_front

Specifiers | Signature
-|-
public | void **push_front**(const value_type& val)
public | void **push_front**(value_type&& val)

Prepends the given element value to the beginning of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/push_front)

### pop_back

Specifiers | Signature
-|-
public | void **pop_back**()

Removes the last element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/pop_back)

### pop_front

Specifiers | Signature
-|-
public | void **pop_front**()

Removes the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/pop_front)

### insert

Specifiers | Signature
-|-
public | iterator **insert**(const_iterator position, const value_type& val)
public | iterator **insert**(const_iterator position, size_type n, const value_type& val)
public | template <class InputIterator> iterator **insert**(const_iterator position, InputIterator first, InputIterator last)
public | iterator **insert**(const_iterator position, value_type&& val)
public | iterator **insert**(const_iterator position, boost::initializer_list<value_type> il)

Inserts elements at the specified location in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/insert)

### erase

Specifiers | Signature
-|-
public | iterator **erase**(const_iterator position)
public | iterator **erase**(const_iterator first, const_iterator last)

Removes specified elements from the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/erase)

### swap

Specifiers | Signature
-|-
public | template<class t, class s> void **swap**(basic_observable_deque<t, s>& x)

Exchanges the contents of the container with those of **x**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/swap)

### clear

Specifiers | Signature
-|-
public | void **clear**() throw()

Removes all elements from the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/clear)

### emplace

Specifiers | Signature
-|-
public | template <class... Args> iterator **emplace**(const_iterator position, Args&&... args)

Inserts a new element into the container directly before **position**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/emplace)

### emplace_back

Specifiers | Signature
-|-
public | template <class... Args> void **emplace_back**(Args&&... args)

Appends a new element to the end of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/emplace_back)

### emplace_front

Specifiers | Signature
-|-
public | template <class... Args> void **emplace_front**(Args&&... args)

Inserts a new element to the beginning of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/emplace_front)

### get_allocator

Specifiers | Signature
-|-
public | allocator_type **get_allocator**() const throw()

Returns the allocator associated with the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/get_allocator)

## Inherited functions

### begin

Specifiers | Signature
-|-
public | iterator **begin**() throw()
public | const_iterator **begin**() const throw()

Returns an iterator to the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/begin)

### end

Specifiers | Signature
-|-
public | iterator **end**() throw()
public | const_iterator **end**() const throw()

Returns an iterator to the element following the last element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/end)

### cbegin

Specifiers | Signature
-|-
public | const_iterator **cbegin**() const throw()

Returns an iterator to the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/cbegin)

### cend

Specifiers | Signature
-|-
public | const_iterator **cend**() const throw()

Returns an iterator to the element following the last element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/cend)

### max_size

Specifiers | Signature
-|-
public | size_type **max_size**() const throw()

Returns the maximum number of elements the container is able to hold.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/max_size)

### empty

Specifiers | Signature
-|-
public | bool **empty**() const throw()

Checks if the container has no elements, i.e. whether **begin() == end()**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/empty)

### front

Specifiers | Signature
-|-
public | reference front()
public | const_reference **front**() const

Returns a reference to the first element in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/deque/front)

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

# class template basic_property specializations

## class template observable_deque

The **observable_deque** is a generalization class for observable double-ended queues
with any value type and size using **std\::string**.

It is declared as:

```c++
template<class T, size_t N> class observable_deque : public basic_observable_deque<T, std\::string>
{
public:
    static ptr create();
    static ptr create(size_type n);
    static ptr create(size_type n, const value_type& val);
    template <class InputIterator> static ptr create(InputIterator first, InputIterator last);
    static ptr create(const this_type& x);
    static ptr create(this_type&& x);
    static ptr create(const boost::initializer_list<value_type>& il);
};
```

## class template wobservable_deque

The **wobservable_deque** is a generalization class for observable double-ended queues
with any value type and size using **std\::wstring**.

It is declared as:

```c++
template<class T, size_t N> class wobservable_deque : public basic_observable_deque<T, std\::wstring>
{
public:
    static ptr create();
    static ptr create(size_type n);
    static ptr create(size_type n, const value_type& val);
    template <class InputIterator> static ptr create(InputIterator first, InputIterator last);
    static ptr create(const this_type& x);
    static ptr create(this_type&& x);
    static ptr create(const boost::initializer_list<value_type>& il);
};
```
