---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class basic_observable_array

```c++
<go_boost/mvvm.hpp>
```

**basic_observable_array class**

The **basic_observable_array** is a container that encapsulates static (or fixed
size) contiguous arrays. It wraps the [**boost\::container\::static_vector**](https://www.boost.org/doc/libs/1_69_0/doc/html/boost/container/static_vector.html)
and adds notifications when items get added, removed, or when the whole array is
reset or swapped.

It is declared as:

```c++
template<class T, class S, size_t N>
class basic_observable_array
    : public basic_observable_sequence_container<S, boost::container::static_vector<T, N>>
{
public:
    virtual ~basic_observable_array();

protected:
    basic_observable_array();

public:
    static ptr create();

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
};
```

## Template parameters

Parameter | Description
-|-
T | The element type
S | The string class
N | The number of elements in the array

## Member types

Member type | Definition
-|-
string_type | S
container_type | boost\::container\::static_vector<T, N>
this_type | basic_observable_array<T, S, N>
ptr | boost\::shared_ptr\<this_type>
wptr | boost\::weak_ptr\<this_type>
value_type | container_type\::value_type
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

Constructs a new **basic_observable_array<value_type, string_type, N>** object and return it as a
**basic_observable_array<value_type, string_type, N>\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_observable_array** object.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array)

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_observable_array**()

1. Constructs a **basic_observable_array** object.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array)

### Subscript operator

Specifiers | Signature
-|-
public | const_reference **operator[]**(size_type n) const
public | reference **operator[]**(size_type n)

Returns a reference to the element at specified location **n**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/operator_at)

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

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/rbegin)

### rend

Specifiers | Signature
-|-
public | reverse_iterator **rend**() throw()
public | const_reverse_iterator **rend**() const throw()

Returns a reverse iterator to the element following the last element of the
reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/rend)

### crbegin

Specifiers | Signature
-|-
public | const_reverse_iterator **crbegin**() const throw()

Returns a reverse iterator to the first element of the reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/crbegin)

### crend

Specifiers | Signature
-|-
public | const_reverse_iterator **crend**() const throw()

Returns a reverse iterator to the element following the last element of the
reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/crend)

### size

Specifiers | Signature
-|-
public | size_type **size**() const throw()

Returns the number of elements in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/size)

### at

Specifiers | Signature
-|-
public | const_reference *at**(size_type n) const
public | reference **at**(size_type n)

Returns a reference to the element at specified location *n*.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/at)

### back

Specifiers | Signature
-|-
public | reference **back**()
public | const_reference **back**() const

Returns reference to the last element in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/back)

### data

Specifiers | Signature
-|-
public | pointer **data**() throw()
public | const_pointer **data**() const throw()

Returns pointer to the underlying array serving as element storage.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/data)

## Inherited functions

### begin

Specifiers | Signature
-|-
public | iterator **begin**() throw()
public | const_iterator **begin**() const throw()

Returns an iterator to the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/begin)

### end

Specifiers | Signature
-|-
public | iterator **end**() throw()
public | const_iterator **end**() const throw()

Returns an iterator to the element following the last element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/end)

### cbegin

Specifiers | Signature
-|-
public | const_iterator **cbegin**() const throw()

Returns an iterator to the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/cbegin)

### cend

Specifiers | Signature
-|-
public | const_iterator **cend**() const throw()

Returns an iterator to the element following the last element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/cend)

### max_size

Specifiers | Signature
-|-
public | size_type **max_size**() const throw()

Returns the maximum number of elements the container is able to hold.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/max_size)

### empty

Specifiers | Signature
-|-
public | bool **empty**() const throw()

Checks if the container has no elements, i.e. whether **begin() == end()**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/empty)

### front

Specifiers | Signature
-|-
public | reference front()
public | const_reference **front**() const

Returns a reference to the first element in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/front)

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

## class template observable_array

The **observable_array** is a generalization class for observable arrays with any value
type and size using **std\::string**.

It is declared as:

```c++
template<class T, size_t N> class observable_array : public basic_observable_array<T, std\::string, N>
{
public:
    static ptr create();
};
```

## class template wobservable_array

The **wobservable_array** is a generalization class for observable arrays with any value
type and size using **std\::wstring**.

It is declared as:

```c++
template<class T, size_t N> class wobservable_array : public basic_observable_array<T, std\::wstring, N>
{
public:
    static ptr create();
};
```
