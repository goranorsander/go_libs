#ifndef GO_DIAGNOSTICS_LOG_DETAIL_QUEUE_BUFFER_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_DETAIL_QUEUE_BUFFER_HPP_INCLUDED

//
//  queue_buffer.hpp
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

#include <go/diagnostics/log/detail/buffer_interface.hpp>
#include <go/diagnostics/log/log_line.hpp>
#include <go/utility/spin_lock.hpp>

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
    , go::utility::noncopyable_nonmovable
{
public:
    typedef L log_line_type;
    typedef queue_buffer<L> this_type;

    typedef typename L::string_type string_type;
    typedef typename L::out_stream_type out_stream_type;
    typedef typename L::char_type char_type;
    typedef std::size_t size_type;

public:
    virtual ~queue_buffer() = default;
    queue_buffer() = default;

    virtual void push(L&& logline) override
    {
        const std::lock_guard<go::utility::spin_lock> lock(this->_lock);
        element e(std::move(logline));
        this->_queue.push(std::move(e));
    }

    virtual bool try_pop(L& logline) override
    {
        const std::lock_guard<go::utility::spin_lock> lock(this->_lock);
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

        element(log_line_type&& l)
            : logline(std::move(l))
        {
        }

        element& operator=(const element&) = delete;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

        element& operator=(element&&) = default;

#else

        element& operator=(element&& other)
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
    go::utility::spin_lock _lock;
};

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_DETAIL_QUEUE_BUFFER_HPP_INCLUDED
