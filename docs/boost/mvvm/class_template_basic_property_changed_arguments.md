---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class template basic_property_changed_arguments

```c++
<go_boost/mvvm.hpp>
```

The class **basic_property_changed_arguments** hold the arguments asociated wtih the
**property_changed** signal on
[notify_property_changed_interface](./class_template_basic_notify_property_changed_interface.html).

It is declared as:

```c++
template<class S>
class basic_property_changed_arguments
    : public go_boost::signals::slot_arguments
{
public:
    typedef S string_type;
    typedef basic_property_changed_arguments<string_type> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~basic_property_changed_arguments();

protected:
    explicit basic_property_changed_arguments(const string_type& property_name_);

public:
    static boost::shared_ptr<basic_property_changed_arguments<S>> create(const string_type& property_name_);

public:
    go_boost::property::nameless::read_only::value_property<string_type> property_name;
};
```

## Member types

Member type | Definition
-|-
string_type | S
this_type | basic_property_changed_arguments<string_type>
ptr | boost\::shared_ptr\<this_type>
wptr | boost\::weak_ptr\<this_type>

## Member properties

Property type | Property name
-|-
go_boost\::property\::nameless\::read_only\::value_property<string_type> | property_name

### Property property_name

Gets the name of the property that changed.

## Static member functions

### create

Specifiers | Signature
-|-
public static | boost\::shared_ptr\<basic_property_changed_arguments\<S>> **create**(const string_type& property_name_)

Constructs a new **basic_property_changed_arguments\<S>** object and return it as a
**basic_property_changed_arguments\<S>\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_property_changed_arguments** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_property_changed_arguments**()

1. Constructs a **basic_property_changed_arguments** object.

# class template basic_property_changed_argument specializations

## typedef property_changed_argument

The **property_changed_argument** is a type definition for property name using
**std::string** type.

It is defined as:

```c++
typedef basic_property_changed_argument<std::string> property_changed_argument;
```

## typedef wproperty_changed_argument

The **wproperty_changed_argument** is a type definition for property name using
**std::wstring** type.

It is defined as:

```c++
typedef basic_property_changed_argument<std::wstring> wproperty_changed_argument;
```
