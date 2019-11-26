---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class event_subscription_key

```c++
<go_boost/mvvm/event_subscription_key.hpp>
```

**event_subscription_key class**

The **event_subscription_key** is a class used to identify connected events.

It is declared as:

```c++
GO_BOOST_IMPLEMENT_UNSIGNED_INTEGER_TYPE_SPECIALIZER(event_subscription_key, uint3264_t, 0)
```

## Member functions

See [fundamental_type_specializer](./../utility/class_template_fundamental_type_specializer.html)
for a description of the **GO_BOOST_IMPLEMENT_UNSIGNED_INTEGER_TYPE_SPECIALIZER** macro.

## Global functions

### reset

Specifiers | Signature
-|-
n/a | void **reset**(event_subscription_key& key)

Resets the **event_subscription_key** to the null value.

### is_null_key

Specifiers | Signature
-|-
n/a | bool **is_null_key**(const event_subscription_key& key)

Returns true if *key* is equal to the null value, false otherwise.
