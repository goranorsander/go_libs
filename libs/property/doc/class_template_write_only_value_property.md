```c++
namespace go::property::write_only
```

# class template value_property

```c++
<go/property/write_only_value_property.hpp>
```

**Generic write only value property class**

The **value_property** is a generalization class for write only properties with any value type and name using **std::string**.
It is implemented using the value storage policy.

It is declared as:

```c++
template<class T> class value_property
    : public basic_value_property<T, std::string>
{
public:
    virtual ~value_property();
    explicit value_property(const string_type& property_name);
    value_property(const string_type& property_name, const value_type& v);
    this_type& operator=(const this_type& v);
    this_type& operator=(const value_type& v);

    // The following operators and functions are inherited from detail::property_base<T, policy::value<T>, std::string>
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
string_type | std::string
this_type | value_property<value_type, string_type>
get_function_signature | std::function<value_type(void)>
set_function_signature | std::function<void(const value_type&)>

## Member functions

### (destructor)

*public virtual member function*

Destroys the **value_property** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*assign name (1)* | **value_property**(const **string_type**& property_name)
*assign name, bind getter and setter (2)* | **value_property**(const **string_type**& property_name, const **value_type**& v)

1. Constructs a **value_property** object with the name *property_name*.
2. Constructs a **value_property** object with the name *property_name* and value value *v*.

### operator=

*public member function*

Operator | Signature
-|-
*assign copy (1)* | **this_type**& **operator=(const **this_type**& v)
*assign value (2)* | **this_type**& **operator=(const **value_type**& v)

1. Copies an **value_property** object.
2. Assign a value to the **value_property** object.

## Inherited functions

### operator value_type()

*public member function*

Conversion function (or cast operator) that return the value of the **value_property** object.

### value_type operator()()

*public member function*

Function call operator that return the value of the **value_property** object.

### void operator()(const value_type& v)

*public member function*

Function call operator that assign the value of the **value_property** object.

### value_type operator*() const

*public member function*

Indirection operator that return the value of the **value_property** object.

### get

*public member function*

Function that return the value of the **value_property** object.

### set

*public member function*

Function that assign the value of the **value_property** object.

### name

*public member function*

Function that return the name of the **value_property** object.

Copyright &copy; 2014-2017 Göran Orsander
