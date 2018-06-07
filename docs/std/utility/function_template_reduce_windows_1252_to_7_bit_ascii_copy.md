---
layout: std_lib_utility
---

```c++
namespace go::utility::string
```

# function template reduce_windows_1252_to_7_bit_ascii_copy

```c++
<go/utility/string/ascii.hpp>
```

The **reduce_windows_1252_to_7_bit_ascii_copy** function is used to reduce a
string to only containing 7-bit ASCII characters by removing any non-7-bit
ASCII character.

It is declared as:

```c++
template<class S>
S reduce_windows_1252_to_7_bit_ascii_copy(const S& s, const bool strict = true);
```

## Template parameters

Parameter | Description
-|-
S|The string class

## Parameters

Parameter | Description
-|-
container|The container
s|The string to be reduced
strict|Use strict or imaginative reduction

## Return value

A reduced copy of the string.
