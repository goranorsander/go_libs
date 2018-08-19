---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# class string_cast_exception

```c++
<go/utility/string_cast_exception.hpp>
```

Exception class used by function template **string_cast**.

It is declared as:

```c++
class string_cast_exception
    : public go::exception::exception
{
public:
    virtual ~string_cast_exception();
    explicit string_cast_exception(const char* message);
    explicit string_cast_exception(const std::string& message);
};
```

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **string_cast_exception** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*from c-string (1)* | public explicit | **string_cast_exception**(const char\* message)
*from std\::string (2)* | public explicit | **string_cast_exception**(const std\::string& message)

1. Copies the null-terminated character sequence (C-string) pointed by *message*.
2. Copies the character sequence (std\::string) handled by *message*.
