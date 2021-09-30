#ifndef GO_SIGNALS_CONNECTION_HPP_INCLUDED
#define GO_SIGNALS_CONNECTION_HPP_INCLUDED

//
//  connection.hpp
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

#include <list>
#include <go/signals/detail/connection_cleaner.hpp>

namespace go
{
namespace signals
{

template<typename, typename ...>
class signal;

class connection
{
    template<typename, typename ...>
    friend class signal;

public:
    virtual ~connection() = default;
    connection() = default;
    connection(const connection&) = delete;

    connection(connection&& other)
        : _id(other._id)
        , _data(std::move(other._data))
        , _cleaners(std::move(other._cleaners))
    {
    }

    connection(std::shared_ptr<detail::connection_data>&& data);

public:
    connection& operator=(const connection&) = delete;

    connection& operator=(connection&& other)
    {
        if (&other != this)
        {
            const_cast<connection_id_type&>(_id) = other._id;
            _data = std::move(other._data);
            _cleaners = std::move(other._cleaners);
        }
        return *this;
    }

public:
    connection_id_type id() const;

    bool is_locked() const;
    void set_lock(const bool lock);

    void disconnect();

private:
    static connection_id_type next_id();

private:
    const connection_id_type _id = next_id();
    std::shared_ptr<detail::connection_data> _data;
    std::list<detail::connection_cleaner_ptr> _cleaners;
};

inline connection_id_type connection::next_id()
{
    static connection_id_type id = 0;
    return ++id;
}

inline connection::connection(std::shared_ptr<detail::connection_data>&& data)
    : _data(std::move(data))
    , _cleaners()
{
    if (_data)
    {
        _data->id = id();
    }
}

inline connection_id_type connection::id() const
{
    return _id;
}

inline bool connection::is_locked() const
{
    return _data->locked;
}

inline void connection::set_lock(const bool lock)
{
    _data->locked = lock;
}

inline void connection::disconnect()
{
    decltype(_cleaners) cleaners = _cleaners;

    for (auto it = cleaners.cbegin(); it != cleaners.cend(); ++it)
    {
        if (*it == nullptr)
            continue;
        const detail::connection_cleaner& cleaner = **it;
        cleaner.deleter(cleaner.data);
    }
}

} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_CONNECTION_HPP_INCLUDED
