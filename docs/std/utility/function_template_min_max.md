---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# function template max_of

```c++
<go/utility/min_max.hpp>
```

The **max_of** function is workaround to avoid problems caused by
a macro definition of **max** in *windef.h* when the recommended
solution, to define **NOMINMAX**, is not usable.

It is declared as:

```c++
template <typename T>
constexpr const T& max_of(const T& lhs, const T& rhs);
```

## Template parameters

Parameter | Description
-|-
T|The type to compare

## Parameters

Parameter | Description
-|-
lhs|The *left hand side* value being compared
rhs|The *right hand side* value being compared

## Return value

The greater of lhs and rhs.

# function template min_of

```c++
<go/utility/min_max.hpp>
```

The **min_of** function is workaround to avoid problems caused by
a macro definition of **min** in *windef.h* when the recommended
solution, to define **NOMINMAX**, is not usable.

It is declared as:

```c++
template <typename T>
constexpr const T& min_of(const T& lhs, const T& rhs);
```

## Template parameters

Parameter | Description
-|-
T|The type to compare

## Parameters

Parameter | Description
-|-
lhs|The *left hand side* value being compared
rhs|The *right hand side* value being compared

## Return value

The smaller of lhs and rhs.
