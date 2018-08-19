---
layout: std_lib_property_nameless_read_only
---

```c++
namespace go::property::nameless::read_only
```

# class template reference_property

```c++
<go/property/nameless/read_only_reference_property.hpp>
```

**Generic read-only reference property class**

The **reference_property** is a generalization class for read-only properties with any value type and name string class.
It is implemented using the reference storage policy.

It is declared as:

```c++
template<class T, class S> class reference_property
    : public detail::property_base<T, policy::reference<T>, S>
{
public:
    virtual ~reference_property();
    explicit reference_property(const string_type& property_name);
    reference_property(const string_type& property_name, const value_type& other);
    this_type& operator=(const this_type& other);
    this_type& operator=(const value_type& other);
    bool empty() const;
    void clear();
    explicit operator bool() const;
    bool operator!() const;

    // The following operators and functions are inherited from detail::property_base<T, policy::reference<T>, S>
    operator value_type() const;
    value_type operator()() const;
    value_type operator*() const;
    value_type get() const;
    const string_type& name() const;
};
```

## Template parameters

Parameter | Description
-|-
T | The property value type
S | The property name string class

## Member types

Member type | Definition
-|-
value_type | T
string_type | S
this_type | reference_property<value_type, string_type>
policy_type | policy\::reference<value_type>

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **reference_property** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*assign name (1)* | public explicit | **reference_property**(const **string_type**& property_name)
*assign name and value (2)* | public | **reference_property**(const **string_type**& property_name, const **value_type**& other)

1. Constructs a **reference_property** object with the name *property_name*.
2. Constructs a **reference_property** object with the name *property_name* and value *other*.

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | public | **this_type**& operator=(const **this_type**& other)
*assign value (2)* | public | **this_type**& operator=(const **value_type**& other)

1. Copies an **reference_property** object.
2. Assign a value to the **reference_property** object.

### empty

Specifiers | Signature
-|-
public | bool **empty**() const

Test whether property is empty.

### clear

Specifiers | Signature
-|-
public | void **clear**()

Clear the property.

### operator bool

Specifiers | Signature
-|-
public explicit | operator **bool**() const

Test whether property is empty.

### operator!

Specifiers | Signature
-|-
public | bool operator**!**() const

Test whether property is empty.

## Inherited functions

### Cast operator

Specifiers | Signature
-|-
public | operator **value_type**() const

Conversion function (or cast operator) that return the value of the **reference_property** object.

### Get value operator

Specifiers | Signature
-|-
public | **value_type** operator()() const

Function call operator that return the value of the **reference_property** object.

### Indirection operator

Specifiers | Signature
-|-
public | **value_type** operator\*() const

Indirection operator that return the value of the **reference_property** object.

### get

Specifiers | Signature
-|-
public | **value_type get**() const

Function that return the value of the **reference_property** object.

### name

Specifiers | Signature
-|-
public | **const string_type**& **name**() const

Function that return the name of the **reference_property** object.
