#ifndef GO_DIAGNOSTICS_LOG_DETAIL_BUFFER_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_DETAIL_BUFFER_HPP_INCLUDED

//
//  buffer.hpp
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

#include <go/utility/noncopyable_nonmovable.hpp>

namespace go
{
namespace diagnostics
{
namespace log
{
namespace detail
{

template <class L>
class buffer
    : go::utility::noncopyable_nonmovable
{
public:
    typedef L log_line_type;
    typedef buffer<L> this_type;

    typedef typename L::string_type string_type;
    typedef typename L::out_stream_type out_stream_type;
    typedef typename L::char_type char_type;

public:
    static GO_CONSTEXPR const std::size_t size = 32768;

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
        : go::utility::noncopyable_nonmovable()
        , _buffer(static_cast<element*>(std::malloc(size * sizeof(element))))
        , _write_state()
    {
        for (std::size_t i = 0; i <= size; ++i)
        {
            _write_state[i].store(0, std::memory_order_relaxed);
        }
    }

    bool push(log_line_type&& logline, unsigned int const write_index)
    {
        new (&_buffer[write_index]) element(std::move(logline));
        _write_state[write_index].store(1, std::memory_order_release);
        return _write_state[size].fetch_add(1, std::memory_order_acquire) + 1 == size;
    }

    bool try_pop(log_line_type & logline, unsigned int const read_index)
    {
        if (_write_state[read_index].load(std::memory_order_acquire))
        {
            element& item = _buffer[read_index];
            logline = std::move(item.logline);
            return true;
        }
        return false;
    }

private:
    struct element
    {
        ~element() = default;

        element(log_line_type && nanologline)
            : logline(std::move(nanologline))
        {
        }

        log_line_type logline;
    };

private:
    element* _buffer;
    std::atomic<unsigned int> _write_state[size + 1];
};

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_DETAIL_BUFFER_HPP_INCLUDED
