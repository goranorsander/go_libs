---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class basic_observable_array

```c++
<go/mvvm.hpp>
```

**basic_observable_array class**

The **basic_observable_array** is a container that encapsulates static (or fixed
size) contiguous arrays. It wraps the [**std\::array**](https://en.cppreference.com/w/cpp/container/array)
and adds notifications when items get added, removed, or when the whole array is
reset or swapped.

It is declared as:

```c++
template<class T, class S, size_t N>
class basic_observable_array
    : public basic_observable_sequence_container<S, std::array<T, N>>
{
public:
    virtual ~basic_observable_array() = default;

protected:
    basic_observable_array();

public:
    static ptr create();

    constexpr const_reference operator[](size_type n) const;
    reference operator[](size_type n);

protected:
    virtual container_type& container();
    virtual const container_type& container() const;

public:
    reverse_iterator rbegin() noexcept;
    constexpr const_reverse_iterator rbegin() const noexcept;
    reverse_iterator rend() noexcept;
    constexpr const_reverse_iterator rend() const noexcept;
    constexpr const_reverse_iterator crbegin() const noexcept;
    constexpr const_reverse_iterator crend() const noexcept;
    constexpr size_type size() const noexcept;
    constexpr const_reference at(size_type n) const;
    reference at(size_type n);
    reference back();
    constexpr const_reference back() const;
    pointer data() noexcept;
    constexpr const_pointer data() const noexcept;
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
container_type | std\::array<T, N>
this_type | basic_observable_array<T, S, N>
ptr | std\::shared_ptr\<this_type>
wptr | std\::weak_ptr\<this_type>
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
public constexpr | const_reference **operator[]**(size_type n) const
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
public | reverse_iterator **rbegin**() noexcept
public constexpr | const_reverse_iterator **rbegin**() const noexcept

Returns a reverse iterator to the first element of the reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/rbegin)

### rend

Specifiers | Signature
-|-
public | reverse_iterator **rend**() noexcept
public constexpr | const_reverse_iterator **rend**() const noexcept

Returns a reverse iterator to the element following the last element of the
reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/rend)

### crbegin

Specifiers | Signature
-|-
public constexpr | const_reverse_iterator **crbegin**() const noexcept

Returns a reverse iterator to the first element of the reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/crbegin)

### crend

Specifiers | Signature
-|-
public constexpr | const_reverse_iterator **crend**() const noexcept

Returns a reverse iterator to the element following the last element of the
reversed container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/crend)

### size

Specifiers | Signature
-|-
public constexpr | size_type **size**() const noexcept

Returns the number of elements in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/size)

### at

Specifiers | Signature
-|-
public constexpr | const_reference *at**(size_type n) const
public | reference **at**(size_type n)

Returns a reference to the element at specified location *n*.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/at)

### back

Specifiers | Signature
-|-
public | reference **back**()
public constexpr | const_reference **back**() const

Returns reference to the last element in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/back)

### data

Specifiers | Signature
-|-
public | pointer **data**() noexcept
public constexpr | const_pointer **data**() const noexcept

Returns pointer to the underlying array serving as element storage.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/data)

## Inherited functions

### begin

Specifiers | Signature
-|-
public | iterator **begin**() noexcept
public constexpr | const_iterator **begin**() const noexcept

Returns an iterator to the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/begin)

### end

Specifiers | Signature
-|-
public | iterator **end**() noexcept
public constexpr | const_iterator **end**() const noexcept

Returns an iterator to the element following the last element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/end)

### cbegin

Specifiers | Signature
-|-
public constexpr | const_iterator **cbegin**() const noexcept

Returns an iterator to the first element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/cbegin)

### cend

Specifiers | Signature
-|-
public constexpr | const_iterator **cend**() const noexcept

Returns an iterator to the element following the last element of the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/cend)

### max_size

Specifiers | Signature
-|-
public constexpr | size_type **max_size**() const noexcept

Returns the maximum number of elements the container is able to hold.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/max_size)

### empty

Specifiers | Signature
-|-
public constexpr | bool **empty**() const noexcept

Checks if the container has no elements, i.e. whether **begin() == end()**.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/empty)

### front

Specifiers | Signature
-|-
public | reference front()
public constexpr | const_reference **front**() const

Returns a reference to the first element in the container.

[See **cppreference.com** for a detailed description.](https://en.cppreference.com/w/cpp/container/array/front)

### notify_assign

Specifiers | Signature
-|-
protected | void **notify_assign**(const std\::size_t& before, const std\::size_t& after)

Emit signal to notify that the container have been assigned new elements.

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
