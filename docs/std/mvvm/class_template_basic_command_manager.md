---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class template basic_command_manager

```c++
<go/mvvm.hpp>
```

**Generic command manager**

The **basic_command_manager** is a generalization class to manage commands.

It is declared as:

```c++
template<class S, typename M = std::recursive_mutex>
class basic_command_manager
    : public basic_notify_command_execution_interface<S, M>
    , public go::utility::noncopyable_nonmovable
{
public:
    virtual ~basic_command_manager();

protected:
    basic_command_manager() = default;

public:
    static ptr create();

    void execute(const std::shared_ptr<basic_command_interface<S, M>>& command) const;
    void post(const std::shared_ptr<basic_command_interface<S, M>>& command, const bool keep_command_alive = false);
    void execute_commands();

    size_t commands() const;
};
```

## Template parameters

Parameter | Description
-|-
S | The manager string class
M | The manager mutex class

## Member types

Member type | Definition
-|-
string_type | S
mutex_type | M
this_type | basic_command_manager<S, M>
ptr | std\::shared_ptr<basic_command_manager<S, M>>
wptr | std\::weak_ptr<basic_command_manager<S, M>>

## Static member functions

### create

Specifiers | Signature
-|-
public static | ptr create()

Constructs a new **basic_command_manager** object and return it as a
**basic_command_manager<string_type, mutex_type>\::ptr** object.

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
public | **void** execute(const std\::shared_ptr<basic_command_interface<S, M>>& command) const

Execute a command immediately.

### post

Specifiers | Signature
-|-
public | **void** post(const std\::shared_ptr<basic_command_interface<S, M>>& command, const bool keep_command_alive = false)

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
and **std::recursive_mutex** types.

It is defined as:

```c++
typedef basic_command_manager<std::string, std::recursive_mutex> command_manager;
```

## typedef wcommand_manager

The **wcommand_manager** is a type definition for commands name using **std::wstring**
and **std::recursive_mutex** types.

It is defined as:

```c++
typedef basic_command_manager<std::wstring, std::recursive_mutex> wcommand_interface;
```
