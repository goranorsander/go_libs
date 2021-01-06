#ifndef GO_MVVM_NOTIFY_EVENT_FIRING_INTERFACE_HPP_INCLUDED
#define GO_MVVM_NOTIFY_EVENT_FIRING_INTERFACE_HPP_INCLUDED

//
//  notify_event_firing_interface.hpp
//
//  Copyright 2016-2021 Göran Orsander
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
#include <go/signals/signal.hpp>

namespace go
{
namespace mvvm
{

template<class S, class L> class basic_notify_event_firing_interface;
typedef basic_notify_event_firing_interface<std::string, std::recursive_mutex> notify_event_firing_interface;
typedef basic_notify_event_firing_interface<std::wstring, std::recursive_mutex> notify_wevent_firing_interface;

template<class S, class L = std::recursive_mutex>
class basic_notify_event_firing_interface
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_notify_event_firing_interface<S, L> this_type;
    typedef typename go::signals::signal<std::function<void(const std::shared_ptr<basic_event<string_type>>&)>, L> event_fired_signal;

public:
    virtual ~basic_notify_event_firing_interface() = 0;

protected:
    basic_notify_event_firing_interface() GO_DEFAULT_CONSTRUCTOR

public:
    event_fired_signal event_fired;
};

template<>
inline basic_notify_event_firing_interface<std::string, std::recursive_mutex>::~basic_notify_event_firing_interface()
{
    this->event_fired.disconnect_all_slots();
}

template<>
inline basic_notify_event_firing_interface<std::wstring, std::recursive_mutex>::~basic_notify_event_firing_interface()
{
    this->event_fired.disconnect_all_slots();
}

template<>
inline basic_notify_event_firing_interface<std::string, go::async::placebo_lockable>::~basic_notify_event_firing_interface()
{
    this->event_fired.disconnect_all_slots();
}

template<>
inline basic_notify_event_firing_interface<std::wstring, go::async::placebo_lockable>::~basic_notify_event_firing_interface()
{
    this->event_fired.disconnect_all_slots();
}

template<class S, class L>
inline basic_notify_event_firing_interface<S, L>::~basic_notify_event_firing_interface()
{
    this->event_fired.disconnect_all_slots();
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_NOTIFY_EVENT_FIRING_INTERFACE_HPP_INCLUDED
