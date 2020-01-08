---
layout: boost_lib_async
---

```c++
namespace go_boost::async
```

# class placebo_lockable

```c++
<go_boost/async/placebo_lockable.hpp>
```

The class **placebo_lockable** is a place holder, a
[placebo](https://en.wikipedia.org/wiki/Placebo), for a lockable, e.g. a
boost::mutex, when a lockable is required but not necessary.

It is declared as:

```c++
class placebo_lockable
    : noncopyable_nonmovable
{
public:
    virtual ~placebo_lockable();
    constexpr placebo_lockable() noexcept;
    void lock();
    bool try_lock();
    void unlock();
};
```

## Member types

Member type | Definition
-|-
scoped_lock | boost\::unique_lock<placebo_lockable>
scoped_try_lock | boost\::detail\::try_lock_wrapper<placebo_lockable>

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **placebo_lockable** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **placebo_lockable**()

1. Constructs a **placebo_lockable** object.

### lock

Specifiers | Signature
-|-
public | void lock()

Placeholder for the boost::mutex lock function. Does nothing.

### try_lock

Specifiers | Signature
-|-
public | bool try_lock()

Placeholder for the boost::mutex try_lock function. Does nothing. Always returns **true**.

### unlock

Specifiers | Signature
-|-
public | void unlock()

Placeholder for the boost::mutex unlock function. Does nothing.
