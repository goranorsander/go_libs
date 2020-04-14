---
layout: std_lib_string_encoding
---

```c++
namespace go::string
```

# function template reduce_to_7_bit_ascii

```c++
<go/string/encoding/ascii.hpp>
```

The **reduce_to_7_bit_ascii** function is used to reduce a string to only
containing 7-bit ASCII characters by removing any non-7-bit ASCII character.

It is declared as:

```c++
template<class S>
S& reduce_to_7_bit_ascii(S& s);
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

A reference to the reduced string.
