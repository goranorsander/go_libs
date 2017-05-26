```c++
namespace go::exception
```

# class exception

```c++
<go/exception/exception.hpp>
```

Base class for exceptions in the **GO C++ Libraries**.

All objects thrown by components of the **GO C++ Libraries** are derived from the class
go\::exception\::**exception** which is derived from std\::**exception**. Therefore, all
**GO C++ Libraries** exceptions can be caught by catching either go\::exception\::**exception**
or std\::**exception** by reference.

It is declared as:

```c++
class exception
    : public std::exception
{
public:
    virtual ~exception() GO_NOEXCEPT_OR_NOTHROW;
    exception(const exception& other);
    explicit exception(const char* message);
    explicit exception(const std::string& message);
    exception& operator=(const exception& other);
    virtual const char* what() const GO_NOEXCEPT_OR_NOTHROW;
    virtual std::string message() const GO_NOEXCEPT_OR_NOTHROW;
};
```

## Member functions

### (destructor)

*public virtual member function*

Destroys the **exception** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*public member function*

Constructor | Signature
-|-
*copy (1)* | **exception**(const **exception**& other)
*from c-string (2)* | **exception**(const char\* message)
*from std::string (3)* | **exception**(const std::string& message)

1. Constructs a copy of *other*.
2. Copies the null-terminated character sequence (C-string) pointed by *message*.
3. Copies the character sequence (std::string) handled by *message*.

### operator=

*public member function*

Copies an **exception** object.

### what

*public virtual member function*

Returns a pointer to an array that contains a null-terminated sequence of characters (i.e., a C-string).
This array includes the same sequence of characters that make up the std::string object holding the
**exception** message. An additional terminating null-character ('\0') is added at the end.

As a virtual function, derived classes may redefine this function so that specific values are returned.

### message

*public virtual member function*

Returns a std::string object holding the **exception** message.

As a virtual function, derived classes may redefine this function so that specific values are returned.

Copyright &copy; 2014-2017 Göran Orsander
