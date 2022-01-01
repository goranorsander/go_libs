#ifndef GO_BOOST_DIAGNOSTICS_LOG_LOG_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_LOG_HPP_INCLUDED

//
//  log.hpp
//
//  Copyright 2018-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/diagnostics/log/detail/logger.hpp>
#include <go_boost/diagnostics/log/log_line.hpp>
#include <go_boost/diagnostics/log/policy/guaranteed_logger.hpp>
#include <go_boost/diagnostics/log/policy/non_guaranteed_logger.hpp>

#define GO_BOOST_LOG(level) go_boost::diagnostics::log::is_logged(level) && go_boost::diagnostics::log::log() == go_boost::diagnostics::log::log_line(level, __FILE__, GO_BOOST_FUNC, __LINE__)
#define GO_BOOST_LOG_FATAL GO_BOOST_LOG(go_boost::diagnostics::log::log_level_fatal)
#define GO_BOOST_LOG_ERROR GO_BOOST_LOG(go_boost::diagnostics::log::log_level_error)
#define GO_BOOST_LOG_WARN GO_BOOST_LOG(go_boost::diagnostics::log::log_level_warning)
#define GO_BOOST_LOG_INFO GO_BOOST_LOG(go_boost::diagnostics::log::log_level_info)
#define GO_BOOST_LOG_DEBUG GO_BOOST_LOG(go_boost::diagnostics::log::log_level_debug)
#define GO_BOOST_LOG_TRACE GO_BOOST_LOG(go_boost::diagnostics::log::log_level_trace)

#define GO_BOOST_WLOG(level) go_boost::diagnostics::log::is_wlogged(level) && go_boost::diagnostics::log::wlog() == go_boost::diagnostics::log::wlog_line(level, GO_BOOST_WFILE, GO_BOOST_WFUNC, __LINE__)
#define GO_BOOST_WLOG_FATAL GO_BOOST_WLOG(go_boost::diagnostics::log::log_level_fatal)
#define GO_BOOST_WLOG_ERROR GO_BOOST_WLOG(go_boost::diagnostics::log::log_level_error)
#define GO_BOOST_WLOG_WARN GO_BOOST_WLOG(go_boost::diagnostics::log::log_level_warning)
#define GO_BOOST_WLOG_INFO GO_BOOST_WLOG(go_boost::diagnostics::log::log_level_info)
#define GO_BOOST_WLOG_DEBUG GO_BOOST_WLOG(go_boost::diagnostics::log::log_level_debug)
#define GO_BOOST_WLOG_TRACE GO_BOOST_WLOG(go_boost::diagnostics::log::log_level_trace)

namespace go_boost
{
namespace diagnostics
{
namespace log
{

class log
    : go_boost::type_traits::noncopyable_nonmovable
{
public:
    virtual ~log() GO_BOOST_DEFAULT_DESTRUCTOR
    log() GO_BOOST_DEFAULT_CONSTRUCTOR

    bool operator==(log_line& logline)
    {
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        logger_atom().load(boost::memory_order_acquire)->add(std::move(logline));
#else
        logger_atom().load(boost::memory_order_acquire)->add(logline);
#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        return true;
    }

    static detail::logger_atm& logger_atom()
    {
        static detail::logger_atm atom;
        return atom;
    }

    static detail::logger_ptr& logger_instance()
    {
        static detail::logger_ptr instance;
        return instance;
    }

    static boost::atomic<unsigned int>& log_level()
    {
#if !defined(GO_BOOST_COMP_CLANG)
        static boost::atomic<unsigned int> level = 0;
#else
        static boost::atomic<unsigned int> level;
#endif  // #if !defined(GO_BOOST_COMP_CLANG)
        return level;
    }
};

class wlog
    : go_boost::type_traits::noncopyable_nonmovable
{
public:
    virtual ~wlog() GO_BOOST_DEFAULT_DESTRUCTOR
    wlog() GO_BOOST_DEFAULT_CONSTRUCTOR

    bool operator==(wlog_line& logline)
    {
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        logger_atom().load(boost::memory_order_acquire)->add(std::move(logline));
#else
        logger_atom().load(boost::memory_order_acquire)->add(logline);
#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        return true;
    }

    static detail::wlogger_atm& logger_atom()
    {
        static detail::wlogger_atm atom;
        return atom;
    }

    static detail::wlogger_ptr& logger_instance()
    {
        static detail::wlogger_ptr instance;
        return instance;
    }

    static boost::atomic<unsigned int>& log_level()
    {
#if !defined(GO_BOOST_COMP_CLANG)
        static boost::atomic<unsigned int> level = 0;
#else
        static boost::atomic<unsigned int> level;
#endif  // #if !defined(GO_BOOST_COMP_CLANG)
        return level;
    }
};

inline void initialize(const policy::guaranteed_logger<file_writer>& policy, const std::string& log_directory, const std::string& log_file_name, boost::uint32_t log_file_roll_size_mb)
{
    log::logger_instance().reset(new detail::logger(policy, log_directory, log_file_name, log_file_roll_size_mb));
    log::logger_atom().store(log::logger_instance().get(), boost::memory_order_seq_cst);
}

inline void initialize(const policy::non_guaranteed_logger<file_writer>& policy, const std::string& log_directory, const std::string& log_file_name, boost::uint32_t log_file_roll_size_mb)
{
    log::logger_instance().reset(new detail::logger(policy, log_directory, log_file_name, log_file_roll_size_mb));
    log::logger_atom().store(log::logger_instance().get(), boost::memory_order_seq_cst);
}

inline void initialize(const policy::guaranteed_logger<wfile_writer>& policy, const std::wstring& log_directory, const std::wstring& log_file_name, boost::uint32_t log_file_roll_size_mb)
{
    wlog::logger_instance().reset(new detail::wlogger(policy, log_directory, log_file_name, log_file_roll_size_mb));
    wlog::logger_atom().store(wlog::logger_instance().get(), boost::memory_order_seq_cst);
}

inline void initialize(const policy::non_guaranteed_logger<wfile_writer>& policy, const std::wstring& log_directory, const std::wstring& log_file_name, boost::uint32_t log_file_roll_size_mb)
{
    wlog::logger_instance().reset(new detail::wlogger(policy, log_directory, log_file_name, log_file_roll_size_mb));
    wlog::logger_atom().store(wlog::logger_instance().get(), boost::memory_order_seq_cst);
}

inline void set_log_level(const log_level level)
{
    log::log_level().store(static_cast<unsigned int>(level), boost::memory_order_release);
}

inline void set_wlog_level(const log_level level)
{
    wlog::log_level().store(static_cast<unsigned int>(level), boost::memory_order_release);
}

inline bool is_logged(const log_level level)
{
    return static_cast<unsigned int>(level) <= log::log_level().load(boost::memory_order_relaxed);
}

inline bool is_wlogged(const log_level level)
{
    return static_cast<unsigned int>(level) <= wlog::log_level().load(boost::memory_order_relaxed);
}

} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_LOG_HPP_INCLUDED
