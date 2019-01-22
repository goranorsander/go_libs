---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# class recursive_spin_lock

```c++
<go/utility/recursive_spin_lock.hpp>
```

The class **recursive_spin_lock** is a [lockable](https://en.cppreference.com/w/cpp/named_req/Lockable).
It implements the *Lockable* requirements using
[std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic).

**recursive_spin_lock** offers exclusive, recursive ownership semantics:

* A calling thread owns a **recursive_spin_lock** for a period of time that starts
  when it successfully calls either lock or try_lock. During this period, the 
  thread may make additional calls to lock or try_lock. The period of ownership 
  ends when the thread makes a matching number of calls to unlock.
* When a thread owns a **recursive_spin_lock**, all other threads will block (for 
  calls to lock) or receive a false return value (for try_lock) if they attempt 
  to claim ownership of the **recursive_spin_lock**.

It is declared as:

```c++
struct recursive_spin_lock
    : noncopyable_nonmovable
{
public:
    virtual ~recursive_spin_lock() = default;
    recursive_spin_lock() noexcept;

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

Destroys the **recursive_spin_lock** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | public | **recursive_spin_lock**()

1. Constructs a **recursive_spin_lock** object.

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
