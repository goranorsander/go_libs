---
layout: std_lib_property_read_only
---

```c++
namespace go::property::read_only
```

# class template basic_property

```c++
<go/property/read_only_property.hpp>
```

**Generic read-only property class**

The **basic_property** is a generalization class for read-only properties with any value type and name string class.
It is implemented using the proxy storage policy.

It is declared as:

```c++
template<class T, class S> class basic_property
    : public detail::property_base<T, policy::proxy<T>, S>
{
public:
    virtual ~basic_property();
    explicit basic_property(const string_type& property_name);
    basic_property(const string_type& property_name, const get_function_signature& get_function);
    this_type& operator=(const this_type& other);
    this_type& operator=(const value_type& other);
    void getter(const get_function_signature& f);

    // The following operators and functions are inherited from detail::property_base<T, policy::proxy<T>, S>
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
this_type | basic_property<value_type, string_type>
policy_type | policy\::proxy<value_type>
get_function_signature | std\::function<value_type(void)>

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_property** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*assign name (1)* | public explicit | **basic_property**(const **string_type**& property_name)
*assign name and bind getter (2)* | public | **basic_property**(const **string_type**& property_name, const **get_function_signature**& get_function)

1. Constructs a **basic_property** object with the name *property_name*.
2. Constructs a **basic_property** object with the name *property_name* and get function *get_function*.

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | public | **this_type**& operator=(const **this_type**& other)
*assign value (2)* | public | **this_type**& operator=(const **value_type**& other)

1. Copies an **basic_property** object.
2. Assign a value to the **basic_property** object.

### getter

Specifiers | Signature
-|-
public | **void getter**(const get_function_signature& f)

Binds a *getter* function to the **basic_property** object. This function is invoked when the property
value is gotten (returned or retrieved).

## Inherited functions

### Cast operator

Specifiers | Signature
-|-
public | operator **value_type**() const

Conversion function (or cast operator) that return the value of the **basic_property** object.

### Get value operator

Specifiers | Signature
-|-
public | **value_type** operator()() const

Function call operator that return the value of the **basic_property** object.

### Indirection operator

Specifiers | Signature
-|-
public | **value_type** operator\*() const

Indirection operator that return the value of the **basic_property** object.

### get

Specifiers | Signature
-|-
public | **value_type get**() const

Function that return the value of the **basic_property** object.

### name

Specifiers | Signature
-|-
public | **const string_type**& **name**() const

Function that return the name of the **basic_property** object.

# class template basic_property specializations

## class template property

The **property** is a generalization class for properties with any value type and name
using **std::string**. It is implemented using the proxy storage policy.

It is declared as:

```c++
template<class T> class property : public basic_property<T, std::string>;
```

## class template wproperty

The **wproperty** is a generalization class for properties with any value type and name
using **std::wstring**. It is implemented using the proxy storage policy.

It is declared as:

```c++
template<class T> class wproperty : public basic_property<T, std::wstring>;
```

## class template u16property

The **u16property** is a generalization class for properties with any value type and name
using **std::u16string**. It is implemented using the proxy storage policy.

It is declared as:

```c++
template<class T> class u16property : public basic_property<T, std::u16string>;
```

## class template u32property

The **u32property** is a generalization class for properties with any value type and name
using **std::u32string**. It is implemented using the proxy storage policy.

It is declared as:

```c++
template<class T> class u32property : public basic_property<T, std::u32string>;
```
