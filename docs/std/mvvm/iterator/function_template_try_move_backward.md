---
layout: std_lib_mvvm_iterator
---

```c++
namespace go::mvvm::iterator
```

# function template try_move_backward

```c++
<go/mvvm/iterator/try_move_backward.hpp>
```

The **try_move_backward** function is used to move an iterator backward.
The function is intended to be used with *forward only* iterators.

It is declared as:

```c++
template<class I, class C>
bool try_move_backward(const std::shared_ptr<C>& container, I& it);
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
