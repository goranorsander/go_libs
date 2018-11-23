#ifndef GO_DIAGNOSTICS_LOG_LOG_LEVEL_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_LOG_LEVEL_HPP_INCLUDED

//
//  log_level.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

namespace go
{
namespace diagnostics
{
namespace log
{

enum class log_level
    : int8_t
{
    none = 0,
    fatal = 1,
    error = 2,
    warning = 3,
    info = 4,
    debug = 5,
    trace = 6,
    all = 7,
    undefined = ~0
};

inline std::string::value_type* to_string(const log_level& loglevel)
{
    switch (loglevel)
    {
    case log_level::none:
        return "NONE";
    case log_level::fatal:
        return "FATAL";
    case log_level::error:
        return "ERROR";
    case log_level::warning:
        return "WARN";
    case log_level::info:
        return "INFO";
    case log_level::debug:
        return "DEBUG";
    case log_level::trace:
        return "TRACE";
    case log_level::all:
        return "ALL";
    case log_level::undefined:
    default:
        break;
    }
    return "UNDEFINED";
}

inline std::wstring::value_type* to_wstring(const log_level& loglevel)
{
    switch (loglevel)
    {
    case log_level::none:
        return L"NONE";
    case log_level::fatal:
        return L"FATAL";
    case log_level::error:
        return L"ERROR";
    case log_level::warning:
        return L"WARN";
    case log_level::info:
        return L"INFO";
    case log_level::debug:
        return L"DEBUG";
    case log_level::trace:
        return L"TRACE";
    case log_level::all:
        return L"ALL";
    case log_level::undefined:
    default:
        break;
    }
    return L"UNDEFINED";
}

} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // #ifndef GO_DIAGNOSTICS_LOG_LOG_LEVEL_HPP_INCLUDED
