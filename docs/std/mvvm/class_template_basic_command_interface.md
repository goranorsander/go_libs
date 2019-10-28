---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class template basic_command_interface

```c++
<go/mvvm.hpp>
```

**Generic command interface**

The **basic_command_interface** is a generalization class for commands. A command
is a request for some action to be taken. The command shall preferably hold all
information necessary to perform the action.

It is declared as:

```c++
template<class S, class L = std::recursive_mutex>
class basic_command_interface
    : public std::enable_shared_from_this<basic_command_interface<S, L>>
    , public go::type_traits::noncopyable_nonmovable
{
public:
    virtual ~basic_command_interface() = 0;

protected:
    basic_command_interface(const S& cmd_name, const std::shared_ptr<command_parameters>& params);

public:
    virtual std::shared_ptr<command_parameters> parameters() const;
    virtual void notify_can_execute_changed();

protected:
    virtual bool can_execute(const std::shared_ptr<command_parameters>& params) = 0;
    virtual void execute(const std::shared_ptr<command_parameters>& params) = 0;

public:
    command_name_type command_name;
    can_execute_changed_signal can_execute_changed;
};
```

## Template parameters

Parameter | Description
-|-
S | The command string class
L | The command lockable class

## Member types

Member type | Definition
-|-
string_type | S
lockable_type | L
this_type | basic_command_interface<S, L>
ptr | std\::shared_ptr<basic_command_interface<S, L>>
wptr | std\::weak_ptr<basic_command_interface<S, L>>
command_parameters_type | std\::shared_ptr<command_parameters>
can_execute_changed_signal | go\::signals\::signal<std\::function<void(const std\::shared_ptr<basic_command_interface<S, L>>&)>>
command_name_type | go\::property\::nameless\::read_only\::property<S>

## Member properties

Property type | Property name
-|-
command_name_type | command_name

### Property command_name

Gets the name of the command.

## Member signals

Signal | Description
-|-
can_execute_changed | Emitted when the *can execute* state have changed.

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **basic_command_interface** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*constructor (1)* | protected | **basic_command_interface**(const S& cmd_name, const std::shared_ptr<command_parameters>& params)

1. Constructs a **basic_command_interface** object with a name and parameters.

### parameters

Specifiers | Signature
-|-
public virtual | std\::shared_ptr<command_parameters> parameters() const

Returns the command parameters.

### notify_can_execute_changed

Specifiers | Signature
-|-
public virtual | **void** notify_can_execute_changed()

Emits the **can_execute_changed** signal.

### can_execute

Specifiers | Signature
-|-
protected abstract | **bool** can_execute(const std\::shared_ptr<command_parameters>& params)

Returns **true** it the command can be executed, **false** otherwise.

### execute

Specifiers | Signature
-|-
protected abstract | **void** execute(const std\::shared_ptr<command_parameters>& params)

Executes the command.

# class template basic_command_interface specializations

## typedef command_interface

The **command_interface** is a type definition for commands name using **std::string**
and **std::recursive_mutex** types.

It is defined as:

```c++
typedef basic_command_interface<std::string, std::recursive_mutex> command_interface;
```

## typedef wcommand_interface

The **wcommand_interface** is a type definition for commands name using **std::wstring**
and **std::recursive_mutex** types.

It is defined as:

```c++
typedef basic_command_interface<std::wstring, std::recursive_mutex> wcommand_interface;
```
