---
layout: std_lib_type_traits
---

```c++
namespace go::type_traits
```

# class nonmovable

```c++
<go/type_traits/nonmovable.hpp>
```

Base class for non-copyable objects in the **GO Std C++ Libraries**.

The class **nonmovable** has protected constructor members to emphasize that it is
to be used only as a base class. It is intended to be used as a private base class.
go\::type_traits\::**nonmovable** has private deleted move constructor and a move
assignment operator and cannot be moved. A class that derives from it inherits
these properties.

It is declared as:

```c++
class nonmovable
{
public:
    virtual ~nonmovable() = 0;

protected:
    nonmovable() = default;
    nonmovable(const nonmovable&) = default;
    auto operator=(const nonmovable&)->nonmovable& = default;

private:
    nonmovable(nonmovable&&) = delete;
    auto operator=(nonmovable&&)->nonmovable& = delete;
};
```

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **nonmovable** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **nonmovable**()
*copy constructor (2)* | protected | **nonmovable**(const **nonmovable**& other)
*move constructor (3)* | private | **nonmovable**(**nonmovable**&& other)

1. Constructs a **nonmovable** object.
2. Copy constructor. Constructs the **nonmovable** with the copy of the contents of other.
3. Move constructor. Deleted.

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | protected | auto operator=(const **nonmovable**&)->**nonmovable**&
*assign by move (2)* | private | auto operator=(**nonmovable**&&)->**nonmovable**&

1. Copy assignment operator.
2. Move asignment operator. Deleted.
