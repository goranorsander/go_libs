```c++
namespace go::property
```

# class template wproperty

```c++
<go/property/property.hpp>
```

**Generic property class**

The **wproperty** is a generalization class for properties with any value type and name using **std::wstring**.
It is implemented using the proxy storage policy.

It is declared as:

```c++
template<class T> class wproperty
    : public basic_property<T, std::wstring>
{
public:
    virtual ~wproperty();
    explicit wproperty(const string_type& property_name);
    wproperty(const string_type& property_name, const get_function_signature& get_function, const set_function_signature& set_function);
    this_type& operator=(const this_type& v);
    this_type& operator=(const value_type& v);

    // The following operators and functions are inherited from basic_property<T, std::wstring>
    void getter(const get_function_signature& f);
    void setter(const set_function_signature& f);

    // The following operators and functions are inherited from detail::property_base<T, policy::proxy<T>, std::wstring>
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
string_type | std::wstring
this_type | property<value_type, string_type>
get_function_signature | std::function<value_type(void)>
set_function_signature | std::function<void(const value_type&)>

## Member functions

### (destructor)

*public virtual member function*

Destroys the **wproperty** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*assign name (1)* | **wproperty**(const **string_type**& property_name)
*assign name, bind getter and setter (2)* | **wproperty**(const **string_type**& property_name, const **get_function_signature**& get_function, const **set_function_signature**& set_function)

1. Constructs a **wproperty** object with the name *property_name*.
2. Constructs a **wproperty** object with the name *property_name*, get function *get_function*, and set function *set_function*.

### operator=

*public member function*

Operator | Signature
-|-
*assign copy (1)* | **this_type**& **operator=(const **this_type**& v)
*assign value (2)* | **this_type**& **operator=(const **value_type**& v)

1. Copies an **wproperty** object.
2. Assign a value to the **wproperty** object.

## Inherited functions

### getter

*public member function*

Binds a *getter* function to the **wproperty** object. This function is invoked when the property
value is gotten (returned or retrieved).

### setter

*public member function*

Binds a *setter* function to the **wproperty** object. This function is invoked when the property
value is set (assigned or updated).

### operator value_type()

*public member function*

Conversion function (or cast operator) that return the value of the **wproperty** object.

### value_type operator()()

*public member function*

Function call operator that return the value of the **wproperty** object.

### void operator()(const value_type& v)

*public member function*

Function call operator that assign the value of the **wproperty** object.

### value_type operator*() const

*public member function*

Indirection operator that return the value of the **wproperty** object.

### get

*public member function*

Function that return the value of the **wproperty** object.

### set

*public member function*

Function that assign the value of the **wproperty** object.

### name

*public member function*

Function that return the name of the **wproperty** object.

Copyright &copy; 2014-2017 Göran Orsander
