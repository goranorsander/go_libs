---
layout: std_lib_utility_string
---

```c++
namespace go::string
```

# function template create

```c++
<go/string/create.hpp>
```

The **create** function is used to create string objects with the contents
initialized with a copy of the null-terminated character string pointed to
by sz. The following string classes are supported:

Class|Expected encoding
-|-
std\::string|ASCII, ISO/IEC 8859-1, or Windows 1252
std\::wstring|UCS-2 or UCS-4
std\::u16string|UTF-16
std\::u32string|UTF-32
go\::utility\::u2string|UCS-2
go\::utility\::u8string|UTF-8

The **create** function will try to encode the string using the expected
encoding for the destination string class.

It is declared as:

```c++
template<class to_string, typename from_char_t>
to_string create(const from_char_t* sz);
```

## Template parameters

Parameter | Description
-|-
to_string|The string class to convert to
from_char_t|The character type to convert from, usually implicit

## Parameters

Parameter | Description
-|-
sz|The null-terminated character string being copied to the created string object

## Return value

A string object of the **to_string** class.
