---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# enum notify_container_changed_action

```c++
<go_boost/mvvm.hpp>
```

The **notify_container_changed_action** enumeration is used to identify what type of
change that was applied to a container.

It is declared as:

```c++
enum notify_container_changed_action
{
    notify_container_changed_action_add,
    notify_container_changed_action_remove,
    notify_container_changed_action_reset,
    notify_container_changed_action_swap,
    undefined_notify_container_changed_action = ~0
};
```

## Enumerators

Enumerator | Description
-|-
notify_container_changed_action_add | Elements have been added to the container
notify_container_changed_action_remove | Elements have been removed from the container
notify_container_changed_action_reset | The contaier have been reset
notify_container_changed_action_swap | The contents of the container have been swapped with another container
undefined_notify_container_changed_action | Undefined
