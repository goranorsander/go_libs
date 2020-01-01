//
//  log_example.cpp
//
//  Copyright 2018-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
int main() { return -1; }
#else

#include <go/diagnostics.hpp>
#include <go/namespace_alias.hpp>

int main()
{
    GO_LOG_FATAL << "GO_LOG_FATAL : uninitialized";
    GO_LOG_TRACE << "GO_LOG_TRACE : uninitialized";

    dl::initialize(dl::policy::guaranteed_logger<dl::file_writer>(), "./", "log_example", 10);
    dl::set_log_level(dl::log_level::trace);

    GO_LOG(dl::log_level::fatal) << "GO_LOG(dl::log_level::fatal) @ trace";
    GO_LOG(dl::log_level::error) << "GO_LOG(dl::log_level::error) @ trace";
    GO_LOG(dl::log_level::warning) << "GO_LOG(dl::log_level::warning) @ trace";
    GO_LOG(dl::log_level::info) << "GO_LOG(dl::log_level::info) @ trace";
    GO_LOG(dl::log_level::debug) << "GO_LOG(dl::log_level::debug) @ trace";
    GO_LOG(dl::log_level::trace) << "GO_LOG(dl::log_level::trace) @ trace";

    GO_LOG_FATAL << "GO_LOG_FATAL @ trace";
    GO_LOG_ERROR << "GO_LOG_ERROR @ trace";
    GO_LOG_WARN << "GO_LOG_WARN @ trace";
    GO_LOG_INFO << "GO_LOG_INFO @ trace";
    GO_LOG_DEBUG << "GO_LOG_DEBUG @ trace";
    GO_LOG_TRACE << "GO_LOG_TRACE @ trace";

    dl::set_log_level(dl::log_level::info);

    GO_LOG(dl::log_level::warning) << "GO_LOG(dl::log_level::warning) @ info";
    GO_LOG(dl::log_level::info) << "GO_LOG(dl::log_level::info) @ info";
    GO_LOG(dl::log_level::debug) << "GO_LOG(dl::log_level::debug) @ info";

    GO_LOG_WARN << "GO_LOG_WARN @ info";
    GO_LOG_INFO << "GO_LOG_INFO @ info";
    GO_LOG_DEBUG << "GO_LOG_DEBUG @ info";

    const char mbc = 'A';
    const wchar_t swc = L'B';
    const uint16_t u16 = 16;
    const uint32_t u32 = 32;
    const uint64_t u64 = 64;
    const int16_t i16 = -16;
    const int32_t i32 = -32;
    const int64_t i64 = -64;
    const float f = 123.456f;
    const double d = 1234.5678;
    const bool b = true;
    const char* mbs = "Multibyte string";
    const wchar_t* sws = L"System wide string";
    const std::string std_mbs("std::string");
    const std::wstring std_sws(L"std::wstring");

    GO_LOG_INFO << "GO_LOG_INFO : char ....... = " << mbc;
    GO_LOG_INFO << "GO_LOG_INFO : wchar_t .... = " << swc;
    GO_LOG_INFO << "GO_LOG_INFO : uint16_t ... = " << u16;
    GO_LOG_INFO << "GO_LOG_INFO : uint32_t ... = " << u32;
    GO_LOG_INFO << "GO_LOG_INFO : uint64_t ... = " << u64;
    GO_LOG_INFO << "GO_LOG_INFO : int16_t .... = " << i16;
    GO_LOG_INFO << "GO_LOG_INFO : int32_t .... = " << i32;
    GO_LOG_INFO << "GO_LOG_INFO : int64_t .... = " << i64;
    GO_LOG_INFO << "GO_LOG_INFO : float ...... = " << f;
    GO_LOG_INFO << "GO_LOG_INFO : double ..... = " << d;
    GO_LOG_INFO << "GO_LOG_INFO : bool ....... = " << b;
    GO_LOG_INFO << "GO_LOG_INFO : char* ...... = " << mbs;
    GO_LOG_INFO << "GO_LOG_INFO : wchar_t* ... = " << sws;
    GO_LOG_INFO << "GO_LOG_INFO : std::string  = " << std_mbs;
    GO_LOG_INFO << "GO_LOG_INFO : std::wstring = " << std_sws;

    dl::set_log_level(dl::log_level::none);

    GO_LOG(dl::log_level::fatal) << "GO_LOG(dl::log_level::fatal) @ none";

    GO_LOG_FATAL << "GO_LOG_WARN @ none";

    return 0;
}

#endif  // Required C++11 feature is not supported by this compiler
