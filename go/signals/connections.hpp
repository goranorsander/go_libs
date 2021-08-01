#ifndef GO_SIGNALS_CONNECTIONS_HPP_INCLUDED
#define GO_SIGNALS_CONNECTIONS_HPP_INCLUDED

//
//  connections.hpp
//
//  Copyright 2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <map>
#include <go/signals/signal.hpp>

namespace go
{
namespace signals
{

template <typename S, typename F>
class connections;

template <typename S, typename F>
class connections<std::shared_ptr<S>, F>
{
public:
    typedef connections<std::shared_ptr<S>, F> this_type;
    typedef std::shared_ptr<S> slot_owner_type;
    typedef std::function<F> function_type;
    typedef signal<F> signal_type;
    typedef connection connection_type;
    typedef signal_type* const signal_pointer;
    typedef typename slot_owner_type::element_type* const slot_owner_pointer;
    typedef std::pair<slot_owner_pointer, signal_pointer> slot_owner_connection_key_type;
    typedef std::map<slot_owner_connection_key_type, connection_type> slot_owner_connection_type;

public:
    ~connections()
    {
    }

    connections()
        : _connections()
    {
    }

public:
    bool connect(const slot_owner_type& slot_owner, signal_type& signal, function_type function)
    {
        const slot_owner_connection_key_type key(this->addressof(slot_owner), this->addressof(signal));
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(key);
        if (it != this->_connections.end())
        {
            return false;
        }
        this->_connections[key] = signal.connect(function);
        return true;
    }

    bool disconnect(const slot_owner_type& slot_owner, signal_type& signal)
    {
        const typename slot_owner_connection_type::iterator it = this->_connections.find(slot_owner_connection_key_type(this->addressof(slot_owner), this->addressof(signal)));
        if (it != this->_connections.end())
        {
            it->first.second->disconnect(it->second);
            this->_connections.erase(it);
            return true;
        }
        return false;
    }

    void erase(const slot_owner_type& slot_owner, const signal_type& signal)
    {
        typename slot_owner_connection_type::iterator it = this->_connections.find(slot_owner_connection_key_type(this->addressof(slot_owner), this->addressof(signal)));
        if (it != this->_connections.end())
        {
            this->_connections.erase(it);
        }
    }

    void insert(const slot_owner_type& slot_owner, const signal_type& signal, const connection_type& connection)
    {
        this->_connections[slot_owner_connection_key_type(this->addressof(slot_owner), this->addressof(signal))] = connection;
    }

    GO_CONSTEXPR bool try_get_connection(const slot_owner_type& slot_owner, const signal_type& signal, connection_type& connection) const
    {
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(slot_owner_connection_key_type(this->addressof(slot_owner), this->addressof(signal)));
        if (it != this->_connections.end())
        {
            connection = it->second;
            return true;
        }
        return false;
    }

private:
    slot_owner_pointer addressof(const slot_owner_type& slot_owner) const
    {
        const typename slot_owner_type::element_type* address = slot_owner.get();
        return const_cast<slot_owner_pointer>(address);
    }

    signal_pointer addressof(const signal_type& signal) const
    {
        return const_cast<signal_pointer>(std::addressof(signal));
    }

private:
    slot_owner_connection_type _connections;
};

template <typename S, typename F>
class connections<std::weak_ptr<S>, F>
{
public:
    typedef connections<std::shared_ptr<S>, F> this_type;
    typedef std::weak_ptr<S> slot_owner_type;
    typedef std::function<F> function_type;
    typedef signal<F> signal_type;
    typedef connection connection_type;
    typedef signal_type* const signal_pointer;
    typedef std::shared_ptr<S> slot_owner_ptr;
    typedef typename slot_owner_type::element_type* const slot_owner_pointer;
    typedef std::pair<slot_owner_pointer, signal_pointer> slot_owner_connection_key_type;
    typedef std::map<slot_owner_connection_key_type, connection_type> slot_owner_connection_type;

public:
    ~connections()
    {
    }

    connections()
        : _connections()
    {
    }

public:
    bool connect(const slot_owner_type& slot_owner, signal_type& signal, function_type function)
    {
        slot_owner_ptr slot_owner_ = slot_owner.lock();
        if (!slot_owner_)
        {
            return false;
        }
        const slot_owner_connection_key_type key(this->addressof(slot_owner), this->addressof(signal));
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(key);
        if (it != this->_connections.end())
        {
            return false;
        }
        this->_connections[key] = signal.connect(function);
        return true;
    }

    bool disconnect(const slot_owner_type& slot_owner, signal_type& signal)
    {
        slot_owner_ptr slot_owner_ = slot_owner.lock();
        if (!slot_owner_)
        {
            return false;
        }
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(slot_owner_connection_key_type(this->addressof(slot_owner_), this->addressof(signal)));
        if (it != this->_connections.end())
        {
            it->second.disconnect();
            this->_connections.erase(it);
            return true;
        }
        return false;
    }

    void erase(const slot_owner_type& slot_owner, const signal_type& signal)
    {
        typename slot_owner_connection_type::iterator it = this->_connections.find(slot_owner_connection_key_type(this->addressof(slot_owner.lock()), this->addressof(signal)));
        if (it != this->_connections.end())
        {
            this->_connections.erase(it);
        }
    }

    void insert(const slot_owner_type& slot_owner, const signal_type& signal, const connection_type& connection)
    {
        slot_owner_ptr slot_owner_ = slot_owner.lock();
        if (!slot_owner_)
        {
            return;
        }
        this->_connections[slot_owner_connection_key_type(this->addressof(slot_owner_), this->addressof(signal))] = connection;
    }

    GO_CONSTEXPR bool try_get_connection(const slot_owner_type& slot_owner, const signal_type& signal, connection_type& connection) const
    {
        slot_owner_ptr slot_owner_ = slot_owner.lock();
        if (!slot_owner_)
        {
            return false;
        }
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(slot_owner_connection_key_type(this->addressof(slot_owner_), this->addressof(signal)));
        if (it != this->_connections.end())
        {
            connection = it->second;
            return true;
        }
        return false;
    }

private:
    slot_owner_pointer addressof(const slot_owner_ptr& slot_owner) const
    {
        const typename slot_owner_type::element_type* address = slot_owner.get();
        return const_cast<slot_owner_pointer>(address);
    }

    signal_pointer addressof(const signal_type& signal) const
    {
        return const_cast<signal_pointer>(std::addressof(signal));
    }

private:
    slot_owner_connection_type _connections;
};

template <typename S, typename F>
class connections
{
public:
    typedef connections<S, F> this_type;
    typedef S slot_owner_type;
    typedef std::function<F> function_type;
    typedef signal<F> signal_type;
    typedef connection connection_type;
    typedef signal_type* const signal_pointer;
    typedef slot_owner_type* const slot_owner_pointer;
    typedef std::pair<slot_owner_pointer, signal_pointer> slot_owner_connection_key_type;
    typedef std::map<slot_owner_connection_key_type, connection_type> slot_owner_connection_type;

public:
    ~connections()
    {
    }

    connections()
        : _connections()
    {
    }

public:
    bool connect(const slot_owner_type& slot_owner, signal_type& signal, function_type function)
    {
        const slot_owner_connection_key_type key(this->addressof(slot_owner), this->addressof(signal));
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(key);
        if (it != this->_connections.end())
        {
            return false;
        }
        this->_connections[key] = signal.connect(function);
        return true;
    }

    bool disconnect(const slot_owner_type& slot_owner, signal_type& signal)
    {
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(slot_owner_connection_key_type(this->addressof(slot_owner), this->addressof(signal)));
        if (it != this->_connections.end())
        {
            it->second.disconnect();
            this->_connections.erase(it);
            return true;
        }
        return false;
    }

    void erase(const slot_owner_type& slot_owner, const signal_type& signal)
    {
        typename slot_owner_connection_type::iterator it = this->_connections.find(slot_owner_connection_key_type(this->addressof(slot_owner), this->addressof(signal)));
        if (it != this->_connections.end())
        {
            this->_connections.erase(it);
        }
    }

    void insert(const slot_owner_type& slot_owner, const signal_type& signal, const connection_type& connection)
    {
        this->_connections[slot_owner_connection_key_type(this->addressof(slot_owner), this->addressof(signal))] = connection;
    }

    GO_CONSTEXPR bool try_get_connection(const slot_owner_type& slot_owner, const signal_type& signal, connection_type& connection) const
    {
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(slot_owner_connection_key_type(this->addressof(slot_owner), this->addressof(signal)));
        if (it != this->_connections.end())
        {
            connection = it->second;
            return true;
        }
        return false;
    }

private:
    slot_owner_pointer addressof(const slot_owner_type& slot_owner) const
    {
        const slot_owner_type* address = std::addressof(slot_owner);
        return const_cast<slot_owner_pointer>(address);
    }

    signal_pointer addressof(const signal_type& signal) const
    {
        return const_cast<signal_pointer>(std::addressof(signal));
    }

private:
    slot_owner_connection_type _connections;
};

}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_CONNECTIONS_HPP_INCLUDED
