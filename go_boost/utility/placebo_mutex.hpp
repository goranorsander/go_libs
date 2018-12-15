#ifndef GO_BOOST_UTILITY_PLACEBO_MUTEX_HPP_INCLUDED
#define GO_BOOST_UTILITY_PLACEBO_MUTEX_HPP_INCLUDED

//
//  placebo_mutex.hpp
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

#include <boost/thread/mutex.hpp>
#include <boost/thread/null_mutex.hpp>

namespace go_boost
{
namespace utility
{

class placebo_mutex
    : public boost::null_mutex
    , noncopyable_nonmovable
{
public:
    virtual ~placebo_mutex();
    placebo_mutex() BOOST_NOEXCEPT;

#if defined BOOST_THREAD_PROVIDES_NESTED_LOCKS
    typedef boost::unique_lock<placebo_mutex> scoped_lock;
    typedef boost::detail::try_lock_wrapper<placebo_mutex> scoped_try_lock;
#endif
};

inline placebo_mutex::~placebo_mutex()
{
}

inline placebo_mutex::placebo_mutex() BOOST_NOEXCEPT
    : boost::null_mutex()
    , noncopyable_nonmovable()
{
}

}
}

#endif  // #ifndef GO_BOOST_UTILITY_PLACEBO_MUTEX_HPP_INCLUDED
