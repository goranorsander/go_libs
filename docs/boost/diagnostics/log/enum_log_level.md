---
layout: boost_lib_diagnostics_log
---

```c++
namespace go_boost::diagnostics::log
```

# enum log_level

```c++
<go_boost/diagnostics/log_level.hpp>
```

The **log_level** enumeration is used to identify log levels.

It is declared as:

```c++
enum log_level
{
    log_level_none = 0,
    log_level_fatal = 1,
    log_level_error = 2,
    log_level_warning = 3,
    log_level_info = 4,
    log_level_debug = 5,
    log_level_trace = 6,
    log_level_all = 7,
    log_level_undefined = ~0
};
```

## Enumerators

Enumerator | Description
-|-
log_level_none | No logging, only intended to be used to configure the application log level at runtime
log_level_fatal | Any error that is forcing a shutdown of the service or application to prevent data loss (or further data loss)
log_level_error | Any error which is fatal to the operation, but not the service or application
log_level_warning | Anything that can potentially cause application oddities, but from which it is automatically recovering
log_level_info | Generally useful information
log_level_debug | Information that is diagnostically helpful to developers and system administrators
log_level_trace | More detailed information than **log_level_debug** intended for developers
log_level_all | Log everything, only intended to be used to configure the application log level at runtime
log_level_undefined | Undefined

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
