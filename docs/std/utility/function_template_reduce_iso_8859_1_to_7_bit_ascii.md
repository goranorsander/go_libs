---
layout: std_lib_utility
---

```c++
namespace go::utility::string
```

# function template reduce_iso_8859_1_to_7_bit_ascii

```c++
<go/utility/string/ascii.hpp>
```

The **reduce_iso_8859_1_to_7_bit_ascii** function is used to reduce a string
to only containing 7-bit ASCII characters by removing any non-7-bit ASCII
character.

It is declared as:

```c++
template<class S>
S& reduce_iso_8859_1_to_7_bit_ascii(S& s, const bool strict = true);
```

## Template parameters

Parameter | Description
-|-
S|The string class

## Parameters

Parameter | Description
-|-
s|The string to be reduced
strict|Use strict or imaginative reduction

## Return value

A reference to the reduced string.
