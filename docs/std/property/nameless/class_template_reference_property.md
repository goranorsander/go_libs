---
layout: std_lib_property_nameless
---

```c++
namespace go::property::nameless
```

# class template reference_property

```c++
<go/property/reference_property.hpp>
```

**Generic reference property class**

The **reference_property** is a generalization class for properties with any value type and name string class.
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
this_type | reference_property<value_type, string_type>
policy_type | policy\::reference<value_type>

## Member functions

### (destructor)

*public virtual member function*

Destroys the **reference_property** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*assign name (1)* | **reference_property**(const **string_type**& property_name)
*assign name and value (2)* | **reference_property**(const **string_type**& property_name, const **value_type**& other)

1. Constructs a **reference_property** object with the name *property_name*.
2. Constructs a **reference_property** object with the name *property_name* and value *other*.

### operator=

*public member function*

Operator | Signature
-|-
*assign copy (1)* | **this_type**& operator=(const **this_type**& other)
*assign value (2)* | **this_type**& operator=(const **value_type**& other)

1. Copies an **reference_property** object.
2. Assign a value to the **reference_property** object.

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

Conversion function (or cast operator) that return the value of the **reference_property** object.

### value_type operator()() const

*public member function*

Function call operator that return the value of the **reference_property** object.

### void operator()(const value_type& other)

*public member function*

Function call operator that assign the value of the **reference_property** object.

### value_type operator*() const

*public member function*

Indirection operator that return the value of the **reference_property** object.

### value_type get() const

*public member function*

Function that return the value of the **reference_property** object.

### void set(const value_type& other)

*public member function*

Function that assign the value of the **reference_property** object.

### const string_type& name() const

*public member function*

Function that return the name of the **reference_property** object.
