#ifndef GO_BOOST_UTILITY_SPIN_LOCK_HPP_INCLUDED
#define GO_BOOST_UTILITY_SPIN_LOCK_HPP_INCLUDED

//
//  spin_lock.hpp
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

#include <boost/atomic.hpp>
#include <boost/thread/mutex.hpp>
#include <go_boost/utility/noncopyable_nonmovable.hpp>

namespace go_boost
{
namespace utility
{

struct spin_lock
    : noncopyable_nonmovable
{
public:
    virtual ~spin_lock() GO_BOOST_DEFAULT_DESTRUCTOR
    spin_lock() BOOST_NOEXCEPT;

public:
    void lock();
    bool try_lock();
    void unlock();

    typedef boost::unique_lock<spin_lock> scoped_lock;
    typedef boost::detail::try_lock_wrapper<spin_lock> scoped_try_lock;

private:
    boost::atomic_flag _lock;
};

inline spin_lock::spin_lock() BOOST_NOEXCEPT
    : noncopyable_nonmovable()
    , _lock()
{
}

inline void spin_lock::lock()
{
    while (_lock.test_and_set(boost::memory_order_acquire))
    {
    }
}

inline bool spin_lock::try_lock()
{
    return !_lock.test_and_set(boost::memory_order_acquire);
}

inline void spin_lock::unlock()
{
    _lock.clear(boost::memory_order_release);
}

} // namespace utility
} // namespace go_boost

#endif  // #ifndef GO_BOOST_UTILITY_SPIN_LOCK_HPP_INCLUDED
