---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# class template monitor

```c++
<go/utility/monitor.hpp>
```

The **monitor** is a class template that implement the [monitor pattern](https://en.wikipedia.org/wiki/Monitor_%28synchronization%29)
for synchronizing object access from multiple threads.

It is declared as:

```c++
template<class T, class L = go::utility::recursive_spin_lock>
class monitor
{
public:
    class monitor_object;

public:
    virtual ~monitor() = default;
    monitor() = default;
    monitor(const monitor&) = delete;
    monitor(monitor&& other) = default;
    template<typename ...Args>
    monitor(Args&&... args);

public:
    this_type& operator=(const this_type&) = delete;
    this_type& operator=(this_type&&) = default;
    this_type& operator=(const value_type& value);
    this_type& operator=(value_type&& value);
    monitor_object operator->();
    monitor_object operator*();
    monitor_object lock();
    reference unsafe_access();
    const_reference unsafe_access() const;
};
```

## Template parameters

Parameter | Description
-|-
T | The guarded value type
L | The monitor lockable class

## Member types

Member type | Definition
-|-
this_type | monitor\<T>
value_type | T
lockable_type | L
this_type | monitor<T, L>
pointer | T*
const_pointer | const T*
reference | T&
const_reference | const T&

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **monitor** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | public | **monitor**()
*move constructor (2)* | public | **monitor**(monitor&& other)
*constructor (3)* | public | template<typename ...Args> **monitor**(Args&&... args)

1. Constructs a **monitor**.
2. Constructs a **monitor** object with the contents of **other** using move semantics.
3. Constructs a **monitor**.

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign move (1)* | public | this_type& **operator=**(this_type&& other)
*assign move (2)* | public | this_type& **operator=**(const value_type& value)
*assign replace (2)* | public | this_type& **operator=**(value_type&& value)

1. Move assignment operator. Replaces the contents with those of **other** using move semantics.
2. Copy value assignment operator. Replaces the value with **value**.
3. Move value assignment operator. Replaces the value with **value** using move semantics.

### Member of pointer operator

Operator | Specifiers | Signature
-|-
*Member of pointer* | public | monitor_object **operator->**()

Member of pointer operator. Returns a **monitor_object** that
have locked the monitored object, i.e. the object associated
with the **monitor** object.

### Indirection operator

Operator | Specifiers | Signature
-|-
*Indirection* | public | monitor_object **operator\***()

Indirection operator. Returns a **monitor_object** that have
locked the monitored object, i.e. the object associated with
the **monitor** object.

### lock

Specifiers | Signature
-|-
public | monitor_object **lock**()

Returns a **monitor_object** that have locked the monitored
object, i.e. the object associated with the **monitor** object.

### unsafe_access

Specifiers | Signature
-|-
public | reference **unsafe_access**()
public | const_reference **unsafe_access**() const

Returns a reference* to the object associated with the
**monitor** object.

##  Nested classes

### monitor_object

Nnn.

```c++
class monitor_object
{
public:
    ~monitor_object() = default;
    monitor_object() = delete;
    monitor_object(const monitor_object&) = delete;
    monitor_object(monitor_object&&) = default;

public:
    monitor_object& operator=(const monitor_object&) = delete;
    monitor_object& operator=(monitor_object&&) = default;
    pointer operator->();
    const_pointer operator->() const;
    reference operator*();
    const_reference operator*() const;
    reference get();
    const_reference get() const;
};
```
