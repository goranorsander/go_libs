---
layout: std_lib_exception
---

```c++
namespace go::exception
```

# GO Std Exception Library

```c++
<go/exception.hpp>
```

## Description

**Exception**

A **exception** represent a callback with multiple targets. Exception are connected to 
some set of slots, which are callback receivers. The slots are called when the 
**exception** is *"emitted"*.

...

## Example

This example is intended to show how exception can be used. It implements a 
simple fire lasers command that the fleet commander can give to the ships.

```c++
nn
```

Output

```
nn
```

## Reference

### Class reference

* [exception](./class_template_exception.html)
* [slot](./abstract_class_slot.html)
* [slot_arguments](./abstract_class_slot_arguments.html)
* [slot_key](./class_slot_key.html)
