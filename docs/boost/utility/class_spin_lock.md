---
layout: boost_lib_utility
---

```c++
namespace go_boost::utility
```

# class spin_lock

```c++
<go_boost/utility/spin_lock.hpp>
```

The class **spin_lock** is a [lockable](https://en.cppreference.com/w/cpp/named_req/Lockable).
It implements the *Lockable* requirements using a
[boost::atomic_flag](https://www.boost.org/doc/libs/1_70_0/doc/html/atomic/interface.html#atomic.interface.interface_atomic_flag).

It is declared as:

```c++
struct spin_lock
    : noncopyable_nonmovable
{
public:
    virtual ~spin_lock() = default;
    spin_lock() noexcept;

    void lock();
    bool try_lock();
    void unlock();
};
```

## Member functions

### Destructor

Specifiers |
-|
public |

Destroys the **spin_lock** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | public | **spin_lock**()

1. Constructs a **spin_lock** object.

### lock

Specifiers | Signature
-|-
public | void lock()

Blocks until a lock can be obtained for the current execution agent
(thread, process, task). If an exception is thrown, no lock is obtained.

### try_lock

Specifiers | Signature
-|-
public | bool try_lock()

Attempts to acquire the lock for the current execution agent (thread,
process, task) without blocking. If an exception is thrown, no lock is
obtained.

Returns **true** if the lock was acquired, **false** otherwise.

### unlock

Specifiers | Signature
-|-
public | void unlock()

Releases the lock held by the execution agent. Throws no exceptions.
