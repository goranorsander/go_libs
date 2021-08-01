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

#include <vector>
#include <go/signals/detail/connection_cleaner.hpp>

namespace go
{
namespace signals
{

class connection
{
    template<typename>
    friend class signal;

public:
    virtual ~connection() = default;
    connection() = default;
    connection(const connection&) = delete;
    connection(connection&&) = default;
    connection(std::shared_ptr<detail::connection_data>&& data);

public:
    connection& operator=(const connection&) = delete;
    connection& operator=(connection&&) = default;

public:
    connection_id_type id() const;

    bool is_locked() const;
    void set_lock(const bool lock);

    void disconnect();

private:
    std::shared_ptr<detail::connection_data> _data;
    std::vector<detail::connection_cleaner> _cleaners;
};

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
    return reinterpret_cast<connection_id_type>(this);
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
        const detail::connection_cleaner& cleaner = *it;

        cleaner.deleter(cleaner.data);
    }
}

} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_CONNECTION_HPP_INCLUDED
