---
layout: std_lib_utility_range
---

```c++
namespace go::utility::range
```

# class template sequentially_increasing

```c++
<go/utility/range/sequentially_increasing.hpp>
```

The **sequentially_increasing** class template is intended to be used together
with **std::generate** to initialize a range with sequentially increasing values.

It is declared as:

```c++
template<class T> class sequentially_increasing
{
public:
    virtual ~sequentially_increasing();
    sequentially_increasing(const value_type& start_at, const value_type& increment);

    value_type operator()();
};
```

## Template parameters

Parameter | Description
-|-
T | The value type

## Member types

Member type | Definition
-|-
this_type | sequentially_increasing\<T>
value_type | T

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **sequentially_increasing** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*constructor (1)* | public | **sequentially_increasing**(const value_type& start_at, const value_type& increment)

1. Constructs a **sequentially_increasing**.

### Get value operator

Specifiers | Signature
-|-
public | **value_type** operator()() const

Function call operator that return the next value of the **sequentially_increasing** object.
