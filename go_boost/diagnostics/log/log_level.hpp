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

inline std::string::value_type* to_string(const log_level& loglevel)
{
    switch (loglevel)
    {
    case log_level_none:
        return "NONE";
    case log_level_fatal:
        return "FATAL";
    case log_level_error:
        return "ERROR";
    case log_level_warning:
        return "WARN";
    case log_level_info:
        return "INFO";
    case log_level_debug:
        return "DEBUG";
    case log_level_trace:
        return "TRACE";
    case log_level_all:
        return "ALL";
    case log_level_undefined:
    default:
        break;
    }
    return "UNDEFINED";
}

inline std::wstring::value_type* to_wstring(const log_level& loglevel)
{
    switch (loglevel)
    {
    case log_level_none:
        return L"NONE";
    case log_level_fatal:
        return L"FATAL";
    case log_level_error:
        return L"ERROR";
    case log_level_warning:
        return L"WARN";
    case log_level_info:
        return L"INFO";
    case log_level_debug:
        return L"DEBUG";
    case log_level_trace:
        return L"TRACE";
    case log_level_all:
        return L"ALL";
    case log_level_undefined:
    default:
        break;
    }
    return L"UNDEFINED";
}

} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_LOG_LEVEL_HPP_INCLUDED
