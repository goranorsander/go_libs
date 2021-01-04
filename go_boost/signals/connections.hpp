#ifndef GO_BOOST_SIGNALS_CONNECTIONS_HPP_INCLUDED
#define GO_BOOST_SIGNALS_CONNECTIONS_HPP_INCLUDED

//
//  connections.hpp
//
//  Copyright 2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <map>
#include <boost/signals2/connection.hpp>
#include <boost/weak_ptr.hpp>

namespace go_boost
{
namespace signals
{

template <typename S, typename F>
class connections;

template <typename S, typename F>
class connections<boost::shared_ptr<S>, F>
{
public:
    typedef connections<boost::shared_ptr<S>, F> this_type;
    typedef boost::shared_ptr<S> slot_owner_type;
    typedef boost::function<F> function_type;
    typedef boost::signals2::signal<F> signal_type;
    typedef boost::signals2::connection connection_type;
    typedef typename slot_owner_type::element_type* const slot_owner_pointer;
    typedef std::map<slot_owner_pointer, connection_type> slot_owner_connection_type;

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
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(addressof(slot_owner));
        if (it != this->_connections.end())
        {
            return false;
        }
        this->_connections[addressof(slot_owner)] = signal.connect(function);
        return true;
    }

    bool disconnect(const slot_owner_type& slot_owner, signal_type& signal)
    {
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(addressof(slot_owner));
        if (it != this->_connections.end())
        {
            signal.disconnect(it->second);
            this->_connections.erase(it);
            return true;
        }
        return false;
    }

    void erase(const slot_owner_type& slot_owner)
    {
        typename slot_owner_connection_type::iterator it = this->_connections.find(addressof(slot_owner));
        if (it != this->_connections.end())
        {
            this->_connections.erase(it);
        }
    }

    void insert(const slot_owner_type& slot_owner, const connection_type& connection)
    {
        this->_connections[addressof(slot_owner)] = connection;
    }

    GO_BOOST_CONSTEXPR bool try_get_connection(const slot_owner_type& slot_owner, connection_type& connection) const
    {
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(addressof(slot_owner));
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

private:
    slot_owner_connection_type _connections;
};

template <typename S, typename F>
class connections<boost::weak_ptr<S>, F>
{
public:
    typedef connections<boost::shared_ptr<S>, F> this_type;
    typedef boost::weak_ptr<S> slot_owner_type;
    typedef boost::function<F> function_type;
    typedef boost::signals2::signal<F> signal_type;
    typedef boost::signals2::connection connection_type;
    typedef boost::shared_ptr<S> slot_owner_ptr;
    typedef typename slot_owner_type::element_type* const slot_owner_pointer;
    typedef std::map<slot_owner_pointer, connection_type> slot_owner_connection_type;

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
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(addressof(slot_owner_));
        if (it != this->_connections.end())
        {
            return false;
        }
        this->_connections[addressof(slot_owner_)] = signal.connect(function);
        return true;
    }

    bool disconnect(const slot_owner_type& slot_owner, signal_type& signal)
    {
        slot_owner_ptr slot_owner_ = slot_owner.lock();
        if (!slot_owner_)
        {
            return false;
        }
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(addressof(slot_owner_));
        if (it != this->_connections.end())
        {
            signal.disconnect(it->second);
            this->_connections.erase(it);
            return true;
        }
        return false;
    }

    void erase(const slot_owner_type& slot_owner)
    {
        typename slot_owner_connection_type::iterator it = this->_connections.find(addressof(slot_owner.lock()));
        if (it != this->_connections.end())
        {
            this->_connections.erase(it);
        }
    }

    void insert(const slot_owner_type& slot_owner, const connection_type& connection)
    {
        slot_owner_ptr slot_owner_ = slot_owner.lock();
        if (!slot_owner_)
        {
            return;
        }
        this->_connections[addressof(slot_owner_)] = connection;
    }

    GO_BOOST_CONSTEXPR bool try_get_connection(const slot_owner_type& slot_owner, connection_type& connection) const
    {
        slot_owner_ptr slot_owner_ = slot_owner.lock();
        if (!slot_owner_)
        {
            return false;
        }
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(addressof(slot_owner_));
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

private:
    slot_owner_connection_type _connections;
};

template <typename S, typename F>
class connections
{
public:
    typedef connections<S, F> this_type;
    typedef S slot_owner_type;
    typedef boost::function<F> function_type;
    typedef boost::signals2::signal<F> signal_type;
    typedef boost::signals2::connection connection_type;
    typedef slot_owner_type* const slot_owner_pointer;
    typedef std::map<slot_owner_pointer, connection_type> slot_owner_connection_type;

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
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(addressof(slot_owner));
        if (it != this->_connections.end())
        {
            return false;
        }
        this->_connections[addressof(slot_owner)] = signal.connect(function);
        return true;
    }

    bool disconnect(const slot_owner_type& slot_owner, signal_type& signal)
    {
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(addressof(slot_owner));
        if (it != this->_connections.end())
        {
            signal.disconnect(it->second);
            this->_connections.erase(it);
            return true;
        }
        return false;
    }

    void erase(const slot_owner_type& slot_owner)
    {
        typename slot_owner_connection_type::iterator it = this->_connections.find(addressof(slot_owner));
        if (it != this->_connections.end())
        {
            this->_connections.erase(it);
        }
    }

    void insert(const slot_owner_type& slot_owner, const connection_type& connection)
    {
        this->_connections[addressof(slot_owner)] = connection;
    }

    GO_BOOST_CONSTEXPR bool try_get_connection(const slot_owner_type& slot_owner, connection_type& connection) const
    {
        const typename slot_owner_connection_type::const_iterator it = this->_connections.find(addressof(slot_owner));
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
        const slot_owner_type* address = boost::addressof(slot_owner);
        return const_cast<slot_owner_pointer>(address);
    }

private:
    slot_owner_connection_type _connections;
};

}
}

#endif  // #ifndef GO_BOOST_SIGNALS_CONNECTIONS_HPP_INCLUDED
