#ifndef GO_BOOST_DIAGNOSTICS_LOG_LOG_LEVEL_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_LOG_LEVEL_HPP_INCLUDED

//
//  log_level.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

namespace go_boost
{
namespace diagnostics
{
namespace log
{

enum log_level
{
    log_level_none = 0,
    log_level_fatal = 1,
    log_level_error = 2,
    log_level_warning = 3,
    log_level_info = 4,
    log_level_debug = 5,
    log_level_trace = 6,
    log_level_all = 7,
    log_level_undefined = ~0
};

inline const std::string::value_type* to_string(const log_level& loglevel)
{
    static const std::string::value_type* none = "NONE";
    static const std::string::value_type* fatal = "FATAL";
    static const std::string::value_type* error = "ERROR";
    static const std::string::value_type* warn = "WARN";
    static const std::string::value_type* info = "INFO";
    static const std::string::value_type* debug = "DEBUG";
    static const std::string::value_type* trace = "TRACE";
    static const std::string::value_type* all = "ALL";
    static const std::string::value_type* undefined = "UNDEFINED";

    switch (loglevel)
    {
    case log_level_none:
        return none;
    case log_level_fatal:
        return fatal;
    case log_level_error:
        return error;
    case log_level_warning:
        return warn;
    case log_level_info:
        return info;
    case log_level_debug:
        return debug;
    case log_level_trace:
        return trace;
    case log_level_all:
        return all;
    case log_level_undefined:
    default:
        break;
    }
    return undefined;
}

inline const std::wstring::value_type* to_wstring(const log_level& loglevel)
{
    static const std::wstring::value_type* none = L"NONE";
    static const std::wstring::value_type* fatal = L"FATAL";
    static const std::wstring::value_type* error = L"ERROR";
    static const std::wstring::value_type* warn = L"WARN";
    static const std::wstring::value_type* info = L"INFO";
    static const std::wstring::value_type* debug = L"DEBUG";
    static const std::wstring::value_type* trace = L"TRACE";
    static const std::wstring::value_type* all = L"ALL";
    static const std::wstring::value_type* undefined = L"UNDEFINED";

    switch (loglevel)
    {
    case log_level_none:
        return none;
    case log_level_fatal:
        return fatal;
    case log_level_error:
        return error;
    case log_level_warning:
        return warn;
    case log_level_info:
        return info;
    case log_level_debug:
        return debug;
    case log_level_trace:
        return trace;
    case log_level_all:
        return all;
    case log_level_undefined:
    default:
        break;
    }
    return undefined;
}

} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_LOG_LEVEL_HPP_INCLUDED
