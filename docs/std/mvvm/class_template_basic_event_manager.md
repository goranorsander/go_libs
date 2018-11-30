---
layout: std_lib_mvvm
---

```c++
namespace go::mvvm
```

# class template basic_event_manager

```c++
<go/mvvm.hpp>
```

**Generic event manager**

The **basic_event_manager** is a generalization class to manage events.

It is declared as:

```c++
template<class S, class L = std::recursive_mutex>
class basic_event_manager
    : public basic_notify_event_firing_interface<S>
    , public go::utility::noncopyable_nonmovable
{
public:
    virtual ~basic_event_manager();

protected:
    basic_event_manager();

public:
    static ptr create();

    event_subscription_key_type subscribe(const S& event_type, basic_event_function_type&& fire_event_function);
    void unsubscribe(const S& event_type, const event_subscription_key_type& event_subscription_key);
    void unsubscribe_all(const S& event_type);
    void unsubscribe_all();
    void fire(const std::shared_ptr<basic_event<S>>& e) const;
    void post(const std::shared_ptr<basic_event<S>>& e, const bool keep_event_alive = true);
    void fire_events();
    size_t events() const;
};
```

## Template parameters

Parameter | Description
-|-
S | The manager string class
L | The manager lockable class

## Member types

Member type | Definition
-|-
string_type | S
lockable_type | L
this_type | basic_event_manager<S, L>
ptr | std\::shared_ptr<basic_event_manager<S, L>>
wptr | std\::weak_ptr<basic_event_manager<S, L>>
basic_event_ptr | std\::shared_ptr<basic_event<S>>
basic_event_function_type | std\::function<void(const std\::shared_ptr<basic_event<S>>&)>

## Static member functions

### create

Specifiers | Signature
-|-
public static | ptr create()

Constructs a new **basic_event_manager** object and return it as a
**basic_event_manager<string_type, lockable_type>\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_event_manager** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*constructor (1)* | protected | **basic_event_manager**()

1. Constructs a **basic_event_manager** object.

### subscribe

Specifiers | Signature
-|-
public | event_subscription_key_type **subscribe**(const S& event_type, basic_event_function_type&& fire_event_function)

Subscribe to an *event type* by registering a call back function.

### unsubscribe

Specifiers | Signature
-|-
public | void **unsubscribe**(const S& event_type, const event_subscription_key_type& event_subscription_key)

Unsubscribe a specific subscription.

### unsubscribe_all

Specifiers | Signature
-|-
public | void **unsubscribe_all**(const S& event_type)
public | void **unsubscribe_all**()

Unsubscribe all subscriptions or all subscriptions associated with an *event type*.

### fire

Specifiers | Signature
-|-
public | void **fire**(const std\::shared_ptr<basic_event<S>>& e) const

Fire an event immediately.

### post

Specifiers | Signature
-|-
public | void **post**(const std\::shared_ptr<basic_event<S>>& e, const bool keep_event_alive = true)

Post an event to be fired later on.

### fire_events

Specifiers | Signature
-|-
public | void **fire_events**()

Fire all posted events.

### events

Specifiers | Signature
-|-
public | size_t events() const

Return the number of posted events waiting to be executed.

# class template basic_event_manager specializations

## typedef event_manager

The **event_manager** is a type definition for events name using **std::string**
and **std::recursive_mutex** types.

It is defined as:

```c++
typedef basic_event_manager<std::string, std::recursive_mutex> event_manager;
```

## typedef wevent_manager

The **wevent_manager** is a type definition for events name using **std::wstring**
and **std::recursive_mutex** types.

It is defined as:

```c++
typedef basic_event_manager<std::wstring, std::recursive_mutex> wevent_interface;
```
