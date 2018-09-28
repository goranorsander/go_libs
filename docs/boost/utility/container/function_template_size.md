---
layout: boost_lib_utility_container
---

```c++
namespace go_boost::utility::container
```

# function template size

```c++
<go_boost/utility/container/size.hpp>
```

The **size** function is used to get the number of elements in a
container.

It is declared as:

```c++
template<class C>
boost::size_t size(C& container);
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
#include <go_boost/utility.hpp>

namespace u = go_boost::utility;
namespace uc = go_boost::utility::container;

int main()
{
    boost::container::slist<int> container = { 1, 2, 3, 4, 5 };
    boost::cout << uc::size(container) << boost::endl;
    return 0;
}
```

Output

```
5
```
