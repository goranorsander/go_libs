#ifndef GO_DIAGNOSTICS_LOG_LOG_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_LOG_HPP_INCLUDED

//
//  log.hpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/diagnostics/log/detail/logger.hpp>
#include <go/diagnostics/log/log_line.hpp>
#include <go/diagnostics/log/policy/guaranteed_logger.hpp>
#include <go/diagnostics/log/policy/non_guaranteed_logger.hpp>

#define GO_LOG(level) go::diagnostics::log::is_logged(level) && go::diagnostics::log::log() == go::diagnostics::log::log_line(level, __FILE__, GO_FUNC, __LINE__)
#define GO_LOG_FATAL GO_LOG(go::diagnostics::log::log_level::fatal)
#define GO_LOG_ERROR GO_LOG(go::diagnostics::log::log_level::error)
#define GO_LOG_WARN GO_LOG(go::diagnostics::log::log_level::warning)
#define GO_LOG_INFO GO_LOG(go::diagnostics::log::log_level::info)
#define GO_LOG_DEBUG GO_LOG(go::diagnostics::log::log_level::debug)
#define GO_LOG_TRACE GO_LOG(go::diagnostics::log::log_level::trace)

#define GO_WLOG(level) go::diagnostics::log::is_wlogged(level) && go::diagnostics::log::wlog() == go::diagnostics::log::wlog_line(level, GO_WFILE, GO_WFUNC, __LINE__)
#define GO_WLOG_FATAL GO_WLOG(go::diagnostics::log::log_level::fatal)
#define GO_WLOG_ERROR GO_WLOG(go::diagnostics::log::log_level::error)
#define GO_WLOG_WARN GO_WLOG(go::diagnostics::log::log_level::warning)
#define GO_WLOG_INFO GO_WLOG(go::diagnostics::log::log_level::info)
#define GO_WLOG_DEBUG GO_WLOG(go::diagnostics::log::log_level::debug)
#define GO_WLOG_TRACE GO_WLOG(go::diagnostics::log::log_level::trace)

namespace go
{
namespace diagnostics
{
namespace log
{

class log
    : go::type_traits::noncopyable_nonmovable
{
public:
    virtual ~log() = default;
    log() = default;

    bool operator==(log_line& logline)
    {
        logger_atom().load(std::memory_order_acquire)->add(std::move(logline));
        return true;
    }

    static detail::logger_atm& logger_atom()
    {
        static detail::logger_atm atom;
        return atom;
    }

    static detail::logger_uptr& logger_instance()
    {
        static detail::logger_uptr instance;
        return instance;
    }

    static std::atomic<unsigned int>& log_level()
    {
        static std::atomic<unsigned int> level = { 0 };
        return level;
    }
};

class wlog
    : go::type_traits::noncopyable_nonmovable
{
public:
    virtual ~wlog() = default;
    wlog() = default;

    bool operator==(wlog_line& logline)
    {
        logger_atom().load(std::memory_order_acquire)->add(std::move(logline));
        return true;
    }

    static detail::wlogger_atm& logger_atom()
    {
        static detail::wlogger_atm atom;
        return atom;
    }

    static detail::wlogger_uptr& logger_instance()
    {
        static detail::wlogger_uptr instance;
        return instance;
    }

    static std::atomic<unsigned int>& log_level()
    {
        static std::atomic<unsigned int> level = { 0 };
        return level;
    }
};

inline void initialize(const policy::guaranteed_logger<file_writer>& policy, const std::string& log_directory, const std::string& log_file_name, uint32_t log_file_roll_size_mb)
{
    log::logger_instance().reset(new detail::logger(policy, log_directory, log_file_name, log_file_roll_size_mb));
    log::logger_atom().store(log::logger_instance().get(), std::memory_order_seq_cst);
}

inline void initialize(const policy::non_guaranteed_logger<file_writer>& policy, const std::string& log_directory, const std::string& log_file_name, uint32_t log_file_roll_size_mb)
{
    log::logger_instance().reset(new detail::logger(policy, log_directory, log_file_name, log_file_roll_size_mb));
    log::logger_atom().store(log::logger_instance().get(), std::memory_order_seq_cst);
}

inline void initialize(const policy::guaranteed_logger<wfile_writer>& policy, const std::wstring& log_directory, const std::wstring& log_file_name, uint32_t log_file_roll_size_mb)
{
    wlog::logger_instance().reset(new detail::wlogger(policy, log_directory, log_file_name, log_file_roll_size_mb));
    wlog::logger_atom().store(wlog::logger_instance().get(), std::memory_order_seq_cst);
}

inline void initialize(const policy::non_guaranteed_logger<wfile_writer>& policy, const std::wstring& log_directory, const std::wstring& log_file_name, uint32_t log_file_roll_size_mb)
{
    wlog::logger_instance().reset(new detail::wlogger(policy, log_directory, log_file_name, log_file_roll_size_mb));
    wlog::logger_atom().store(wlog::logger_instance().get(), std::memory_order_seq_cst);
}

inline void set_log_level(const log_level level)
{
    log::log_level().store(static_cast<unsigned int>(level), std::memory_order_release);
}

inline void set_wlog_level(const log_level level)
{
    wlog::log_level().store(static_cast<unsigned int>(level), std::memory_order_release);
}

inline bool is_logged(const log_level level)
{
    return static_cast<unsigned int>(level) <= log::log_level().load(std::memory_order_relaxed);
}

inline bool is_wlogged(const log_level level)
{
    return static_cast<unsigned int>(level) <= wlog::log_level().load(std::memory_order_relaxed);
}

} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_LOG_HPP_INCLUDED
