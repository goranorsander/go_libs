---
layout: std_lib_signals
---

```c++
namespace go::signals
```

# class template default_collector

```c++
<go/signals/default_collector.hpp>
```

**Generic default_collector class**

The **default_collector** is the **signal** default return
value collector.

It is declared as:

```c++
template<typename ReturnValueType>
struct default_collector
    : return_last_signal_collector<ReturnValueType>
{
    virtual ~default_collector() = default;
    default_collector() = default;
};
```

## Template parameters

Parameter | Description
-|-
ReturnValueType | The return value type

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **default_collector** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | public | **default_collector**()

1. Constructs a **default_collector** object.
