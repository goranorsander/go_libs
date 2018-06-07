---
layout: std_lib_utility_string
---

```c++
namespace go::utility::string
```

# function template is_7_bit_ascii_character

```c++
<go/utility/string/ascii.hpp>
```

The **is_7_bit_ascii_character** function is used to test if a character is a
7-bit ASCII character.

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

**true** if and only if **c** have a valid 7-bit ASCII character value,
**false** otherwise.
