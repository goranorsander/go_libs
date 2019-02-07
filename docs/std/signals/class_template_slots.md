---
layout: std_lib_signals
---

```c++
namespace go::signals
```

# class template slots

```c++
<go/signals/slots.hpp>
```

**Generic slots class**

The **slots** is a base class for signal slots.

It is declared as:

```c++
template<class Collector, class ReturnValueType, class... Args>
class slots<ReturnValueType(Args...), Collector>
    : private return_value_collector_invoker<Collector, ReturnValueType (Args...)>
    , go::utility::noncopyable_nonmovable
{
protected:
    using signal_function_type = std::function<ReturnValueType (Args...)>;
    using signal_return_value_type = typename signal_function_type::result_type;

public:
    virtual ~slots() = default;

protected:
    explicit slots(const signal_function_type& signal_function);

    template <typename R>
    typename std::enable_if<std::is_void<R>::value && std::is_same<R, signal_return_value_type>::value, R>::type emit(Args... args) const;
    template <typename R>
    typename std::enable_if<!std::is_void<R>::value && std::is_same<R, signal_return_value_type>::value, R>::type emit(Args... args) const;
    std::size_t connections() const;
    slot_key add_slot(const signal_function_type& signal_function);
    bool remove_slot(const slot_key& key);
    void remove_all_slots();
};
```

## Member types

Member type | Definition
-|-
signal_function_type | std\::function\<ReturnValueType (Args...)>
signal_return_value_type | signal_function_type\::result_type

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **slots** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*constructor (1)* | protected | **slots**(const signal_function_type& signal_function)

1. Constructs a **slots** object.

### emit

Specifiers | Signature
-|-
protected | void **emit**(Args... args) const
protected | signal_return_value_type **emit**(Args... args) const

Emit a **signal** on all connected slots.

### connections

Specifiers | Signature
-|-
protected | std\::size_t **connections**() const

Returns the number of connected slots.

### add_slot

Specifiers | Signature
-|-
protected | slot_key **add_slot**(const signal_function_type& signal_function)

Add a slot to a **signal**.

### remove_slot

Specifiers | Signature
-|-
protected | void **remove_slot**(const slot_key& key)

Remove a slot from a **signal**.

### remove_all_slots

Specifiers | Signature
-|-
protected | void **remove_all_slots**()

Remove all slots from a **signal**.
