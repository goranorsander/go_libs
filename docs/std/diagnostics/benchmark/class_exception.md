---
layout: std_lib_diagnostics_benchmark
---

```c++
namespace go::diagnostics::benchmark
```

# class exception

```c++
<go/diagnostics/benchmark/exception.hpp>
```

Exception class used by the **GO Std Diagnostics Benchmark Library**.

It is declared as:

```c++
class exception
    : public go::exception::exception
{
public:
    virtual ~exception();
    explicit exception(const char* message);
    explicit exception(const std::string& message);
};
```

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **exception** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*from c-string (1)* | public explicit | **exception**(const char\* message)
*from std\::string (2)* | public explicit | **exception**(const std\::string& message)

1. Copies the null-terminated character sequence (C-string) pointed by *message*.
2. Copies the character sequence (std\::string) handled by *message*.
