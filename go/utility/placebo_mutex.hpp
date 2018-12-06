#ifndef GO_UTILITY_PLACEBO_MUTEX_HPP_INCLUDED
#define GO_UTILITY_PLACEBO_MUTEX_HPP_INCLUDED

//
//  placebo_mutex.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/utility/noncopyable_nonmovable.hpp>

#if !defined(GO_NO_CXX11_MUTEX)
#include <mutex>
#endif  // #if !defined(GO_NO_CXX11_MUTEX)

namespace go
{
namespace utility
{

class placebo_mutex
    : noncopyable_nonmovable
{
public:
    virtual ~placebo_mutex() GO_DEFAULT_DESTRUCTOR
    placebo_mutex() GO_NOEXCEPT GO_DEFAULT_CONSTRUCTOR

public:
    void lock();
    bool try_lock();
    void unlock();

#if !defined(GO_NO_CXX11_MUTEX)

    typedef std::mutex::native_handle_type native_handle_type;

    native_handle_type native_handle();

#endif  // #if !defined(GO_NO_CXX11_MUTEX)
};

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

#if !defined(GO_NO_CXX11_MUTEX)

inline placebo_mutex::native_handle_type placebo_mutex::native_handle()
{
    return placebo_mutex::native_handle_type();
}

#endif  // #if !defined(GO_NO_CXX11_MUTEX)

}
}

#endif  // #ifndef GO_UTILITY_PLACEBO_MUTEX_HPP_INCLUDED
