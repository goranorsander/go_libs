#ifndef GO_BOOST_UTILITY_PLACEBO_LOCKABLE_HPP_INCLUDED
#define GO_BOOST_UTILITY_PLACEBO_LOCKABLE_HPP_INCLUDED

//
//  placebo_lockable.hpp
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

#include <go_boost/utility/noncopyable_nonmovable.hpp>
#include <go_boost/utility/recursive_spin_lock.hpp>

namespace go_boost
{
namespace utility
{

class placebo_lockable
    : noncopyable_nonmovable
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
    : noncopyable_nonmovable()
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

#endif  // #ifndef GO_BOOST_UTILITY_PLACEBO_LOCKABLE_HPP_INCLUDED
