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

namespace go_boost
{
namespace signals
{

template <typename S>
class connections
{
public:
    typedef connections<S> this_type;
    typedef S slot_owner_type;
    typedef boost::signals2::connection connection_type;
    typedef std::map<slot_owner_type, connection_type> slot_owner_connection_type;

public:
    virtual ~connections()
    {
    }

    connections()
        : _connections()
    {
    }

public:
    void erase(const slot_owner_type& slot_owner)
    {
        slot_owner_connection_type::iterator it = this->_connections.find(slot_owner);
        if (it != this->_connections.end())
        {
            this->_connections.erase(it);
        }
    }

    void insert(const slot_owner_type& slot_owner, const connection_type& connection)
    {
        this->_connections[slot_owner] = connection;
    }

    GO_BOOST_CONSTEXPR bool try_get_connection(const slot_owner_type& slot_owner, connection_type& connection) const
    {
        const slot_owner_connection_type::const_iterator it = this->_connections.find(slot_owner);
        if (it != this->_connections.end())
        {
            connection = it->second;
            return true;
        }
        return false;
    }

    GO_BOOST_CONSTEXPR bool try_get_slot_owner(const connection_type& connection, slot_owner_type& slot_owner) const
    {
        for(const slot_owner_connection_type::value_type& it : this->_connections)
        {
            if (it.second == connection)
            {
                slot_owner = it.first;
                return true;
            }
        }
        return false;
    }

private:
    slot_owner_connection_type _connections;
};

}
}

#endif  // #ifndef GO_BOOST_SIGNALS_CONNECTIONS_HPP_INCLUDED
