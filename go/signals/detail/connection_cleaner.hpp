#ifndef GO_SIGNALS_DETAIL_CONNECTION_CLEANER_HPP_INCLUDED
#define GO_SIGNALS_DETAIL_CONNECTION_CLEANER_HPP_INCLUDED

//
//  connection_cleaner.hpp
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

#include <functional>
#include <memory>

#include <go/signals/detail/connection_data.hpp>

namespace go
{
namespace signals
{
namespace detail
{

struct connection_cleaner;
using connection_cleaner_ptr = std::shared_ptr<connection_cleaner>;

struct connection_cleaner
{
    ~connection_cleaner() = default;
    connection_cleaner() = default;
    connection_cleaner(const connection_cleaner&) = delete;
#if defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)
    connection_cleaner(connection_cleaner&& other)
        : deleter(std::move(other.deleter))
        , data(std::move(other.data))
    {
    }
#else
    connection_cleaner(connection_cleaner&&) = default;
#endif  // #if defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

    connection_cleaner& operator=(const connection_cleaner&) = delete;
#if defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)
    connection_cleaner& operator=(connection_cleaner&& other)
    {
        if (this != &other)
        {
            deleter = std::move(other.deleter);
            data = std::move(other.data);
        }
        return *this;
    }
#else
    connection_cleaner& operator=(connection_cleaner&&) = default;
#endif  // #if defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

    std::function<void(std::shared_ptr<connection_data>)> deleter;
    std::shared_ptr<connection_data> data;
};

} // namespace detail
} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_DETAIL_CONNECTION_CLEANER_HPP_INCLUDED
