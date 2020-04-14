---
layout: std_lib_string_encoding
---

```c++
namespace go::string
```

# function template is_7_bit_ascii_character

```c++
<go/string/encoding/iso_8859_1.hpp>
```

The **is_7_bit_ascii_character** function is used to test if a character is a
8-bit ISO 8859-1 character.

It is declared as:

```c++
template<typename C>
bool is_7_bit_ascii_character(const C c);
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
