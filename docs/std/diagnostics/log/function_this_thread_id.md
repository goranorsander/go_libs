---
layout: std_lib_diagnostics_log
---

```c++
namespace go::diagnostics::log
```

# function this_thread_id

```c++
<go/diagnostics/log/thread_id.hpp>
```

The **this_thread_id** function returns the id of the current thread.

It is declared as:

```c++
std::thread::id this_thread_id();
```

## Return value

The thread id.
