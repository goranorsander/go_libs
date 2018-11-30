---
layout: boost_lib_signals
---

```c++
namespace go_boost::signals
```

# class template signal

```c++
<go_boost/signals/signal.hpp>
```

**Generic signal class**

The **signal** is a generalization class for signals. It is inspired by the 
Boost.Signals2 library and try to adopt the same terminology. A signal 
represent a callback with multiple targets. Signals are connected to some set 
of slots, which are callback receivers. The slots are called when the signal 
is *"emitted"*.

It is declared as:

```c++
template<typename F, class L = boost::recursive_mutex> class signal
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
L | The mutex type

## Member types

Member type | Definition
-|-
function_type | F
lockable_type | L
this_type | **signal**<function_type, lockable_type>

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

1. Constructs a **signal** object.

### connect

Specifiers | Signature
-|-
public | template\<typename F1> slot_key_type **connect**(F1&& f)

Connect a slot, i.e. a callback receiver, to a **signal**.

### disconnect

Specifiers | Signature
-|-
public | void **disconnect**(const slot_key_type slot_key)

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
