#ifndef GO_MVVM_SIGNAL_HPP_INCLUDED
#define GO_MVVM_SIGNAL_HPP_INCLUDED

//
//  signal.hpp
//
//  Copyright 2016 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <functional>
#include <map>

namespace go
{
namespace mvvm
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
    {
    }
	
public:
    template<typename F1>
	slot_key_type connect(F1 f)
	{
		const slot_key_type slot_key = ++_slot_next_key;
		_connections[slot_key] = f;
        return slot_key;
	}
	
	void disconnect(const slot_key_type slot_key)
	{
		_connections.erase(slot_key);
	}

    void disconnect_all_slots()
    {
        _connections.clear();
    }

    bool empty() const
    {
        return _connections.empty();
    }

    template<typename... Args>
    void operator()(Args&&... args) const
    {
        for(auto& connection : _connections)
        {
            function_type safe_f = connection.second;
            auto f = std::bind(std::forward<function_type>(safe_f), std::forward<Args>(args)...);
            f();
        }
    }

	template<typename... Args>
	typename void call(Args&&... args) const
	{
		for(auto& connection: _connections)
		{
            function_type safe_f = connection.second;
            auto f = std::bind(std::forward<function_type>(safe_f), std::forward<Args>(args)...);
            f();
        }
	}

protected:
    slot_key_type _slot_next_key;
	connections_type _connections;
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_SIGNAL_HPP_INCLUDED
