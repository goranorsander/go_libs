#ifndef GO_DIAGNOSTICS_LOG_DETAIL_QUEUE_BUFFER_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_DETAIL_QUEUE_BUFFER_HPP_INCLUDED

//
//  queue_buffer.hpp
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

#include <go/diagnostics/log/detail/buffer.hpp>
#include <go/diagnostics/log/detail/buffer_interface.hpp>
#include <go/diagnostics/log/detail/spin_lock.hpp>
#include <go/diagnostics/log/log_line.hpp>
#include <go/utility/noncopyable_nonmovable.hpp>

#include <queue>

namespace go
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
    , go::utility::noncopyable_nonmovable
{
public:
    typedef L log_line_type;
    typedef queue_buffer<L> this_type;

    typedef typename buffer<log_line_type> buffer_type;
    typedef typename L::string_type string_type;
    typedef typename L::out_stream_type out_stream_type;
    typedef typename L::char_type char_type;

public:
    virtual ~queue_buffer() = default;

    queue_buffer()
        : buffer_interface<L>()
        , go::utility::noncopyable_nonmovable()
        , _buffers()
        , _current_write_buffer()
        , _current_read_buffer{ nullptr }
        , _write_index(0)
#if defined (GO_NO_CXX11_INITIALIZER_LISTS)
        , _flag()
#else
        , _flag{ ATOMIC_FLAG_INIT }
#endif  // #if defined (GO_NO_CXX11_INITIALIZER_LISTS)
        , _read_index(0)
    {
#if defined (GO_NO_CXX11_INITIALIZER_LISTS)
        _flag.clear(std::memory_order_relaxed);
#endif  // #if defined (GO_NO_CXX11_INITIALIZER_LISTS)
        setup_next_write_buffer();
    }

    virtual void push(L&& logline) override;

    virtual bool try_pop(L& logline) override
    {
        if (_current_read_buffer == nullptr)
        {
            _current_read_buffer = get_next_read_buffer();
        }

        buffer_type* read_buffer = _current_read_buffer;

        if (read_buffer == nullptr)
        {
            return false;
        }

        if (bool success = read_buffer->try_pop(logline, _read_index))
        {
            _read_index++;
            if (_read_index == buffer_type::size)
            {
                _read_index = 0;
                _current_read_buffer = nullptr;
                const spin_lock lock(_flag);
                _buffers.pop();
            }
            return true;
        }

        return false;
    }

private:
    void setup_next_write_buffer()
    {
        std::unique_ptr<buffer_type> next_write_buffer(new buffer_type());
        _current_write_buffer.store(next_write_buffer.get(), std::memory_order_release);
        const spin_lock lock(_flag);
        _buffers.push(std::move(next_write_buffer));
        _write_index.store(0, std::memory_order_relaxed);
    }

    buffer_type* get_next_read_buffer()
    {
        const spin_lock lock(_flag);
        return _buffers.empty() ? nullptr : _buffers.front().get();
    }

private:
    std::queue<std::unique_ptr<buffer_type>> _buffers;
    std::atomic<buffer_type*> _current_write_buffer;
    buffer_type* _current_read_buffer;
    std::atomic<unsigned int> _write_index;
    std::atomic_flag _flag;
    unsigned int _read_index;
};

template <>
inline void queue_buffer<log_line>::push(log_line&& logline)
{
    const unsigned int write_index = _write_index.fetch_add(1, std::memory_order_relaxed);
    if (write_index < buffer_type::size)
    {
        if (_current_write_buffer.load(std::memory_order_acquire)->push(std::move(logline), write_index))
        {
            setup_next_write_buffer();
        }
    }
    else
    {
        while (_write_index.load(std::memory_order_acquire) >= buffer_type::size)
        {
        }
        push(std::move(logline));
    }
}

template <>
inline void queue_buffer<wlog_line>::push(wlog_line&& logline)
{
    const unsigned int write_index = _write_index.fetch_add(1, std::memory_order_relaxed);
    if (write_index < buffer_type::size)
    {
        if (_current_write_buffer.load(std::memory_order_acquire)->push(std::move(logline), write_index))
        {
            setup_next_write_buffer();
        }
    }
    else
    {
        while (_write_index.load(std::memory_order_acquire) >= buffer_type::size)
        {
        }
        push(std::move(logline));
    }
}

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_DETAIL_QUEUE_BUFFER_HPP_INCLUDED
