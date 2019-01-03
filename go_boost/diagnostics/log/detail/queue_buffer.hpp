#ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_QUEUE_BUFFER_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_DETAIL_QUEUE_BUFFER_HPP_INCLUDED

//
//  queue_buffer.hpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/diagnostics/log/detail/buffer.hpp>
#include <go_boost/diagnostics/log/detail/buffer_interface.hpp>
#include <go_boost/diagnostics/log/log_line.hpp>
#include <go_boost/utility/spin_lock.hpp>

#include <boost/shared_ptr.hpp>

#include <queue>

namespace go_boost
{
namespace diagnostics
{
namespace log
{
namespace detail
{

template <class L>
class queue_buffer
    : public buffer_interface<L>
    , go_boost::utility::noncopyable_nonmovable
{
public:
    typedef L log_line_type;
    typedef queue_buffer<L> this_type;

    typedef buffer<log_line_type> buffer_type;
    typedef typename L::string_type string_type;
    typedef typename L::out_stream_type out_stream_type;
    typedef typename L::char_type char_type;

public:
    virtual ~queue_buffer() GO_BOOST_DEFAULT_DESTRUCTOR

    queue_buffer()
        : buffer_interface<L>()
        , go_boost::utility::noncopyable_nonmovable()
        , _buffers()
        , _current_write_buffer()
        , _current_read_buffer(GO_BOOST_NULLPTR)
        , _write_index(0)
        , _spin_lock()
        , _read_index(0)
    {
        setup_next_write_buffer();
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    virtual void push(L&& logline) GO_BOOST_OVERRIDE;

#else

    virtual void push(const L& logline) GO_BOOST_OVERRIDE;

#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    virtual bool try_pop(L& logline) GO_BOOST_OVERRIDE
    {
        if (_current_read_buffer == GO_BOOST_NULLPTR)
        {
            _current_read_buffer = get_next_read_buffer();
        }

        buffer_type* read_buffer = _current_read_buffer;

        if (read_buffer == GO_BOOST_NULLPTR)
        {
            return false;
        }

        if (bool success = read_buffer->try_pop(logline, _read_index))
        {
            _read_index++;
            if (_read_index == buffer_type::size)
            {
                _read_index = 0;
                _current_read_buffer = GO_BOOST_NULLPTR;
                const boost::lock_guard<go_boost::utility::spin_lock> lock(_spin_lock);
                _buffers.pop();
            }
            return true;
        }

        return false;
    }

private:
    void setup_next_write_buffer()
    {
        boost::shared_ptr<buffer_type> next_write_buffer(new buffer_type());
        _current_write_buffer.store(next_write_buffer.get(), boost::memory_order_release);
        const boost::lock_guard<go_boost::utility::spin_lock> lock(_spin_lock);
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        _buffers.push(std::move(next_write_buffer));
#else
        _buffers.push(next_write_buffer);
#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        _write_index.store(0, boost::memory_order_relaxed);
    }

    buffer_type* get_next_read_buffer()
    {
        const boost::lock_guard<go_boost::utility::spin_lock> lock(_spin_lock);
        return _buffers.empty() ? GO_BOOST_NULLPTR : _buffers.front().get();
    }

private:
    std::queue<boost::shared_ptr<buffer_type>> _buffers;
    boost::atomic<buffer_type*> _current_write_buffer;
    buffer_type* _current_read_buffer;
    boost::atomic<unsigned int> _write_index;
    go_boost::utility::spin_lock _spin_lock;
    unsigned int _read_index;
};

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template <>
inline void queue_buffer<log_line>::push(log_line&& logline)
{
    const unsigned int write_index = _write_index.fetch_add(1, boost::memory_order_relaxed);
    if (write_index < buffer_type::size)
    {
        if (_current_write_buffer.load(boost::memory_order_acquire)->push(std::move(logline), write_index))
        {
            setup_next_write_buffer();
        }
    }
    else
    {
        while (_write_index.load(boost::memory_order_acquire) >= buffer_type::size)
        {
        }
        push(std::move(logline));
    }
}

template <>
inline void queue_buffer<wlog_line>::push(wlog_line&& logline)
{
    const unsigned int write_index = _write_index.fetch_add(1, boost::memory_order_relaxed);
    if (write_index < buffer_type::size)
    {
        if (_current_write_buffer.load(boost::memory_order_acquire)->push(std::move(logline), write_index))
        {
            setup_next_write_buffer();
        }
    }
    else
    {
        while (_write_index.load(boost::memory_order_acquire) >= buffer_type::size)
        {
        }
        push(std::move(logline));
    }
}

#else

template <>
inline void queue_buffer<log_line>::push(const log_line& logline)
{
    const unsigned int write_index = _write_index.fetch_add(1, boost::memory_order_relaxed);
    if (write_index < buffer_type::size)
    {
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        if (_current_write_buffer.load(boost::memory_order_acquire)->push(std::move(logline), write_index))
#else
        if (_current_write_buffer.load(boost::memory_order_acquire)->push(logline, write_index))
#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        {
            setup_next_write_buffer();
        }
    }
    else
    {
        while (_write_index.load(boost::memory_order_acquire) >= buffer_type::size)
        {
        }
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        push(std::move(logline));
#else
        push(logline);
#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    }
}

template <>
inline void queue_buffer<wlog_line>::push(const wlog_line& logline)
{
    const unsigned int write_index = _write_index.fetch_add(1, boost::memory_order_relaxed);
    if (write_index < buffer_type::size)
    {
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        if (_current_write_buffer.load(boost::memory_order_acquire)->push(std::move(logline), write_index))
#else
        if (_current_write_buffer.load(boost::memory_order_acquire)->push(logline, write_index))
#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        {
            setup_next_write_buffer();
        }
    }
    else
    {
        while (_write_index.load(boost::memory_order_acquire) >= buffer_type::size)
        {
        }
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        push(std::move(logline));
#else
        push(logline);
#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    }
}

#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_QUEUE_BUFFER_HPP_INCLUDED
