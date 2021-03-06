---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class basic_observable_vector

```c++
<go_boost/mvvm.hpp>
```

**basic_observable_vector class**

The **basic_observable_vector** is a container that encapsulates dynamic contiguous
arrays. It wraps the [**std\::vector**](https://en.cppreference.com/w/cpp/container/vector)
and adds notifications when items get added, removed, or when the whole array is
reset or swapped.

It is declared as:

```c++
template<class T, class S> class basic_observable_vector
    : public basic_observable_sequence_container<S, std::vector<T>>
{
public:
    virtual ~basic_observable_vector();

protected:
    basic_observable_vector();
    explicit basic_observable_vector(size_type n);
    basic_observable_vector(size_type n, const value_type& val);
    template <class InputIterator> basic_observable_vector(InputIterator first, InputIterator last);
    explicit basic_observable_vector(const this_type& x);
    explicit basic_observable_vector(this_type&& x);
    explicit basic_observable_vector(const boost::initializer_list<value_type>& il);

public:
    static ptr create();
    static ptr create(size_type n);
    static ptr create(size_type n, const value_type& val);
    template <class InputIterator> static ptr create(InputIterator first, InputIterator last);
    static ptr create(const this_type& x);
    static ptr create(this_type&& x);
    static ptr create(const boost::initializer_list<value_type>& il);

public:
    this_type& operator=(const this_type& x) noexcept;
    this_type& operator=(this_type&& x) noexcept;
    this_type& operator=(const boost::initializer_list<value_type>& il) noexcept;
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
    pointer data() throw();
    const_pointer data() const throw();
    void resize(size_type n);
    void resize(size_type n, const value_type& val);
    size_type capacity() const throw();
    void reserve(size_type n);
    void shrink_to_fit();
    template <class InputIterator> void assign(InputIterator first, InputIterator last);
    void assign(size_type n, const value_type& val);
    void assign(const boost::initializer_list<value_type>& il);
    void push_back(const value_type& val);
    void push_back(value_type&& val);
    void pop_back();
    iterator insert(const_iterator position, const value_type& val);
    iterator insert(const_iterator position, size_type n, const value_type& val);
    template <class InputIterator> iterator insert(const_iterator position, InputIterator first, InputIterator last);
    iterator insert(const_iterator position, value_type&& val);
    iterator insert(const_iterator position, boost::initializer_list<value_type> il);
    iterator erase(const_iterator position);
    iterator erase(const_iterator first, const_iterator last);
    template<class t, class s> void swap(basic_observable_vector<t, s>& x);
    void clear() throw();
    template <class... Args> iterator emplace(const_iterator position, Args&&... args);
    template <class... Args> void emplace_back(Args&&... args);
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
container_type | std\::vector<T>
this_type | basic_observable_vector<T, S>
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

Constructs a new **basic_observable_vector<value_type, string_type, lockable_type>** object and return it as a
**basic_observable_vector<value_type, string_type, lockable_type>\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_observable_vector** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_observable_vector**()
*constructor (2)* | protected explicit | **basic_observable_vector**(size_type n)
*constructor (3)* | protected | **basic_observable_vector**(size_type n, const value_type& val)
*constructor (4)* | protected | template <class InputIterator> **basic_observable_vector**(InputIterator first, InputIterator last)
*copy constructor (5)* | protected explicit | **basic_observable_vector**(const this_type& x)
*move constructor (6)* | protected explicit | **basic_observable_vector**(this_type&& x)
*constructor (7)* | protected explicit | **basic_observable_vector**(const boost::initializer_list<value_type>& il)

1. Constructs a **basic_observable_vector** object with an empty container.
2. Constructs a **basic_observable_vector** object with **n** default-inserted instances of **T**.
3. Constructs a **basic_observable_vector** object with **n** copies of elements with value **val**.
4. Constructs a **basic_observable_vector** object with the contents of the range **[first, last)**.
5. Constructs a **basic_observable_vector** object with the copy of the contents of **x**.
6. Constructs a **basic_observable_vector** object with the contents of **x** using move semantics.
7. Constructs a **basic_observable_vector** object with the contents of the initializer list **il**.

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | public | this_type& **operator=**(const this_type& x) noexcept
*assign move (2)* | public | this_type& **operator=**(this_type&& x) noexcept
*assign replace (2)* | public | this_type& **operator=**(const boost\::initializer_list<value_type>& il) noexcept

1. Copy assignment operator. Replaces the contents with a copy of the contents of **x**.
2. Move assignment operator. Replaces the contents with those of **x** using move semantics.
3. Replaces the contents with those identified by initializer list **il**.

### Subscript operator

Specifiers | Signature
-|-
public | const_reference **operator[]**(size_type n) const
public | reference **operator[]**(size_type n)

Returns a reference to the element at specified location **n**.

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

### size

Specifiers | Signature
-|-
public | size_type **size**() const throw()

Returns the number of elements in the container.

### at

Specifiers | Signature
-|-
public | const_reference *at**(size_type n) const
public | reference **at**(size_type n)

Returns a reference to the element at specified location **n**.

### back

Specifiers | Signature
-|-
public | reference **back**()
public | const_reference **back**() const

Returns reference to the last element in the container.

### data

Specifiers | Signature
-|-
public | pointer **data**() throw()
public | const_pointer **data**() const throw()

Returns pointer to the underlying array serving as element storage.

### resize

Specifiers | Signature
-|-
public | void **resize**(size_type n)
public | void **resize**(size_type n, const value_type& val)

Resizes the container to contain **n** elements.

If the current size is greater than **n**, the container is reduced to its first
**n** elements.

If the current size is less than **n**,

1. additional default-inserted elements are appended
2. additional copies of **val** are appended

### capacity

Specifiers | Signature
-|-
public | size_type **capacity**() const throw()

Returns the number of elements that the container has currently allocated space for.

### reserve

Specifiers | Signature
-|-
public | void **reserve**(size_type n)

Increase the capacity of the vector to a value that's greater or equal to **n**.

### shrink_to_fit

Specifiers | Signature
-|-
public | void **shrink_to_fit**()

Requests the removal of unused capacity.

It is a non-binding request to reduce **capacity**() to **size**().

### assign

Specifiers | Signature
-|-
public | template <class InputIterator> void **assign**(InputIterator first, InputIterator last)
public | void **assign**(size_type n, const value_type& val)
public | void **assign**(const boost::initializer_list<value_type>& il)

Replaces the contents of the container.

### push_back

Specifiers | Signature
-|-
public | void **push_back**(const value_type& val)
public | void **push_back**(value_type&& val)

Appends the given element value to the end of the container.

### pop_back

Specifiers | Signature
-|-
public | void **pop_back**()

Removes the last element of the container.

### insert

Specifiers | Signature
-|-
public | iterator **insert**(const_iterator position, const value_type& val)
public | iterator **insert**(const_iterator position, size_type n, const value_type& val)
public | template <class InputIterator> iterator **insert**(const_iterator position, InputIterator first, InputIterator last)
public | iterator **insert**(const_iterator position, value_type&& val)
public | iterator **insert**(const_iterator position, boost::initializer_list<value_type> il)

Inserts elements at the specified location in the container.

### erase

Specifiers | Signature
-|-
public | iterator **erase**(const_iterator position)
public | iterator **erase**(const_iterator first, const_iterator last)

Removes specified elements from the container.

### swap

Specifiers | Signature
-|-
public | template<class t, class s> void **swap**(basic_observable_vector<t, s>& x)

Exchanges the contents of the container with those of **x**.

### clear

Specifiers | Signature
-|-
public | void **clear**() throw()

Removes all elements from the container.

### emplace

Specifiers | Signature
-|-
public | template <class... Args> iterator **emplace**(const_iterator position, Args&&... args)

Inserts a new element into the container directly before **position**.

### emplace_back

Specifiers | Signature
-|-
public | template <class... Args> void **emplace_back**(Args&&... args)

Appends a new element to the end of the container.

### get_allocator

Specifiers | Signature
-|-
public | allocator_type **get_allocator**() const throw()

Returns the allocator associated with the container.

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

# class template basic_property specializations

## class template observable_vector

The **observable_vector** is a generalization class for observable vectors with any value
type and size using **std\::string**.

It is declared as:

```c++
template<class T> class observable_vector : public basic_observable_vector<T, std\::string>
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

## class template wobservable_vector

The **wobservable_vector** is a generalization class for observable vectors with any value
type and size using **std\::wstring**.

It is declared as:

```c++
template<class T> class wobservable_vector : public basic_observable_vector<T, std\::wstring>
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
