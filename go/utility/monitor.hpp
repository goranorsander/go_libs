#ifndef GO_UTILITY_MONITOR_HPP_INCLUDED
#define GO_UTILITY_MONITOR_HPP_INCLUDED

//
//  monitor.hpp
//
//  Copyright 2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <mutex>

#include <go/utility/recursive_spin_lock.hpp>

namespace go
{
namespace utility
{

template<class T, class L = go::utility::recursive_spin_lock>
class monitor
{
public:
    using value_type = T;
    using lockable_type = L;
    using this_type = monitor<T, L>;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

public:
    class monitor_object
    {
    public:
        ~monitor_object() GO_DEFAULT_DESTRUCTOR

        monitor_object() = delete;
        monitor_object(const monitor_object&) = delete;
        monitor_object(monitor_object&&) = default;

    private:
        explicit monitor_object(this_type* m)
            : m_monitor(m)
            , m_guard(m->m_lock)
        {
        }

    public:
        monitor_object& operator=(const monitor_object&) = delete;
        monitor_object& operator=(monitor_object&&) = default;

        pointer operator->()
        {
            return &m_monitor->m_object;
        }

        const_pointer operator->() const
        {
            return &m_monitor->m_object;
        }

        reference operator*()
        {
            return m_monitor->m_object;
        }

        const_reference operator*() const
        {
            return m_monitor->m_object;
        }

        reference get()
        {
            return m_monitor->m_object;
        }

        const_reference get() const
        {
            return m_monitor->m_object;
        }

    private:
        this_type* m_monitor;
        std::unique_lock<lockable_type> m_guard;

        friend class this_type;
    };

public:
    virtual ~monitor() GO_DEFAULT_DESTRUCTOR

    monitor() = default;
    monitor(const monitor&) = delete;
    monitor(monitor&& other) = default;

    template<typename ...Args>
    monitor(Args&&... args)
        : m_lock()
        , m_object(std::forward<Args>(args)...)
    {
    }

public:
    this_type& operator=(const this_type&) = delete;
    this_type& operator=(this_type&&) = default;

    this_type& operator=(const value_type& value)
    {
        monitor_object m(this);
        *m = value;
        return *this;
    }

    this_type& operator=(value_type&& value)
    {
        monitor_object m(this);
        *m = std::move(value);
        return *this;
    }

    monitor_object operator->()
    {
        return monitor_object(this);
    }

    monitor_object operator*()
    {
        return monitor_object(this);
    }

    monitor_object lock()
    {
        return monitor_object(this);
    }

    reference unsafe_access()
    {
        return m_object;
    }

    const_reference unsafe_access() const
    {
        return m_object;
    }

private:
    lockable_type m_lock;
    value_type m_object;
};

}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_UTILITY_MONITOR_HPP_INCLUDED
