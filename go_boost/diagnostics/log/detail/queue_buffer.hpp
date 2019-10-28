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
    , go_boost::type_traits::noncopyable_nonmovable
{
public:
    typedef L log_line_type;
    typedef queue_buffer<L> this_type;

    typedef typename L::string_type string_type;
    typedef typename L::out_stream_type out_stream_type;
    typedef typename L::char_type char_type;
    typedef std::size_t size_type;

public:
    virtual ~queue_buffer() GO_BOOST_DEFAULT_DESTRUCTOR
    queue_buffer() GO_BOOST_DEFAULT_CONSTRUCTOR

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    virtual void push(L&& logline) GO_BOOST_OVERRIDE
    {
        const boost::lock_guard<go_boost::utility::spin_lock> lock(this->_lock);
        element e(std::move(logline));
        this->_queue.push(std::move(e));
    }

#else

    virtual void push(const L& logline) GO_BOOST_OVERRIDE
    {
        const boost::lock_guard<go_boost::utility::spin_lock> lock(this->_lock);
        element e(logline);
        this->_queue.push(e);
}

#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    virtual bool try_pop(L& logline) GO_BOOST_OVERRIDE
    {
        const boost::lock_guard<go_boost::utility::spin_lock> lock(this->_lock);
        if (this->_queue.empty())
        {
            return false;
        }
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        logline = std::move(this->_queue.front().logline);
#else
        logline = this->_queue.front().logline;
#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        this->_queue.pop();
        return true;
    }

private:
    struct element
    {
        ~element() GO_BOOST_DEFAULT_DESTRUCTOR

        element()
            : logline(log_level_none, nullptr, nullptr, 0)
        {
        }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)

        element(const element&) = delete;

#endif  // #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
#if !(defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || defined(GO_BOOST_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR))

        element(element&&) = default;

#else

        element(element&& other)
            : logline(std::move(other.logline))
        {
        }

#endif  // #if !(defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) && defined(GO_BOOST_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR))

        element(log_line_type&& l)
            : logline(std::move(l))
        {
        }

#if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)

        element& operator=(const element&) = delete;

#endif  // #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
#if !(defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || defined(GO_BOOST_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR))

        element& operator=(element&&) noexcept = default;

#else

        element& operator=(element&& other) BOOST_NOEXCEPT_OR_NOTHROW
        {
            if (&other != this)
            {
                logline = std::move(other.logline);
            }
            return *this;
        }

#endif  // #if !(defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || defined(GO_BOOST_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR))

#else
#if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)

        element(const element&) = delete;

#endif  // #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)

        element(const log_line_type& l)
            : logline(l)
        {
        }

#if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)

        element& operator=(const element&) = delete;

#endif  // #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

        log_line_type logline;
    };

private:
    std::queue<element> _queue;
    go_boost::utility::spin_lock _lock;
};

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_QUEUE_BUFFER_HPP_INCLUDED
