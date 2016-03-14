#ifndef GO_SIGNALS_SIGNAL_HPP_INCLUDED
#define GO_SIGNALS_SIGNAL_HPP_INCLUDED

//
//  signal.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <functional>
#include <map>
#include <mutex>

namespace go
{
namespace signals
{

typedef unsigned int slot_key_type;

template<typename F>
class signal
{
public:
    typedef F function_type;

protected:
    typedef std::map<slot_key_type, function_type> connections_type;

public:
    virtual ~signal()
    {
    }

    signal()
        : _slot_next_key(0)
        , _connections()
        , _signal_guard()
    {
    }

public:
    template<typename F1>
	slot_key_type connect(F1 f)
	{
        std::lock_guard<std::recursive_mutex> lock(_signal_guard);
		const slot_key_type slot_key = ++_slot_next_key;
		_connections[slot_key] = f;
        return slot_key;
	}

	void disconnect(const slot_key_type slot_key)
	{
        std::lock_guard<std::recursive_mutex> lock(_signal_guard);
		_connections.erase(slot_key);
	}

    void disconnect_all_slots()
    {
        std::lock_guard<std::recursive_mutex> lock(_signal_guard);
        _connections.clear();
    }

    bool empty() const
    {
        std::lock_guard<std::recursive_mutex> lock(_signal_guard);
        return _connections.empty();
    }

    template<typename... A>
    void operator()(A&&... a) const
    {
        std::lock_guard<std::recursive_mutex> lock(_signal_guard);
        for(auto& connection : _connections)
        {
            function_type safe_f = connection.second;
            auto f = std::bind(std::forward<function_type>(safe_f), std::forward<A>(a)...);
            f();
        }
    }

	template<typename... A>
	void call(A&&... a) const
	{
        operator()(std::forward<A>(a)...);
    }

protected:
    slot_key_type _slot_next_key;
	connections_type _connections;

private:
    mutable std::recursive_mutex _signal_guard;
};

} // namespace signals
} // namespace go

#endif  // #ifndef GO_SIGNALS_SIGNAL_HPP_INCLUDED
