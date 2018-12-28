---
layout: std_lib_diagnostics_log
---

```c++
namespace go::diagnostics::log
```

# function timestamp_now

```c++
<go/diagnostics/log/thread_id.hpp>
```

The **timestamp_now** function returns the current time as a timestamp.

It is declared as:

```c++
typedef std::chrono::microseconds::rep timestamp_type;

timestamp_type timestamp_now();
```

## Return value

The thread id.

# function format_timestamp

```c++
<go/diagnostics/log/thread_id.hpp>
```

The **format_timestamp** will format the **timestamp** parameter as a string
and insert it into the **os** stream parameter.

It is declared as:

```c++
typedef std::chrono::microseconds::rep timestamp_type;

void format_timestamp(std::ostream& os, const timestamp_type timestamp);
void format_timestamp(std::wostream& os, const timestamp_type timestamp);
```
