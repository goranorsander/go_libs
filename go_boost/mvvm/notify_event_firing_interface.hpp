#ifndef GO_BOOST_MVVM_NOTIFY_EVENT_FIRING_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_NOTIFY_EVENT_FIRING_INTERFACE_HPP_INCLUDED

//
//  notify_event_firing_interface.hpp
//
//  Copyright 2016-2018 Göran Orsander
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
#include <go_boost/signals.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, typename M> class basic_notify_event_firing_interface;
typedef basic_notify_event_firing_interface<std::string, boost::recursive_mutex> notify_event_firing_interface;
typedef basic_notify_event_firing_interface<std::wstring, boost::recursive_mutex> notify_wevent_firing_interface;

template<class S, typename M = boost::recursive_mutex>
class basic_notify_event_firing_interface
    : public go_boost::signals::slot
{
public:
    typedef S string_type;
    typedef M mutex_type;
    typedef basic_notify_event_firing_interface<S, M> this_type;
    typedef typename boost::signals2::signal<void(const boost::shared_ptr<basic_event<S>>&)> event_fired_signal;

public:
    virtual ~basic_notify_event_firing_interface() = 0;

protected:
    basic_notify_event_firing_interface();

public:
    event_fired_signal event_fired;
};

template<>
inline basic_notify_event_firing_interface<std::string, boost::recursive_mutex>::~basic_notify_event_firing_interface()
{
    event_fired.disconnect_all_slots();
}

template<>
inline basic_notify_event_firing_interface<std::wstring, boost::recursive_mutex>::~basic_notify_event_firing_interface()
{
    event_fired.disconnect_all_slots();
}

template<class S, typename M>
inline basic_notify_event_firing_interface<S, M>::~basic_notify_event_firing_interface()
{
    event_fired.disconnect_all_slots();
}

template<>
inline basic_notify_event_firing_interface<std::string, boost::recursive_mutex>::basic_notify_event_firing_interface()
    : go_boost::signals::slot()
    , event_fired()
{
}

template<>
inline basic_notify_event_firing_interface<std::wstring, boost::recursive_mutex>::basic_notify_event_firing_interface()
    : go_boost::signals::slot()
    , event_fired()
{
}

template<class S, typename M>
inline basic_notify_event_firing_interface<S, M>::basic_notify_event_firing_interface()
    : go_boost::signals::slot()
    , event_fired()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_NOTIFY_EVENT_FIRING_INTERFACE_HPP_INCLUDED
