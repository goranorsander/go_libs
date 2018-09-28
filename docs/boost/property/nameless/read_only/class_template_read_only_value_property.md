---
layout: boost_lib_property_nameless_read_only
---

```c++
namespace go_boost::property::nameless::read_only
```

# class template value_property

```c++
<go_boost/property/nameless/read_only_value_property.hpp>
```

**Generic read-only value property class**

The **value_property** is a generalization class for read-only properties with any value type and name string class.
It is implemented using the value storage policy.

It is declared as:

```c++
template<class T, class S> class value_property
    : public detail::property_base<T, policy::value<T>, S>
{
public:
    virtual ~value_property();
    explicit value_property(const string_type& property_name);
    value_property(const string_type& property_name, const value_type& other);
    this_type& operator=(const this_type& other);
    this_type& operator=(const value_type& other);

    // The following operators and functions are inherited from detail::property_base<T, policy::value<T>, S>
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
this_type | value_property<value_type, string_type>
policy_type | policy\::value<value_type>

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **value_property** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*assign name (1)* | public explicit | **value_property**(const **string_type**& property_name)
*assign name and value (2)* | public | **value_property**(const **string_type**& property_name, const **value_type**& other)

1. Constructs a **value_property** object with the name *property_name*.
2. Constructs a **value_property** object with the name *property_name* and value *other*.

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | public | **this_type**& operator=(const **this_type**& other)
*assign value (2)* | public | **this_type**& operator=(const **value_type**& other)

1. Copies an **value_property** object.
2. Assign a value to the **value_property** object.

## Inherited functions

### Cast operator

Specifiers | Signature
-|-
public | operator **value_type**() const

Conversion function (or cast operator) that return the value of the **value_property** object.

### Get value operator

Specifiers | Signature
-|-
public | **value_type** operator()() const

Function call operator that return the value of the **value_property** object.

### Indirection operator

Specifiers | Signature
-|-
public | **value_type** operator\*() const

Indirection operator that return the value of the **value_property** object.

### get

Specifiers | Signature
-|-
public | **value_type get**() const

Function that return the value of the **value_property** object.

### name

Specifiers | Signature
-|-
public | **const string_type**& **name**() const

Function that return the name of the **value_property** object.
