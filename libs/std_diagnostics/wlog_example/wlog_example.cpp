//
//  wlog_example.cpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
int main() { return -1; }
#else

#include <go/diagnostics.hpp>

namespace l = go::diagnostics::log;

int main()
{
    GO_WLOG_FATAL << "GO_WLOG_FATAL : uninitialized";
    GO_WLOG_TRACE << "GO_WLOG_TRACE : uninitialized";

    l::initialize(l::policy::guaranteed_logger<l::wfile_writer>(), L"./", L"wlog_example", 10);
    l::set_wlog_level(l::log_level::trace);

    GO_WLOG(l::log_level::fatal) << L"GO_WLOG(l::log_level::fatal) @ trace";
    GO_WLOG(l::log_level::error) << L"GO_WLOG(l::log_level::error) @ trace";
    GO_WLOG(l::log_level::warning) << L"GO_WLOG(l::log_level::warning) @ trace";
    GO_WLOG(l::log_level::info) << L"GO_WLOG(l::log_level::info) @ trace";
    GO_WLOG(l::log_level::debug) << L"GO_WLOG(l::log_level::debug) @ trace";
    GO_WLOG(l::log_level::trace) << L"GO_WLOG(l::log_level::trace) @ trace";

    GO_WLOG_FATAL << L"GO_WLOG_FATAL @ trace";
    GO_WLOG_ERROR << L"GO_WLOG_ERROR @ trace";
    GO_WLOG_WARN << L"GO_WLOG_WARN @ trace";
    GO_WLOG_INFO << L"GO_WLOG_INFO @ trace";
    GO_WLOG_DEBUG << L"GO_WLOG_DEBUG @ trace";
    GO_WLOG_TRACE << L"GO_WLOG_TRACE @ trace";

    l::set_wlog_level(l::log_level::info);

    GO_WLOG(l::log_level::warning) << L"GO_WLOG(l::log_level::warning) @ info";
    GO_WLOG(l::log_level::info) << L"GO_WLOG(l::log_level::info) @ info";
    GO_WLOG(l::log_level::debug) << L"GO_WLOG(l::log_level::debug) @ info";

    GO_WLOG_WARN << L"GO_WLOG_WARN @ info";
    GO_WLOG_INFO << L"GO_WLOG_INFO @ info";
    GO_WLOG_DEBUG << L"GO_WLOG_DEBUG @ info";

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

    GO_WLOG_INFO << L"GO_WLOG_INFO : char ....... = " << mbc;
    GO_WLOG_INFO << L"GO_WLOG_INFO : wchar_t .... = " << swc;
    GO_WLOG_INFO << L"GO_WLOG_INFO : uint16_t ... = " << u16;
    GO_WLOG_INFO << L"GO_WLOG_INFO : uint32_t ... = " << u32;
    GO_WLOG_INFO << L"GO_WLOG_INFO : uint64_t ... = " << u64;
    GO_WLOG_INFO << L"GO_WLOG_INFO : int16_t .... = " << i16;
    GO_WLOG_INFO << L"GO_WLOG_INFO : int32_t .... = " << i32;
    GO_WLOG_INFO << L"GO_WLOG_INFO : int64_t .... = " << i64;
    GO_WLOG_INFO << L"GO_WLOG_INFO : float ...... = " << f;
    GO_WLOG_INFO << L"GO_WLOG_INFO : double ..... = " << d;
    GO_WLOG_INFO << L"GO_WLOG_INFO : bool ....... = " << b;
    GO_WLOG_INFO << L"GO_WLOG_INFO : char* ...... = " << mbs;
    GO_WLOG_INFO << L"GO_WLOG_INFO : wchar_t* ... = " << sws;
    GO_WLOG_INFO << L"GO_WLOG_INFO : std::string  = " << std_mbs;
    GO_WLOG_INFO << L"GO_WLOG_INFO : std::wstring = " << std_sws;

    l::set_wlog_level(l::log_level::none);

    GO_WLOG(l::log_level::fatal) << L"GO_WLOG(l::log_level::fatal) @ none";

    GO_WLOG_FATAL << L"GO_WLOG_WARN @ none";

    return 0;
}

#endif  // Required C++11 feature is not supported by this compiler
