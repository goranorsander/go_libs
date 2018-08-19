---
layout: std_lib_property_nameless_write_only
---

```c++
namespace go::property::nameless::read_only
```

# class template property

```c++
<go/property/nameless/write_only_property.hpp>
```

**Generic write-only property class**

The **property** is a generalization class for write-only properties with any value type and name string class.
It is implemented using the proxy storage policy.

It is declared as:

```c++
template<class T, class S> class property
    : public detail::property_base<T, policy::proxy<T>, S>
{
public:
    virtual ~property();
    explicit property(const string_type& property_name);
    property(const string_type& property_name, const get_function_signature& get_function, const set_function_signature& set_function);
    this_type& operator=(const this_type& other);
    this_type& operator=(const value_type& other);
    void getter(const get_function_signature& f);
    void setter(const set_function_signature& f);

    // The following operators and functions are inherited from detail::property_base<T, policy::proxy<T>, S>
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
this_type | property<value_type, string_type>
policy_type | policy\::proxy<value_type>
get_function_signature | std\::function<value_type(void)>
set_function_signature | std\::function<void(const value_type&)>

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **property** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*assign name (1)* | public explicit | **property**(const **string_type**& property_name)
*assign name, bind getter and setter (2)* | public | **property**(const **string_type**& property_name, const **get_function_signature**& get_function, const **set_function_signature**& set_function)

1. Constructs a **property** object with the name *property_name*.
2. Constructs a **property** object with the name *property_name*, get function *get_function*, and set function *set_function*.

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | public | **this_type**& operator=(const **this_type**& other)
*assign value (2)* | public | **this_type**& operator=(const **value_type**& other)

1. Copies an **property** object.
2. Assign a value to the **property** object.

### getter

Specifiers | Signature
-|-
public | **void getter**(const get_function_signature& f)

Binds a *getter* function to the **property** object. This function is invoked when the property
value is gotten (returned or retrieved).

### setter

Specifiers | Signature
-|-
public | **void setter**(const set_function_signature& f)

Binds a *setter* function to the **property** object. This function is invoked when the property
value is set (assigned or updated).

## Inherited functions

### Cast operator

Specifiers | Signature
-|-
public | operator **value_type**() const

Conversion function (or cast operator) that return the value of the **property** object.

### Get value operator

Specifiers | Signature
-|-
public | **value_type** operator()() const

Function call operator that return the value of the **property** object.

### Set value operator

Specifiers | Signature
-|-
public | void operator()(const **value_type**& other)

Function call operator that assign the value of the **property** object.

### Indirection operator

Specifiers | Signature
-|-
public | **value_type** operator\*() const

Indirection operator that return the value of the **property** object.

### get

Specifiers | Signature
-|-
public | **value_type get**() const

Function that return the value of the **property** object.

### set

Specifiers | Signature
-|-
public | **void set**(const value_type& other)

Function that assign the value of the **property** object.

### name

Specifiers | Signature
-|-
public | **const string_type**& **name**() const

Function that return the name of the **property** object.
