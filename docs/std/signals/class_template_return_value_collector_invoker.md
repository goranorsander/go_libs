---
layout: std_lib_signals
---

```c++
namespace go::signals
```

# class template return_value_collector_invoker

```c++
<go/signals/return_value_collector_invoker.hpp>
```

**Generic return_value_collector_invoker class**

The **return_value_collector_invoker** is a class to emit signals
and collect return values.

It is declared as:

```c++
template<class Collector, class ReturnValueType, class... Args>
struct return_value_collector_invoker<Collector, ReturnValueType (Args...)>
{
    virtual ~return_value_collector_invoker() = default;
    return_value_collector_invoker() = default;

    bool invoke(Collector& collector, const std::function<ReturnValueType (Args...)>& signal_callback_function, Args... args) const;
};

template<class Collector, class... Args>
struct return_value_collector_invoker<Collector, void (Args...)>
{
    virtual ~return_value_collector_invoker() = default;
    return_value_collector_invoker() = default;

    bool invoke(Collector& collector, const std::function<void (Args...)>& signal_callback_function, Args... args) const;
};
```

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **return_value_collector_invoker** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | public | **return_value_collector_invoker**()

1. Constructs a **return_value_collector_invoker** object.

### invoke

Specifiers | Signature
-|-
public | bool **invoke**(Collector& collector, const std::function<ReturnValueType (Args...)>& signal_callback_function, Args... args) const
public | bool **invoke**(Collector& collector, const std::function<void (Args...)>& signal_callback_function, Args... args) const

Function that invoke a signal call back and collect return values.
