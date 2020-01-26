---
layout: boost_lib_utility_string
---

```c++
namespace go_boost::string
```

# function template reduce_to_7_bit_ascii_copy

```c++
<go_boost/string/ascii.hpp>
```

The **reduce_to_7_bit_ascii_copy** function is used to reduce a string to only
containing 7-bit ASCII characters by removing any non-7-bit ASCII character.

It is declared as:

```c++
template<class S>
S reduce_to_7_bit_ascii_copy(const S& s);
```

## Template parameters

Parameter | Description
-|-
S|The string class

## Parameters

Parameter | Description
-|-
s|The string to be reduced

## Return value

A reduced copy of the string.
