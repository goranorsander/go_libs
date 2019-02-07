---
layout: std_lib_signals
---

```c++
namespace go::signals
```

# class template return_last_signal_collector

```c++
<go/signals/return_last_signal_collector.hpp>
```

**Generic return_last_signal_collector class**

The **return_last_signal_collector** is a **signal** return value
collector that will return the value from the last slot emitted.

It is declared as:

```c++
template<typename ReturnValueType>
struct return_last_signal_collector
{
    virtual ~return_last_signal_collector() = default;
    return_last_signal_collector() = default;

    bool operator()(signal_return_value_type r);
    signal_return_value_type return_value() const;
};
```

## Template parameters

Parameter | Description
-|-
ReturnValueType | The return value type

## Member types

Member type | Definition
-|-
signal_return_value_type | ReturnValueType

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **return_last_signal_collector** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | public | **return_last_signal_collector**()

1. Constructs a **return_last_signal_collector** object.

### Set value operator

Specifiers | Signature
-|-
public | void operator()(const **signal_return_value_type**& other)

Operator that assign the return value of the
**return_last_signal_collector** object.

### return_value

Specifiers | Signature
-|-
public | signal_return_value_type **return_value**() const

Function that return the return value collected by the
**return_last_signal_collector** object.
