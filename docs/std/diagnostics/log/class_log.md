---
layout: std_lib_diagnostics_log
---

```c++
namespace go::diagnostics::log
```

# class log

```c++
<go/diagnostics/log.hpp>
```

The **log** class provide the logging function.

It is declared as:

```c++
class log
    : go::utility::noncopyable_nonmovable
{
public:
    virtual ~log() = default;
    log() = default;
    bool operator==(log_line& logline);
    static detail::logger_atm& logger_atom();
    static detail::logger_ptr& logger_instance();
    static std::atomic<unsigned int>& log_level();
};
```

## Static member functions

### logger_atom

Specifiers | Signature
-|-
public static | detail::logger_atm& **logger_atom**()

Returns a reference to the *logger atom* used for thread synchronization.

### logger_instance

Specifiers | Signature
-|-
public static | detail::logger_ptr& **logger_instance**()

Returns a reference to the *logger* instance.

### log_level

Specifiers | Signature
-|-
public static | std\::atomic\<unsigned int\>& **log_level**()

Returns a reference to the atomic *log level*.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **log** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | public | **log**()

1. Constructs a **log** object.

### Equality operator

Operator | Specifiers | Signature
-|-
*log line (1)* | public | bool operator==(**log_line**& logline)

1. Using (possibly abusing) the equality operator to do compound assignment of log line.

## Macros

For convenience a set of macros are available to simplify logging.

### GO_LOG(level)

Provide the log stream at log level *level*.

```c++
GO_LOG(l::log_level_info) << "A log message";
```

### GO_LOG_FATAL

Provide the log stream at log level go\::diagnostics\::log\::log_level\::**fatal**.

```c++
GO_LOG_FATAL << "A log message";
```

### GO_LOG_ERROR

Provide the log stream at log level go\::diagnostics\::log\::log_level\::**error**.

```c++
GO_LOG_ERROR << "A log message";
```

### GO_LOG_WARN

Provide the log stream at log level go\::diagnostics\::log\::log_level\::**warn**.

```c++
GO_LOG_WARN << "A log message";
```

### GO_LOG_INFO

Provide the log stream at log level go\::diagnostics\::log\::log_level\::**info**.

```c++
GO_LOG_INFO << "A log message";
```

### GO_LOG_DEBUG

Provide the log stream at log level go\::diagnostics\::log\::log_level\::**debug**.

```c++
GO_LOG_DEBUG << "A log message";
```

### GO_LOG_TRACE

Provide the log stream at log level go\::diagnostics\::log\::log_level\::**trace**.

```c++
GO_LOG_TRACE << "A log message";
```

# class wlog

```c++
<go/diagnostics/log.hpp>
```

The **wlog** class provide the logging function.

It is declared as:

```c++
class wlog
    : go::utility::noncopyable_nonmovable
{
public:
    virtual ~wlog() = default;
    wlog() = default;
    bool operator==(wlog_line& logline);
    static detail::wlogger_atm& logger_atom();
    static detail::wlogger_ptr& logger_instance();
    static std::atomic<unsigned int>& log_level();
};
```

## Static member functions

### logger_atom

Specifiers | Signature
-|-
public static | detail::wlogger_atm& **logger_atom**()

Returns a reference to the *logger atom* used for thread synchronization.

### logger_instance

Specifiers | Signature
-|-
public static | detail::wlogger_ptr& **logger_instance**()

Returns a reference to the *logger* instance.

### log_level

Specifiers | Signature
-|-
public static | std\::atomic\<unsigned int\>& **log_level**()

Returns a reference to the atomic *log level*.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **wlog** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | public | **wlog**()

1. Constructs a **wlog** object.

### Equality operator

Operator | Specifiers | Signature
-|-
*log line (1)* | public | bool operator==(**wlog_line**& logline)

1. Using (possibly abusing) the equality operator to do compound assignment of log line.

## Macros

For convenience a set of macros are available to simplify logging.

### GO_WLOG(level)

Provide the log stream at log level *level*.

```c++
GO_WLOG(l::log_level_info) << L"A log message";
```

### GO_WLOG_FATAL

Provide the log stream at log level go\::diagnostics\::log\::log_level\::**fatal**.

```c++
GO_WLOG_FATAL << L"A log message";
```

### GO_WLOG_ERROR

Provide the log stream at log level go\::diagnostics\::log\::log_level\::**error**.

```c++
GO_WLOG_ERROR << L"A log message";
```

### GO_WLOG_WARN

Provide the log stream at log level go\::diagnostics\::log\::log_level\::**warn**.

```c++
GO_WLOG_WARN << L"A log message";
```

### GO_WLOG_INFO

Provide the log stream at log level go\::diagnostics\::log\::log_level\::**info**.

```c++
GO_WLOG_INFO << L"A log message";
```

### GO_WLOG_DEBUG

Provide the log stream at log level go\::diagnostics\::log\::log_level\::**debug**.

```c++
GO_WLOG_DEBUG << L"A log message";
```

### GO_WLOG_TRACE

Provide the log stream at log level go\::diagnostics\::log\::log_level\::**trace**.

```c++
GO_WLOG_TRACE << L"A log message";
```
