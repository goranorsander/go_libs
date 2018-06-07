---
layout: std_lib_utility_container
---

```c++
namespace go::utility::container
```

# function template size

```c++
<go/utility/container/size.hpp>
```

The **size** function is used to get the number of elements in a
container.

It is declared as:

```c++
template<class C>
std::size_t size(C& container);
```

## Template parameters

Parameter | Description
-|-
C|The container class

## Parameters

Parameter | Description
-|-
container|The container to get size of

## Return value

The number of elements in the container.

# Example

Get the number of elements.

```c++
#include <iostream>
#include <go/utility.hpp>

namespace u = go::utility;
namespace uc = go::utility::container;

int main()
{
    std::forward_list<int> container = { 1, 2, 3, 4, 5 };
    std::cout << uc::size(container) << std::endl;
    return 0;
}
```

Output

```
5
```
