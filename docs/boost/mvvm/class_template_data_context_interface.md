---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class template data_context_interface

```c++
<go_boost/mvvm.hpp>
```

**Generic data context interface**

The **data_context_interface** is a generalization class for data contexts.

It is declared as:

```c++
template<class T> class data_context_interface
    : public notify_data_context_change_interface
{
public:
    typedef T data_type;
    typedef data_context_interface<data_type> this_type;
    typedef go_boost::property::nameless::property<data_type> data_context_type;

public:
    virtual ~data_context_interface() = 0;

protected:
    data_context_interface();
    explicit data_context_interface(const data_type& t);

public:
    data_context_type data_context;

protected:
    virtual void bind_data_context_properties();
    virtual void on_data_context_will_change();
    virtual void on_data_context_changed();
};
```

## Template parameters

Parameter | Description
-|-
T | The data class

## Member types

Member type | Definition
-|-
data_type | T
this_type | data_context_interface<data_type>
data_context_type | go_boost\::property\::nameless\::property<data_type>

## Member properties

Property type | Property name
-|-
data_context_type | data_context

### Property data_context

Gets or sets the data context.

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **data_context_interface** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*constructor (1)* | protected | **data_context_interface**()
*constructor (2)* | protected explicit | **data_context_interface**(const data_type& t)

1. Constructs a **data_context_interface** object.
2. Constructs a **data_context_interface** object with a data context assigned.

### bind_data_context_properties

Specifiers | Signature
-|-
protected virtual | void **bind_data_context_properties**()

Bind the data context property accessors.

### on_data_context_will_change

Specifiers | Signature
-|-
protected virtual | void **on_data_context_will_change**()

Called when the data context is about to change.

### on_data_context_changed

Specifiers | Signature
-|-
protected virtual | void **on_data_context_changed**()

Called when the data context have changed.
