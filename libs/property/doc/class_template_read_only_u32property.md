```c++
namespace go::property::read_only
```

# class template u32property

```c++
<go/property/read_only_property.hpp>
```

**Generic read only property class**

The **u32property** is a generalization class for read only properties with any value type and name using **std::u32string**.
It is implemented using the proxy storage policy.

It is declared as:

```c++
template<class T> class u32property
    : public basic_property<T, std::u32string>
{
public:
    virtual ~u32property();
    explicit u32property(const string_type& property_name);
    u32property(const string_type& property_name, const get_function_signature& get_function);
    this_type& operator=(const this_type& v);
    this_type& operator=(const value_type& v);

    // The following operators and functions are inherited from basic_property<T, std::u32string>
    void getter(const get_function_signature& f);

    // The following operators and functions are inherited from detail::property_base<T, policy::proxy<T>, std::u32string>
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
string_type | std::u32string
this_type | property<value_type, string_type>
get_function_signature | std::function<value_type(void)>

## Member functions

### (destructor)

*public virtual member function*

Destroys the **u32property** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*assign name (1)* | **u32property**(const **string_type**& property_name)
*assign name and bind getter (2)* | **u32property**(const **string_type**& property_name, const **get_function_signature**& get_function)

1. Constructs a **u32property** object with the name *property_name*.
2. Constructs a **u32property** object with the name *property_name* and get function *get_function*.

### operator=

*public member function*

Operator | Signature
-|-
*assign copy (1)* | **this_type**& **operator=(const **this_type**& v)
*assign value (2)* | **this_type**& **operator=(const **value_type**& v)

1. Copies an **u32property** object.
2. Assign a value to the **u32property** object.

## Inherited functions

### getter

*public member function*

Binds a *getter* function to the **u32property** object. This function is invoked when the property
value is gotten (returned or retrieved).

### operator value_type()

*public member function*

Conversion function (or cast operator) that return the value of the **u32property** object.

### value_type operator()()

*public member function*

Function call operator that return the value of the **u32property** object.

### value_type operator*() const

*public member function*

Indirection operator that return the value of the **u32property** object.

### get

*public member function*

Function that return the value of the **u32property** object.

### name

*public member function*

Function that return the name of the **u32property** object.

Copyright &copy; 2014-2017 Göran Orsander