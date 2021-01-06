#ifndef GO_BOOST_DIAGNOSTICS_LOG_TIMESTAMP_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_TIMESTAMP_HPP_INCLUDED

//
//  timestamp.hpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#if defined(_MSC_VER) && (_MSC_VER <= 1500)
GO_BOOST_MSVC_BEGIN_SUPPRESS_WARNING(4189)
#endif  // #if defined(_MSC_VER) && (_MSC_VER <= 1500)

#if defined(BOOST_NO_CXX11_AUTO_DECLARATIONS)
#include <boost/typeof/std/utility.hpp>
#endif  // #if defined(BOOST_NO_CXX11_AUTO_DECLARATIONS)

#include <boost/chrono/include.hpp>
#include <cstdio>
#include <ctime>

namespace go_boost
{
namespace diagnostics
{
namespace log
{

typedef boost::chrono::microseconds::rep timestamp_type;

const timestamp_type one_second_as_microseconds = static_cast<timestamp_type>(1000000ll);

inline timestamp_type timestamp_now()
{
#if defined(GO_BOOST_COMP_MSVC)
    const timestamp_type micro_timestamp = boost::chrono::duration_cast<boost::chrono::microseconds>(boost::chrono::high_resolution_clock::now().time_since_epoch()).count();
    const std::time_t time_t_now = std::time(0);
    const timestamp_type micro_time_t_now = static_cast<timestamp_type>(time_t_now) * one_second_as_microseconds;
    const timestamp_type micro_part = micro_timestamp % one_second_as_microseconds;
    return micro_time_t_now + micro_part;
#else
    return boost::chrono::duration_cast<boost::chrono::microseconds>(boost::chrono::high_resolution_clock::now().time_since_epoch()).count();
#endif  // #if defined(GO_BOOST_COMP_MSVC)
}

inline void format_timestamp(std::ostream& os, const timestamp_type timestamp)
{
    const std::time_t time_t = static_cast<std::time_t>(timestamp / one_second_as_microseconds);
    struct tm result;
#if defined(BOOST_NO_CXX11_AUTO_DECLARATIONS)
    BOOST_AUTO(error, localtime_s(&result, &time_t));
#else
#if !defined(GO_BOOST_NO_CXX11_LOCALTIME_S)
    /*const auto error =*/ localtime_s(&result, &time_t);
#else
    /*const auto error =*/ localtime_r(&time_t, &result);
#endif  // #if !defined(GO_BOOST_NO_CXX11_LOCALTIME_S)
#endif  // #if defined(BOOST_NO_CXX11_AUTO_DECLARATIONS)
    char ymd_hms[32];
    std::strftime(ymd_hms, 32, "%Y-%m-%d %H:%M:%S.", &result);
    char microseconds[7];
#if defined(GO_BOOST_NO_CXX11_SNPRINTF)
    std::sprintf(microseconds, "%06li", static_cast<boost::int64_t>(timestamp % one_second_as_microseconds));
#else
#if defined(GO_BOOST_COMP_MSVC) || defined(GO_BOOST_COMP_GCC_MINGW)
	std::snprintf(microseconds, 7, "%06lli", static_cast<boost::int64_t>(timestamp % one_second_as_microseconds));
#else
	std::snprintf(microseconds, 7, "%06li", static_cast<boost::int64_t>(timestamp % one_second_as_microseconds));
#endif  // #if defined(GO_BOOST_COMP_MSVC) || defined(GO_BOOST_COMP_GCC_MINGW)
#endif  // #if defined(GO_BOOST_NO_CXX11_SNPRINTF)
    os << '[' << ymd_hms << microseconds << ']';
}

inline void format_timestamp(std::wostream& os, const timestamp_type timestamp)
{
    const std::time_t time_t = static_cast<std::time_t>(timestamp / one_second_as_microseconds);
    struct tm result;
#if defined(BOOST_NO_CXX11_AUTO_DECLARATIONS)
    BOOST_AUTO(error, localtime_s(&result, &time_t));
#else
#if !defined(GO_BOOST_NO_CXX11_LOCALTIME_S)
    /*const auto error =*/ localtime_s(&result, &time_t);
#else
    /*const auto error =*/ localtime_r(&time_t, &result);
#endif  // #if !defined(GO_BOOST_NO_CXX11_LOCALTIME_S)
#endif  // #if defined(BOOST_NO_CXX11_AUTO_DECLARATIONS)
    wchar_t ymd_hms[32];
    std::wcsftime(ymd_hms, 32, L"%Y-%m-%d %H:%M:%S.", &result);
    wchar_t microseconds[7];
#if defined(GO_BOOST_COMP_MSVC) || defined(GO_BOOST_COMP_GCC_MINGW)
	std::swprintf(microseconds, 7, L"%06lli", static_cast<boost::int64_t>(timestamp % one_second_as_microseconds));
#else
	std::swprintf(microseconds, 7, L"%06li", static_cast<boost::int64_t>(timestamp % one_second_as_microseconds));
#endif  // #if defined(GO_BOOST_COMP_MSVC) || defined(GO_BOOST_COMP_GCC_MINGW)
	os << L'[' << ymd_hms << microseconds << L']';
}

} // namespace log
} // namespace diagnostics
} // namespace go_boost

#if defined(_MSC_VER) && (_MSC_VER <= 1500)
GO_BOOST_MSVC_END_SUPPRESS_WARNING
#endif  // #if defined(_MSC_VER) && (_MSC_VER <= 1500)

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_TIMESTAMP_HPP_INCLUDED
