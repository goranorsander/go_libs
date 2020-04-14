---
layout: std_lib_string_encoding
---

```c++
namespace go::string
```

# function template reduce_to_windows_1252

```c++
<go/string/encoding/windows_1252.hpp>
```

The **reduce_to_windows_1252** function is used to reduce a string to only
containing 8-bit windows-1252 characters by removing any non-8-bit windows-1252 character.

It is declared as:

```c++
template<class S>
S& reduce_to_windows_1252(S& s);
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
