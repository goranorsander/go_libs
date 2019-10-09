#ifndef GO_DIAGNOSTICS_LOG_DETAIL_RING_BUFFER_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_DETAIL_RING_BUFFER_HPP_INCLUDED

//
//  ring_buffer.hpp
//
//  Copyright 2018-2019 Göran Orsander
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
    typedef std::size_t size_type;

public:
    virtual ~ring_buffer() = default;

    explicit ring_buffer(const size_type size)
        : buffer_interface<L>()
        , go::utility::noncopyable_nonmovable()
        , _size(size)
        , _ring{ new element[size] }
        , _write_index(0)
        , _pad()
        , _read_index(0)
    {
    }

    virtual void push(L&& logline) override;

    virtual bool try_pop(L& logline) override
    {
        element& item = this->_ring[this->_read_index % this->_size];
        const std::lock_guard<go::utility::spin_lock> lock(item.lock);
        if (item.written)
        {
            logline = std::move(item.logline);
            item.written = false;
            ++(this->_read_index);
            return true;
        }
        return false;
    }

private:
    struct element
    {
        ~element() = default;

        element()
            : lock()
            , written(false)
            , logline(log_level::none, nullptr, nullptr, 0)
        {
        }

        element(const element&) = delete;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

        element(element&&) = default;

#else

        element(element&& other)
            : lock(std::move(other.lock))
            , written(std::move(other.written))
            , logline(std::move(other.logline))
        {
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

        element& operator=(const element&) = delete;

#if !(defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR) || defined(GO_COMP_CLANG))

        element& operator=(element&&) noexcept = default;

#else

        element& operator=(element&& other) GO_NOEXCEPT_OR_NOTHROW
        {
            if(this != &other)
            {
                lock = std::move(other.lock);
                written = std::move(other.written);
                logline = std::move(other.logline);
            }
            return *this;
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

        go::utility::spin_lock lock;
        bool written;
        log_line_type logline;
    };

private:
    const size_type _size;
    std::unique_ptr<element[]> _ring;
    std::atomic<size_type> _write_index;
    char_type _pad[64];
    size_type _read_index;
};

template <>
inline void ring_buffer<log_line>::push(log_line&& logline)
{
    const size_type write_index = this->_write_index.fetch_add(1, std::memory_order_relaxed) % this->_size;
    element& item = this->_ring[write_index];
    const std::lock_guard<go::utility::spin_lock> lock(item.lock);
    item.logline = std::move(logline);
    item.written = true;
}

template <>
inline void ring_buffer<wlog_line>::push(wlog_line&& logline)
{
    const size_type write_index = this->_write_index.fetch_add(1, std::memory_order_relaxed) % this->_size;
    element& item = this->_ring[write_index];
    const std::lock_guard<go::utility::spin_lock> lock(item.lock);
    item.logline = std::move(logline);
    item.written = true;
}

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_DETAIL_RING_BUFFER_HPP_INCLUDED
