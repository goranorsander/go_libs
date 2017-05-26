```c++
namespace go::property::write_only
```

# class template reference_u16property

```c++
<go/property/write_only_reference_property.hpp>
```

**Generic write only reference property class**

The **reference_u16property** is a generalization class for write only properties with any value type and name using **std::u16string**.
It is implemented using the reference storage policy.

It is declared as:

```c++
template<class T> class reference_u16property
    : public basic_reference_property<T, std::u16string>
{
public:
    virtual ~reference_u16property();
    explicit reference_u16property(const string_type& property_name);
    reference_u16property(const string_type& property_name, const value_type& v);
    this_type& operator=(const this_type& v);
    this_type& operator=(const value_type& v);

    // The following operators and functions are inherited from basic_reference_property<T, std::u16string>
    bool empty() const;
    void clear();
    explicit operator bool() const;
    bool operator!() const;

    // The following operators and functions are inherited from detail::property_base<T, policy::reference<T>, std::u16string>
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
string_type | std::u16string
this_type | reference_u16property<value_type, string_type>
get_function_signature | std::function<value_type(void)>
set_function_signature | std::function<void(const value_type&)>

## Member functions

### (destructor)

*public virtual member function*

Destroys the **reference_u16property** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*assign name (1)* | **reference_u16property**(const **string_type**& property_name)
*assign name, bind getter and setter (2)* | **reference_u16property**(const **string_type**& property_name, const **value_type**& v)

1. Constructs a **reference_u16property** object with the name *property_name*.
2. Constructs a **reference_u16property** object with the name *property_name* and value reference *v*.

### operator=

*public member function*

Operator | Signature
-|-
*assign copy (1)* | **this_type**& **operator=(const **this_type**& v)
*assign value (2)* | **this_type**& **operator=(const **value_type**& v)

1. Copies an **reference_u16property** object.
2. Assign a value to the **reference_u16property** object.

## Inherited functions

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

### operator value_type()

*public member function*

Conversion function (or cast operator) that return the value of the **reference_u16property** object.

### value_type operator()()

*public member function*

Function call operator that return the value of the **reference_u16property** object.

### void operator()(const value_type& v)

*public member function*

Function call operator that assign the value of the **reference_u16property** object.

### value_type operator*() const

*public member function*

Indirection operator that return the value of the **reference_u16property** object.

### get

*public member function*

Function that return the value of the **reference_u16property** object.

### set

*public member function*

Function that assign the value of the **reference_u16property** object.

### name

*public member function*

Function that return the name of the **reference_u16property** object.

Copyright &copy; 2014-2017 Göran Orsander
