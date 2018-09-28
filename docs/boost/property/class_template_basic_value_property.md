---
layout: boost_lib_property
---

```c++
namespace go_boost::property
```

# class template basic_value_property

```c++
<go_boost/property/value_property.hpp>
```

**Generic value property class**

The **basic_value_property** is a generalization class for properties with any value type
and name string class. It is implemented using the value storage policy.

It is declared as:

```c++
template<class T, class S> class basic_value_property
    : public detail::property_base<T, policy::value<T>, S>
{
public:
    virtual ~basic_value_property();
    explicit basic_value_property(const string_type& property_name);
    basic_value_property(const string_type& property_name, const value_type& other);
    this_type& operator=(const this_type& other);
    this_type& operator=(const value_type& other);

    // The following operators and functions are inherited from detail::property_base<T, policy::value<T>, S>
    operator value_type() const;
    value_type operator()() const;
    void operator()(const value_type& other);
    value_type operator*() const;
    value_type get() const;
    void set(const value_type& other);
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
this_type | basic_value_property<value_type, string_type>
policy_type | policy\::value<value_type>

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_value_property** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*assign name (1)* | public explicit | **basic_value_property**(const **string_type**& property_name)
*assign name and value (2)* | public | **basic_value_property**(const **string_type**& property_name, const **value_type**& other)

1. Constructs a **basic_value_property** object with the name *property_name*.
2. Constructs a **basic_value_property** object with the name *property_name* and value *other*.

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | public | **this_type**& operator=(const **this_type**& other)
*assign value (2)* | public | **this_type**& operator=(const **value_type**& other)

1. Copies an **basic_value_property** object.
2. Assign a value to the **basic_value_property** object.

## Inherited functions

### Cast operator

Specifiers | Signature
-|-
public | operator **value_type**() const

Conversion function (or cast operator) that return the value of the **basic_value_property** object.

### Get value operator

Specifiers | Signature
-|-
public | **value_type** operator()() const

Function call operator that return the value of the **basic_value_property** object.

### Set value operator

Specifiers | Signature
-|-
public | void operator()(const **value_type**& other)

Function call operator that assign the value of the **basic_value_property** object.

### Indirection operator

Specifiers | Signature
-|-
public | **value_type** operator\*() const

Indirection operator that return the value of the **basic_value_property** object.

### get

Specifiers | Signature
-|-
public | **value_type get**() const

Function that return the value of the **basic_value_property** object.

### set

Specifiers | Signature
-|-
public | **void set**(const value_type& other)

Function that assign the value of the **basic_value_property** object.

### name

Specifiers | Signature
-|-
public | **const string_type**& **name**() const

Function that return the name of the **basic_value_property** object.

# class template basic_property specializations

## class template value_property

The **value_property** is a generalization class for properties with any value type and name
using **std::string**. It is implemented using the proxy storage policy.

It is declared as:

```c++
template<class T> class value_property : public basic_property<T, std::string>;
```

## class template value_wproperty

The **value_wproperty** is a generalization class for properties with any value type and name
using **std::wstring**. It is implemented using the proxy storage policy.

It is declared as:

```c++
template<class T> class value_wproperty : public basic_property<T, std::wstring>;
```

## class template value_u16property

The **value_u16property** is a generalization class for properties with any value type and name
using **go_boost::u16string**. It is implemented using the proxy storage policy.

It is declared as:

```c++
template<class T> class value_u16property : public basic_property<T, go_boost::u16string>;
```

## class template value_u32property

The **value_u32property** is a generalization class for properties with any value type and name
using **go_boost::u32string**. It is implemented using the proxy storage policy.

It is declared as:

```c++
template<class T> class value_u32property : public basic_property<T, go_boost::u32string>;
```
