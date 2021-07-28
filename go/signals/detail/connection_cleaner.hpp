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

struct connection_cleaner
{
    std::function<void(std::shared_ptr<connection_data>)> deleter;
    std::shared_ptr<connection_data> data;
};

} // namespace detail
} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_DETAIL_CONNECTION_CLEANER_HPP_INCLUDED
