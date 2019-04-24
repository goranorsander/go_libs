#ifndef GO_DIAGNOSTICS_LOG_DETAIL_LOGGER_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_DETAIL_LOGGER_HPP_INCLUDED

//
//  logger.hpp
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

#include <go/diagnostics/log/file_writer.hpp>
#include <go/diagnostics/log/policy/logging_policy_interface.hpp>

#include <atomic>

namespace go
{
namespace diagnostics
{
namespace log
{
namespace detail
{

template <class W> class basic_logger;
typedef basic_logger<file_writer> logger;
typedef basic_logger<wfile_writer> wlogger;

typedef std::atomic<logger*> logger_atm;
typedef std::atomic<wlogger*> wlogger_atm;

typedef std::unique_ptr<logger> logger_uptr;
typedef std::unique_ptr<wlogger> wlogger_uptr;

template <class W>
class basic_logger
{
public:
    typedef W file_writer_type;
    typedef basic_logger<W> this_type;

    typedef typename W::log_line_type log_line_type;
    typedef typename W::out_file_stream_type out_file_stream_type;
    typedef typename W::string_type string_type;
    typedef typename W::out_stream_type out_stream_type;
    typedef typename W::char_type char_type;
    typedef typename go::diagnostics::log::policy::logging_policy_interface<file_writer_type> logging_policy_interface_type;

public:
    ~basic_logger()
    {
        _state.store(logger_state::shutdown);
        _thread->join();
		_thread.reset();
    }

    basic_logger(const logging_policy_interface_type& policy, const string_type& log_directory, const string_type& log_file_name, const uint32_t log_file_roll_size_mb)
        : _state(logger_state::init)
        , _buffer_base(policy.create_buffer())
        , _file_writer(log_directory, log_file_name, go::utility::max_of(1u, log_file_roll_size_mb))
        , _thread()
    {
		_thread.reset(new std::thread(&basic_logger::pop, this));
        _state.store(logger_state::ready, std::memory_order_release);
    }

    void add(log_line_type&& logline)
    {
        _buffer_base->push(std::move(logline));
    }

private:
    void pop()
    {
        try
        {
            while (_state.load(std::memory_order_acquire) == logger_state::init)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(50));
            }

            log_line_type logline(log_level::none, nullptr, nullptr, 0);

            while (_state.load() == logger_state::ready)
            {
                if (_buffer_base->try_pop(logline))
                {
                    _file_writer.write(logline);
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::microseconds(50));
                }
            }

            // Pop and log all remaining entries
            while (_buffer_base->try_pop(logline))
            {
                _file_writer.write(logline);
            }
        }
        catch (...) {}
    }

private:
    enum class logger_state
        : int8_t
    {
        init,
        ready,
        shutdown
    };

private:
    std::atomic<logger_state> _state;
    std::unique_ptr<buffer_interface<log_line_type>> _buffer_base;
    file_writer_type _file_writer;
    std::unique_ptr<std::thread> _thread;
};

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_DETAIL_LOGGER_HPP_INCLUDED
