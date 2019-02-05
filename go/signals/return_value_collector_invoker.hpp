#ifndef GO_SIGNALS_RETURN_VALUE_COLLECTOR_INVOKER_HPP_INCLUDED
#define GO_SIGNALS_RETURN_VALUE_COLLECTOR_INVOKER_HPP_INCLUDED

//
//  return_value_collector_invoker.hpp
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

#include <go/signals/return_value_collector_invoker_fwd.hpp>

namespace go
{
namespace signals
{

template<class Collector, class ReturnValueType, class... Args>
struct return_value_collector_invoker<Collector, ReturnValueType (Args...)>
{
    virtual ~return_value_collector_invoker() = default;
    return_value_collector_invoker() = default;

    bool invoke(Collector& collector, const std::function<ReturnValueType (Args...)>& signal_callback_function, Args... args) const
    {
        return collector(signal_callback_function(args...));
    }
};

template<class Collector, class... Args>
struct return_value_collector_invoker<Collector, void (Args...)>
{
    virtual ~return_value_collector_invoker() = default;
    return_value_collector_invoker() = default;

    bool invoke(Collector& collector, const std::function<void (Args...)>& signal_callback_function, Args... args) const
    {
        signal_callback_function(args...);
        return collector();
    }
};

} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_RETURN_VALUE_COLLECTOR_INVOKER_HPP_INCLUDED
