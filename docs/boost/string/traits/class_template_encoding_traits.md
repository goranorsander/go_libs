---
layout: boost_lib_string_traits
---

```c++
namespace go_boost::string::traits
```

# GO Boost String Library

```c++
<go_boost/string/traits.hpp>
```

The **encoding_traits** is a class template that is specialized for string types.

It is declared as:

```c++
template <typename S>
struct encoding_traits;
```

It is expected to be implemented as follows:

```c++
template <>
struct encoding_traits<a_string_class>
{
    using this_type = encoding_traits<a_string_class>;
    using string_type = a_string_class;
    using char_type = typename a_string_class::value_type;
    using encoding = an_encoding_tag;
};
```

## Template parameters

Parameter | Description
-|-
S | The string type

## Member types

Member type | Definition
-|-
this_type | encoding_traits\<S>
string_type | S
char_type | The character type
encoding | The encoding tag
