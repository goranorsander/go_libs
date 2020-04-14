---
layout: std_lib_utility
---

```c++
namespace go::utility
```

# class template value_guard

```c++
<go/utility/value_guard.hpp>
```

The **value_guard** is a class template that restore an associated objects original
value on destruction, typically on scope exit.

It is declared as:

```c++
template<class Facet> struct deletable_facet
    : Facet
{
    typedef Facet facet_type;
    typedef deletable_facet<facet_type> this_type;

    using Facet::Facet; // Inherit constructors

    ~deletable_facet() GO_DEFAULT_DESTRUCTOR
};
```

## Template parameters

Parameter | Description
-|-
Facet | The facet class

## Member types

Member type | Definition
-|-
this_type | deletable_facet\<Facet>
facet_type | Facet

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **deletable_facet** object.

### Constructor

Same as the inherited **Facet** class.
