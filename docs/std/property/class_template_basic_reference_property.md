---
layout: std_lib_property
---

```c++
namespace go::property
```

# class template basic_reference_property

```c++
<go/property/reference_property.hpp>
```

**Generic reference property class**

The **basic_reference_property** is a generalization class for properties with any value
type and name string class. It is implemented using the reference storage policy.

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
this_type | basic_reference_property<value_type, string_type>
policy_type | policy\::reference<value_type>

## Member functions

### (destructor)

*public virtual member function*

Destroys the **basic_reference_property** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*assign name (1)* | **basic_reference_property**(const **string_type**& property_name)
*assign name and value (2)* | **basic_reference_property**(const **string_type**& property_name, const **value_type**& other)

1. Constructs a **basic_reference_property** object with the name *property_name*.
2. Constructs a **basic_reference_property** object with the name *property_name* and value *other*.

### operator=

*public member function*

Operator | Signature
-|-
*assign copy (1)* | **this_type**& operator=(const **this_type**& other)
*assign value (2)* | **this_type**& operator=(const **value_type**& other)

1. Copies an **basic_reference_property** object.
2. Assign a value to the **basic_reference_property** object.

### bool empty() const

*public member function*

Test whether property is empty.

### void clear()

*public member function*

Clear the property.

### explicit operator bool() const

*public member function*

Test whether property is empty.

### bool operator!() const

*public member function*

Test whether property is empty.

## Inherited functions

### operator value_type() const

*public member function*

Conversion function (or cast operator) that return the value of the **basic_reference_property** object.

### value_type operator()() const

*public member function*

Function call operator that return the value of the **basic_reference_property** object.

### void operator()(const value_type& other)

*public member function*

Function call operator that assign the value of the **basic_reference_property** object.

### value_type operator*() const

*public member function*

Indirection operator that return the value of the **basic_reference_property** object.

### value_type get() const

*public member function*

Function that return the value of the **basic_reference_property** object.

### void set(const value_type& other)

*public member function*

Function that assign the value of the **basic_reference_property** object.

### const string_type& name() const

*public member function*

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
using **std::u16string**. It is implemented using the reference storage policy.

It is declared as:

```c++
template<class T> class reference_u16property : public basic_reference_property<T, std::u16string>;
```

## class template reference_u32property

The **reference_u32property** is a generalization class for properties with any value type and name
using **std::u32string**. It is implemented using the reference storage policy.

It is declared as:

```c++
template<class T> class reference_u32property : public basic_reference_property<T, std::u32string>;
```
