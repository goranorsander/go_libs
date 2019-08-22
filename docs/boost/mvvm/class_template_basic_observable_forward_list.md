---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class basic_observable_forward_list

```c++
<go_boost/mvvm.hpp>
```

**basic_observable_forward_list class**

The **basic_observable_forward_list** is a container that encapsulates singly-linked lists.
It wraps the [**boost\::container\::slist**](https://www.boost.org/doc/libs/1_71_0/doc/html/boost/container/slist.html)
and adds notifications when items get added, removed, or when the whole double-ended
list is reset or swapped.

It is declared as:

```c++
template<class T, class S> class basic_observable_forward_list
    : public basic_observable_sequence_container<S, boost::container::slist<T>>
{
public:
    virtual ~basic_observable_forward_list();

protected:
    basic_observable_forward_list();
    explicit basic_observable_forward_list(size_type n);
    basic_observable_forward_list(size_type n, const value_type& val);
    template <class InputIterator> basic_observable_forward_list(InputIterator first, InputIterator last);
    explicit basic_observable_forward_list(const this_type& x);
    explicit basic_observable_forward_list(this_type&& x);
    explicit basic_observable_forward_list(const boost::initializer_list<value_type>& il);

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

protected:
    virtual container_type& container();
    virtual const container_type& container() const;

public:
    iterator before_begin() throw();
    const_iterator before_begin() const throw();
    const_iterator cbefore_begin() const throw();
    size_type size() const throw();
    void resize(size_type n);
    void resize(size_type n, const value_type& val);
    void shrink_to_fit();
    template <class InputIterator> void assign(InputIterator first, InputIterator last);
    void assign(size_type n, const value_type& val);
    void assign(const boost::initializer_list<value_type>& il);
    void push_front(const value_type& val);
    void push_front(value_type&& val);
    void pop_front();
    template<class t, class s> void swap(basic_observable_forward_list<t, s>& x);
    void clear() throw();
    template <class... Args> void emplace_front(Args&&... args);
    template <class... Args> iterator emplace_after(const_iterator position, Args&&... args);
    iterator insert_after(const_iterator position, const value_type& val);
    iterator insert_after(const_iterator position, value_type&& val);
    iterator insert_after(const_iterator position, size_type n, const value_type& val);
    template <class InputIterator> iterator insert_after(const_iterator position, InputIterator first, InputIterator last);
    iterator insert_after(const_iterator position, boost::initializer_list<value_type> il);
    iterator erase_after(const_iterator position);
    iterator erase_after(const_iterator position, const_iterator last);
    allocator_type get_allocator() const throw();
    template<class t, class s> void splice_after(const_iterator position, basic_observable_forward_list<t, s>& x);
    template<class t, class s> void splice_after(const_iterator position, basic_observable_forward_list<t, s>&& x);
    template<class t, class s> void splice_after(const_iterator position, basic_observable_forward_list<t, s>& x, const_iterator i);
    template<class t, class s> void splice_after(const_iterator position, basic_observable_forward_list<t, s>&& x, const_iterator i);
    template<class t, class s> void splice_after(const_iterator position, basic_observable_forward_list<t, s>& x, const_iterator first, const_iterator last);
    template<class t, class s> void splice_after(const_iterator position, basic_observable_forward_list<t, s>&& x, const_iterator first, const_iterator last);
    void remove(const value_type& val);
    template <class Predicate> void remove_if(Predicate pred);
    void unique();
    template <class BinaryPredicate> void unique(BinaryPredicate binary_pred);
    template<class t, class s> void merge(basic_observable_forward_list<t, s>& x);
    template<class t, class s> void merge(basic_observable_forward_list<t, s>&& x);
    template<class t, class s, class Compare> void merge(basic_observable_forward_list<t, s>& x, Compare comp);
    template<class t, class s, class Compare> void merge(basic_observable_forward_list<t, s>&& x, Compare comp);
    void sort();
    template <class Compare> void sort(Compare comp);
    void reverse();
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
container_type | boost\::container\::slist<T>
this_type | basic_observable_forward_list<T, S>
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

Constructs a new **basic_observable_forward_list<value_type, string_type, lockable_type>** object and return it as a
**basic_observable_forward_list<value_type, string_type, lockable_type>\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_observable_forward_list** object.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/~forward_list)

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_observable_forward_list**()
*constructor (2)* | protected explicit | **basic_observable_forward_list**(size_type n)
*constructor (3)* | protected | **basic_observable_forward_list**(size_type n, const value_type& val)
*constructor (4)* | protected | template <class InputIterator> **basic_observable_forward_list**(InputIterator first, InputIterator last)
*copy constructor (5)* | protected explicit | **basic_observable_forward_list**(const this_type& x)
*move constructor (6)* | protected explicit | **basic_observable_forward_list**(this_type&& x)
*constructor (7)* | protected explicit | **basic_observable_forward_list**(const boost::initializer_list<value_type>& il)

1. Constructs a **basic_observable_forward_list** object with an empty container.
2. Constructs a **basic_observable_forward_list** object with **n** default-inserted instances of **T**.
3. Constructs a **basic_observable_forward_list** object with **n** copies of elements with value **val**.
4. Constructs a **basic_observable_forward_list** object with the contents of the range **[first, last)**.
5. Constructs a **basic_observable_forward_list** object with the copy of the contents of **x**.
6. Constructs a **basic_observable_forward_list** object with the contents of **x** using move semantics.
7. Constructs a **basic_observable_forward_list** object with the contents of the initializer list **il**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/forward_list)

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | public | this_type& **operator=**(const this_type& x)
*assign move (2)* | public | this_type& **operator=**(this_type&& x)
*assign replace (2)* | public | this_type& **operator=**(const boost\::initializer_list<value_type>& il)

1. Copy assignment operator. Replaces the contents with a copy of the contents of **x**.
2. Move assignment operator. Replaces the contents with those of **x** using move semantics.
3. Replaces the contents with those identified by initializer list **il**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/operator%3D)

### container

Specifiers | Signature
-|-
protected virtual | container_type& **container**()
protected virtual | const container_type& **container**() const

Return a referense to the underlying container storage.

### before_begin

Specifiers | Signature
-|-
public | iterator **before_begin**() throw()
public | const_iterator **before_begin**() const throw()

Returns an iterator to the element before the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/before_begin)

### cbefore_begin

Specifiers | Signature
-|-
public | const_iterator **cbefore_begin**() const throw()

Returns an iterator to the element before the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/cbefore_begin)

### size

Specifiers | Signature
-|-
public | size_type **size**() const throw()

Returns the number of elements in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/size)

### resize

Specifiers | Signature
-|-
public | void **resize**(size_type n)
public | void **resize**(size_type n, const value_type& val)

Resizes the container to contain **n** elements.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/resize)

### shrink_to_fit

Specifiers | Signature
-|-
public | void **shrink_to_fit**()

Requests the removal of unused capacity.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/shrink_to_fit)

### assign

Specifiers | Signature
-|-
public | template <class InputIterator> void **assign**(InputIterator first, InputIterator last)
public | void **assign**(size_type n, const value_type& val)
public | void **assign**(const boost::initializer_list<value_type>& il)

Replaces the contents of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/assign)

### push_front

Specifiers | Signature
-|-
public | void **push_front**(const value_type& val)
public | void **push_front**(value_type&& val)

Prepends the given element value to the beginning of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/push_front)

### pop_front

Specifiers | Signature
-|-
public | void **pop_front**()

Removes the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/pop_front)

### swap

Specifiers | Signature
-|-
public | template<class t, class s> void **swap**(basic_observable_forward_list<t, s>& x)

Exchanges the contents of the container with those of **x**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/swap)

### clear

Specifiers | Signature
-|-
public | void **clear**() throw()

Removes all elements from the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/clear)

### emplace_front

Specifiers | Signature
-|-
public | template <class... Args> void **emplace_front**(Args&&... args)

Inserts a new element to the beginning of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/emplace_front)

### emplace_after

Specifiers | Signature
-|-
public | template <class... Args> iterator **emplace_after**(const_iterator position, Args&&... args)

Inserts a new element into a position after the specified position in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/emplace_after)

### insert_after

Specifiers | Signature
-|-
public | iterator **insert_after**(const_iterator position, const value_type& val)
public | iterator **insert_after**(const_iterator position, value_type&& val)
public | iterator **insert_after**(const_iterator position, size_type n, const value_type& val)
public | template <class InputIterator> iterator **insert_after**(const_iterator position, InputIterator first, InputIterator last)
public | iterator **insert_after**(const_iterator position, boost::initializer_list<value_type> il)

Inserts elements after the specified position in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/insert_after)

### erase_after

Specifiers | Signature
-|-
public | iterator erase_after(const_iterator position)
public | iterator erase_after(const_iterator position, const_iterator last)

Removes specified elements from the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/erase_after)

### get_allocator

Specifiers | Signature
-|-
public | allocator_type **get_allocator**() const throw()

Returns the allocator associated with the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/get_allocator)

### splice_after

Specifiers | Signature
-|-
public | template<class t, class s> void **splice_after**(const_iterator position, basic_observable_forward_list<t, s>& x)
public | template<class t, class s> void **splice_after**(const_iterator position, basic_observable_forward_list<t, s>&& x)
public | template<class t, class s> void **splice_after**(const_iterator position, basic_observable_forward_list<t, s>& x, const_iterator i)
public | template<class t, class s> void **splice_after**(const_iterator position, basic_observable_forward_list<t, s>&& x, const_iterator i)
public | template<class t, class s> void **splice_after**(const_iterator position, basic_observable_forward_list<t, s>& x, const_iterator first, const_iterator last)
public | template<class t, class s> void **splice_after**(const_iterator position, basic_observable_forward_list<t, s>&& x, const_iterator first, const_iterator last)

Moves elements from another forward_list to **\*this**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/splice_after)

### remove

Specifiers | Signature
-|-
public | void **remove**(const value_type& val)

Removes all elements that are equal to **val**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/remove)

### remove_if

Specifiers | Signature
-|-
public | template <class Predicate> void **remove_if**(Predicate pred)

Removes all elements for which predicate **pred** returns **true**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/remove_if)

### unique

Specifiers | Signature
-|-
public | void **unique**()
public | template <class BinaryPredicate> void **unique**(BinaryPredicate binary_pred)

Removes all consecutive duplicate elements from the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/unique)

### merge

Specifiers | Signature
-|-
public | template<class t, class s> void **merge**(basic_observable_forward_list<t, s>& x)
public | template<class t, class s> void **merge**(basic_observable_forward_list<t, s>&& x)
public | template<class t, class s, class Compare> void **merge**(basic_observable_forward_list<t, s>& x, Compare comp)
public | template<class t, class s, class Compare> void **merge**(basic_observable_forward_list<t, s>&& x, Compare comp)

Merges two sorted lists into one. The lists should be sorted into ascending order.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/merge)

### sort

Specifiers | Signature
-|-
public | void **sort**()
public | template <class Compare> void **sort**(Compare comp)

Sorts the elements in ascending order.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/sort)

### reverse

Specifiers | Signature
-|-
public | void reverse()

Reverses the order of the elements in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/reverse)

## Inherited functions

### begin

Specifiers | Signature
-|-
public | iterator **begin**() throw()
public | const_iterator **begin**() const throw()

Returns an iterator to the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/begin)

### end

Specifiers | Signature
-|-
public | iterator **end**() throw()
public | const_iterator **end**() const throw()

Returns an iterator to the element following the last element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/end)

### cbegin

Specifiers | Signature
-|-
public | const_iterator **cbegin**() const throw()

Returns an iterator to the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/cbegin)

### cend

Specifiers | Signature
-|-
public | const_iterator **cend**() const throw()

Returns an iterator to the element following the last element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/cend)

### max_size

Specifiers | Signature
-|-
public | size_type **max_size**() const throw()

Returns the maximum number of elements the container is able to hold.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/max_size)

### empty

Specifiers | Signature
-|-
public | bool **empty**() const throw()

Checks if the container has no elements, i.e. whether **begin() == end()**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/empty)

### front

Specifiers | Signature
-|-
public | reference front()
public | const_reference **front**() const

Returns a reference to the first element in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/forward_list/front)

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

## class template observable_forward_list

The **observable_forward_list** is a generalization class for observable singly-linked lists
with any value type and size using **std\::string**.

It is declared as:

```c++
template<class T, size_t N> class observable_forward_list : public basic_observable_forward_list<T, std\::string>
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

## class template wobservable_forward_list

The **wobservable_forward_list** is a generalization class for observable singly-linked lists
with any value type and size using **std\::wstring**.

It is declared as:

```c++
template<class T, size_t N> class wobservable_forward_list : public basic_observable_forward_list<T, std\::wstring>
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
