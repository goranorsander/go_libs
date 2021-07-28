#ifndef GO_SIGNALS_SIGNAL_HPP_INCLUDED
#define GO_SIGNALS_SIGNAL_HPP_INCLUDED

//
//  signal.hpp
//
//  Copyright 2016-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <list>
#include <mutex>

#include <go/signals/connection.hpp>
#include <go/signals/detail/int_sequence.hpp>
#include <go/signals/detail/placeholder_signal.hpp>
#include <go/signals/detail/signal_lock.hpp>
#include <go/signals/placeholder.hpp>
#include <go/signals/slot.hpp>

namespace go
{
namespace signals
{

template<typename R, typename... Args>
class signal<R(Args...)>
    : public detail::signal_lock<std::recursive_mutex>
{
public:
    using this_type = signal<R(Args...)>;
    using base_type = detail::signal_lock<std::recursive_mutex>;
    using lockable_type = typename base_type::lockable_type;
    using result_type = R;
    using function_type = std::function<R(Args...)>;
    using signal_pointer = this_type*;
    using slot_pointer = slot*;
    using size_type = size_t;

public:
    ~signal();
    signal();
    signal(const this_type& other);
    signal(this_type&&) = default;

public:
    this_type& operator=(const this_type& other);
    this_type& operator=(this_type&&) = default;

    R operator()(Args... args) const;

    template<typename T>
    R operator()(Args... args, const T& agg) const;

public:
    R call(Args... args) const;

    template<typename T>
    R call(Args... args, const T& agg) const;

    void connect(signal_pointer sg);
    void disconnect(signal_pointer sg);

    connection connect(const function_type& fn, slot_pointer owner = nullptr);
    connection connect(function_type&& fn, slot_pointer owner = nullptr);

    template<typename T, typename U>
    connection connect(T *p, const U& fn, slot_pointer owner = nullptr);

    void disconnect(const connection& connection);
    void disconnect(slot_pointer owner);

    void disconnect_all_slots();

    bool empty() const;
    size_type size() const;

private:
    using connection_data_ptr = std::shared_ptr<detail::connection_data>;

    struct callback_data
    {
        function_type callback;
        connection_data_ptr connection;
        slot_pointer owner;
    };

    using callback_list_type = std::list<callback_data>;

private:
    template<typename T, typename U, int... Ns>
    function_type construct_mem_fn(const T& fn, U* p, detail::int_sequence<Ns...>) const;

    void copy_callbacks(const callback_list_type& callbacks);

    connection_data_ptr create_connection(function_type&& fn, slot_pointer owner);
    void destroy_connection(const connection_data_ptr& connection);

private:
    callback_list_type _callbacks;
    signal_pointer _parent;
    std::list<signal_pointer> _children;
};

template<typename R, typename... Args>
signal<R(Args...)>::~signal()
{
    const std::lock_guard<std::recursive_mutex> lock(this->_mutex);
    for (const auto& callback : this->_callbacks)
    {
        if (callback.owner != nullptr)
        {
            callback.owner->_data = nullptr;
            callback.owner->_cleaners.clear();
        }
    }
    if (this->_parent != nullptr)
    {
        this->_parent->_children.remove(this);
    }
    for (signal_pointer sig : this->_children)
    {
        sig->_parent = nullptr;
    }
}

template<typename R, typename... Args>
signal<R(Args...)>::signal()
    : detail::signal_lock<std::recursive_mutex>()
    , _callbacks{}
    , _parent{ nullptr }
    , _children{}
{
}

template<typename R, typename... Args>
signal<R(Args...)>::signal(const this_type& other)
    : detail::signal_lock<std::recursive_mutex>(other)
    , _callbacks{}
    , _parent{ nullptr }
    , _children{}
{
    std::unique_lock<std::recursive_mutex> lock_this(this->_mutex, std::defer_lock);
    std::unique_lock<std::recursive_mutex> lock_other(other._mutex, std::defer_lock);
    std::lock(lock_this, lock_other);
    this->copy_callbacks(other._callbacks);
}

template<typename R, typename... Args>
signal<R(Args...)>::this_type& signal<R(Args...)>::operator=(const this_type& other)
{
    detail::signal_lock<std::recursive_mutex>::operator=(other);
    std::unique_lock<std::recursive_mutex> lock_this(this->_mutex, std::defer_lock);
    std::unique_lock<std::recursive_mutex> lock_other(other._mutex, std::defer_lock);
    std::lock(lock_this, lock_other);
    this->copy_callbacks(other._callbacks);
    return *this;
}

template<typename R, typename... Args>
R signal<R(Args...)>::operator()(Args... args) const
{
    return this->call(args...);
}

template<typename R, typename... Args>
template<typename T>
R signal<R(Args...)>::operator()(Args... args, const T& agg) const
{
    return this->call(args..., agg);
}

template<typename R, typename... Args>
R signal<R(Args...)>::call(Args... args) const
{
    const std::lock_guard<std::recursive_mutex> lock(this->_mutex);
    if (!this->_locked)
    {
        for (signal_pointer sig : this->_children)
        {
            sig->operator()(std::forward<Args>(args)...);
        }
        for (auto it = this->_callbacks.cbegin(); it != this->_callbacks.cend(); ++it)
        {
            const callback_data& callback = *it;
            if (!callback.connection->locked)
            {
                if (std::next(it, 1) == this->_callbacks.cend())
                {
                    return callback.callback(std::forward<Args>(args)...);
                }
                callback.callback(std::forward<Args>(args)...);
            }
        }
    }
    return R();
}

template<typename R, typename... Args>
template<typename T>
R signal<R(Args...)>::call(Args... args, const T& agg) const
{
    std::vector<R> result;
    const std::lock_guard<std::recursive_mutex> lock(this->_mutex);
    if (!this->_locked)
    {
        for (signal_pointer sig : this->_children)
        {
            sig->operator()(std::forward<Args>(args)...);
        }
        result.reserve(this->_callbacks.size());
        for (const auto& callback : this->_callbacks)
        {
            if (!callback.connection->locked)
            {
                result.push_back(std::move(callback.callback(std::forward<Args>(args)...)));
            }
        }
    }
    return agg(std::move(result));
}

template<typename R, typename... Args>
void signal<R(Args...)>::connect(signal_pointer sg)
{
    std::unique_lock<std::recursive_mutex> lock_this(this->_mutex, std::defer_lock);
    std::unique_lock<std::recursive_mutex> lock_sg(sg->_mutex, std::defer_lock);
    std::lock(lock_this, lock_sg);
    if (this->_parent == sg)
    {
        return;
    }
    auto it = std::find(this->_children.cbegin(), this->_children.cend(), sg);
    if (it == this->_children.cend())
    {
        sg->_parent = this;
        this->_children.push_back(std::move(sg));
    }
}

template<typename R, typename... Args>
void signal<R(Args...)>::disconnect(signal_pointer sg)
{
    const std::lock_guard<std::recursive_mutex> lock(this->_mutex);
    this->_children.remove(sg);
}

template<typename R, typename... Args>
connection signal<R(Args...)>::connect(const function_type& fn, slot_pointer owner)
{
    return this->create_connection(static_cast<function_type>(fn), owner);
}

template<typename R, typename... Args>
connection signal<R(Args...)>::connect(function_type&& fn, slot_pointer owner)
{
    return this->create_connection(std::move(fn), owner);
}

template<typename R, typename... Args>
template<typename T, typename U>
connection signal<R(Args...)>::connect(T* p, const U& fn, slot_pointer owner)
{
    auto mem_fn = std::move(this->construct_mem_fn(fn, p, detail::make_int_sequence<sizeof...(Args)>{}));
    return this->create_connection(std::move(mem_fn), owner);
}

template<typename R, typename... Args>
void signal<R(Args...)>::disconnect(const connection& connection)
{
    this->destroy_connection(connection._data);
}

template<typename R, typename... Args>
void signal<R(Args...)>::disconnect(slot_pointer owner)
{
    if (owner != nullptr)
    {
        this->destroy_connection(owner->_data);
    }
}

template<typename R, typename... Args>
void signal<R(Args...)>::disconnect_all_slots()
{
    const std::lock_guard<std::recursive_mutex> lock(this->_mutex);
    for (const auto& callback : this->_callbacks)
    {
        if (callback.owner != nullptr)
        {
            callback.owner->_data = nullptr;
            callback.owner->_cleaners.clear();
        }
    }
    this->_callbacks.clear();
    for (auto sig : this->_children)
    {
        if (sig->_parent == this) // should be an assert
        {
            sig->_parent = nullptr;
        }
    }
    this->_children.clear();
}

template<typename R, typename... Args>
bool signal<R(Args...)>::empty() const
{
    const std::lock_guard<std::recursive_mutex> lock(this->_mutex);
    return this->_callbacks.empty();
}

template<typename R, typename... Args>
signal<R(Args...)>::size_type signal<R(Args...)>::size() const
{
    const std::lock_guard<std::recursive_mutex> lock(this->_mutex);
    return this->_callbacks.size();
}

template<typename R, typename... Args>
template<typename T, typename U, int... Ns>
typename signal<R(Args...)>::function_type signal<R(Args...)>::construct_mem_fn(const T& fn, U* p, detail::int_sequence<Ns...>) const
{
    return std::bind(fn, p, detail::placeholder_signal<Ns>{}...);
}

template<typename R, typename... Args>
void signal<R(Args...)>::copy_callbacks(const callback_list_type& callbacks)
{
    for (auto it = callbacks.begin(); it != callbacks.end(); ++it)
    {
        const callback_data& callback = *it;
        if (callback.owner == nullptr)
        {
            callback_data data;
            data.callback = jn.callback;
            data.connection = jn.connection;
            data.owner = nullptr;
            this->_callbacks.push_back(std::move(data));
        }
    }
}

template<typename R, typename... Args>
signal<R(Args...)>::connection_data_ptr signal<R(Args...)>::create_connection(function_type&& fn, slot_pointer owner)
{
    connection_data_ptr connection = std::make_shared<detail::connection_data>();
    if (owner != nullptr)
    {
        auto deleter = [this](connection_data_ptr connection)
        {
            this->destroy_connection(connection);
        };
        detail::connection_cleaner cleaner;
        cleaner.deleter = deleter;
        cleaner.data = connection;
        owner->_data = connection;
        owner->_cleaners.emplace_back(cleaner);
    }
    callback_data callback;
    callback.callback = std::move(fn);
    callback.connection = connection;
    callback.owner = owner;
    const std::lock_guard<std::recursive_mutex> lock(this->_mutex);
    this->_callbacks.push_back(std::move(callback));
    return connection;
}

template<typename R, typename... Args>
void signal<R(Args...)>::destroy_connection(const connection_data_ptr& connection)
{
    const std::lock_guard<std::recursive_mutex> lock(this->_mutex);
    for (auto it = this->_callbacks.begin(); it != this->_callbacks.end(); ++it)
    {
        const callback_data& callback = *it;
        if (callback.connection == connection)
        {
            if (callback.owner != nullptr)
            {
                callback.owner->_data = nullptr;
                callback.owner->_cleaners.clear();
            }
            this->_callbacks.erase(it);
            break;
        }
    }
}

} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_SIGNAL_HPP_INCLUDED
