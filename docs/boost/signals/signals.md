---
layout: boost_lib_signals
---

```c++
namespace go_boost::signals
```

# GO Boost Signals Library

```c++
<go_boost/signals.hpp>
```

## Description

**Signals**

A **signal** represent a callback with multiple targets. Signals are connected to 
some set of slots, which are callback receivers. The slots are called when the 
**signal** is *"emitted"*.

The signals in the **Boost.Signals2** library provide a good framework for 
implementing C#-style events and delegates. Unfortunately the C++ Standard 
Library have no alternative to **Boost.Signals2**. 

The **GO Signals Library** is not an actual library. It only include the 
**Boost.Signals2** library.
