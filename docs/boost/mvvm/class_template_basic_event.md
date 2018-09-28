---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# class template basic_event

```c++
<go_boost/mvvm.hpp>
```

**Generic event interface**

The **basic_event** is a generalization class for events. An event is a notification
that something of interest occured. The event shall preferably hold all information
necessary to describe what happened and allow the application and/or user to react.

It is declared as:

```c++
template<class S>
class basic_event
    : public boost::enable_shared_from_this<basic_event<S>>
    , public go_boost::utility::noncopyable_nonmovable
{
public:
    virtual ~basic_event();

protected:
    explicit basic_event(const S& event_type_);

public:
    event_type_type event_type;

public:
    static ptr create(const S& event_type_);

private:
    const S _event_type;
};
```

## Template parameters

Parameter | Description
-|-
S | The event string class

## Member types

Member type | Definition
-|-
string_type | S
this_type | basic_event<S>
ptr | boost\::shared_ptr<basic_event<S>>
wptr | boost\::weak_ptr<basic_event<S>>
event_type_type | go_boost\::property\::nameless\::read_only\::property<S>

## Member properties

Property type | Property name
-|-
event_type_type | event_type

### Property event_type

Gets the type of the event.

## Static member functions

### create

Specifiers | Signature
-|-
public static | ptr **create**(const S& event_type_)

Constructs a new **basic_event** object and return it as a
**basic_event<string_type>\::ptr** object.

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_event** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*constructor (1)* | protected explicit | **basic_event**(const S& event_type_)

1. Constructs a **basic_event** object with an event type.

# class template basic_event specializations

## typedef event

The **event** is a type definition for event names using **std::string** type.

It is defined as:

```c++
typedef basic_event<std::string> event;
```

## typedef wevent

The **wevent** is a type definition for event names using **std::wstring** type.

It is defined as:

```c++
typedef basic_event<std::wstring> wevent;
```
