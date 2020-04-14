---
layout: boost_lib_string_encoding
---

```c++
namespace go_boost::string
```

# function template is_windows_1252_character

```c++
<go_boost/string/encoding/windows_1252.hpp>
```

The **is_windows_1252_character** function is used to test if a character is a
8-bit windows-1252 character.

It is declared as:

```c++
template<typename C>
bool is_windows_1252_character(const C c);
```

## Template parameters

Parameter | Description
-|-
C|The character type

## Parameters

Parameter | Description
-|-
container|The container
c|The character to test

## Return value

**true** if and only if **c** have a valid 8-bit windows-1252 character value,
**false** otherwise.
