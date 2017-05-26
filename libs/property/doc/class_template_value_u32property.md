```c++
namespace go::property
```

# class template value_u32property

```c++
<go/property/value_property.hpp>
```

**Generic value property class**

The **value_u32property** is a generalization class for properties with any value type and name using **std::u32string**.
It is implemented using the value storage policy.

It is declared as:

```c++
template<class T> class value_u32property
    : public basic_value_property<T, std::u32string>
{
public:
    virtual ~value_u32property();
    explicit value_u32property(const string_type& property_name);
    value_u32property(const string_type& property_name, const value_type& v);
    this_type& operator=(const this_type& v);
    this_type& operator=(const value_type& v);

    // The following operators and functions are inherited from detail::property_base<T, policy::value<T>, std::u32string>
    operator value_type() const;
    value_type operator()() const;
    void operator()(const value_type& v);
    value_type operator*() const;
    value_type get() const;
    void set(const value_type& v);
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
string_type | std::u32string
this_type | value_u32property<value_type, string_type>
get_function_signature | std::function<value_type(void)>
set_function_signature | std::function<void(const value_type&)>

## Member functions

### (destructor)

*public virtual member function*

Destroys the **value_u32property** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*assign name (1)* | **value_u32property**(const **string_type**& property_name)
*assign name, bind getter and setter (2)* | **value_u32property**(const **string_type**& property_name, const **value_type**& v)

1. Constructs a **value_u32property** object with the name *property_name*.
2. Constructs a **value_u32property** object with the name *property_name* and value value *v*.

### operator=

*public member function*

Operator | Signature
-|-
*assign copy (1)* | **this_type**& **operator=(const **this_type**& v)
*assign value (2)* | **this_type**& **operator=(const **value_type**& v)

1. Copies an **value_u32property** object.
2. Assign a value to the **value_u32property** object.

## Inherited functions

### operator value_type()

*public member function*

Conversion function (or cast operator) that return the value of the **value_u32property** object.

### value_type operator()()

*public member function*

Function call operator that return the value of the **value_u32property** object.

### void operator()(const value_type& v)

*public member function*

Function call operator that assign the value of the **value_u32property** object.

### value_type operator*() const

*public member function*

Indirection operator that return the value of the **value_u32property** object.

### get

*public member function*

Function that return the value of the **value_u32property** object.

### set

*public member function*

Function that assign the value of the **value_u32property** object.

### name

*public member function*

Function that return the name of the **value_u32property** object.

Copyright &copy; 2014-2017 Göran Orsander
