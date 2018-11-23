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

    l::set_wlog_level(l::log_level::none);

    GO_WLOG(l::log_level::fatal) << L"GO_WLOG(l::log_level::fatal) @ none";

    GO_WLOG_FATAL << L"GO_WLOG_WARN @ none";

    return 0;
}

#endif  // Required C++11 feature is not supported by this compiler
