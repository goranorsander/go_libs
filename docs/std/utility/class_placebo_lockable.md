---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# class placebo_lockable

```c++
<go/utility/placebo_lockable.hpp>
```

The class **placebo_lockable** is a place holder, a
[placebo](https://en.wikipedia.org/wiki/Placebo), for a lockable, e.g. a
[std::mutex](https://en.cppreference.com/w/cpp/thread/mutex), when a lockable
is required but not necessary.

It is declared as:

```c++
class placebo_lockable
    : noncopyable_nonmovable
{
public:
    virtual ~placebo_lockable() = default;
    constexpr placebo_lockable() noexcept = default;
    void lock();
    bool try_lock();
    void unlock();
};
```

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

Placeholder for the std::mutex lock function. Does nothing.

### try_lock

Specifiers | Signature
-|-
public | bool try_lock()

Placeholder for the std::mutex try_lock function. Does nothing. Always returns **true**.

### unlock

Specifiers | Signature
-|-
public | void unlock()

Placeholder for the std::mutex unlock function. Does nothing.
