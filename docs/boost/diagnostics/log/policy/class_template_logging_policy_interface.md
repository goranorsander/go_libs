---
layout: boost_lib_diagnostics_log_policy
---

```c++
namespace go_boost::diagnostics::log::policy
```

# class template logging_policy_interface

```c++
<go_boost/diagnostics/file_writer.hpp>
```

The **logging_policy_interface** is a logging policy interface class.

It is declared as:

```c++
template <class W>
class logging_policy_interface
{
public:
    virtual ~logging_policy_interface() = 0;

protected:
    virtual buffer_interface_pointer create_buffer() const = 0;

    friend class go_boost::diagnostics::log::detail::basic_logger<W>;
};
```

## Template parameters

Parameter | Description
-|-
W | The file writer class

## Member types

Member type | Definition
-|-
file_writer_type | W
this_type | logging_policy_interface<W>
log_line_type | W\::log_line_type
out_file_stream_type | W\::out_file_stream_type
string_type | W\::string_type
out_stream_type | W\::out_stream_type
char_type | W\::char_type
buffer_interface_pointer | go_boost\::diagnostics\::log\::detail\::buffer_interface<log_line_type>*

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **logging_policy_interface** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default (1)* | protected | logging_policy_interface()

1. Constructs a **logging_policy_interface** object.

### create_buffer

Specifiers | Signature
-|-
protected abstract | buffer_interface_pointer create_buffer() const

Create a buffer for log lines.
