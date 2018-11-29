#ifndef GO_DIAGNOSTICS_LOG_DETAIL_RING_BUFFER_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_DETAIL_RING_BUFFER_HPP_INCLUDED

//
//  ring_buffer.hpp
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

#include <go/diagnostics/log/detail/buffer_interface.hpp>
#include <go/utility/noncopyable_nonmovable.hpp>
#include <go/utility/spin_lock.hpp>

#include <mutex>

namespace go
{
namespace diagnostics
{
namespace log
{
namespace detail
{

template <class L>
class ring_buffer
    : public buffer_interface<L>
    , go::utility::noncopyable_nonmovable
{
public:
    typedef L log_line_type;
    typedef ring_buffer<L> this_type;

    typedef typename L::string_type string_type;
    typedef typename L::out_stream_type out_stream_type;
    typedef typename L::char_type char_type;

public:
    virtual ~ring_buffer()
    {
        for (std::size_t i = 0; i < _size; ++i)
        {
            _ring[i].~element();
        }
        std::free(_ring);
    }

    explicit ring_buffer(const std::size_t size)
        : buffer_interface<L>()
        , go::utility::noncopyable_nonmovable()
        , _size(size)
        , _ring(static_cast<element*>(std::malloc(size * sizeof(element))))
        , _write_index(0)
        , _read_index(0)
    {
        for (std::size_t i = 0; i < _size; ++i)
        {
            new (&_ring[i]) element();
        }
    }

    virtual void push(L&& logline) override;

    virtual bool try_pop(L& logline) override
    {
        element& item = _ring[_read_index % _size];
        const std::lock_guard<go::utility::spin_lock> lock(item.lock);
        if (item.written == 1)
        {
            logline = std::move(item.logline);
            item.written = 0;
            ++_read_index;
            return true;
        }
        return false;
    }

private:
    struct /*alignas(64)*/ element
    {
        ~element() = default;

        element()
            : lock()
            , written(false)
            , logline(log_level::none, nullptr, nullptr, 0)
        {
        }

        go::utility::spin_lock lock;
        bool written;
        log_line_type logline;
    };

private:
    const std::size_t _size;
    element* _ring;
    std::atomic<unsigned int> _write_index;
    char_type pad[64];
    unsigned int _read_index;
};

template <>
inline void ring_buffer<log_line>::push(log_line&& logline)
{
    const unsigned int write_index = _write_index.fetch_add(1, std::memory_order_relaxed) % _size;
    element& item = _ring[write_index];
    const std::lock_guard<go::utility::spin_lock> lock(item.lock);
    item.logline = std::move(logline);
    item.written = 1;
}

template <>
inline void ring_buffer<wlog_line>::push(wlog_line&& logline)
{
    const unsigned int write_index = _write_index.fetch_add(1, std::memory_order_relaxed) % _size;
    element& item = _ring[write_index];
    const std::lock_guard<go::utility::spin_lock> lock(item.lock);
    item.logline = std::move(logline);
    item.written = 1;
}

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_DETAIL_RING_BUFFER_HPP_INCLUDED
