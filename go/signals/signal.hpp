#ifndef GO_SIGNALS_SIGNAL_HPP_INCLUDED
#define GO_SIGNALS_SIGNAL_HPP_INCLUDED

//
//  signal.hpp
//
//  Copyright 2016-2018 G�ran Orsander
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

template<typename F, typename M = std::recursive_mutex>
class signal
{
public:
    typedef F function_type;
    typedef M mutex_type;
    typedef signal<F, M> this_type;

protected:
    typedef typename std::map<slot_key, function_type> connections_type;

public:
    virtual ~signal() GO_DEFAULT_DESTRUCTOR

    signal()
        : _connections()
        , _signal_guard()
    {
    }

public:
    template<typename F1>
    slot_key connect(F1&& f)
    {
        const std::lock_guard<mutex_type> lock(_signal_guard);
        const slot_key s(f);
        _connections[s] = f;
        return s;
    }

    void disconnect(const slot_key& s)
    {
        const std::lock_guard<mutex_type> lock(_signal_guard);
        _connections.erase(s);
    }

    void disconnect_all_slots()
    {
        const std::lock_guard<mutex_type> lock(_signal_guard);
        _connections.clear();
    }

    bool empty() const
    {
        const std::lock_guard<mutex_type> lock(_signal_guard);
        return _connections.empty();
    }

    template<typename... A>
    void operator()(A... a) const
    {
        const std::lock_guard<mutex_type> lock(_signal_guard);
        if(_connections.empty())
        {
            return;
        }
        for(auto& connection : _connections)
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
    connections_type _connections;

private:
    mutable mutex_type _signal_guard;
};

} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_SIGNAL_HPP_INCLUDED
