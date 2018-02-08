#ifndef GO_MVVM_EVENT_FIRING_OBSERVER_INTERFACE_HPP_INCLUDED
#define GO_MVVM_EVENT_FIRING_OBSERVER_INTERFACE_HPP_INCLUDED

//
//  event_firing_observer_interface.hpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/event.hpp>

namespace go
{
namespace mvvm
{

template<class S> class basic_event_firing_observer_interface;
typedef basic_event_firing_observer_interface<std::string> event_firing_observer_interface;
typedef basic_event_firing_observer_interface<std::wstring> wevent_firing_wobserver_interface;

template<class S>
class basic_event_firing_observer_interface
{
public:
    typedef S string_type;
    typedef basic_event_firing_observer_interface<S> this_type;

public:
    virtual ~basic_event_firing_observer_interface() = 0;

protected:
    basic_event_firing_observer_interface() GO_DEFAULT_CONSTRUCTOR

public:
    virtual void on_event_fired(const std::shared_ptr<basic_event<S>>& /*e*/) = 0;
};

template<>
inline basic_event_firing_observer_interface<std::string>::~basic_event_firing_observer_interface()
{
}

template<>
inline basic_event_firing_observer_interface<std::wstring>::~basic_event_firing_observer_interface()
{
}

template<class S>
inline basic_event_firing_observer_interface<S>::~basic_event_firing_observer_interface()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_EVENT_FIRING_OBSERVER_INTERFACE_HPP_INCLUDED
