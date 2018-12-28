---
layout: std_lib_diagnostics_log
---

```c++
namespace go::diagnostics::log
```

# enum log_level

```c++
<go_boost/diagnostics/log_level.hpp>
```

The **log_level** enumeration is used to identify log levels.

It is declared as:

```c++
enum class log_level
    : int8_t
{
    none = 0,
    fatal = 1,
    error = 2,
    warning = 3,
    info = 4,
    debug = 5,
    trace = 6,
    all = 7,
    undefined = ~0
};
```

## Enumerators

Enumerator | Description
-|-
log_level::none | No logging, only intended to be used to configure the application log level at runtime
log_level::fatal | Any error that is forcing a shutdown of the service or application to prevent data loss (or further data loss)
log_level::error | Any error which is fatal to the operation, but not the service or application
log_level::warning | Anything that can potentially cause application oddities, but from which it is automatically recovering
log_level::info | Generally useful information
log_level::debug | Information that is diagnostically helpful to developers and system administrators
log_level::trace | More detailed information than **log_level::debug** intended for developers
log_level::all | Log everything, only intended to be used to configure the application log level at runtime
log_level::undefined | Undefined

# function to_string

The **to_string** function returns a string representation for a
given log level.

It is declared as:

```c++
std::string::value_type* to_string(const log_level& loglevel);
```

## Parameters

Parameter | Description
-|-
loglevel|The *log level*

## Return value

The string representation.

# function to_wstring

The **to_wstring** function returns a string representation for a
given log level.

It is declared as:

```c++
std::wstring::value_type* to_wstring(const log_level& loglevel);
```

## Parameters

Parameter | Description
-|-
loglevel|The *log level*

## Return value

The string representation.
