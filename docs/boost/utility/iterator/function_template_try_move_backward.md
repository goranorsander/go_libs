---
layout: boost_lib_utility_iterator
---

```c++
namespace go_boost::utility::iterator
```

# function template try_move_backward

```c++
<go_boost/utility/iterator/try_move_backward.hpp>
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

Iterating a boost\::container\::slist backwards.

```c++
#include <forward_list>
#include <iostream>
#include <go_boost/utility.hpp>

namespace u = go_boost::utility;
namespace ui = go_boost::utility::iterator;

int main()
{
    boost::container::slist<int> container = {1, 2, 3, 4, 5};
    boost::container::slist<int>::iterator it = container.end();
    while(ui::try_move_backward(container, it))
    {
        boost::cout << *it << boost::endl;
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
