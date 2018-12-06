#ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_RING_BUFFER_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_DETAIL_RING_BUFFER_HPP_INCLUDED

//
//  ring_buffer.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/diagnostics/log/detail/buffer_interface.hpp>
#include <go_boost/utility/noncopyable_nonmovable.hpp>
#include <go_boost/utility/spin_lock.hpp>

namespace go_boost
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
    , go_boost::utility::noncopyable_nonmovable
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
        , go_boost::utility::noncopyable_nonmovable()
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

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    virtual void push(L&& logline) GO_BOOST_OVERRIDE;

#else

    virtual void push(const L& logline) GO_BOOST_OVERRIDE;

#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    virtual bool try_pop(L& logline) GO_BOOST_OVERRIDE
    {
        element& item = _ring[_read_index % _size];
        const boost::lock_guard<go_boost::utility::spin_lock> lock(item.lock);
        if (item.written == 1)
        {
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            logline = std::move(item.logline);
#else
            logline = item.logline;
#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            item.written = 0;
            ++_read_index;
            return true;
        }
        return false;
    }

private:
    struct /*alignas(64)*/ element
    {
        ~element() GO_BOOST_DEFAULT_DESTRUCTOR

        element()
            : lock()
            , written(false)
            , logline(log_level_none, GO_BOOST_NULLPTR, GO_BOOST_NULLPTR, 0)
        {
        }

        go_boost::utility::spin_lock lock;
        bool written;
        log_line_type logline;
    };

private:
    const std::size_t _size;
    element* _ring;
    boost::atomic<unsigned int> _write_index;
    char_type pad[64];
    unsigned int _read_index;
};

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template <>
inline void ring_buffer<log_line>::push(log_line&& logline)
{
    const unsigned int write_index = _write_index.fetch_add(1, boost::memory_order_relaxed) % _size;
    element& item = _ring[write_index];
    const boost::lock_guard<go_boost::utility::spin_lock> lock(item.lock);
    item.logline = std::move(logline);
    item.written = 1;
}

template <>
inline void ring_buffer<wlog_line>::push(wlog_line&& logline)
{
    const unsigned int write_index = _write_index.fetch_add(1, boost::memory_order_relaxed) % _size;
    element& item = _ring[write_index];
    const boost::lock_guard<go_boost::utility::spin_lock> lock(item.lock);
    item.logline = std::move(logline);
    item.written = 1;
}

#else

template <>
inline void ring_buffer<log_line>::push(const log_line& logline)
{
    const unsigned int write_index = _write_index.fetch_add(1, boost::memory_order_relaxed) % _size;
    element& item = _ring[write_index];
    const boost::lock_guard<go_boost::utility::spin_lock> lock(item.lock);
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    item.logline = std::move(logline);
#else
    item.logline = logline;
#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    item.written = 1;
}

template <>
inline void ring_buffer<wlog_line>::push(const wlog_line& logline)
{
    const unsigned int write_index = _write_index.fetch_add(1, boost::memory_order_relaxed) % _size;
    element& item = _ring[write_index];
    const boost::lock_guard<go_boost::utility::spin_lock> lock(item.lock);
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    item.logline = std::move(logline);
#else
    item.logline = logline;
#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    item.written = 1;
}

#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_RING_BUFFER_HPP_INCLUDED
