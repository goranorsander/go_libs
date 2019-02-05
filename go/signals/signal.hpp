#ifndef GO_SIGNALS_SIGNAL_HPP_INCLUDED
#define GO_SIGNALS_SIGNAL_HPP_INCLUDED

//
//  signal.hpp
//
//  Copyright 2016-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <functional>
#include <mutex>
#include <go/signals/default_collector.hpp>
#include <go/utility/recursive_spin_lock.hpp>
#include <go/signals/slot.hpp>

namespace go
{
namespace signals
{

#if !defined(GO_COMP_MSVC)
template <typename F, class C = default_collector<typename std::function<F>::result_type>, class L = go::utility::recursive_spin_lock>
#else
template <typename F, class C = default_collector<void>, class L = go::utility::recursive_spin_lock>
#endif  // #if !defined(GO_COMP_MSVC)
class signal
    : slots<F, C>
{
public:
    using lockable_type = L;
    using slots_base_type = slots<F, C>;
    using signal_function_type = typename slots_base_type::signal_function_type;
    using signal_return_value_type = typename signal_function_type::result_type;

public:
    virtual ~signal() = default;

    signal(const signal_function_type& signal_function = signal_function_type())
        : slots_base_type(signal_function)
        , _signal_guard()
    {
    }

    slot_key connect(const signal_function_type& signal_function)
    {
        const std::lock_guard<lockable_type> lock(this->_signal_guard);
        return this->add_slot(signal_function);;
    }

    bool disconnect(const slot_key& key)
    {
        const std::lock_guard<lockable_type> lock(this->_signal_guard);
        return this->remove_slot(key);
    }

    void disconnect_all_slots()
    {
        const std::lock_guard<lockable_type> lock(this->_signal_guard);
        this->remove_all_slots();
    }

    bool empty() const
    {
        const std::lock_guard<lockable_type> lock(this->_signal_guard);
        return this->connections() == 0;
    }

    std::size_t size() const
    {
        const std::lock_guard<lockable_type> lock(this->_signal_guard);
        return this->connections();
    }

    template<typename... A>
    void operator()(A... a) const
    {
        const std::lock_guard<lockable_type> lock(this->_signal_guard);
        this->emit<signal_return_value_type>(a...);
    }

    template<typename... A>
    void call(A... a) const
    {
        this->operator()(a...);
    }

private:
    mutable lockable_type _signal_guard;
};

//#include <functional>
//#include <map>
//#include <mutex>
//#include <go/signals/slot_key.hpp>
//#include <go/utility/recursive_spin_lock.hpp>
//
//namespace go
//{
//namespace signals
//{
//
//template<typename F, class L = go::utility::recursive_spin_lock>
//class signal
//{
//public:
//    typedef F function_type;
//    typedef L lockable_type;
//    typedef signal<F, L> this_type;
//
//protected:
//    typedef typename std::map<slot_key, function_type> connections_type;
//
//public:
//    virtual ~signal() GO_DEFAULT_DESTRUCTOR
//
//    signal()
//        : _next_slot_key()
//        , _connections()
//        , _signal_guard()
//    {
//    }
//
//public:
//    template<typename F1>
//    slot_key connect(F1&& f)
//    {
//        const std::lock_guard<lockable_type> lock(this->_signal_guard);
//        const slot_key key = ++(this->_next_slot_key);
//        (this->_connections)[key] = f;
//        return key;
//    }
//
//    void disconnect(const slot_key& key)
//    {
//        const std::lock_guard<lockable_type> lock(this->_signal_guard);
//        this->_connections.erase(key);
//    }
//
//    void disconnect_all_slots()
//    {
//        const std::lock_guard<lockable_type> lock(this->_signal_guard);
//        this->_connections.clear();
//    }
//
//    bool empty() const
//    {
//        const std::lock_guard<lockable_type> lock(this->_signal_guard);
//        return this->_connections.empty();
//    }
//
//    template<typename... A>
//    void operator()(A... a) const
//    {
//        const std::lock_guard<lockable_type> lock(this->_signal_guard);
//        if(this->_connections.empty())
//        {
//            return;
//        }
//        for(auto& connection : this->_connections)
//        {
//            function_type f = connection.second;
//            auto s = std::bind(std::forward<function_type>(f), a...);
//            s();
//        }
//    }
//
//    template<typename... A>
//    void call(A... a) const
//    {
//        operator()(a...);
//    }
//
//protected:
//    slot_key _next_slot_key;
//    connections_type _connections;
//
//private:
//    mutable lockable_type _signal_guard;
//};

} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_SIGNAL_HPP_INCLUDED
