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
#include <mutex>

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

    typedef std::mutex::native_handle_type native_handle_type;

    native_handle_type native_handle();
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

inline placebo_mutex::native_handle_type placebo_mutex::native_handle()
{
    return placebo_mutex::native_handle_type();
}

}
}

#endif  // #ifndef GO_UTILITY_PLACEBO_MUTEX_HPP_INCLUDED
