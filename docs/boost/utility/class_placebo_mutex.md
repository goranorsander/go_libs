---
layout: boost_lib_utility
---

```c++
namespace go_boost::utility
```

# class placebo_mutex

```c++
<go_boost/utility/placebo_mutex.hpp>
```

The class **placebo_mutex** is a place holder, a
[placebo](https://en.wikipedia.org/wiki/Placebo), for a boost::mutex when no
mutex is required but not necessary.

It is declared as:

```c++
class placebo_mutex
    : boost::noncopyable
{
public:
    virtual ~placebo_mutex();
    constexpr placebo_mutex() noexcept;
    void lock();
    bool try_lock();
    void unlock();
    native_handle_type native_handle();
};
```

## Member types

Member type | Definition
-|-
native_handle_type | boost\::mutex\::native_handle_type
scoped_lock | boost\::unique_lock<placebo_mutex>
scoped_try_lock | boost\::detail\::try_lock_wrapper<placebo_mutex>

## Member functions

### Destructor

Specifiers |
-|
public abstract |

Destroys the **placebo_mutex** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default constructor (1)* | protected | **placebo_mutex**()

1. Constructs a **placebo_mutex** object.

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

### native_handle

Specifiers | Signature
-|-
public | native_handle_type native_handle()

Placeholder for the boost::mutex native_handle function. Does nothing. Returns
a default initialized native_handle_type object.
