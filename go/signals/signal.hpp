#ifndef GO_SIGNALS_SIGNAL_HPP_INCLUDED
#define GO_SIGNALS_SIGNAL_HPP_INCLUDED

//
//  signal.hpp
//
//  Copyright 2016-2020 Göran Orsander
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
#include <map>
#include <mutex>
#include <go/signals/slot_key.hpp>

namespace go
{
namespace signals
{

template<typename F, class L = std::recursive_mutex>
class signal
{
public:
    typedef F function_type;
    typedef L lockable_type;
    typedef signal<F, L> this_type;

    typedef typename std::map<slot_key, function_type> connections_type;
    typedef typename connections_type::size_type size_type;

public:
    virtual ~signal() GO_DEFAULT_DESTRUCTOR

    signal()
        : _next_slot_key()
        , _connections()
        , _signal_guard()
    {
    }

public:
    template<typename F1>
    slot_key connect(F1&& f)
    {
        const std::lock_guard<lockable_type> lock(this->_signal_guard);
        const slot_key key = ++(this->_next_slot_key);
        (this->_connections)[key] = f;
        return key;
    }

    void disconnect(const slot_key& key)
    {
        const std::lock_guard<lockable_type> lock(this->_signal_guard);
        this->_connections.erase(key);
    }

    void disconnect_all_slots()
    {
        const std::lock_guard<lockable_type> lock(this->_signal_guard);
        this->_connections.clear();
    }

    bool empty() const
    {
        const std::lock_guard<lockable_type> lock(this->_signal_guard);
        return this->_connections.empty();
    }

    size_type size() const
    {
        const std::lock_guard<lockable_type> lock(this->_signal_guard);
        return this->_connections.size();
    }

    template<typename... A>
    void operator()(A... a) const
    {
        const std::lock_guard<lockable_type> lock(this->_signal_guard);
        if(this->_connections.empty())
        {
            return;
        }
        for(auto& connection : this->_connections)
        {
            function_type f = connection.second;
            auto s = std::bind(std::forward<function_type>(f), a...);
            s();
        }
    }

    template<typename... A>
    void call(A... a) const
    {
        operator()(a...);
    }

protected:
    slot_key _next_slot_key;
    connections_type _connections;

private:
    mutable lockable_type _signal_guard;
};

} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_SIGNAL_HPP_INCLUDED
