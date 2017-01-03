#ifndef GO_BOOST_MVVM_NOTIFY_EVENT_FIRING_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_NOTIFY_EVENT_FIRING_INTERFACE_HPP_INCLUDED

//
//  notify_event_firing_interface.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/signals2.hpp>
#include <go_boost/mvvm/event.hpp>
#include <go_boost/signals/slot.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S> class basic_notify_event_firing_interface;
typedef basic_notify_event_firing_interface<std::string> notify_event_firing_interface;
typedef basic_notify_event_firing_interface<std::wstring> notify_wevent_firing_interface;

template<class S>
class basic_notify_event_firing_interface
    : public go_boost::signals::slot
{
public:
    typedef S string_type;
    typedef basic_notify_event_firing_interface<S> this_type;
    typedef typename boost::signals2::signal<void(const boost::shared_ptr<basic_event<S>>&)> event_fired_signal;

public:
    virtual ~basic_notify_event_firing_interface() = 0;

protected:
    basic_notify_event_firing_interface();

public:
    event_fired_signal event_fired;
};

template<>
inline basic_notify_event_firing_interface<std::string>::~basic_notify_event_firing_interface()
{
    event_fired.disconnect_all_slots();
}

template<>
inline basic_notify_event_firing_interface<std::wstring>::~basic_notify_event_firing_interface()
{
    event_fired.disconnect_all_slots();
}

template<class S>
inline basic_notify_event_firing_interface<S>::~basic_notify_event_firing_interface()
{
    event_fired.disconnect_all_slots();
}

template<>
inline basic_notify_event_firing_interface<std::string>::basic_notify_event_firing_interface()
	: go_boost::signals::slot()
	, event_fired()
{
}

template<>
inline basic_notify_event_firing_interface<std::wstring>::basic_notify_event_firing_interface()
	: go_boost::signals::slot()
	, event_fired()
{
}

template<class S>
inline basic_notify_event_firing_interface<S>::basic_notify_event_firing_interface()
	: go_boost::signals::slot()
	, event_fired()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_NOTIFY_EVENT_FIRING_INTERFACE_HPP_INCLUDED
