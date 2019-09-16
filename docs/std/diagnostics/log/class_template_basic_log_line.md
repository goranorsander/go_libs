---
layout: std_lib_diagnostics_log
---

```c++
namespace go::diagnostics::log
```

# class template basic_log_line

```c++
<go/diagnostics/log_line.hpp>
```

The **basic_log_line** is a class that provide output stream insertion
operators for logging.

It is declared as:

```c++
template<class S, class O>
class basic_log_line
{
public:
    virtual ~basic_log_line() = default;
    basic_log_line(const log_level level, const char_type* file, const char_type* function, const uint32_t line);
    basic_log_line(basic_log_line&&) = default;
    basic_log_line& operator=(basic_log_line&&) noexcept = default;
    void stringify(out_stream_type& os);
    basic_log_line& operator<<(const std::string::value_type arg);
    basic_log_line& operator<<(const std::wstring::value_type arg);
    basic_log_line& operator<<(const int16_t arg);
    basic_log_line& operator<<(const uint16_t arg);
    basic_log_line& operator<<(const int32_t arg);
    basic_log_line& operator<<(const uint32_t arg);
    basic_log_line& operator<<(const int64_t arg);
    basic_log_line& operator<<(const uint64_t arg);
    basic_log_line& operator<<(const float arg);
    basic_log_line& operator<<(const double arg);
    basic_log_line& operator<<(const bool arg);
    basic_log_line& operator<<(const std::string& arg);
    basic_log_line& operator<<(const std::wstring& arg);
    template <std::size_t N>
    basic_log_line& operator<<(const std::string::value_type(&arg)[N]);
    template <typename Arg>
    typename std::enable_if<std::is_same<Arg, const std::string::value_type*>, basic_log_line&>::type
    operator<<(const Arg& arg);
    template <typename Arg>
    typename std::enable_if<std::is_same<Arg, std::string::value_type*>, basic_log_line&>::type
    operator<<(const Arg& arg);
    template <std::size_t N>
    basic_log_line& operator<<(const std::wstring::value_type(&arg)[N]);
    template <typename Arg>
    typename std::enable_if<std::is_same<Arg, const std::wstring::value_type*>, basic_log_line&>::type
    operator<<(const Arg& arg);
    template <typename Arg>
    typename std::enable_if<std::is_same<Arg, std::wstring::value_type*>, basic_log_line&>::type
    operator<<(const Arg& arg);
};
```

## Template parameters

Parameter | Description
-|-
S | The string class
O | The output file stream class

## Member types

Member type | Definition
-|-
string_type | S
out_stream_type | O
this_type | basic_log_line<S, O>
char_type | S\::value_type
string_literal_type | detail\::string_literal_t<char_type>
std_string_literal_type | detail\::string_literal_t<std\::string\::value_type>
std_wstring_literal_type | detail\::string_literal_t<std\::wstring\::value_type>
supported_types_type | std\::tuple<std\::tuple<std\::string\::value_type, std\::wstring\::value_type, uint16_t, uint32_t, uint64_t, int16_t, int32_t, int64_t, float, double, bool, std_string_literal_type, std_wstring_literal_type, std\::string\::value_type*, std\::wstring\::value_type*>

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_log_line** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*assign (1)* | public | basic_log_line(const log_level level, const char_type* file, const char_type* function, const uint32_t line)
*move (2)* | public | basic_log_line(basic_log_line&& other)
*copy (3)* | public | basic_log_line(const basic_log_line& other)

1. Constructs a **basic_log_line** object.
2. Constructs a **basic_log_line** object with the contents of **other** using move semantics.
3. Constructs a **basic_log_line** object with the copy of the contents of **other**.

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign move (1)* | public | basic_log_line& operator=(basic_log_line&& other) noexcept
*assign copy (2)* | public | basic_log_line& operator=(const basic_log_line& other) noexcept

1. Copies an **basic_log_line** object using move semantics.
2. Copies an **basic_log_line** object.

### stringify

Specifiers | Signature
-|-
public | void stringify(out_stream_type& os)

Converts the logged data to a string and outputs it to the stream **os**;

### Insertion operator

Specifiers | Signature
-|-
public | basic_log_line& operator<<(const std\::string\::value_type arg)
public | basic_log_line& operator<<(const std\::wstring\::value_type arg)
public | basic_log_line& operator<<(const int16_t arg)
public | basic_log_line& operator<<(const uint16_t arg)
public | basic_log_line& operator<<(const int32_t arg)
public | basic_log_line& operator<<(const uint32_t arg)
public | basic_log_line& operator<<(const int64_t arg)
public | basic_log_line& operator<<(const uint64_t arg)
public | basic_log_line& operator<<(const float arg)
public | basic_log_line& operator<<(const double arg)
public | basic_log_line& operator<<(const bool arg)
public | basic_log_line& operator<<(const std\::string& arg)
public | basic_log_line& operator<<(const std\::wstring& arg)
public | template <std\::size_t N> basic_log_line& operator<<(const std\::string\::value_type(&arg)[N])
public | template <typename Arg> typename std\::enable_if<std\::is_same<Arg, const std\::string\::value_type*>, basic_log_line&>\::type operator<<(const Arg& arg)
public | template <typename Arg> typename std\::enable_if<std\::is_same<Arg, std\::string\::value_type*>, basic_log_line&>\::type operator<<(const Arg& arg)
public | template <std\::size_t N> basic_log_line& operator<<(const std\::wstring\::value_type(&arg)[N])
public | template <typename Arg> typename std\::enable_if<std\::is_same<Arg, const std\::wstring\::value_type*>, basic_log_line&>\::type operator<<(const Arg& arg)
public | template <typename Arg> typename std\::enable_if<std\::is_same<Arg, std\::wstring\::value_type*>, basic_log_line&>\::type operator<<(const Arg& arg)

Insertion operators used for logging data.

# class template basic_log_line specializations

## class template log_line

The **log_line** is a type definition for commands name using **std::string**
and **std::ofstream** types.

It is declared as:

```c++
typedef basic_log_line<std::string, std::ostream> log_line;
```

## class template wlog_line

The **wlog_line** is a type definition for commands name using **std::wstring**
and **std::wofstream** types.

It is declared as:

```c++
typedef basic_log_line<std::wstring, std::wostream> wlog_line;
```
