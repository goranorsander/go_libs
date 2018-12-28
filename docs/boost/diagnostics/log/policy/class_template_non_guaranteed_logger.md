---
layout: boost_lib_diagnostics_log_policy
---

```c++
namespace go_boost::diagnostics::log::policy
```

# class template non_guaranteed_logger

```c++
<go_boost/diagnostics/file_writer.hpp>
```

The **non_guaranteed_logger** is a logging policy implementation class
without guarantee log lines will not be dropped. It uses a ring buffer
to hold log lines. When the ring gets full, the previous log line in the
slot will be dropped.

It is declared as:

```c++
template <class W>
class non_guaranteed_logger
    : public logging_policy_interface<W>
{
public:
    virtual ~non_guaranteed_logger() = default;
    non_guaranteed_logger(const boost::uint32_t ring_buffer_size_mb);
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
this_type | non_guaranteed_logger<W>
log_line_type | W\::log_line_type
out_file_stream_type | W\::out_file_stream_type
string_type | W\::string_type
out_stream_type | W\::out_stream_type
char_type | W\::char_type
buffer_interface_pointer | logging_policy_interface<file_writer_type>\::buffer_interface_pointer

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **non_guaranteed_logger** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*assign (1)* | public explicit | non_guaranteed_logger(const boost::uint32_t ring_buffer_size_mb)

1. Constructs a **non_guaranteed_logger** object with a specified buffer size.
