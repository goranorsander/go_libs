---
layout: std_lib_utility
---

```c++
namespace go::utility::iterator
```

# function template try_move_backward

```c++
<go/utility/iterator/try_move_backward.hpp>
```

The **try_move_backward** function is used to move an iterator backward.
The function is intended to be used with *forward only* iterators.

It is declared as:

```c++
template<class I, class C>
bool try_move_backward(C& container, I& it);
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
it|The iterator to move backward

## Return value

**true** if and only if **it** was moved backward, **false** otherwise.

# Example

Iterating a std\::forward_list backwards.

```c++
#include <forward_list>
#include <iostream>
#include <go/utility.hpp>

namespace u = go::utility;
namespace ui = go::utility::iterator;

int main()
{
    std::forward_list<int> container = {1, 2, 3, 4, 5};
    std::forward_list<int>::iterator it = container.end();
    while(ui::try_move_backward(container, it))
    {
        std::cout << *it << std::endl;
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
