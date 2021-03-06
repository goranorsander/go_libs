#ifndef GO_DIAGNOSTICS_LOG_TIMESTAMP_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_TIMESTAMP_HPP_INCLUDED

//
//  timestamp.hpp
//
//  Copyright 2018-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <chrono>
#include <cstdio>
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
#if !defined(GO_NO_CXX11_LOCALTIME_S)
    /*const auto error =*/ localtime_s(&result, &time_t);
#else
    /*const auto error =*/ localtime_r(&time_t, &result);
#endif  // #if !defined(GO_NO_CXX11_LOCALTIME_S)
    char ymd_hms[32];
	GO_GCC_BEGIN_SUPPRESS_WARNING(format)
    std::strftime(ymd_hms, 32, "%Y-%m-%d %T.", &result);
	GO_GCC_END_SUPPRESS_WARNING
    char microseconds[7];
#if defined(GO_NO_CXX11_SNPRINTF)
    std::sprintf(microseconds, "%06li", static_cast<int64_t>(timestamp % one_second_as_microseconds));
#else
#if defined(GO_COMP_MSVC) || defined(GO_COMP_GCC_MINGW)
	std::snprintf(microseconds, 7, "%06lli", static_cast<int64_t>(timestamp % one_second_as_microseconds));
#else
    std::snprintf(microseconds, 7, "%06li", static_cast<int64_t>(timestamp % one_second_as_microseconds));
#endif  // #if defined(GO_COMP_MSVC) || defined(GO_COMP_GCC_MINGW)
#endif  // #if defined(GO_NO_CXX11_SNPRINTF)
#if defined(GO_COMP_GCC)
    os << std::string("[") << std::string(ymd_hms) << std::string(microseconds) << std::string("]");
#else
    os << '[' << ymd_hms << microseconds << ']';
#endif  // #if defined(GO_COMP_GCC)
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
#if !defined(GO_NO_CXX11_LOCALTIME_S)
    /*const auto error =*/ localtime_s(&result, &time_t);
#else
    /*const auto error =*/ localtime_r(&time_t, &result);
#endif  // #if !defined(GO_NO_CXX11_LOCALTIME_S)
    wchar_t ymd_hms[32];
	GO_GCC_BEGIN_SUPPRESS_WARNING(format)
    std::wcsftime(ymd_hms, 32, L"%Y-%m-%d %T.", &result);
	GO_GCC_END_SUPPRESS_WARNING
    wchar_t microseconds[7];
#if defined(GO_COMP_MSVC) || defined(GO_COMP_GCC_MINGW)
	std::swprintf(microseconds, 7, L"%06lli", static_cast<int64_t>(timestamp % one_second_as_microseconds));
#else
	std::swprintf(microseconds, 7, L"%06li", static_cast<int64_t>(timestamp % one_second_as_microseconds));
#endif  // #if defined(GO_COMP_MSVC) || defined(GO_COMP_GCC_MINGW)
#if defined(GO_COMP_GCC)
    os << std::wstring(L"[") << std::wstring(ymd_hms) << std::wstring(microseconds) << std::wstring(L"]");
#else
    os << L'[' << ymd_hms << microseconds << L']';
#endif  // #if defined(GO_COMP_GCC)
}

} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_TIMESTAMP_HPP_INCLUDED
