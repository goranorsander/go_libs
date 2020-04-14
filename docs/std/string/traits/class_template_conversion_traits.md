---
layout: std_lib_string_traits
---

```c++
namespace go::string::traits
```

# GO Std String Library

```c++
<go/string/traits.hpp>
```

The **conversion_traits** is a class template that is specialized for string types.

It is declared as:

```c++
template <typename S>
struct conversion_traits;
```

It is expected to implement the following static functions:

```c++
template <>
struct conversion_traits<a_string_class>
{
    using this_type = conversion_traits<a_string_class>;
    using string_type = a_string_class;

    static bool try_convert(const a_string_class& from, a_string_class& to)
    {
        to = from;
        return true;
    }

    static bool try_convert(const a_string_class& from, go::string::u8string& to)
    {
        try
        {
            to = a_string_class_to_u8string_function(from);
            return true;
        }
        catch (...) {}
        return false;
    }

    static bool try_convert(const go::string::u8string& from, a_string_class& to)
    {
        try
        {
            to = u8string_to_a_string_class_function(from);
            return true;
        }
        catch (...) {}
        return false;
    }

private:
    template <typename T1, typename T2>
    static bool try_convert(const T1&, T2&)
    {
        return false; // Make public try_convert functions explicit
    }
};
```

## Template parameters

Parameter | Description
-|-
S | The string type

## Member types

Member type | Definition
-|-
this_type | conversion_traits\<S>
string_type | S

## Member functions

### try_convert

Specifiers | Signature
-|-
public static | bool try_convert(const S& from, S& to)
public static | bool try_convert(const S& from, go::string::u8string& to)
public static | bool try_convert(const go::string::u8string& from, S& to)
private static | template <typename T1, typename T2> bool try_convert(const T1&, T2&)

Returns true if the conversion succeeded, false othetwise.
