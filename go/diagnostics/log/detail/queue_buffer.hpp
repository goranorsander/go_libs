#ifndef GO_DIAGNOSTICS_LOG_DETAIL_QUEUE_BUFFER_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_DETAIL_QUEUE_BUFFER_HPP_INCLUDED

//
//  queue_buffer.hpp
//
//  Copyright 2018-2022 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/async/spin_lock.hpp>
#include <go/diagnostics/log/detail/buffer_interface.hpp>
#include <go/diagnostics/log/log_line.hpp>

#include <mutex>
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
    , go::type_traits::noncopyable_nonmovable
{
public:
    using log_line_type = L;
    using this_type = queue_buffer<L>;

    using string_type = typename L::string_type;
    using out_stream_type = typename L::out_stream_type;
    using char_type = typename L::char_type;
    using size_type = std::size_t;

public:
    virtual ~queue_buffer() = default;
    queue_buffer() = default;

    virtual void push(L&& logline) override
    {
        const std::lock_guard<go::async::spin_lock> lock(this->_lock);
        element e(std::move(logline));
        this->_queue.push(std::move(e));
    }

    virtual bool try_pop(L& logline) override
    {
        const std::lock_guard<go::async::spin_lock> lock(this->_lock);
        if (this->_queue.empty())
        {
            return false;
        }
        logline = std::move(this->_queue.front().logline);
        this->_queue.pop();
        return true;
    }

private:
    struct element
    {
        ~element() = default;

        element()
            : logline(log_level::none, nullptr, nullptr, 0)
        {
        }

        element(const element&) = delete;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

        element(element&&) = default;

#else

        element(element&& other)
            : logline(std::move(other.logline))
        {
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

        explicit element(log_line_type&& l)
            : logline(std::move(l))
        {
        }

        element& operator=(const element&) = delete;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

        element& operator=(element&&) noexcept = default;

#else

        element& operator=(element&& other) GO_NOEXCEPT_OR_NOTHROW
        {
            if(this != &other)
            {
                logline = std::move(other.logline);
            }
            return *this;
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

        log_line_type logline;
    };

private:
    std::queue<element> _queue;
    go::async::spin_lock _lock;
};

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_DETAIL_QUEUE_BUFFER_HPP_INCLUDED
