---
layout: boost_lib_property_read_only
---

```c++
namespace go_boost::property::read_only
```

# class template basic_reference_property

```c++
<go_boost/property/read_only_reference_property.hpp>
```

**Generic read-only reference property class**

The **basic_reference_property** is a generalization class for read-only properties with any value type and name string class.
It is implemented using the reference storage policy.

It is declared as:

```c++
template<class T, class S> class basic_reference_property
    : public detail::property_base<T, policy::reference<T>, S>
{
public:
    virtual ~basic_reference_property();
    explicit basic_reference_property(const string_type& property_name);
    basic_reference_property(const string_type& property_name, const value_type& other);
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
this_type | basic_reference_property<value_type, string_type>
policy_type | policy\::reference<value_type>

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_reference_property** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*assign name (1)* | public explicit | **basic_reference_property**(const **string_type**& property_name)
*assign name and value (2)* | public | **basic_reference_property**(const **string_type**& property_name, const **value_type**& other)

1. Constructs a **basic_reference_property** object with the name *property_name*.
2. Constructs a **basic_reference_property** object with the name *property_name* and value *other*.

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | public | **this_type**& operator=(const **this_type**& other)
*assign value (2)* | public | **this_type**& operator=(const **value_type**& other)

1. Copies an **basic_reference_property** object.
2. Assign a value to the **basic_reference_property** object.

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

Conversion function (or cast operator) that return the value of the **basic_reference_property** object.

### Get value operator

Specifiers | Signature
-|-
public | **value_type** operator()() const

Function call operator that return the value of the **basic_reference_property** object.

### Indirection operator

Specifiers | Signature
-|-
public | **value_type** operator\*() const

Indirection operator that return the value of the **basic_reference_property** object.

### get

Specifiers | Signature
-|-
public | **value_type get**() const

Function that return the value of the **basic_reference_property** object.

### name

Specifiers | Signature
-|-
public | **const string_type**& **name**() const

Function that return the name of the **basic_reference_property** object.

# class template basic_reference_property specializations

## class template reference_property

The **reference_property** is a generalization class for properties with any value type and name
using **std::string**. It is implemented using the reference storage policy.

It is declared as:

```c++
template<class T> class reference_property : public basic_reference_property<T, std::string>;
```

## class template reference_wproperty

The **reference_wproperty** is a generalization class for properties with any value type and name
using **std::wstring**. It is implemented using the reference storage policy.

It is declared as:

```c++
template<class T> class reference_wproperty : public basic_reference_property<T, std::wstring>;
```

## class template reference_u16property

The **reference_u16property** is a generalization class for properties with any value type and name
using **go_boost::u16string**. It is implemented using the reference storage policy.

It is declared as:

```c++
template<class T> class reference_u16property : public basic_reference_property<T, go_boost::u16string>;
```

## class template reference_u32property

The **reference_u32property** is a generalization class for properties with any value type and name
using **go_boost::u32string**. It is implemented using the reference storage policy.

It is declared as:

```c++
template<class T> class reference_u32property : public basic_reference_property<T, go_boost::u32string>;
```
