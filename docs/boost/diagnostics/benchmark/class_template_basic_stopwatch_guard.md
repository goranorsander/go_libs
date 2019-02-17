---
layout: boost_lib_diagnostics_benchmark
---

```c++
namespace go_boost::diagnostics::benchmark
```

# class template basic_stopwatch_guard

```c++
<go_boost/diagnostics/stopwatch_guard.hpp>
```

The **basic_stopwatch_guard** is a class template that start the associated
**basic_stopwatch** object on creation and stop it on destruction, typically
on scope exit.

It is declared as:

```c++
template<class S> class basic_stopwatch_guard
    : public go_boost::utility::scope_guard
{
public:
    virtual ~basic_stopwatch_guard() = default;
    explicit basic_stopwatch_guard(stopwatch_type& stopwatch)
};
```

## Template parameters

Parameter | Description
-|-
S | The stopwatch class

## Member types

Member type | Definition
-|-
stopwatch_type | S
this_type | basic_stopwatch_guard<S>
base_type | go_boost\::utility\::scope_guard

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_stopwatch_guard** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*assign (1)* | public explicit | basic_stopwatch_guard(stopwatch_type& stopwatch)

1. Constructs a **basic_stopwatch_guard** object.

# class template basic_stopwatch_guard specializations

## class template stopwatch_guard

The **stopwatch_guard** is a type definition for guarding a **stopwatch** object.

It is declared as:

```c++
typedef basic_stopwatch_guard<stopwatch> stopwatch_guard;
```
