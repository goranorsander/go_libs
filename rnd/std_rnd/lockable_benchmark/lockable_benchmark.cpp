//
//  lockable_benchmark.cpp
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
int main() { return -1; }
#else

#include <iostream>
#include <vector>
#include <go/async/placebo_lockable.hpp>
#include <go/async/recursive_spin_lock.hpp>
#include <go/async/spin_lock.hpp>
#include <go/diagnostics/benchmark.hpp>
#include <go/namespace_alias.hpp>

#if defined(GO_STD_MUTEX_ASSIGNMENT_OPERATOR_IS_PRIVATE_ISSUE)
#include <memory>
#endif  //#if defined(GO_STD_MUTEX_ASSIGNMENT_OPERATOR_IS_PRIVATE_ISSUE)
#if !defined(GO_NO_CXX11_MUTEX)
#include <mutex>
#endif  // #if !defined(GO_NO_CXX11_MUTEX)

namespace benchmark
{

#if !defined(GO_STD_MUTEX_ASSIGNMENT_OPERATOR_IS_PRIVATE_ISSUE)

template<class L>
void lock_and_unlock(const std::size_t count, db::stopwatch& lock_duration, db::stopwatch& unlock_duration)
{
    GO_USING(lockable_vector, typename std::vector<L>);

    lockable_vector l(1000000);
    const GO_TYPENAME lockable_vector::iterator end = l.end();

    for (std::size_t i = 0; i < count; ++i)
    {
        GO_TYPENAME lockable_vector::iterator it = l.begin();
        lock_duration.start();
        while (it < end)
        {
            it->lock();
            ++it;
        }
        lock_duration.stop();

        it = l.begin();
        unlock_duration.start();
        while (it < end)
        {
            it->unlock();
            ++it;
        }
        unlock_duration.stop();
    }
}

#else

template<class L>
void lock_and_unlock(const std::size_t count, db::stopwatch& lock_duration, db::stopwatch& unlock_duration)
{
    GO_USING(lockable_vector, std::vector<std::shared_ptr<L>>);

    lockable_vector l(1000000);
    const lockable_vector::iterator end = l.end();

    {
        lockable_vector::iterator it = l.begin();
        while (it < end)
        {
            it->reset(new L());
            ++it;
        }
    }

    for (std::size_t i = 0; i < count; ++i)
    {
        lockable_vector::iterator it = l.begin();
        lock_duration.start();
        while (it < end)
        {
            (*it)->lock();
            ++it;
        }
        lock_duration.stop();

        it = l.begin();
        unlock_duration.start();
        while (it < end)
        {
            (*it)->unlock();
            ++it;
        }
        unlock_duration.stop();
    }
}

#endif  // #if !defined(GO_STD_MUTEX_ASSIGNMENT_OPERATOR_IS_PRIVATE_ISSUE)

template<class L>
void recursive_lock_and_unlock(const std::size_t count, db::stopwatch& lock_duration, db::stopwatch& unlock_duration)
{
    GO_USING(lockable, L);

    const std::size_t count_m = count * 1000000;

    lockable l;

    lock_duration.start();
    for (std::size_t i = 0; i < count_m; ++i)
    {
        l.lock();
    }
    lock_duration.stop();

    unlock_duration.start();
    for (std::size_t i = 0; i < count_m; ++i)
    {
        l.unlock();
    }
    unlock_duration.stop();
}

#if !defined(GO_NO_CXX11_MUTEX)

void std_mutex()
{
    db::stopwatch lock_duration;
    db::stopwatch unlock_duration;
    lock_and_unlock<std::mutex>(100, lock_duration, unlock_duration);
    std::cout << "std_mutex: 100M lock in " << lock_duration.total_duration().count() << " microseconds, 100M unlock in " << unlock_duration.total_duration().count() << " microseconds" << std::endl;
}

void std_recursive_mutex()
{
    db::stopwatch lock_duration;
    db::stopwatch unlock_duration;
    lock_and_unlock<std::recursive_mutex>(100, lock_duration, unlock_duration);
    std::cout << "std_recursive_mutex: 100M lock in " << lock_duration.total_duration().count() << " microseconds, 100M unlock in " << unlock_duration.total_duration().count() << " microseconds" << std::endl;
}

void std_recursive_mutex_recursive()
{
    db::stopwatch lock_duration;
    db::stopwatch unlock_duration;
    recursive_lock_and_unlock<std::recursive_mutex>(100, lock_duration, unlock_duration);
    std::cout << "std_recursive_mutex_recursive: 100M lock in " << lock_duration.total_duration().count() << " microseconds, 100M unlock in " << unlock_duration.total_duration().count() << " microseconds" << std::endl;
}

#endif  // #if !defined(GO_NO_CXX11_MUTEX)

void go_utility_placebo_lockable()
{
    db::stopwatch lock_duration;
    db::stopwatch unlock_duration;
    lock_and_unlock<a::placebo_lockable>(100, lock_duration, unlock_duration);
    std::cout << "go_utility_placebo_lockable: 100M lock in " << lock_duration.total_duration().count() << " microseconds, 100M unlock in " << unlock_duration.total_duration().count() << " microseconds" << std::endl;
}

void go_utility_spin_lock()
{
    db::stopwatch lock_duration;
    db::stopwatch unlock_duration;
    lock_and_unlock<a::spin_lock>(100, lock_duration, unlock_duration);
    std::cout << "go_utility_spin_lock: 100M lock in " << lock_duration.total_duration().count() << " microseconds, 100M unlock in " << unlock_duration.total_duration().count() << " microseconds" << std::endl;
}

void go_utility_recursive_spin_lock()
{
    db::stopwatch lock_duration;
    db::stopwatch unlock_duration;
    lock_and_unlock<a::recursive_spin_lock>(100, lock_duration, unlock_duration);
    std::cout << "go_utility_recursive_spin_lock: 100M lock in " << lock_duration.total_duration().count() << " microseconds, 100M unlock in " << unlock_duration.total_duration().count() << " microseconds" << std::endl;
}

void go_utility_recursive_spin_lock_recursive()
{
    db::stopwatch lock_duration;
    db::stopwatch unlock_duration;
    recursive_lock_and_unlock<a::recursive_spin_lock>(100, lock_duration, unlock_duration);
    std::cout << "go_utility_recursive_spin_lock_recursive: 100M lock in " << lock_duration.total_duration().count() << " microseconds, 100M unlock in " << unlock_duration.total_duration().count() << " microseconds" << std::endl;
}

}

int main()
{
#if !defined(GO_NO_CXX11_MUTEX)
    benchmark::std_mutex();
    benchmark::std_recursive_mutex();
    benchmark::std_recursive_mutex_recursive();
#endif  // #if !defined(GO_NO_CXX11_MUTEX)
    benchmark::go_utility_placebo_lockable();
    benchmark::go_utility_spin_lock();
    benchmark::go_utility_recursive_spin_lock();
    return 0;
}

#endif  // Required C++11 feature is not supported by this compiler
