---
layout: boost_lib_string_encoding
---

```c++
namespace go_boost::string
```

# function template reduce_to_windows_1252_copy

```c++
<go_boost/string/encoding/windows_1252.hpp>
```

The **reduce_to_windows_1252_copy** function is used to reduce a string to only
containing 8-bit windows-1252 characters by removing any non-8-bit windows-1252 character.

It is declared as:

```c++
template<class S>
S reduce_to_windows_1252_copy(const S& s);
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
