#ifndef GO_ASYNC_RECURSIVE_SPIN_LOCK_HPP_INCLUDED
#define GO_ASYNC_RECURSIVE_SPIN_LOCK_HPP_INCLUDED

//
//  recursive_spin_lock.hpp
//
//  Copyright 2019-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_ATOMIC_OPERATIONS) || defined(GO_NO_CXX11_MUTEX)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#if !defined(GO_NO_CXX11_THREAD_LOCAL_STORAGE)

#include <atomic>
#include <cassert>
#include <thread>

namespace go
{
namespace async
{

struct recursive_spin_lock
{
public:
    virtual ~recursive_spin_lock() GO_DEFAULT_DESTRUCTOR
    recursive_spin_lock() GO_NOEXCEPT;

public:
    void lock();
    bool try_lock();
    void unlock();

private:
    static const std::thread::id& lock_is_free()
    {
        static const std::thread::id lock_is_free_thread_id;
        return lock_is_free_thread_id;
    }
    
    static const std::thread::id& this_thread_local()
    {
        static thread_local std::thread::id this_thread_local = std::this_thread::get_id();
        return this_thread_local;
    }

private:
    std::atomic<std::thread::id> _lock_owner;
    std::size_t _lock_count;
};

inline recursive_spin_lock::recursive_spin_lock() GO_NOEXCEPT
    : _lock_owner(std::thread::id())
    , _lock_count(0)
{
}

inline void recursive_spin_lock::lock()
{
    if (_lock_owner.load() != this_thread_local())
    {
        std::thread::id lock_is_free_id = lock_is_free();
        while (!_lock_owner.compare_exchange_weak(lock_is_free_id, this_thread_local(), std::memory_order_acquire, std::memory_order_relaxed))
        {
        }
    }
    ++_lock_count;
}

inline bool recursive_spin_lock::try_lock()
{
    if (_lock_owner.load() == this_thread_local())
    {
        ++_lock_count;
        return true;
    }
    else
    {
        std::thread::id lock_is_free_id = lock_is_free();
        if (_lock_owner.compare_exchange_weak(lock_is_free_id, this_thread_local(), std::memory_order_acquire, std::memory_order_relaxed))
        {
            ++_lock_count;
            return true;
        }
    }
    return false;
}

inline void recursive_spin_lock::unlock()
{
    assert(_lock_owner.load() == std::this_thread::get_id());
    assert(_lock_count != 0);

    --_lock_count;
    if (_lock_count == 0)
    {
        _lock_owner.store(lock_is_free(), std::memory_order_release);
    }
}

} // namespace async
} // namespace go

#else  // #if !defined(GO_NO_CXX11_THREAD_LOCAL_STORAGE)

#include <mutex>

namespace go
{
namespace async
{

GO_USING(recursive_spin_lock, std::recursive_mutex);

} // namespace async
} // namespace go

#endif  // #if !defined(GO_NO_CXX11_THREAD_LOCAL_STORAGE)

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_ASYNC_RECURSIVE_SPIN_LOCK_HPP_INCLUDED
