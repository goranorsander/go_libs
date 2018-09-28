---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class data_context_changed_arguments

```c++
<go_boost/mvvm.hpp>
```

The **data_context_changed_arguments** hold the arguments asociated wtih the
**data_context_changed** signal on
[notify_data_context_interface](./class_notify_data_context_change_interface.html).

It is declared as:

```c++
class data_context_changed_arguments
    : public go_boost::signals::slot_arguments
{
public:
    virtual ~data_context_changed_arguments();

protected:
    data_context_changed_arguments();

public:
    static boost::shared_ptr<data_context_changed_arguments> create();
};
```

## Member types

Member type | Definition
-|-
this_type | data_context_changed_arguments
ptr | boost\::shared_ptr\<this_type>
wptr | boost\::weak_ptr\<this_type>

## Static member functions

### create

Specifiers | Signature
-|-
public static | boost\::shared_ptr<data_context_changed_arguments> create()

Constructs a new **data_context_changed_arguments** object and return it as a
**data_context_changed_arguments\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **data_context_changed_arguments** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **data_context_changed_arguments**()

1. Constructs a **data_context_changed_arguments** object.
