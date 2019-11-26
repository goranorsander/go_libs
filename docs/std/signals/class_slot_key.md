---
layout: std_lib_signals
---

```c++
namespace go::signals
```

# class slot_key

```c++
<go/signals/slot_key.hpp>
```

**slot_key class**

The **slot_key** is a class used to identify connected signals.

It is declared as:

```c++
GO_IMPLEMENT_UNSIGNED_INTEGER_TYPE_SPECIALIZER(slot_key, uint3264_t, 0)
```

## Member functions

See [fundamental_type_specializer](./../utility/class_template_fundamental_type_specializer.html)
for a description of the **GO_IMPLEMENT_UNSIGNED_INTEGER_TYPE_SPECIALIZER** macro.

## Global functions

### reset

Specifiers | Signature
-|-
n/a | void **reset**(slot_key& key)

Resets the **slot_key** to the null value.

### is_null_key

Specifiers | Signature
-|-
n/a | bool **is_null_key**(const slot_key& key)

Returns true if *key* is equal to the null value, false otherwise.
