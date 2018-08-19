---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# class noncopyable

```c++
<go/utility/noncopyable.hpp>
```

Base class for non-copyable objects in the **GO Std C++ Libraries**.

The class **noncopyable** has protected constructor members to emphasize that it is
to be used only as a base class. It is intended to be used as a private base class.
go\::utility\::**noncopyable** has private deleted copy constructor and a copy
assignment operator and cannot be copied or assigned. A class that derives from it
inherits these properties.

It is declared as:

```c++
class noncopyable
{
public:
    virtual ~noncopyable() = 0;

protected:
    noncopyable() = default;
    noncopyable(noncopyable&&) = default;
    auto operator=(noncopyable&&)->noncopyable& = default;

private:
    noncopyable(const noncopyable&) = delete;
    auto operator=(const noncopyable&)->noncopyable& = delete;
};
```

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **noncopyable** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **noncopyable**()
*move constructor (2)* | protected | **noncopyable**(**noncopyable**&& other)
*copy constructor (3)* | private | **noncopyable**(const **noncopyable**& other)

1. Constructs a **noncopyable** object.
2. Move constructor. Constructs the **noncopyable** with the contents of other using move semantics. other is left in valid, but unspecified state.
3. Copy constructor. Deleted.

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign by move (1)* | protected | auto operator=(**noncopyable**&&)->**noncopyable**&
*assign copy (2)* | private | auto operator=(const **noncopyable**&)->**noncopyable**&

1. Move asignment operator. Moves a **noncopyable** object.
2. Copy assignment operator. Deleted.
