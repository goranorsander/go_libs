#ifndef GO_BOOST_UTILITY_RECURSIVE_SPIN_LOCK_HPP_INCLUDED
#define GO_BOOST_UTILITY_RECURSIVE_SPIN_LOCK_HPP_INCLUDED

//
//  recursive_spin_lock.hpp
//
//  Copyright 2019-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#include <cassert>

#include <boost/atomic.hpp>
#include <boost/thread.hpp>

namespace go_boost
{
namespace utility
{

struct recursive_spin_lock
{
public:
    virtual ~recursive_spin_lock() GO_BOOST_DEFAULT_DESTRUCTOR
    recursive_spin_lock() GO_BOOST_NOEXCEPT;

public:
    void lock();
    bool try_lock();
    void unlock();

    typedef boost::unique_lock<recursive_spin_lock> scoped_lock;
    typedef boost::detail::try_lock_wrapper<recursive_spin_lock> scoped_try_lock;

private:
    const boost::thread::id& lock_is_free() const;
    const boost::thread::id& this_thread_local() const;

private:
    boost::atomic<boost::thread::id> _lock_owner;
    std::size_t _lock_count;
};

inline recursive_spin_lock::recursive_spin_lock() GO_BOOST_NOEXCEPT
    : _lock_owner(boost::thread::id())
    , _lock_count(0)
{
}

inline void recursive_spin_lock::lock()
{
    if (_lock_owner.load() != this_thread_local())
    {
        boost::thread::id lock_is_free_id = lock_is_free();
        while (!_lock_owner.compare_exchange_weak(lock_is_free_id, this_thread_local(), boost::memory_order_acquire, boost::memory_order_relaxed))
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
        boost::thread::id lock_is_free_id = lock_is_free();
        if (_lock_owner.compare_exchange_weak(lock_is_free_id, this_thread_local(), boost::memory_order_acquire, boost::memory_order_relaxed))
        {
            ++_lock_count;
            return true;
        }
    }
    return false;
}

inline void recursive_spin_lock::unlock()
{
    assert(_lock_owner.load() == boost::this_thread::get_id());
    assert(_lock_count != 0);

    --_lock_count;
    if (_lock_count == 0)
    {
        _lock_owner.store(lock_is_free(), boost::memory_order_release);
    }
}

inline const boost::thread::id& recursive_spin_lock::lock_is_free() const
{
    static const boost::thread::id lock_is_free_thread_id;
    return lock_is_free_thread_id;
}

inline const boost::thread::id& recursive_spin_lock::this_thread_local() const
{
    static boost::thread_specific_ptr<boost::thread::id> this_thread_local;
    if (!this_thread_local.get())
    {
        this_thread_local.reset(new boost::thread::id(boost::this_thread::get_id()));
    }
    return *this_thread_local;
}

} // namespace utility
} // namespace go_boost

#endif  // #ifndef GO_BOOST_UTILITY_RECURSIVE_SPIN_LOCK_HPP_INCLUDED
