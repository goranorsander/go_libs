//
//  wlog_example.cpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_boost/diagnostics.hpp>
#include <go_boost/namespace_alias.hpp>

int main()
{
    GO_BOOST_WLOG_FATAL << "GO_BOOST_WLOG_FATAL : uninitialized";
    GO_BOOST_WLOG_TRACE << "GO_BOOST_WLOG_TRACE : uninitialized";

    dl::initialize(dl::policy::guaranteed_logger<dl::wfile_writer>(), L"./", L"wlog_example", 10);
    dl::set_wlog_level(dl::log_level_trace);

    GO_BOOST_WLOG(dl::log_level_fatal) << L"GO_BOOST_WLOG(dl::log_level_fatal) @ trace";
    GO_BOOST_WLOG(dl::log_level_error) << L"GO_BOOST_WLOG(dl::log_level_error) @ trace";
    GO_BOOST_WLOG(dl::log_level_warning) << L"GO_BOOST_WLOG(dl::log_level_warning) @ trace";
    GO_BOOST_WLOG(dl::log_level_info) << L"GO_BOOST_WLOG(dl::log_level_info) @ trace";
    GO_BOOST_WLOG(dl::log_level_debug) << L"GO_BOOST_WLOG(dl::log_level_debug) @ trace";
    GO_BOOST_WLOG(dl::log_level_trace) << L"GO_BOOST_WLOG(dl::log_level_trace) @ trace";

    GO_BOOST_WLOG_FATAL << L"GO_BOOST_WLOG_FATAL @ trace";
    GO_BOOST_WLOG_ERROR << L"GO_BOOST_WLOG_ERROR @ trace";
    GO_BOOST_WLOG_WARN << L"GO_BOOST_WLOG_WARN @ trace";
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO @ trace";
    GO_BOOST_WLOG_DEBUG << L"GO_BOOST_WLOG_DEBUG @ trace";
    GO_BOOST_WLOG_TRACE << L"GO_BOOST_WLOG_TRACE @ trace";

    dl::set_wlog_level(dl::log_level_info);

    GO_BOOST_WLOG(dl::log_level_warning) << L"GO_BOOST_WLOG(dl::log_level_warning) @ info";
    GO_BOOST_WLOG(dl::log_level_info) << L"GO_BOOST_WLOG(dl::log_level_info) @ info";
    GO_BOOST_WLOG(dl::log_level_debug) << L"GO_BOOST_WLOG(dl::log_level_debug) @ info";

    GO_BOOST_WLOG_WARN << L"GO_BOOST_WLOG_WARN @ info";
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO @ info";
    GO_BOOST_WLOG_DEBUG << L"GO_BOOST_WLOG_DEBUG @ info";

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
    const std::string std_mbs("std::string");
    const std::wstring std_sws(L"std::wstring");

    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO : char ....... = " << mbc;
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO : wchar_t .... = " << swc;
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO : uint16_t ... = " << u16;
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO : uint32_t ... = " << u32;
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO : uint64_t ... = " << u64;
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO : int16_t .... = " << i16;
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO : int32_t .... = " << i32;
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO : int64_t .... = " << i64;
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO : float ...... = " << f;
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO : double ..... = " << d;
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO : bool ....... = " << b;
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO : char* ...... = " << mbs;
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO : wchar_t* ... = " << sws;
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO : std::string  = " << std_mbs;
    GO_BOOST_WLOG_INFO << L"GO_BOOST_WLOG_INFO : std::wstring = " << std_sws;

    dl::set_wlog_level(dl::log_level_none);

    GO_BOOST_WLOG(dl::log_level_fatal) << L"GO_BOOST_WLOG(dl::log_level_fatal) @ none";

    GO_BOOST_WLOG_FATAL << L"GO_BOOST_WLOG_WARN @ none";

    return 0;
}
