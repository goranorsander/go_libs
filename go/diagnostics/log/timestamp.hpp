#ifndef GO_DIAGNOSTICS_LOG_TIMESTAMP_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_TIMESTAMP_HPP_INCLUDED

//
//  timestamp.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/diagnostics/log/log_line.hpp>

#include <chrono>
#include <ctime>

namespace go
{
namespace diagnostics
{
namespace log
{

typedef std::chrono::microseconds::rep timestamp_type;

const timestamp_type one_second_as_microseconds = static_cast<timestamp_type>(1000000ll);

inline timestamp_type timestamp_now()
{
#if defined(GO_COMP_MSVC)
    const timestamp_type micro_timestamp = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    const std::time_t time_t_now = std::time(0);
    const timestamp_type micro_time_t_now = static_cast<timestamp_type>(time_t_now) * one_second_as_microseconds;
    const timestamp_type micro_part = micro_timestamp % one_second_as_microseconds;
    return micro_time_t_now + micro_part;
#else
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
#endif  // #if defined(GO_COMP_MSVC)
}

inline void format_timestamp(std::ostream& os, const timestamp_type timestamp)
{
#if defined(GO_COMP_MSVC)
    const std::time_t time_t = static_cast<std::time_t>(timestamp / one_second_as_microseconds);
#else
    const auto duration = std::chrono::microseconds(timestamp);
    const std::chrono::high_resolution_clock::time_point time_point(duration);
    const std::time_t time_t = std::chrono::high_resolution_clock::to_time_t(time_point);
#endif  // #if defined(GO_COMP_MSVC)
    struct tm result;
    const auto error = localtime_s(&result, &time_t);
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %T.", &result);
    char microseconds[7];
    std::snprintf(microseconds, sizeof(microseconds), "%06lli", static_cast<int64_t>(timestamp % one_second_as_microseconds));
    os << '[' << buffer << microseconds << ']';
}

inline void format_timestamp(std::wostream& os, const timestamp_type timestamp)
{
#if defined(GO_COMP_MSVC)
    const std::time_t time_t = static_cast<std::time_t>(timestamp / one_second_as_microseconds);
#else
    const auto duration = std::chrono::microseconds(timestamp);
    const std::chrono::high_resolution_clock::time_point time_point(duration);
    const std::time_t time_t = std::chrono::high_resolution_clock::to_time_t(time_point);
#endif  // #if defined(GO_COMP_MSVC)
    struct tm result;
    const auto error = localtime_s(&result, &time_t);
    wchar_t buffer[32];
    std::wcsftime(buffer, sizeof(buffer), L"%Y-%m-%d %T.", &result);
    wchar_t microseconds[7];
    std::swprintf(microseconds, sizeof(microseconds), L"%06lli", static_cast<int64_t>(timestamp % one_second_as_microseconds));
    os << L'[' << buffer << microseconds << L']';
}

} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_TIMESTAMP_HPP_INCLUDED
