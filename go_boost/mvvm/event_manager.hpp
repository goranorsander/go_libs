#ifndef GO_BOOST_MVVM_EVENT_MANAGER_HPP_INCLUDED
#define GO_BOOST_MVVM_EVENT_MANAGER_HPP_INCLUDED

//
//  event_manager.hpp
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

#include <list>
#include <map>
#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <go_boost/mvvm/event.hpp>
#include <go_boost/mvvm/notify_event_firing_interface.hpp>
#include <go_boost/utility/noncopyable_nonmovable.hpp>

namespace go_boost
{
namespace mvvm
{

typedef unsigned int event_subscription_key_type;

template<class S> class basic_event_manager;
typedef basic_event_manager<std::string> event_manager;
typedef basic_event_manager<std::wstring> wevent_manager;

template<class S>
class basic_event_manager
    : public basic_notify_event_firing_interface<S>
    , private go_boost::utility::noncopyable_nonmovable
{
public:
    typedef S string_type;
    typedef basic_event_manager<S> this_type;
    typedef typename boost::shared_ptr<basic_event_manager<S>> ptr;
    typedef typename boost::weak_ptr<basic_event_manager<S>> wptr;

public:
    virtual ~basic_event_manager();

protected:
    basic_event_manager();

public:
    static ptr create();

    event_subscription_key_type subscribe(const S& event_type, const boost::function<void(const boost::shared_ptr<basic_event<S>>&)>& fire_event_function);
    void unsubscribe(const S& event_type, const event_subscription_key_type& event_subscription_key);
    void unsubscribe_all(const S& event_type);
    void unsubscribe_all();

    void fire(const boost::shared_ptr<basic_event<S>>& e) const;
    void post(const boost::shared_ptr<basic_event<S>>& e, const bool keep_event_alive = true);
    void fire_events();

private:
    mutable boost::recursive_mutex _events_guard;
    event_subscription_key_type _next_event_subscription_key;
    std::map<S, std::map<event_subscription_key_type, boost::function<void(const boost::shared_ptr<basic_event<S>>&)>>> _subscriptions;
    std::list<std::pair<boost::weak_ptr<basic_event<S>>, boost::shared_ptr<basic_event<S>>>> _events;
};

template<class S>
inline basic_event_manager<S>::~basic_event_manager()
{
    unsubscribe_all();
}

template<class S>
inline basic_event_manager<S>::basic_event_manager()
    : basic_notify_event_firing_interface<S>()
    , go_boost::utility::noncopyable_nonmovable()
    , _events_guard()
    , _next_event_subscription_key(0)
    , _subscriptions()
    , _events()
{
}

template<class S>
inline boost::shared_ptr<basic_event_manager<S>> basic_event_manager<S>::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler()
            : this_type()
        {
        }
    };

    return boost::make_shared<make_shared_enabler>();
}

template<>
inline event_subscription_key_type basic_event_manager<std::string>::subscribe(const std::string& event_type, const boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)>& fire_event_function)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::string, event_subscription_type> subscriptions_type;
    const boost::recursive_mutex::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions == _subscriptions.end())
    {
        std::string key = event_type;
        event_subscription_type value = event_subscription_type();
        _subscriptions[key] = value;
        event_type_subscriptions = _subscriptions.find(event_type);
    }
    const event_subscription_key_type event_subscription_key = ++_next_event_subscription_key;
    event_type_subscriptions->second[event_subscription_key] = fire_event_function;
    return event_subscription_key;
}

template<>
inline event_subscription_key_type basic_event_manager<std::wstring>::subscribe(const std::wstring& event_type, const boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)>& fire_event_function)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::wstring, event_subscription_type> subscriptions_type;
    const boost::recursive_mutex::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions == _subscriptions.end())
    {
        std::wstring key = event_type;
        event_subscription_type value = event_subscription_type();
        _subscriptions[key] = value;
        event_type_subscriptions = _subscriptions.find(event_type);
    }
    const event_subscription_key_type event_subscription_key = ++_next_event_subscription_key;
    event_type_subscriptions->second[event_subscription_key] = fire_event_function;
    return event_subscription_key;
}

template<class S>
inline event_subscription_key_type basic_event_manager<S>::subscribe(const S& event_type, const boost::function<void(const boost::shared_ptr<basic_event<S>>&)>& fire_event_function)
{
    typedef typename boost::function<void(const boost::shared_ptr<basic_event<S>>&)> event_signal_signature;
    typedef typename std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef typename std::map<S, event_subscription_type> subscriptions_type;
    const boost::recursive_mutex::scoped_lock lock(_events_guard);
    typename subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions == _subscriptions.end())
    {
        S key = event_type;
        event_subscription_type value = event_subscription_type();
        _subscriptions[key] = value;
        event_type_subscriptions = _subscriptions.find(event_type);
    }
    const event_subscription_key_type event_subscription_key = ++_next_event_subscription_key;
    event_type_subscriptions->second[event_subscription_key] = fire_event_function;
    return event_subscription_key;
}

template<>
inline void basic_event_manager<std::string>::unsubscribe(const std::string& event_type, const event_subscription_key_type& event_subscription_key)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::string, event_subscription_type> subscriptions_type;
    const boost::recursive_mutex::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(event_subscription_key);
    }
}

template<>
inline void basic_event_manager<std::wstring>::unsubscribe(const std::wstring& event_type, const event_subscription_key_type& event_subscription_key)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::wstring, event_subscription_type> subscriptions_type;
    const boost::recursive_mutex::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(event_subscription_key);
    }
}

template<class S>
inline void basic_event_manager<S>::unsubscribe(const S& event_type, const event_subscription_key_type& event_subscription_key)
{
    typedef typename boost::function<void(const boost::shared_ptr<basic_event<S>>&)> event_signal_signature;
    typedef typename std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef typename std::map<S, event_subscription_type> subscriptions_type;
    const boost::recursive_mutex::scoped_lock lock(_events_guard);
    typename subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(event_subscription_key);
    }
}

template<>
inline void basic_event_manager<std::string>::unsubscribe_all(const std::string& event_type)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::string, event_subscription_type> subscriptions_type;
    const boost::recursive_mutex::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<>
inline void basic_event_manager<std::wstring>::unsubscribe_all(const std::wstring& event_type)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::wstring, event_subscription_type> subscriptions_type;
    const boost::recursive_mutex::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<class S>
inline void basic_event_manager<S>::unsubscribe_all(const S& event_type)
{
    typedef typename boost::function<void(const boost::shared_ptr<basic_event<S>>&)> event_signal_signature;
    typedef typename std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef typename std::map<S, event_subscription_type> subscriptions_type;
    const boost::recursive_mutex::scoped_lock lock(_events_guard);
    typename subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<class S>
inline void basic_event_manager<S>::unsubscribe_all()
{
    const boost::recursive_mutex::scoped_lock lock(_events_guard);
    _subscriptions.clear();
}

template<>
inline void basic_event_manager<std::string>::fire(const boost::shared_ptr<basic_event<std::string>>& e) const
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::string, event_subscription_type> subscriptions_type;
    if(e)
    {
        const boost::recursive_mutex::scoped_lock lock(_events_guard);
        GO_BOOST_TYPENAME subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(e->event_type());
        if(event_type_subscriptions != _subscriptions.end())
        {
            BOOST_FOREACH(const GO_BOOST_TYPENAME event_subscription_type::value_type& subscription, event_type_subscriptions->second)
            {
                subscription.second(e);
            }
            event_fired(e);
        }
    }
}

template<>
inline void basic_event_manager<std::wstring>::fire(const boost::shared_ptr<basic_event<std::wstring>>& e) const
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::wstring, event_subscription_type> subscriptions_type;
    if(e)
    {
        const boost::recursive_mutex::scoped_lock lock(_events_guard);
        GO_BOOST_TYPENAME subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(e->event_type());
        if(event_type_subscriptions != _subscriptions.end())
        {
            BOOST_FOREACH(const GO_BOOST_TYPENAME event_subscription_type::value_type& subscription, event_type_subscriptions->second)
            {
                subscription.second(e);
            }
            event_fired(e);
        }
    }
}

template<class S>
inline void basic_event_manager<S>::fire(const boost::shared_ptr<basic_event<S>>& e) const
{
    typedef typename boost::function<void(const boost::shared_ptr<basic_event<S>>&)> event_signal_signature;
    typedef typename std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef typename std::map<S, event_subscription_type> subscriptions_type;
    if(e)
    {
        const boost::recursive_mutex::scoped_lock lock(_events_guard);
        typename subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(e->event_type());
        if(event_type_subscriptions != _subscriptions.end())
        {
            BOOST_FOREACH(const typename event_subscription_type::value_type& subscription, event_type_subscriptions->second)
            {
                subscription.second(e);
            }
            event_fired(e);
        }
    }
}

template<>
inline void basic_event_manager<std::string>::post(const boost::shared_ptr<basic_event<std::string>>& e, const bool keep_event_alive)
{
    if(e)
    {
        const boost::recursive_mutex::scoped_lock lock(_events_guard);
        _events.push_back(std::pair<boost::weak_ptr<basic_event<std::string>>, boost::shared_ptr<basic_event<std::string>>>(boost::weak_ptr<basic_event<std::string>>(e), keep_event_alive ? e : boost::shared_ptr<basic_event<std::string>>()));
    }
}

template<>
inline void basic_event_manager<std::wstring>::post(const boost::shared_ptr<basic_event<std::wstring>>& e, const bool keep_event_alive)
{
    if(e)
    {
        const boost::recursive_mutex::scoped_lock lock(_events_guard);
        _events.push_back(std::pair<boost::weak_ptr<basic_event<std::wstring>>, boost::shared_ptr<basic_event<std::wstring>>>(boost::weak_ptr<basic_event<std::wstring>>(e), keep_event_alive ? e : boost::shared_ptr<basic_event<std::wstring>>()));
    }
}

template<class S>
inline void basic_event_manager<S>::post(const boost::shared_ptr<basic_event<S>>& e, const bool keep_event_alive)
{
    if(e)
    {
        const boost::recursive_mutex::scoped_lock lock(_events_guard);
        _events.push_back(std::pair<boost::weak_ptr<basic_event<S>>, boost::shared_ptr<basic_event<S>>>(boost::weak_ptr<basic_event<S>>(e), keep_event_alive ? e : boost::shared_ptr<basic_event<S>>()));
    }
}

template<>
inline void basic_event_manager<std::string>::fire_events()
{
    typedef GO_BOOST_TYPENAME std::list<std::pair<boost::weak_ptr<basic_event<std::string>>, boost::shared_ptr<basic_event<std::string>>>> events_type;
    events_type events;
    {
        const boost::recursive_mutex::scoped_lock lock(_events_guard);
        std::swap(events, _events);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME events_type::value_type& e, events)
    {
        fire(e.first.lock());
    }
}

template<>
inline void basic_event_manager<std::wstring>::fire_events()
{
    typedef GO_BOOST_TYPENAME std::list<std::pair<boost::weak_ptr<basic_event<std::wstring>>, boost::shared_ptr<basic_event<std::wstring>>>> events_type;
    std::list<std::pair<boost::weak_ptr<basic_event<std::wstring>>, boost::shared_ptr<basic_event<std::wstring>>>> events;
    {
        const boost::recursive_mutex::scoped_lock lock(_events_guard);
        std::swap(events, _events);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME events_type::value_type& e, events)
    {
        fire(e.first.lock());
    }
}

template<class S>
inline void basic_event_manager<S>::fire_events()
{
    typedef GO_BOOST_TYPENAME std::list<std::pair<boost::weak_ptr<basic_event<S>>, boost::shared_ptr<basic_event<S>>>> events_type;
    std::list<std::pair<boost::weak_ptr<basic_event<S>>, boost::shared_ptr<basic_event<S>>>> events;
    {
        const boost::recursive_mutex::scoped_lock lock(_events_guard);
        std::swap(events, _events);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME events_type::value_type& e, events)
    {
        fire(e.first.lock());
    }
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_EVENT_MANAGER_HPP_INCLUDED
