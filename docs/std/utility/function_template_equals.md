---
layout: std_lib_utility
---

```c++
namespace go::utility::string
```

# function template equals

```c++
<go/utility/string/algorithm.hpp>
```

The **equals** function is used to compare strings.

It is declared as:

```c++
template<class S>
bool equals(const S& s1, const S& s2);
```

## Template parameters

Parameter | Description
-|-
S|The string class

## Parameters

Parameter | Description
-|-
container|The container
s1|First string
s2|Second string

## Return value

**true** if and only if the strings are equal, **false** otherwise.
