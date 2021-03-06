---
layout: std_lib_utility_string
---

```c++
namespace go::string
```

# class create_exception

```c++
<go/string/create_exception.hpp>
```

Exception class used by function template **create**.

It is declared as:

```c++
class create_exception
    : public go::exception::exception
{
public:
    virtual ~create_exception();
    explicit create_exception(const char* message);
    explicit create_exception(const std::string& message);
};
```

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **create_exception** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*from c-string (1)* | public explicit | **create_exception**(const char\* message)
*from std\::string (2)* | public explicit | **create_exception**(const std\::string& message)

1. Copies the null-terminated character sequence (C-string) pointed by *message*.
2. Copies the character sequence (std\::string) handled by *message*.
