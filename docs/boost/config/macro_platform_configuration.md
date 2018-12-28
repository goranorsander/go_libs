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

Macros that are defined if compiler is **clang**.

Macro | Description
-|-
GO_BOOST_PLATFORM_LINUX | Platform is [Linux](https://en.wikipedia.org/wiki/Linux)
GO_BOOST_PLATFORM_WINDOWS | Platform is [Microsoft Windows](https://en.wikipedia.org/wiki/Microsoft_Windows)

## Address model

Macros that are defined if compiler is **gcc**.

Macro | Description
-|-
GO_BOOST_ADDRESS_MODEL_32 | Address model is 32 bits
GO_BOOST_ADDRESS_MODEL_64 | Address model is 64 bits
