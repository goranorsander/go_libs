---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# class placebo_mutex

```c++
<go/utility/placebo_mutex.hpp>
```

The class **placebo_mutex** is a place holder, a
[placebo](https://en.wikipedia.org/wiki/Placebo), for a
[std::mutex](https://en.cppreference.com/w/cpp/thread/mutex) when no
mutex is required but not necessary.

It is declared as:

```c++
class placebo_mutex
    : noncopyable_nonmovable
{
public:
    virtual ~placebo_mutex() = default;
    constexpr placebo_mutex() noexcept = default;
    void lock();
    bool try_lock();
    void unlock();
    native_handle_type native_handle();
};
```

## Member types

Member type | Definition
-|-
native_handle_type | std\::mutex\::native_handle_type

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

### native_handle

Specifiers | Signature
-|-
public | native_handle_type native_handle()

Placeholder for the std::mutex native_handle function. Does nothing. Returns
a default initialized native_handle_type object.
