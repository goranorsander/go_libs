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

#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>

namespace go_boost
{
namespace utility
{

class placebo_mutex
    : boost::noncopyable
{
public:
    virtual ~placebo_mutex();
    placebo_mutex() BOOST_NOEXCEPT;

public:
    void lock();
    bool try_lock();
    void unlock();

#if defined BOOST_THREAD_DEFINES_MUTEX_NATIVE_HANDLE
    typedef boost::mutex::native_handle_type native_handle_type;
    native_handle_type native_handle();
#endif

    typedef boost::unique_lock<placebo_mutex> scoped_lock;
    typedef boost::detail::try_lock_wrapper<placebo_mutex> scoped_try_lock;

private:
#if defined BOOST_THREAD_DEFINES_MUTEX_NATIVE_HANDLE
    pthread_mutex_t m;
#endif
};

inline placebo_mutex::~placebo_mutex()
{
#if defined BOOST_THREAD_DEFINES_MUTEX_NATIVE_HANDLE
    const int res = pthread_mutex_destroy(&m);
    boost::ignore_unused(res);
    BOOST_ASSERT(!res);
#endif
}

inline placebo_mutex::placebo_mutex() BOOST_NOEXCEPT
    : boost::noncopyable()
#if defined BOOST_THREAD_DEFINES_MUTEX_NATIVE_HANDLE
    , m()
#endif
{
#if defined BOOST_THREAD_DEFINES_MUTEX_NATIVE_HANDLE
    const int res = pthread_mutex_init(&m, NULL);
    if (res)
    {
        boost::throw_exception(boost::thread_resource_error(res, "go_boost::utility:: placebo_mutex constructor failed in pthread_mutex_init"));
    }
#endif
}

inline void placebo_mutex::lock()
{
}

inline bool placebo_mutex::try_lock()
{
    return true;
}

inline void placebo_mutex::unlock()
{
}

#if defined BOOST_THREAD_DEFINES_MUTEX_NATIVE_HANDLE
inline placebo_mutex::native_handle_type placebo_mutex::native_handle()
{
    return &m;
}
#endif


}
}

#endif  // #ifndef GO_BOOST_UTILITY_PLACEBO_MUTEX_HPP_INCLUDED
