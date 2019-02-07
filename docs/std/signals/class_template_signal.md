---
layout: std_lib_signals
---

```c++
namespace go::signals
```

# class template signal

```c++
<go/signals/signal.hpp>
```

**Generic signal class**

The **signal** is a generalization class for signals. It is inspired by the 
Boost.Signals2 library and try to adopt the same terminology. A signal 
represent a callback with multiple targets. Signals are connected to some set 
of slots, which are callback receivers. The slots are called when the signal 
is *"emitted"*.

It is declared as:

```c++
template<typename F, class L = std::recursive_mutex> class signal
{
public:
    virtual ~signal();
    signal();
    template<typename F1> slot_key connect(F1&& f);
    void disconnect(const slot_key& s);
    void disconnect_all_slots();
    bool empty() const;
    template<typename... A> void operator()(A... a) const;
    template<typename... A> void call(A... a) const;
};
```

## Template parameters

Parameter | Description
-|-
F | The function type
C | The collector type
L | The lockable type

## Member types

Member type | Definition
-|-
collector_type | C
lockable_type | L
this_type | **signal**<function_type, lockable_type>
base_type | **slots**<F, C>
function_type | base_type\::signal_function_type
return_value_type | base_type\::signal_function_type\::result_type

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **signal** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | public | **signal**()
*constructor (2)* | public | **signal**(const function_type& signal_function)

1. Constructs a **signal** object.
2. Constructs a **signal** object and connects a function.

### connect

Specifiers | Signature
-|-
public | slot_key **connect**(const function_type& signal_function)

Connect a slot, i.e. a callback receiver, to a **signal**.

### disconnect

Specifiers | Signature
-|-
public | void **disconnect**(const slot_key& key)

Disconnect a slot, i.e. a callback receiver, from a **signal**.

### disconnect_all_slots

Specifiers | Signature
-|-
public | void **disconnect_all_slots**()

Disconnect all slots, i.e. a callback receivers, from a **signal**.

### empty

Specifiers | Signature
-|-
public | bool **empty**() const

Returns **true** if the **signal** have no connected slots, i.e. callback 
receivers.

### size

Specifiers | Signature
-|-
public | std\::size_t **size**() const

Returns the number of connected slots.

### Emit signal operator

Specifiers | Signature
-|-
public | template\<typename... A> void operator()(A... a) const

Emits a **signal** to all connected slots, i.e. all callback receivers.

### call

Specifiers | Signature
-|-
public | template\<typename... A> void call(A... a) const

Emits a **signal** to all connected slots, i.e. all callback receivers.
