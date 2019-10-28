---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class template basic_command_manager

```c++
<go_boost/mvvm.hpp>
```

**Generic command manager**

The **basic_command_manager** is a generalization class to manage commands.

It is declared as:

```c++
template<class S, class L = boost::recursive_mutex>
class basic_command_manager
    : public basic_notify_command_execution_interface<S, L>
    , public go_boost::type_traits::noncopyable_nonmovable
{
public:
    virtual ~basic_command_manager();

protected:
    basic_command_manager();

public:
    static ptr create();

    void execute(const boost::shared_ptr<basic_command_interface<S, L>>& command) const;
    void post(const boost::shared_ptr<basic_command_interface<S, L>>& command, const bool keep_command_alive = false);
    void execute_commands();

    size_t commands() const;
};
```

## Template parameters

Parameter | Description
-|-
S | The manager string class
L | The manager lockable class

## Member types

Member type | Definition
-|-
string_type | S
lockable_type | L
this_type | basic_command_manager<S, L>
ptr | boost\::shared_ptr<basic_command_manager<S, L>>
wptr | boost\::weak_ptr<basic_command_manager<S, L>>

## Static member functions

### create

Specifiers | Signature
-|-
public static | ptr create()

Constructs a new **basic_command_manager** object and return it as a
**basic_command_manager<string_type, lockable_type>\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_command_manager** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*constructor (1)* | protected | **basic_command_manager**()

1. Constructs a **basic_command_manager** object.

### execute

Specifiers | Signature
-|-
public | **void** execute(const boost\::shared_ptr<basic_command_interface<S, L>>& command) const

Execute a command immediately.

### post

Specifiers | Signature
-|-
public | **void** post(const boost\::shared_ptr<basic_command_interface<S, L>>& command, const bool keep_command_alive = false)

Post a command to be executed later on.

### execute_commands

Specifiers | Signature
-|-
public | **void** execute_commands()

Execute all posted commands.

### commands

Specifiers | Signature
-|-
public | size_t commands() const

Return the number of posted commands waiting to be executed.

# class template basic_command_manager specializations

## typedef command_manager

The **command_manager** is a type definition for commands name using **std::string**
and **boost::recursive_mutex** types.

It is defined as:

```c++
typedef basic_command_manager<std::string, boost::recursive_mutex> command_manager;
```

## typedef wcommand_manager

The **wcommand_manager** is a type definition for commands name using **std::wstring**
and **boost::recursive_mutex** types.

It is defined as:

```c++
typedef basic_command_manager<std::wstring, boost::recursive_mutex> wcommand_interface;
```
