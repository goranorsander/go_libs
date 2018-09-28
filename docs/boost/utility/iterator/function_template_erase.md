---
layout: boost_lib_utility_iterator
---

```c++
namespace go_boost::utility::iterator
```

# function template erase

```c++
<go_boost/utility/iterator/erase.hpp>
```

The **erase** function is used to remove one or more elements from a
container.

It is declared as:

```c++
template<class I, class C>
I erase(C& container, I& it, const boost::size_t& n);
```

## Template parameters

Parameter | Description
-|-
I|The iterator class
C|The container class

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
#include <go_boost/utility.hpp>

namespace u = go_boost::utility;
namespace ui = go_boost::utility::iterator;

int main()
{
    std::deque<int> container = { 1, 2, 3, 4, 5 };
    std::deque<int>::iterator it = container.begin();
    ++it;
    it = ui::erase(container, it, 3);
    boost::cout << *container.begin() << boost::endl;
    boost::cout << *it << boost::endl;
    boost::cout << container.size() << boost::endl;
    return 0;
}
```

Output

```
1
5
2
```
