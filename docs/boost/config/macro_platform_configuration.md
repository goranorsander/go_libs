---
layout: boost_lib_config
---

```c++
namespace go_boost::config
```

# Platform configuration

```c++
<go_boost/config.hpp>
```

## Platform information

Macros that are defined depending on platform.

Macro | Description
-|-
GO_BOOST_PLATFORM_LINUX | Platform is [Linux](https://en.wikipedia.org/wiki/Linux)
GO_BOOST_PLATFORM_WINDOWS | Platform is [Microsoft Windows](https://en.wikipedia.org/wiki/Microsoft_Windows)

## Address model

Macros that are defined depending on address model.

Macro | Description
-|-
GO_BOOST_ADDRESS_MODEL_32 | Address model is 32 bits
GO_BOOST_ADDRESS_MODEL_64 | Address model is 64 bits
GO_BOOST_L(i) | Append **l** or **ll** to integer number *i* depending on address model, **l** for 32 bits and **ll** for 64 bits
GO_BOOST_UL(i) | Append **ul** or **ull** to unsigned integer number *i* depending on address model, **ul** for 32 bits and **ull** for 64 bits

## Platform dependent types

Macros that are defined depending on platform.

Macro | Description
GO_BOOST_SIZE_OF_WCHAR_T | Size in bytes of **wchar_t**
