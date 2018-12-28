---
layout: boost_lib_diagnostics_log
---

```c++
namespace go_boost::diagnostics::log
```

# class template basic_file_writer

```c++
<go_boost/diagnostics/file_writer.hpp>
```

The **basic_file_writer** is a generalization class for properties with any value type and
name string class. It is implemented using the proxy storage policy.

It is declared as:

```c++
template <class L, class O>
class basic_file_writer
    : go_boost::utility::noncopyable_nonmovable
{
public:
    virtual ~basic_file_writer() = default;
    basic_file_writer(const string_type& log_directory, const string_type& log_file_name, boost::uint32_t log_file_roll_size_mb);
    void write(log_line_type& logline);
};
```

## Template parameters

Parameter | Description
-|-
L | The log line type
O | The output file stream class

## Member types

Member type | Definition
-|-
log_line_type | L
out_file_stream_type | O
this_type | basic_file_writer<L, O>
string_type | L\::string_type
out_stream_type | L\::out_stream_type
char_type | L\::char_type

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_file_writer** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*assign (1)* | public | basic_file_writer(const string_type& log_directory, const string_type& log_file_name, boost::uint32_t log_file_roll_size_mb)

1. Constructs a **basic_file_writer** object.

### write

Specifiers | Signature
-|-
public | void write(log_line_type& logline)

Write a log line to file.

# class template basic_file_writer specializations

## typedef file_writer

The **file_writer** is a type definition for commands name using **log_line**
and **std::ofstream** types.

It is defined as:

```c++
typedef basic_file_writer<log_line, std::ofstream> file_writer;
```

## typedef wfile_writer

The **wfile_writer** is a type definition for commands name using **wlog_line**
and **std::wofstream** types.

It is defined as:

```c++
typedef basic_file_writer<wlog_line, std::wofstream> wfile_writer;
```
