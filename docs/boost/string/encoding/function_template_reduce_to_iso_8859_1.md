---
layout: boost_lib_string_encoding
---

```c++
namespace go_boost::string
```

# function template reduce_to_iso_8859_1

```c++
<go_boost/string/encoding/iso_8859_1.hpp>
```

The **reduce_to_iso_8859_1** function is used to reduce a string to only
containing 8-bit ISO 8859-1 characters by removing any non-8-bit ISO 8859-1 character.

It is declared as:

```c++
template<class S>
S& reduce_to_iso_8859_1(S& s);
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
