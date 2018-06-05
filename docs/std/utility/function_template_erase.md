---
layout: std_lib_utility
---

```c++
namespace go::utility::iterator
```

# function template erase

```c++
<go/utility/iterator/erase.hpp>
```

The **erase** function can be used to remove one or more elements from a
container.

It is declared as:

```c++
template<class I, class C>
inline I erase(C& container, I& it, const std::size_t& n);
```

## Parameters

Parameter | Description
-|-
container|The container
it|Iterator of the first element to be removed
n|The number of consecutive elements to remove

## Return value

An iterator pointing to the new location of the element that followed the last
element removed by the function call. This is the container end if the operation
removed the last element in the sequence.

# Example

Removing the three middle elements from a container having five elemets to
begin with.

```c++
#include <iostream>
#include <go/utility.hpp>

namespace u = go::utility;
namespace ui = go::utility::iterator;

int main()
{
    std::deque<int> container = { 1, 2, 3, 4, 5 };
    std::deque<int>::iterator it = container.begin();
    ++it;
    it = ui::erase(container, it, 3);
    std::cout << *container.begin() << std::endl;
    std::cout << *it << std::endl;
    std::cout << container.size() << std::endl;
    return 0;
}
```

Output

```
1
5
2
```
