#ifndef GO_DIAGNOSTICS_LOG_LOG_LEVEL_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_LOG_LEVEL_HPP_INCLUDED

//
//  log_level.hpp
//
//  Copyright 2018-2021 Göran Orsander
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
#if defined(GO_NO_CXX11_FIXED_WIDTH_INTEGER_TYPES)
    : char
#else
    : int8_t
#endif  // #if defined(GO_NO_CXX11_FIXED_WIDTH_INTEGER_TYPES)
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
    case log_level::none:
        return none;
    case log_level::fatal:
        return fatal;
    case log_level::error:
        return error;
    case log_level::warning:
        return warn;
    case log_level::info:
        return info;
    case log_level::debug:
        return debug;
    case log_level::trace:
        return trace;
    case log_level::all:
        return all;
    case log_level::undefined:
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
    case log_level::none:
        return none;
    case log_level::fatal:
        return fatal;
    case log_level::error:
        return error;
    case log_level::warning:
        return warn;
    case log_level::info:
        return info;
    case log_level::debug:
        return debug;
    case log_level::trace:
        return trace;
    case log_level::all:
        return all;
    case log_level::undefined:
    default:
        break;
    }
    return undefined;
}

} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // #ifndef GO_DIAGNOSTICS_LOG_LOG_LEVEL_HPP_INCLUDED
