---
layout: boost_lib_exception
---

```c++
namespace go_boost::exception
```

# class exception

```c++
<go_boost/exception/exception.hpp>
```

**exception class**

The **exception** is a class used to identify connected exception.

It is declared as:

```c++
class exception
{
public:
    virtual ~exception();
    exception();
...
};
```

## Member types

Member type | Definition
-|-
this_type | exception

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **exception** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | public | **exception**()
*copy constructor (2)* | public | **exception**(const **exception**& other)

1. Constructs a **exception** object.
2. Constructs a **exception** object as a copy of *other*.

### Assignment operator

Specifiers | Signature
-|-
public | this_type& operator=(const this_type& other)

The copy assignment operator *a* **=** *b* replaces the contents of the object 
*a* with a copy of the contents of *b* (*b* is not modified). 

### Equality operator

Specifiers | Signature
-|-
public | bool operator==(const this_type& other) const

The two-way comparison operator *lhs* **==** *rhs*.
Returns true if *lhs* is equal to *rhs*, false otherwise.

### Inequality operator

Specifiers | Signature
-|-
public | bool operator!=(const this_type& other) const

The two-way comparison operator *lhs* **!=** *rhs*.
Returns true if *lhs* is not equal to *rhs*, false otherwise.

### Less than operator

Specifiers | Signature
-|-
public | bool operator<(const this_type& other) const

The two-way comparison operator *lhs* **<** *rhs*.
Returns true if *lhs* is less than *rhs*, false otherwise.

### Greater than operator

Specifiers | Signature
-|-
public | bool operator>(const this_type& other) const

The two-way comparison operator *lhs* **>** *rhs*.
Returns true if *lhs* is greater than *rhs*, false otherwise.

### Less than or equal to operator

Specifiers | Signature
-|-
public | bool operator<=(const this_type& other) const

The two-way comparison operator *lhs* **<=** *rhs*.
Returns true if *lhs* is less than or equal to *rhs*, false otherwise.

### Greater than or equal to operator

Specifiers | Signature
-|-
public | bool operator>=(const this_type& other) const

The two-way comparison operator *lhs* **>=** *rhs*.
Returns true if *lhs* is greater than or equal to *rhs*, false otherwise.

### operator++

Specifiers | Signature
-|-
*pre-increment (1)* | **this_type**& operator++()
*post-increment (2)* | **this_type** operator++(int)

1. Pre-increment.
2. Post-increment.

### reset

Specifiers | Signature
-|-
public | void **reset**()

Resets the **exception** to the null value.

### is_null_key

Specifiers | Signature
-|-
public static | bool **is_null_key**(const this_type& key)

Returns true if *key* is equal to the null value, false otherwise.
