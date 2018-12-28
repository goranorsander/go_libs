---
layout: std_lib_config
---

```c++
namespace go::config
```

# Platform configuration

```c++
<go/config.hpp>
```

## Platform information

Macros that are defined if compiler is **clang**.

Macro | Description
-|-
GO_PLATFORM_LINUX | Platform is [Linux](https://en.wikipedia.org/wiki/Linux)
GO_PLATFORM_WINDOWS | Platform is [Microsoft Windows](https://en.wikipedia.org/wiki/Microsoft_Windows)

## Address model

Macros that are defined if compiler is **gcc**.

Macro | Description
-|-
GO_ADDRESS_MODEL_32 | Address model is 32 bits
GO_ADDRESS_MODEL_64 | Address model is 64 bits
