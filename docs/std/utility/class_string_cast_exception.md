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

### (destructor)

*public virtual member function*

Destroys the **string_cast_exception** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*from c-string (1)* | **string_cast_exception**(const char\* message)
*from std\::string (2)* | **string_cast_exception**(const std\::string& message)

1. Copies the null-terminated character sequence (C-string) pointed by *message*.
2. Copies the character sequence (std\::string) handled by *message*.
