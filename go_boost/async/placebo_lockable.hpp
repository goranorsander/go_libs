#ifndef GO_BOOST_ASYNC_PLACEBO_LOCKABLE_HPP_INCLUDED
#define GO_BOOST_ASYNC_PLACEBO_LOCKABLE_HPP_INCLUDED

//
//  placebo_lockable.hpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/thread.hpp>

namespace go_boost
{
namespace async
{

class placebo_lockable
{
public:
    virtual ~placebo_lockable();
    placebo_lockable() BOOST_NOEXCEPT;

    void lock();
    bool try_lock();
    void unlock();

#if defined BOOST_THREAD_PROVIDES_NESTED_LOCKS
    typedef boost::unique_lock<placebo_lockable> scoped_lock;
    typedef boost::detail::try_lock_wrapper<placebo_lockable> scoped_try_lock;
#endif
};

inline placebo_lockable::~placebo_lockable()
{
}

inline placebo_lockable::placebo_lockable() BOOST_NOEXCEPT
{
}

inline void placebo_lockable::lock()
{
}

inline bool placebo_lockable::try_lock()
{
    return true;
}

inline void placebo_lockable::unlock()
{
}

}
}

#endif  // #ifndef GO_BOOST_ASYNC_PLACEBO_LOCKABLE_HPP_INCLUDED
