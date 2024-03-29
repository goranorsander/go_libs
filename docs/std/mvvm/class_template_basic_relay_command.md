---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class template basic_relay_command

```c++
<go/mvvm.hpp>
```

**Generic relay command**

The **basic_relay_command** is a class for relay commands. A relay command is
command objects through which the view can call methods.

It is declared as:

```c++
template<class S, class L = std::recursive_mutex>
class basic_relay_command
    : public basic_command_interface<S, L>
{
public:
    virtual ~basic_relay_command() = default;

protected:
    basic_relay_command(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params);

public:
    static std::shared_ptr<basic_relay_command<S, L>> create(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params);

protected:
    virtual bool can_execute(const command_parameters_type& params);
    virtual void execute(const command_parameters_type& params);
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
this_type | basic_relay_command<S, L>
ptr | std\::shared_ptr<basic_relay_command<S, L>>
wptr | std\::weak_ptr<basic_relay_command<S, L>>
command_parameters_type | std\::shared_ptr<command_parameters>
can_execute_command_signature | std\::function<bool(const command_parameters_type&)>
execute_command_signature | std\::function<void(const command_parameters_type&)>

## Inherited properties

Property type | Property name
-|-
command_name_type | command_name

### Property command_name

Gets the name of the command.

## Inherited signals

Signal | Description
-|-
can_execute_changed | Emitted when the *can execute* state have changed.

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **basic_relay_command** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*constructor (1)* | protected | **basic_relay_command**(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters_type& params)

1. Constructs a **basic_relay_command** object with a name, *can execute* call back, *execute* call back, and parameters.

### can_execute

Specifiers | Signature
-|-
public virtual | bool **can_execute**(const command_parameters_type& params)

Returns **true** if the associated command can be executed.

### execute

Specifiers | Signature
-|-
public virtual | void **execute**(const command_parameters_type& params)

Executes the associated command.

## Inherited functions

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

# class template basic_relay_command specializations

## typedef command_interface

The **command_interface** is a type definition for commands name using **std::string**
and **std::recursive_mutex** types.

It is defined as:

```c++
typedef basic_relay_command<std::string, std::recursive_mutex> relay_command;
```

## typedef wcommand_interface

The **wcommand_interface** is a type definition for commands name using **std::wstring**
and **std::recursive_mutex** types.

It is defined as:

```c++
typedef basic_relay_command<std::wstring, std::recursive_mutex> relay_wcommand;
```
