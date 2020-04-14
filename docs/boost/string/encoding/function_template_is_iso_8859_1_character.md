---
layout: boost_lib_string_encoding
---

```c++
namespace go_boost::string
```

# function template is_iso_8859_1_character

```c++
<go_boost/string/encoding/iso_8859_1.hpp>
```

The **is_iso_8859_1_character** function is used to test if a character is a
8-bit ISO 8859-1 character.

It is declared as:

```c++
template<typename C>
bool is_iso_8859_1_character(const C c);
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

**true** if and only if **c** have a valid 8-bit ISO 8859-1 character value,
**false** otherwise.
