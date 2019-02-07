#ifndef GO_SIGNALS_RETURN_LAST_SIGNAL_COLLECTOR_HPP_INCLUDED
#define GO_SIGNALS_RETURN_LAST_SIGNAL_COLLECTOR_HPP_INCLUDED

//
//  return_last_signal_collector.hpp
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

namespace go
{
namespace signals
{

template<typename ReturnValueType>
struct return_last_signal_collector
{
    using signal_return_value_type = ReturnValueType;

    virtual ~return_last_signal_collector() = default;
    return_last_signal_collector() = default;

    bool operator()(signal_return_value_type r)
    {
        _return_value = r;
        return true;
    }

    signal_return_value_type return_value() const
    {
        return _return_value;
    }

private:
    ReturnValueType _return_value;
};

} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_RETURN_LAST_SIGNAL_COLLECTOR_HPP_INCLUDED
