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
template<typename F, typename M = std::recursive_mutex> class signal
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
M | The mutex type

## Member types

Member type | Definition
-|-
function_type | F
mutex_type | M
this_type | **signal**<function_type, mutex_type>

## Member functions

### (destructor)

*public virtual member function*

Destroys the **signal** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*default constructor (1)* | **signal**()

1. Constructs a **signal** object.

### template\<typename F1> slot_key_type connect(F1&& f)

*public member function*

Connect a slot, i.e. a callback receiver, to a **signal**.

### void disconnect(const slot_key_type slot_key)

*public member function*

Disconnect a slot, i.e. a callback receiver, from a **signal**.

### void disconnect_all_slots()

*public member function*

Disconnect all slots, i.e. a callback receivers, from a **signal**.

### bool empty() const

*public member function*

Returns **true** if the **signal** have no connected slots, i.e. callback 
receivers.

### template\<typename... A> void operator()(A... a) const

*public member function*

Emits a **signal** to all connected slots, i.e. all callback receivers.

### template\<typename... A> void call(A... a) const

*public member function*

Emits a **signal** to all connected slots, i.e. all callback receivers.
