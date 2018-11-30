---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class basic_notify_command_execution_interface

```c++
<go_boost/mvvm.hpp>
```

**basic_notify_command_execution_interface class**

The **basic_notify_command_execution_interface** is implemented to receive notifications
when a [command](./class_template_basic_command_interface.html) is executed.

It is declared as:

```c++
template<class S, class L = boost::recursive_mutex>
class basic_notify_command_execution_interface
    : public go_boost::signals::slot
{
public:
    virtual ~basic_notify_command_execution_interface() = 0;

protected:
    basic_notify_command_execution_interface();

public:
    command_executed_signal command_executed;
    command_not_executed_signal command_not_executed;
};
```

## Template parameters

Parameter | Description
-|-
S | The string class
L | The lockable class

## Member types

Member type | Definition
-|-
string_type | S
lockable_type | L
this_type | basic_notify_command_execution_interface<S, L>
command_executed_signal | go_boost\::signals\::signal<boost\::function<void(const boost\::shared_ptr<basic_command_interface<string_type, lockable_type>>&)>>
command_not_executed_signal | go_boost\::signals\::signal<boost\::function<void(const boost\::shared_ptr<basic_command_interface<string_type, lockable_type>>&)>>

## Member signals

Signal | Description
-|-
command_executed | Emitted after a command was executed.
command_not_executed | Emitted when a command was supposed to be executed but was not.

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **basic_notify_command_execution_interface** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_notify_command_execution_interface**()

1. Constructs a **basic_notify_command_execution_interface** object.

# class template basic_notify_command_execution_interface specializations

## typedef notify_command_execution_interface

The **notify_command_execution_interface** is a type definition for observing commands
using **std::string** type being executed.

It is defined as:

```c++
typedef basic_notify_command_execution_interface<std::string> notify_command_execution_interface;
```

## typedef notify_wcommand_execution_interface

The **notify_wcommand_execution_interface** is a type definition for observing commands
using **std::wstring** type being executed.

It is defined as:

```c++
typedef basic_notify_command_execution_interface<std::wstring> notify_wcommand_execution_interface;
```
