---
layout: std_lib_signals
---

```c++
namespace go::signals
```

# class slot_key

```c++
<go/signals/slot_key.hpp>
```

**slot_key class**

The **slot_key** is a class used to identify connected signals.

It is declared as:

```c++
class slot_key
{
public:
    virtual ~slot_key();
    slot_key();
    slot_key(const slot_key& other)
    this_type& operator=(const this_type& other);
    bool operator==(const this_type& other) const;
    bool operator!=(const this_type& other) const;
    bool operator<(const this_type& other) const;
    bool operator>(const this_type& other) const;
    bool operator<=(const this_type& other) const;
    bool operator>=(const this_type& other) const;
    this_type& operator++();
    this_type operator++(int);
    void reset();
    static bool is_null_key(const this_type& key);
};
```

## Member types

Member type | Definition
-|-
this_type | slot_key

## Member functions

### (destructor)

*public virtual member function*

Destroys the **slot_key** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*default constructor (1)* | **slot_key**()
*copy constructor (2)* | **slot_key**(const **slot_key**& other)

1. Constructs a **slot_key** object.
2. Constructs a **slot_key** object as a copy of *other*.

### this_type& operator=(const this_type& other)

*public member function*

The copy assignment operator *a* **=** *b* replaces the contents of the object 
*a* with a copy of the contents of *b* (*b* is not modified). 

### bool operator==(const this_type& other) const

*public member function*

The two-way comparison operator *lhs* **==** *rhs*.
Returns true if *lhs* is equal to *rhs*, false otherwise.

### bool operator!=(const this_type& other) const

*public member function*

The two-way comparison operator *lhs* **!=** *rhs*.
Returns true if *lhs* is not equal to *rhs*, false otherwise.

### bool operator<(const this_type& other) const

*public member function*

The two-way comparison operator *lhs* **<** *rhs*.
Returns true if *lhs* is less than *rhs*, false otherwise.

### bool operator>(const this_type& other) const

*public member function*

The two-way comparison operator *lhs* **>** *rhs*.
Returns true if *lhs* is greater than *rhs*, false otherwise.

### bool operator<=(const this_type& other) const

*public member function*

The two-way comparison operator *lhs* **<=** *rhs*.
Returns true if *lhs* is less than or equal to *rhs*, false otherwise.

### bool operator>=(const this_type& other) const

*public member function*

The two-way comparison operator *lhs* **>=** *rhs*.
Returns true if *lhs* is greater than or equal to *rhs*, false otherwise.

### operator++

Constructor | Signature
-|-
*pre-increment (1)* | **this_type**& operator++()
*post-increment (2)* | **this_type** operator++(int)

1. Pre-increment.
2. Post-increment.

### void reset()

*public member function*

Resets the **slot_key** to the null value.

### static bool is_null_key(const this_type& key)

*public static member function*

Returns true if *key* is equal to the null value, false otherwise.
