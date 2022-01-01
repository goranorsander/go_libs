#ifndef GO_SIGNALS_DETAIL_SIGNAL_LOCK_HPP_INCLUDED
#define GO_SIGNALS_DETAIL_SIGNAL_LOCK_HPP_INCLUDED

//
//  signal_lock.hpp
//
//  Copyright 2021-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_MUTEX) || defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

namespace go
{
namespace signals
{
namespace detail
{

template<class L>
class signal_lock
{
public:
    using this_type = signal_lock<L>;
    using lockable_type = L;

public:
    virtual ~signal_lock() = default;

protected:
    signal_lock();
    signal_lock(const this_type& other);
#if defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)
    signal_lock(this_type&& other)
        : _mutex(std::move(other._mutex))
        , _locked(std::move(other._locked))
    {
    }
#else
    signal_lock(this_type&&) = default;
#endif  // #if defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

protected:
    signal_lock<L>& operator=(const this_type& other);
#if defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)
    signal_lock<L>& operator=(this_type&& other)
    {
        if(&other != this)
        {
            this->_mutex = std::move(other._mutex);
            this->_locked = std::move(other._locked);
        }
        return *this;
    }
#else
    signal_lock<L>& operator=(this_type&&) = default;
#endif  // #if defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

public:
    bool is_locked() const;
    void set_lock(const bool lock);

protected:
    mutable lockable_type _mutex;
    bool _locked;
};

template<class L>
signal_lock<L>::signal_lock()
    : _mutex{}
    , _locked{ false }
{
}

template<class L>
signal_lock<L>::signal_lock(const this_type& other)
    : _mutex{}
    , _locked{ other._locked }
{
}

template<class L>
signal_lock<L>& signal_lock<L>::operator=(const this_type& other)
{
    std::unique_lock<std::recursive_mutex> lock_this(this->_mutex, std::defer_lock);
    std::unique_lock<std::recursive_mutex> lock_other(other._mutex, std::defer_lock);
    std::lock(lock_this, lock_other);
    this->_locked = other._locked;
    return *this;
}

template<class L>
bool signal_lock<L>::is_locked() const
{
    return this->_locked;
}

template<class L>
void signal_lock<L>::set_lock(const bool lock)
{
    this->_locked = lock;
}

} // namespace detail
} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_DETAIL_SIGNAL_LOCK_HPP_INCLUDED
