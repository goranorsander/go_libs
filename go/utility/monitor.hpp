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

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
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

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)
#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

        monitor_object(monitor_object&&) = default;

#else

        monitor_object(monitor_object&& other)
            : m_monitor(std::move(other->m_monitor))
            , m_guard(std::move(other->m_lock))
        {
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    private:
        monitor_object(const monitor_object&) = delete;

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
#else

        monitor_object(const monitor_object& other)
            : m_monitor(other->m_monitor)
            , m_guard(other->m_lock)
        {
        }

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    private:
        monitor_object() = delete;

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

        explicit monitor_object(this_type* m)
            : m_monitor(m)
            , m_guard(m->m_lock)
        {
        }

    public:
#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)
#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

        monitor_object& operator=(monitor_object&&) noexcept = default;

#else

        monitor_object& operator=(monitor_object&& other) GO_NOEXCEPT_OR_NOTHROW
        {
            if (this != &other)
            {
                m_monitor = std::move(other->m_monitor);
                m_guard = std::move(other->m_lock);
            }
            return *this;
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)
#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    private:
        monitor_object& operator=(const monitor_object&) = delete;

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
#else

        monitor_object& operator=(const monitor_object& other) noexcept
        {
            if(this != &other)
            {
                m_monitor = other->m_monitor;
                m_guard = other->m_lock;
            }
            return *this;
    }

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    public:
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

        friend class monitor<value_type, lockable_type>;
    };

public:
#if defined(_MSC_VER) && (_MSC_VER <= 1800)

    virtual ~monitor()
    {
    }

    monitor()
        : m_lock()
        , m_object()
    {
    }

#else

    virtual ~monitor() GO_DEFAULT_DESTRUCTOR
    monitor() = default;

#endif  // #if defined(_MSC_VER) && (_MSC_VER <= 1800)

    monitor(const monitor&) = delete;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

    monitor(monitor&&) = default;

#else

    monitor(monitor&& other)
        : m_lock(std::move(other.m_lock))
        , m_object(std::move(other.m_object))
    {
    }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

    template<typename ...Args>
    monitor(Args&&... args)
        : m_lock()
        , m_object(std::forward<Args>(args)...)
    {
    }

public:
    this_type& operator=(const this_type&) = delete;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

    this_type& operator=(this_type&&) noexcept = default;

#else

    this_type& operator=(this_type&& other) GO_NOEXCEPT_OR_NOTHROW
    {
        if(this != &other)
        {
            m_lock = std::move(other.m_lock);
            m_object = std::move(other.m_object);
        }
        return *this;
    }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

    this_type& operator=(const value_type& value) GO_NOEXCEPT_OR_NOTHROW
    {
        monitor_object m(this);
        *m = value;
        return *this;
    }

    this_type& operator=(value_type&& value) GO_NOEXCEPT_OR_NOTHROW
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
