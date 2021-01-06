#ifndef GO_ASYNC_SPIN_LOCK_HPP_INCLUDED
#define GO_ASYNC_SPIN_LOCK_HPP_INCLUDED

//
//  spin_lock.hpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_ATOMIC_OPERATIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <atomic>

namespace go
{
namespace async
{

struct spin_lock
{
public:
    virtual ~spin_lock() GO_DEFAULT_DESTRUCTOR
    spin_lock() GO_NOEXCEPT;

public:
    void lock();
    bool try_lock();
    void unlock();

private:
    std::atomic_flag _lock;
};

inline spin_lock::spin_lock() GO_NOEXCEPT
#if defined (GO_NO_CXX11_INITIALIZER_LISTS) || defined (GO_NO_CXX11_LIST_INITIALIZATION_INSIDE_MEMBER_INITIALIZER_LIST)
    : _lock()
#else
    : _lock ATOMIC_FLAG_INIT
#endif  // #if defined (GO_NO_CXX11_INITIALIZER_LISTS) || defined (GO_NO_CXX11_LIST_INITIALIZATION_INSIDE_MEMBER_INITIALIZER_LIST)
{
#if defined (GO_NO_CXX11_INITIALIZER_LISTS) || defined (GO_NO_CXX11_LIST_INITIALIZATION_INSIDE_MEMBER_INITIALIZER_LIST)
    _lock.clear(std::memory_order_relaxed);
#endif  // #if defined (GO_NO_CXX11_INITIALIZER_LISTS) || defined (GO_NO_CXX11_LIST_INITIALIZATION_INSIDE_MEMBER_INITIALIZER_LIST)
}

inline void spin_lock::lock()
{
    while (_lock.test_and_set(std::memory_order_acquire))
    {
    }
}

inline bool spin_lock::try_lock()
{
    return !_lock.test_and_set(std::memory_order_acquire);
}

inline void spin_lock::unlock()
{
    _lock.clear(std::memory_order_release);
}

} // namespace async
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_ASYNC_SPIN_LOCK_HPP_INCLUDED
