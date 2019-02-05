#ifndef GO_SIGNALS_DEFAULT_COLLECTOR_HPP_INCLUDED
#define GO_SIGNALS_DEFAULT_COLLECTOR_HPP_INCLUDED

//
//  default_collector.hpp
//
//  Copyright 2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/signals/return_last_signal_collector.hpp>

namespace go
{
namespace signals
{

template<typename ReturnValueType>
struct default_collector : return_last_signal_collector<ReturnValueType>
{
    virtual ~default_collector() = default;
    default_collector() = default;
};

template<>
struct default_collector<void>
{
    using signal_return_value_type = void;

    virtual ~default_collector() = default;
    default_collector() = default;

    bool operator()(void)
    {
        return true;
    }

    void return_value() const
    {
    }
};

} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_DEFAULT_COLLECTOR_HPP_INCLUDED
