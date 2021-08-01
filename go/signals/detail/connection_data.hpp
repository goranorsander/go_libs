#ifndef GO_SIGNALS_DETAIL_CONNECTION_DATA_HPP_INCLUDED
#define GO_SIGNALS_DETAIL_CONNECTION_DATA_HPP_INCLUDED

//
//  connection_data.hpp
//
//  Copyright 2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

namespace go
{
namespace signals
{

using connection_id_type = uint64_t;

namespace detail
{

struct connection_data
{
    bool locked = false;
    connection_id_type id = 0;
};

} // namespace detail
} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_DETAIL_CONNECTION_DATA_HPP_INCLUDED
