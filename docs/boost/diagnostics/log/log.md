---
layout: boost_lib_diagnostics_log
---

```c++
namespace go_boost::diagnostics::log
```

# GO Boost Diagnostics Log Library

```c++
<go_boost/diagnostics/log.hpp>
```

## Description

The **GO Boost Diagnostics Log Library** provide a fast, low latency
logging function. The implementation is much inspired by
[NanoLog](https://github.com/Iyengar111/NanoLog).

## Example

The following sample show how-to do logging with the
**GO Boost Diagnostics Log Library**. The logging framework
must be initialized to do logging. Log entries are filtered
by log level.

```c++
#include <go_boost/config.hpp>
#include <go_boost/diagnostics/log.hpp>

namespace l = go_boost::diagnostics::log;

int main()
{
    GO_BOOST_LOG_FATAL << "GO_BOOST_LOG_FATAL : uninitialized";
    GO_BOOST_LOG_TRACE << "GO_BOOST_LOG_TRACE : uninitialized";

    l::initialize(l::policy::guaranteed_logger<l::file_writer>(), "./", "log_example", 10);
    l::set_log_level(l::log_level_trace);

    GO_BOOST_LOG(l::log_level_fatal) << "GO_BOOST_LOG(l::log_level_fatal) @ trace";
    GO_BOOST_LOG(l::log_level_error) << "GO_BOOST_LOG(l::log_level_error) @ trace";
    GO_BOOST_LOG(l::log_level_warning) << "GO_BOOST_LOG(l::log_level_warning) @ trace";
    GO_BOOST_LOG(l::log_level_info) << "GO_BOOST_LOG(l::log_level_info) @ trace";
    GO_BOOST_LOG(l::log_level_debug) << "GO_BOOST_LOG(l::log_level_debug) @ trace";
    GO_BOOST_LOG(l::log_level_trace) << "GO_BOOST_LOG(l::log_level_trace) @ trace";

    GO_BOOST_LOG_FATAL << "GO_BOOST_LOG_FATAL @ trace";
    GO_BOOST_LOG_ERROR << "GO_BOOST_LOG_ERROR @ trace";
    GO_BOOST_LOG_WARN << "GO_BOOST_LOG_WARN @ trace";
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO @ trace";
    GO_BOOST_LOG_DEBUG << "GO_BOOST_LOG_DEBUG @ trace";
    GO_BOOST_LOG_TRACE << "GO_BOOST_LOG_TRACE @ trace";

    l::set_log_level(l::log_level_info);

    GO_BOOST_LOG(l::log_level_warning) << "GO_BOOST_LOG(l::log_level_warning) @ info";
    GO_BOOST_LOG(l::log_level_info) << "GO_BOOST_LOG(l::log_level_info) @ info";
    GO_BOOST_LOG(l::log_level_debug) << "GO_BOOST_LOG(l::log_level_debug) @ info";

    GO_BOOST_LOG_WARN << "GO_BOOST_LOG_WARN @ info";
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO @ info";
    GO_BOOST_LOG_DEBUG << "GO_BOOST_LOG_DEBUG @ info";

    const char mbc = 'A';
    const wchar_t swc = L'B';
    const boost::uint16_t u16 = 16;
    const boost::uint32_t u32 = 32;
    const boost::uint64_t u64 = 64;
    const boost::int16_t i16 = -16;
    const boost::int32_t i32 = -32;
    const boost::int64_t i64 = -64;
    const float f = 123.456f;
    const double d = 1234.5678;
    const bool b = true;
    const char* mbs = "Multibyte string";
    const wchar_t* sws = L"System wide string";
    const std::string boost_mbs("std::string");
    const std::wstring boost_sws(L"std::wstring");

    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO : char ....... = " << mbc;
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO : wchar_t .... = " << swc;
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO : uint16_t ... = " << u16;
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO : uint32_t ... = " << u32;
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO : uint64_t ... = " << u64;
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO : int16_t .... = " << i16;
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO : int32_t .... = " << i32;
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO : int64_t .... = " << i64;
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO : float ...... = " << f;
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO : double ..... = " << d;
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO : bool ....... = " << b;
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO : char* ...... = " << mbs;
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO : wchar_t* ... = " << sws;
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO : std::string  = " << boost_mbs;
    GO_BOOST_LOG_INFO << "GO_BOOST_LOG_INFO : std::wstring = " << boost_sws;

    l::set_log_level(l::log_level_none);

    GO_BOOST_LOG(l::log_level_fatal) << "GO_BOOST_LOG(l::log_level_fatal) @ none";

    GO_BOOST_LOG_FATAL << "GO_BOOST_LOG_WARN @ none";

    return 0;
}

```

Output

```
[2018-12-23 19:20:10.491440][FATAL][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):24] GO_BOOST_LOG(l::log_level_fatal) @ trace
[2018-12-23 19:20:10.491490][ERROR][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):25] GO_BOOST_LOG(l::log_level_error) @ trace
[2018-12-23 19:20:10.491503][WARN][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):26] GO_BOOST_LOG(l::log_level_warning) @ trace
[2018-12-23 19:20:10.491510][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):27] GO_BOOST_LOG(l::log_level_info) @ trace
[2018-12-23 19:20:10.491512][DEBUG][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):28] GO_BOOST_LOG(l::log_level_debug) @ trace
[2018-12-23 19:20:10.491513][TRACE][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):29] GO_BOOST_LOG(l::log_level_trace) @ trace
[2018-12-23 19:20:10.491515][FATAL][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):31] GO_BOOST_LOG_FATAL @ trace
[2018-12-23 19:20:10.491516][ERROR][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):32] GO_BOOST_LOG_ERROR @ trace
[2018-12-23 19:20:10.491517][WARN][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):33] GO_BOOST_LOG_WARN @ trace
[2018-12-23 19:20:10.491518][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):34] GO_BOOST_LOG_INFO @ trace
[2018-12-23 19:20:10.491519][DEBUG][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):35] GO_BOOST_LOG_DEBUG @ trace
[2018-12-23 19:20:10.491521][TRACE][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):36] GO_BOOST_LOG_TRACE @ trace
[2018-12-23 19:20:10.491522][WARN][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):40] GO_BOOST_LOG(l::log_level_warning) @ info
[2018-12-23 19:20:10.491523][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):41] GO_BOOST_LOG(l::log_level_info) @ info
[2018-12-23 19:20:10.491524][WARN][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):44] GO_BOOST_LOG_WARN @ info
[2018-12-23 19:20:10.491532][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):45] GO_BOOST_LOG_INFO @ info
[2018-12-23 19:20:10.491551][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):64] GO_BOOST_LOG_INFO : char ....... = A
[2018-12-23 19:20:10.491553][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):65] GO_BOOST_LOG_INFO : wchar_t .... = 66
[2018-12-23 19:20:10.491555][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):66] GO_BOOST_LOG_INFO : uint16_t ... = 16
[2018-12-23 19:20:10.491556][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):67] GO_BOOST_LOG_INFO : uint32_t ... = 32
[2018-12-23 19:20:10.491557][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):68] GO_BOOST_LOG_INFO : uint64_t ... = 64
[2018-12-23 19:20:10.491558][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):69] GO_BOOST_LOG_INFO : int16_t .... = -16
[2018-12-23 19:20:10.491560][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):70] GO_BOOST_LOG_INFO : int32_t .... = -32
[2018-12-23 19:20:10.491561][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):71] GO_BOOST_LOG_INFO : int64_t .... = -64
[2018-12-23 19:20:10.491562][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):72] GO_BOOST_LOG_INFO : float ...... = 123.456
[2018-12-23 19:20:10.491564][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):73] GO_BOOST_LOG_INFO : double ..... = 1234.57
[2018-12-23 19:20:10.491571][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):74] GO_BOOST_LOG_INFO : bool ....... = 1
[2018-12-23 19:20:10.491572][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):75] GO_BOOST_LOG_INFO : char* ...... = Multibyte string
[2018-12-23 19:20:10.491574][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):76] GO_BOOST_LOG_INFO : wchar_t* ... = System wide string
[2018-12-23 19:20:10.515431][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):77] GO_BOOST_LOG_INFO : std::string  = std::string
[2018-12-23 19:20:10.515435][INFO][2b58][C:\go_libs\libs\boost_diagnostics\log_example\log_example.cpp:int __cdecl main(void):78] GO_BOOST_LOG_INFO : std::wstring = std::wstring
```

## Reference

### Nested namespaces

* [policy](./policy/policy.html)

### Class reference

* [go_boost\::diagnostics\::log\::**basic_file_writer**](./class_template_basic_file_writer.html)
  * [go_boost\::diagnostics\::log\::**file_writer**](./class_template_basic_file_writer.html)
  * [go_boost\::diagnostics\::log\::**wfile_writer**](./class_template_basic_file_writer.html)
* [go_boost\::diagnostics\::log\::**basic_log_line**](./class_template_basic_log_line.html)
  * [go_boost\::diagnostics\::log\::**log_line**](./class_template_basic_log_line.html)
  * [go_boost\::diagnostics\::log\::**wlog_line**](./class_template_basic_log_line.html)
* [go_boost\::diagnostics\::log\::**log**](./class_log.html)
* [go_boost\::diagnostics\::log\::**log_level**](./enum_log_level.html)
* [go_boost\::diagnostics\::log\::**wlog**](./class_log.html)

### Function reference

* [format_timestamp](./function_timestamp.html)
* [this_thread_id](./function_this_thread_id.html)
* [timestamp_now](./function_timestamp.html)
* [to_string](./enum_log_level.html)
