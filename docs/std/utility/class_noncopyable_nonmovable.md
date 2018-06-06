---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# class noncopyable_nonmovable

```c++
<go/utility/noncopyable_nonmovable.hpp>
```

Base class for non-copyable objects in the **GO Std C++ Libraries**.

The class **noncopyable_nonmovable** has protected constructor members to emphasize that it is
to be used only as a base class. It is intended to be used as a private base class.
go\::utility\::**noncopyable_nonmovable** has private deleted copy constructor, move constructor,
copy assignment operator and move assignment operator. It cannot be copied, moved or assigned. A
class that derives from it inherits these properties.

It is declared as:

```c++
class noncopyable_nonmovable
{
public:
    virtual ~noncopyable_nonmovable() = 0;

protected:
    noncopyable_nonmovable() = default;

private:
    noncopyable_nonmovable(const noncopyable_nonmovable&) = delete;
    noncopyable_nonmovable(noncopyable_nonmovable&&) = delete;
    auto operator=(const noncopyable_nonmovable&)->noncopyable_nonmovable& = delete;
    auto operator=(noncopyable_nonmovable&&)->noncopyable_nonmovable& = delete;
};
```

## Member functions

### (destructor)

*public virtual abstract member function*

Destroys the **noncopyable_nonmovable** object.

As a virtual function, derived classes may redefine its behavior.

### (constructor)

*private member function*

Constructor | Signature
-|-
*default constructor (1)* | **noncopyable_nonmovable**()
*copy constructor (2)* | **noncopyable_nonmovable**(const **noncopyable_nonmovable**& other)
*move constructor (3)* | **noncopyable_nonmovable**(**noncopyable_nonmovable**&& other)

1. Constructs a **noncopyable_nonmovable** object.
2. Copy constructor. Constructs the **noncopyable_nonmovable** with the copy of the contents of other.
3. Move constructor. Deleted.

### operator=

*private member function*

Operator | Signature
-|-
*assign copy (1)* | auto operator=(const **noncopyable_nonmovable**&)->**noncopyable_nonmovable**&
*assign by move (2)* | auto operator=(**noncopyable_nonmovable**&&)->**noncopyable_nonmovable**&

1. Copy assignment operator.
2. Move asignment operator. Deleted.
