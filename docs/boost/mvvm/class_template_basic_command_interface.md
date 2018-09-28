---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class template basic_command_interface

```c++
<go_boost/mvvm.hpp>
```

**Generic command interface**

The **basic_command_interface** is a generalization class for commands. A command
is a request for some action to be taken. The command shall preferably hold all
information necessary to perform the action.

It is declared as:

```c++
template<class S, typename M = boost::recursive_mutex>
class basic_command_interface
    : public boost::enable_shared_from_this<basic_command_interface<S, M>>
    , public go_boost::utility::noncopyable_nonmovable
{
public:
    virtual ~basic_command_interface() = 0;

protected:
    basic_command_interface(const S& cmd_name, const boost::shared_ptr<command_parameters>& params);

public:
    virtual boost::shared_ptr<command_parameters> parameters() const;
    virtual void notify_can_execute_changed();

protected:
    virtual bool can_execute(const boost::shared_ptr<command_parameters>& params) = 0;
    virtual void execute(const boost::shared_ptr<command_parameters>& params) = 0;

public:
    command_name_type command_name;
    can_execute_changed_signal can_execute_changed;
};
```

## Template parameters

Parameter | Description
-|-
S | The command string class
M | The command mutex class

## Member types

Member type | Definition
-|-
string_type | S
mutex_type | M
this_type | basic_command_interface<S, M>
ptr | boost\::shared_ptr<basic_command_interface<S, M>>
wptr | boost\::weak_ptr<basic_command_interface<S, M>>
command_parameters_type | boost\::shared_ptr<command_parameters>
can_execute_changed_signal | go_boost\::signals\::signal<boost\::function<void(const boost\::shared_ptr<basic_command_interface<S, M>>&)>>
command_name_type | go_boost\::property\::nameless\::read_only\::property<S>

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
*constructor (1)* | protected | **basic_command_interface**(const S& cmd_name, const boost::shared_ptr<command_parameters>& params)

1. Constructs a **basic_command_interface** object with a name and parameters.

### parameters

Specifiers | Signature
-|-
public virtual | boost\::shared_ptr<command_parameters> parameters() const

Returns the command parameters.

### notify_can_execute_changed

Specifiers | Signature
-|-
public virtual | **void** notify_can_execute_changed()

Emits the **can_execute_changed** signal.

### can_execute

Specifiers | Signature
-|-
protected abstract | **bool** can_execute(const boost\::shared_ptr<command_parameters>& params)

Returns **true** it the command can be executed, **false** otherwise.

### execute

Specifiers | Signature
-|-
protected abstract | **void** execute(const boost\::shared_ptr<command_parameters>& params)

Executes the command.

# class template basic_command_interface specializations

## typedef command_interface

The **command_interface** is a type definition for commands name using **std::string**
and **boost::recursive_mutex** types.

It is defined as:

```c++
typedef basic_command_interface<std::string, boost::recursive_mutex> command_interface;
```

## typedef wcommand_interface

The **wcommand_interface** is a type definition for commands name using **std::wstring**
and **boost::recursive_mutex** types.

It is defined as:

```c++
typedef basic_command_interface<std::wstring, boost::recursive_mutex> wcommand_interface;
```
