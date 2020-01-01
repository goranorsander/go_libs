#ifndef GO_BOOST_MVVM_EVENT_FIRING_OBSERVER_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_EVENT_FIRING_OBSERVER_INTERFACE_HPP_INCLUDED

//
//  event_firing_observer_interface.hpp
//
//  Copyright 2016-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/mvvm/event.hpp>

namespace go_boost
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
    basic_event_firing_observer_interface();

public:
    virtual void on_event_fired(const boost::shared_ptr<basic_event<S>>& /*e*/) = 0;
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

template<>
inline basic_event_firing_observer_interface<std::string>::basic_event_firing_observer_interface()
{
}

template<>
inline basic_event_firing_observer_interface<std::wstring>::basic_event_firing_observer_interface()
{
}

template<class S>
inline basic_event_firing_observer_interface<S>::basic_event_firing_observer_interface()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_EVENT_FIRING_OBSERVER_INTERFACE_HPP_INCLUDED
