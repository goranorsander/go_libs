---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# class nonmovable

```c++
<go/utility/nonmovable.hpp>
```

Base class for non-copyable objects in the **GO Std C++ Libraries**.

The class **nonmovable** has protected constructor members to emphasize that it is
to be used only as a base class. It is intended to be used as a private base class.
go\::utility\::**nonmovable** has private deleted move constructor and a move
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

### (destructor)

*public virtual abstract member function*

Destroys the **nonmovable** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*protected member function*

Constructor | Signature
-|-
*default constructor (1)* | **nonmovable**()
*copy constructor (2)* | **nonmovable**(const **nonmovable**& other)

1. Constructs a **nonmovable** object.
2. Copy constructor. Constructs the **nonmovable** with the copy of the contents of other.

*private member function*

Constructor | Signature
-|-
*move constructor (3)* | **nonmovable**(**nonmovable**&& other)

3. Move constructor. Deleted.

### operator=

*protected member function*

Operator | Signature
-|-
*assign copy (1)* | auto operator=(const **nonmovable**&)->**nonmovable**&

1. Copy assignment operator.

*private member function*

Operator | Signature
-|-
*assign by move (2)* | auto operator=(**nonmovable**&&)->**nonmovable**&

2. Move asignment operator. Deleted.
