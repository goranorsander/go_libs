---
layout: boost_lib_mvvm_iterator
---

```c++
namespace go_boost::mvvm::iterator
```

# function template erase

```c++
<go_boost/mvvm/iterator/erase.hpp>
```

The **erase** function is used to remove one or more elements from a
container.

It is declared as:

```c++
template<class I, class C>
I erase(const boost::shared_ptr<C>& container, I& it, const boost::size_t& n);
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
