---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# function template exchange

```c++
<go/utility/exchange.hpp>
```

The **exchange** function is workaround that add **std::exchange**
functionality to C\++11 (**std::exchange** was added to C\++14).

It is declared as:

```c++
template<class T, class U = T>
T exchange(T& obj, U&& new_value);
```

## Template parameters

Parameter | Description
-|-
T|The type to exchange to
U|The type to exchange from

## Parameters

Parameter | Description
-|-
obj|Object whose value to replace
new_value|The value to assign to **obj**

## Return value

The old value of **obj**.
