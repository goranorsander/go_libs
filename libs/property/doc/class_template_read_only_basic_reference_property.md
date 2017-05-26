```c++
namespace go::property::read_only
```

# class template basic_reference_property

```c++
<go/property/read_only_reference_property.hpp>
```

**Generic read only reference property class**

The **basic_reference_property** is a generalization class for read only properties with any value type and name string class.
It is implemented using the reference storage policy.

It is declared as:

```c++
template<class T, class S> class basic_reference_property
    : public detail::property_base<T, policy::reference<T>, S>
{
public:
    virtual ~basic_reference_property();
    explicit basic_reference_property(const string_type& property_name);
    basic_reference_property(const string_type& property_name, const value_type& v);
    this_type& operator=(const this_type& v);
    this_type& operator=(const value_type& v);
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
policy_type | policy::reference<value_type>

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
*assign name and value (2)* | **basic_reference_property**(const **string_type**& property_name, const **value_type**& v)

1. Constructs a **basic_reference_property** object with the name *property_name*.
2. Constructs a **basic_reference_property** object with the name *property_name* and value *v*.

### operator=

*public member function*

Operator | Signature
-|-
*assign copy (1)* | **this_type**& **operator=(const **this_type**& v)
*assign value (2)* | **this_type**& **operator=(const **value_type**& v)

1. Copies an **basic_reference_property** object.
2. Assign a value to the **basic_reference_property** object.

### empty

*public member function*

Test whether property is empty.

### clear

*public member function*

Clear the property.

### operator bool()

*public member function*

Test whether property is empty.

### bool operator!() const;

*public member function*

Test whether property is empty.

## Inherited functions

### operator value_type()

*public member function*

Conversion function (or cast operator) that return the value of the **basic_reference_property** object.

### value_type operator()()

*public member function*

Function call operator that return the value of the **basic_reference_property** object.

### value_type operator*() const

*public member function*

Indirection operator that return the value of the **basic_reference_property** object.

### get

*public member function*

Function that return the value of the **basic_reference_property** object.

### name

*public member function*

Function that return the name of the **basic_reference_property** object.

Copyright &copy; 2014-2017 Göran Orsander
