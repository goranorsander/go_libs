---
layout: std_lib_diagnostics_log_policy
---

```c++
namespace go::diagnostics::log::policy
```

# class template guaranteed_logger

```c++
<go/diagnostics/file_writer.hpp>
```

The **guaranteed_logger** is a logging policy implementation class
that guarantee log lines will not be dropped.

It is declared as:

```c++
template <class W>
class guaranteed_logger
    : public logging_policy_interface<W>
{
public:
    virtual ~guaranteed_logger() = default;
    guaranteed_logger() = default;
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
this_type | guaranteed_logger<W>
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

Destroys the **guaranteed_logger** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default (1)* | public | guaranteed_logger()

1. Constructs a **guaranteed_logger** object.
