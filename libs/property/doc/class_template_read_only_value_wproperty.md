```c++
namespace go::property::read_only
```

# class template value_wproperty

```c++
<go/property/read_only_value_property.hpp>
```

**Generic read only value property class**

The **value_wproperty** is a generalization class for read only properties with any value type and name using **std::wstring**.
It is implemented using the value storage policy.

It is declared as:

```c++
template<class T> class value_wproperty
    : public basic_value_property<T, std::wstring>
{
public:
    virtual ~value_wproperty();
    explicit value_wproperty(const string_type& property_name);
    value_wproperty(const string_type& property_name, const value_type& v);
    this_type& operator=(const this_type& v);
    this_type& operator=(const value_type& v);

    // The following operators and functions are inherited from detail::property_base<T, policy::value<T>, std::wstring>
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

## Member types

Member type | Definition
-|-
value_type | T
string_type | std::wstring
this_type | value_wproperty<value_type, string_type>

## Member functions

### (destructor)

*public virtual member function*

Destroys the **value_wproperty** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*assign name (1)* | **value_wproperty**(const **string_type**& property_name)
*assign name and value (2)* | **value_wproperty**(const **string_type**& property_name, const **value_type**& v)

1. Constructs a **value_wproperty** object with the name *property_name*.
2. Constructs a **value_wproperty** object with the name *property_name* and value value *v*.

### operator=

*public member function*

Operator | Signature
-|-
*assign copy (1)* | **this_type**& **operator=(const **this_type**& v)
*assign value (2)* | **this_type**& **operator=(const **value_type**& v)

1. Copies an **value_wproperty** object.
2. Assign a value to the **value_wproperty** object.

## Inherited functions

### operator value_type()

*public member function*

Conversion function (or cast operator) that return the value of the **value_wproperty** object.

### value_type operator()()

*public member function*

Function call operator that return the value of the **value_wproperty** object.

### value_type operator*() const

*public member function*

Indirection operator that return the value of the **value_wproperty** object.

### get

*public member function*

Function that return the value of the **value_wproperty** object.

### name

*public member function*

Function that return the name of the **value_wproperty** object.

Copyright &copy; 2014-2017 Göran Orsander
