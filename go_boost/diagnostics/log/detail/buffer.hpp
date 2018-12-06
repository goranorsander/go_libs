#ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_BUFFER_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_DETAIL_BUFFER_HPP_INCLUDED

//
//  buffer.hpp
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

#include <go_boost/utility/noncopyable_nonmovable.hpp>

namespace go_boost
{
namespace diagnostics
{
namespace log
{
namespace detail
{

template <class L>
class buffer
    : go_boost::utility::noncopyable_nonmovable
{
public:
    typedef L log_line_type;
    typedef buffer<L> this_type;

    typedef typename L::string_type string_type;
    typedef typename L::out_stream_type out_stream_type;
    typedef typename L::char_type char_type;

public:
    static GO_BOOST_CONSTEXPR const std::size_t size = 32768;

    virtual ~buffer()
    {
        unsigned int write_count = _write_state[size].load();
        for (std::size_t i = 0; i < write_count; ++i)
        {
            _buffer[i].~element();
        }
        std::free(_buffer);
    }

    buffer()
        : go_boost::utility::noncopyable_nonmovable()
        , _buffer(static_cast<element*>(std::malloc(size * sizeof(element))))
        , _write_state()
    {
        for (std::size_t i = 0; i <= size; ++i)
        {
            _write_state[i].store(0, boost::memory_order_relaxed);
        }
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    bool push(log_line_type&& logline, unsigned int const write_index)
    {
        new (&_buffer[write_index]) element(std::move(logline));
        _write_state[write_index].store(1, boost::memory_order_release);
        return _write_state[size].fetch_add(1, boost::memory_order_acquire) + 1 == size;
    }

#else

    bool push(const log_line_type& logline, unsigned int const write_index)
    {
        new (&_buffer[write_index]) element(logline);
        _write_state[write_index].store(1, boost::memory_order_release);
        return _write_state[size].fetch_add(1, boost::memory_order_acquire) + 1 == size;
    }

#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    bool try_pop(log_line_type& logline, unsigned int const read_index)
    {
        if (_write_state[read_index].load(boost::memory_order_acquire))
        {
            element& item = _buffer[read_index];
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            logline = std::move(item.logline);
#else
            logline = item.logline;
#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            return true;
        }
        return false;
    }

private:
    struct element
    {
        ~element() GO_BOOST_DEFAULT_DESTRUCTOR

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

        element(log_line_type&& nanologline)
            : logline(std::move(nanologline))
        {
        }

#else

        element(const log_line_type& nanologline)
            : logline(nanologline)
        {
        }

#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

        log_line_type logline;
    };

private:
    element* _buffer;
    boost::atomic<unsigned int> _write_state[size + 1];
};

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_BUFFER_HPP_INCLUDED
