---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class template basic_command_execution_observer_interface

```c++
<go/mvvm.hpp>
```

**Generic command execution observer interface**

The **basic_command_execution_observer_interface** is a generalization class for
observing [command](./class_template_basic_command_interface.html) execution.

It is declared as:

```c++
template<class S, class L = std::recursive_mutex>
class basic_command_execution_observer_interface
{
public:
    virtual ~basic_command_execution_observer_interface() = 0;

protected:
    basic_command_execution_observer_interface() = default;

public:
    virtual void on_command_executed(const std::shared_ptr<basic_command_interface<S, L>>& /*c*/) = 0;
    virtual void on_command_not_executed(const std::shared_ptr<basic_command_interface<S, L>>& /*c*/) = 0;
};
```

## Template parameters

Parameter | Description
-|-
S | The observer string class
L | The observer lockable class

## Member types

Member type | Definition
-|-
string_type | S
lockable_type | L
this_type | basic_command_execution_observer_interface<S, L>

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **basic_command_execution_observer_interface** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **basic_command_execution_observer_interface**()

1. Constructs a **basic_command_execution_observer_interface** object.

### on_command_executed

Specifiers | Signature
-|-
public abstract | **void on_command_executed**(const std\::shared_ptr<basic_command_interface<S, L>>& c) = 0

This is a callback member function that is called by classes implementing the
[basic_notify_command_execution_interface](./class_template_basic_command_execution_observer_interface.html),
e.g. the [basic_command_manager](./class_template_basic_command_manager.html), if
connected to the signal **basic_notify_command_execution_interface\::command_executed**.

The [command manager](./class_template_basic_command_manager.html) call this member
function as a signal that a [command](./class_template_basic_command_interface.html)
have been executed.

### on_command_not_executed

Specifiers | Signature
-|-
public abstract | **void on_command_not_executed**(const std\::shared_ptr<basic_command_interface<S, L>>& c) = 0

The [command manager](./class_template_basic_command_manager.html) call this member
function as a signal that a [command](./class_template_basic_command_interface.html)
were not executed.
