```c++
namespace go::property
```

# class template property

```c++
<go/property/property.hpp>
```

**Generic property class**

The **property** is a generalization class for properties with any value type and name using **std::string**.
It is implemented using the proxy storage policy.

It is declared as:

```c++
template<class T> class property
    : public basic_property<T, std::string>
{
public:
    virtual ~property();
    explicit property(const string_type& property_name);
    property(const string_type& property_name, const get_function_signature& get_function, const set_function_signature& set_function);
    this_type& operator=(const this_type& v);
    this_type& operator=(const value_type& v);

    // The following operators and functions are inherited from basic_property<T, std::string>
    void getter(const get_function_signature& f);
    void setter(const set_function_signature& f);

    // The following operators and functions are inherited from detail::property_base<T, policy::proxy<T>, std::string>
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
this_type | property<value_type, string_type>
get_function_signature | std::function<value_type(void)>
set_function_signature | std::function<void(const value_type&)>

## Member functions

### (destructor)

*public virtual member function*

Destroys the **property** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*assign name (1)* | **property**(const **string_type**& property_name)
*assign name, bind getter and setter (2)* | **property**(const **string_type**& property_name, const **get_function_signature**& get_function, const **set_function_signature**& set_function)

1. Constructs a **property** object with the name *property_name*.
2. Constructs a **property** object with the name *property_name*, get function *get_function*, and set function *set_function*.

### operator=

*public member function*

Operator | Signature
-|-
*assign copy (1)* | **this_type**& **operator=(const **this_type**& v)
*assign value (2)* | **this_type**& **operator=(const **value_type**& v)

1. Copies an **property** object.
2. Assign a value to the **property** object.

## Inherited functions

### getter

*public member function*

Binds a *getter* function to the **property** object. This function is invoked when the property
value is gotten (returned or retrieved).

### setter

*public member function*

Binds a *setter* function to the **property** object. This function is invoked when the property
value is set (assigned or updated).

### operator value_type()

*public member function*

Conversion function (or cast operator) that return the value of the **property** object.

### value_type operator()()

*public member function*

Function call operator that return the value of the **property** object.

### void operator()(const value_type& v)

*public member function*

Function call operator that assign the value of the **property** object.

### value_type operator*() const

*public member function*

Indirection operator that return the value of the **property** object.

### get

*public member function*

Function that return the value of the **property** object.

### set

*public member function*

Function that assign the value of the **property** object.

### name

*public member function*

Function that return the name of the **property** object.

Copyright &copy; 2014-2017 Göran Orsander
