#ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_LOGGER_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_DETAIL_LOGGER_HPP_INCLUDED

//
//  logger.hpp
//
//  Copyright 2018-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/diagnostics/log/file_writer.hpp>
#include <go_boost/diagnostics/log/policy/logging_policy_interface.hpp>

#include <boost/atomic/atomic.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace go_boost
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

typedef boost::atomic<logger*> logger_atm;
typedef boost::atomic<wlogger*> wlogger_atm;

typedef boost::shared_ptr<logger> logger_ptr;
typedef boost::shared_ptr<wlogger> wlogger_ptr;

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
    typedef typename go_boost::diagnostics::log::policy::logging_policy_interface<file_writer_type> logging_policy_interface_type;

public:
    ~basic_logger()
    {
        _state.store(logger_state_shutdown);
        _thread->join();
		_thread.reset();
    }

    basic_logger(const logging_policy_interface_type& policy, const string_type& log_directory, const string_type& log_file_name, const boost::uint32_t log_file_roll_size_mb)
        : _state(logger_state_init)
        , _buffer_base(policy.create_buffer())
        , _file_writer(log_directory, log_file_name, go_boost::utility::max_of(1u, log_file_roll_size_mb))
        , _thread()
    {
		_thread.reset(new boost::thread(&basic_logger::pop, this));
        _state.store(logger_state_ready, boost::memory_order_release);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    void add(log_line_type&& logline)
    {
        _buffer_base->push(std::move(logline));
    }

#else

    void add(const log_line_type& logline)
    {
        _buffer_base->push(logline);
    }

#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

private:
    void pop()
    {
        try
        {
            while (_state.load(boost::memory_order_acquire) == logger_state_init)
            {
                boost::this_thread::sleep_for(boost::chrono::microseconds(50));
            }

            log_line_type logline(log_level_none, GO_BOOST_NULLPTR, GO_BOOST_NULLPTR, 0);

            while (_state.load() == logger_state_ready)
            {
                if (_buffer_base->try_pop(logline))
                {
                    _file_writer.write(logline);
                }
                else
                {
                    boost::this_thread::sleep_for(boost::chrono::microseconds(50));
                }
            }

            // Pop and log all remaining entries
            while (_buffer_base->try_pop(logline))
            {
                _file_writer.write(logline);
            }
        }
        catch(...) {}
    }

private:
    enum logger_state
    {
        logger_state_init,
        logger_state_ready,
        logger_state_shutdown
    };

private:
    boost::atomic<logger_state> _state;
    boost::scoped_ptr<buffer_interface<log_line_type>> _buffer_base;
    file_writer_type _file_writer;
	boost::scoped_ptr<boost::thread> _thread;
};

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_LOGGER_HPP_INCLUDED
