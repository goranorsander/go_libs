---
layout: std_lib_diagnostics_benchmark
---

```c++
namespace go::diagnostics::benchmark
```

# GO Std Diagnostics Benchmark Library

```c++
<go/diagnostics/benchmark.hpp>
```

## Description

The **GO Std Diagnostics Benchmark Library** provide a fast, low latency
functions for benchmarking code.

## Example

The following sample show how-to do benchmarking with the
**GO Std Diagnostics Benchmark Library**.

```c++
#include <iostream>
#include <go/config.hpp>
#include <go/diagnostics.hpp>

namespace b = go::diagnostics::benchmark;

uint64_t fibonacci_number(const uint64_t n)
{
    return ((n == 0) || (n == 1)) ? 1 : fibonacci_number(n - 1) + fibonacci_number(n - 2);
}

int main()
{
    b::stopwatch sw;
    uint64_t n = 0;
    while (n < 31)
    {
        uint64_t fn = 0;
        {
            b::stopwatch_guard g(sw);
            fn = fibonacci_number(n);
        }
        std::cout << "Fibonacci number " << n << " = " << fn << " (time = " << sw.last_duration().count() << " microseconds, total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        ++n;
    }
    return 0;
}
```

Output

```
Fibonacci number 0 = 1 (time = 1 microseconds, total time = 1 microseconds)
Fibonacci number 1 = 1 (time = 0 microseconds, total time = 1 microseconds)
Fibonacci number 2 = 2 (time = 0 microseconds, total time = 1 microseconds)
Fibonacci number 3 = 3 (time = 0 microseconds, total time = 1 microseconds)
Fibonacci number 4 = 5 (time = 0 microseconds, total time = 1 microseconds)
Fibonacci number 5 = 8 (time = 0 microseconds, total time = 1 microseconds)
Fibonacci number 6 = 13 (time = 1 microseconds, total time = 2 microseconds)
Fibonacci number 7 = 21 (time = 1 microseconds, total time = 3 microseconds)
Fibonacci number 8 = 34 (time = 1 microseconds, total time = 4 microseconds)
Fibonacci number 9 = 55 (time = 2 microseconds, total time = 6 microseconds)
Fibonacci number 10 = 89 (time = 6 microseconds, total time = 12 microseconds)
Fibonacci number 11 = 144 (time = 5 microseconds, total time = 17 microseconds)
Fibonacci number 12 = 233 (time = 9 microseconds, total time = 26 microseconds)
Fibonacci number 13 = 377 (time = 13 microseconds, total time = 39 microseconds)
Fibonacci number 14 = 610 (time = 18 microseconds, total time = 57 microseconds)
Fibonacci number 15 = 987 (time = 30 microseconds, total time = 87 microseconds)
Fibonacci number 16 = 1597 (time = 48 microseconds, total time = 135 microseconds)
Fibonacci number 17 = 2584 (time = 76 microseconds, total time = 211 microseconds)
Fibonacci number 18 = 4181 (time = 126 microseconds, total time = 337 microseconds)
Fibonacci number 19 = 6765 (time = 183 microseconds, total time = 520 microseconds)
Fibonacci number 20 = 10946 (time = 214 microseconds, total time = 734 microseconds)
Fibonacci number 21 = 17711 (time = 488 microseconds, total time = 1222 microseconds)
Fibonacci number 22 = 28657 (time = 854 microseconds, total time = 2076 microseconds)
Fibonacci number 23 = 46368 (time = 1633 microseconds, total time = 3709 microseconds)
Fibonacci number 24 = 75025 (time = 2140 microseconds, total time = 5849 microseconds)
Fibonacci number 25 = 121393 (time = 3553 microseconds, total time = 9402 microseconds)
Fibonacci number 26 = 196418 (time = 5776 microseconds, total time = 15178 microseconds)
Fibonacci number 27 = 317811 (time = 8402 microseconds, total time = 23580 microseconds)
Fibonacci number 28 = 514229 (time = 13806 microseconds, total time = 37386 microseconds)
Fibonacci number 29 = 832040 (time = 19960 microseconds, total time = 57346 microseconds)
Fibonacci number 30 = 1346269 (time = 29201 microseconds, total time = 86547 microseconds)
```

## Reference

### Class reference

* [go\::diagnostics\::benchmark\::**exception**](./class_exception.html)
* [go\::diagnostics\::benchmark\::**basic_stopwatch**](./class_template_basic_stopwatch.html)
  * [go\::diagnostics\::benchmark\::**stopwatch**](./class_template_basic_stopwatch.html)
* [go\::diagnostics\::benchmark\::**basic_stopwatch_guard**](./class_template_basic_stopwatch_guard.html)
  * [go\::diagnostics\::benchmark\::**stopwatch_guard**](./class_template_basic_stopwatch_guard.html)
