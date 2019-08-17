---
layout: std_lib_utility_iterator
---

```c++
namespace go::utility::iterator
```

# function template reverse

```c++
<go/utility/iterator/reverse.hpp>
```

The **reverse** function is an adaptor that make it possible
to iterate a container in reverse order using ranged-based
for-loops.

It is declared as:

```c++
template <typename I>
struct reverse_adaptor_wrapper;

template <typename A>
auto begin(reverse_adaptor_wrapper<A> adaptor);

template <typename A>
auto end(reverse_adaptor_wrapper<A> adaptor);

template <typename C>
reverse_adaptor_wrapper<C> reverse(C&& iterable);
```

## Template parameters

Parameter | Description
-|-
I|The iterator class
A|The adaptor class
C|The container class

## Parameters

Parameter | Description
-|-
iterable|The iterable container to be adapted for reverse iteration.

## Return value

A reverse adaptor wrapper object that is used by the supporting
**begin** and **end** function during reversed ranged-based
for-looping.

# Example

Printing elements of a list in reverse order.

```c++
#include <iostream>
#include <go/utility.hpp>

namespace ui = go::utility::iterator;

int main()
{
    std::list<int> container = { 1, 2, 3, 4, 5 };
    for (int i : ui::reverse(container))
    {
        std::cout << i << std::endl;
    }
    return 0;
}
```

Output

```
5
4
3
2
1
```
