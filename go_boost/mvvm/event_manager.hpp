#ifndef GO_BOOST_MVVM_EVENT_MANAGER_HPP_INCLUDED
#define GO_BOOST_MVVM_EVENT_MANAGER_HPP_INCLUDED

//
//  event_manager.hpp
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

#include <deque>
#include <map>
#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <go_boost/mvvm/event.hpp>
#include <go_boost/mvvm/notify_event_firing_interface.hpp>
#include <go_boost/utility/noncopyable_nonmovable.hpp>
#include <go_boost/utility/placebo_mutex.hpp>

namespace go_boost
{
namespace mvvm
{

typedef unsigned int event_subscription_key_type;

template<class S, typename M> class basic_event_manager;
typedef basic_event_manager<std::string, boost::recursive_mutex> event_manager;
typedef basic_event_manager<std::wstring, boost::recursive_mutex> wevent_manager;

namespace single_threaded
{

typedef basic_event_manager<std::string, go_boost::utility::placebo_mutex> event_manager;
typedef basic_event_manager<std::wstring, go_boost::utility::placebo_mutex> wevent_manager;

}

template<class S, typename M = boost::recursive_mutex>
class basic_event_manager
    : public basic_notify_event_firing_interface<S, M>
    , private go_boost::utility::noncopyable_nonmovable
{
public:
    typedef S string_type;
    typedef M mutex_type;
    typedef basic_event_manager<S, M> this_type;
    typedef typename boost::shared_ptr<basic_event_manager<S, M>> ptr;
    typedef typename boost::weak_ptr<basic_event_manager<S, M>> wptr;

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

    size_t events() const;

private:
    mutable mutex_type _events_guard;
    event_subscription_key_type _next_event_subscription_key;
    std::map<S, std::map<event_subscription_key_type, boost::function<void(const boost::shared_ptr<basic_event<S>>&)>>> _subscriptions;
    std::deque<std::pair<boost::weak_ptr<basic_event<S>>, boost::shared_ptr<basic_event<S>>>> _events;
};

template<class S, typename M>
inline basic_event_manager<S, M>::~basic_event_manager()
{
    unsubscribe_all();
}

template<class S, typename M>
inline basic_event_manager<S, M>::basic_event_manager()
    : basic_notify_event_firing_interface<S, M>()
    , go_boost::utility::noncopyable_nonmovable()
    , _events_guard()
    , _next_event_subscription_key(0)
    , _subscriptions()
    , _events()
{
}

template<>
inline event_subscription_key_type basic_event_manager<std::string, boost::recursive_mutex>::subscribe(const std::string& event_type, const boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)>& fire_event_function)
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
inline event_subscription_key_type basic_event_manager<std::wstring, boost::recursive_mutex>::subscribe(const std::wstring& event_type, const boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)>& fire_event_function)
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

template<>
inline event_subscription_key_type basic_event_manager<std::string, go_boost::utility::placebo_mutex>::subscribe(const std::string& event_type, const boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)>& fire_event_function)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::string, event_subscription_type> subscriptions_type;
    const go_boost::utility::placebo_mutex::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions == _subscriptions.end())
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
inline event_subscription_key_type basic_event_manager<std::wstring, go_boost::utility::placebo_mutex>::subscribe(const std::wstring& event_type, const boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)>& fire_event_function)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::wstring, event_subscription_type> subscriptions_type;
    const go_boost::utility::placebo_mutex::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions == _subscriptions.end())
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

template<class S, typename M>
inline event_subscription_key_type basic_event_manager<S, M>::subscribe(const S& event_type, const boost::function<void(const boost::shared_ptr<basic_event<S>>&)>& fire_event_function)
{
    typedef typename boost::function<void(const boost::shared_ptr<basic_event<S>>&)> event_signal_signature;
    typedef typename std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef typename std::map<S, event_subscription_type> subscriptions_type;
    const typename mutex_type::scoped_lock lock(_events_guard);
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
inline void basic_event_manager<std::string, boost::recursive_mutex>::unsubscribe(const std::string& event_type, const event_subscription_key_type& event_subscription_key)
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
inline void basic_event_manager<std::wstring, boost::recursive_mutex>::unsubscribe(const std::wstring& event_type, const event_subscription_key_type& event_subscription_key)
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

template<>
inline void basic_event_manager<std::string, go_boost::utility::placebo_mutex>::unsubscribe(const std::string& event_type, const event_subscription_key_type& event_subscription_key)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::string, event_subscription_type> subscriptions_type;
    const go_boost::utility::placebo_mutex::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(event_subscription_key);
    }
}

template<>
inline void basic_event_manager<std::wstring, go_boost::utility::placebo_mutex>::unsubscribe(const std::wstring& event_type, const event_subscription_key_type& event_subscription_key)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::wstring, event_subscription_type> subscriptions_type;
    const go_boost::utility::placebo_mutex::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(event_subscription_key);
    }
}

template<class S, typename M>
inline void basic_event_manager<S, M>::unsubscribe(const S& event_type, const event_subscription_key_type& event_subscription_key)
{
    typedef typename boost::function<void(const boost::shared_ptr<basic_event<S>>&)> event_signal_signature;
    typedef typename std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef typename std::map<S, event_subscription_type> subscriptions_type;
    const typename mutex_type::scoped_lock lock(_events_guard);
    typename subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(event_subscription_key);
    }
}

template<>
inline void basic_event_manager<std::string, boost::recursive_mutex>::unsubscribe_all(const std::string& event_type)
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
inline void basic_event_manager<std::wstring, boost::recursive_mutex>::unsubscribe_all(const std::wstring& event_type)
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

template<>
inline void basic_event_manager<std::string, go_boost::utility::placebo_mutex>::unsubscribe_all(const std::string& event_type)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::string, event_subscription_type> subscriptions_type;
    const go_boost::utility::placebo_mutex::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<>
inline void basic_event_manager<std::wstring, go_boost::utility::placebo_mutex>::unsubscribe_all(const std::wstring& event_type)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::wstring, event_subscription_type> subscriptions_type;
    const go_boost::utility::placebo_mutex::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<class S, typename M>
inline void basic_event_manager<S, M>::unsubscribe_all(const S& event_type)
{
    typedef typename boost::function<void(const boost::shared_ptr<basic_event<S>>&)> event_signal_signature;
    typedef typename std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef typename std::map<S, event_subscription_type> subscriptions_type;
    const typename mutex_type::scoped_lock lock(_events_guard);
    typename subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<class S, typename M>
inline void basic_event_manager<S, M>::unsubscribe_all()
{
    const typename mutex_type::scoped_lock lock(this->_events_guard);
    this->_subscriptions.clear();
}

template<>
inline void basic_event_manager<std::string, boost::recursive_mutex>::fire(const boost::shared_ptr<basic_event<std::string>>& e) const
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
            this->event_fired(e);
        }
    }
}

template<>
inline void basic_event_manager<std::wstring, boost::recursive_mutex>::fire(const boost::shared_ptr<basic_event<std::wstring>>& e) const
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
            this->event_fired(e);
        }
    }
}

template<>
inline void basic_event_manager<std::string, go_boost::utility::placebo_mutex>::fire(const boost::shared_ptr<basic_event<std::string>>& e) const
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::string, event_subscription_type> subscriptions_type;
    if (e)
    {
        const go_boost::utility::placebo_mutex::scoped_lock lock(_events_guard);
        GO_BOOST_TYPENAME subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(e->event_type());
        if (event_type_subscriptions != _subscriptions.end())
        {
            BOOST_FOREACH(const GO_BOOST_TYPENAME event_subscription_type::value_type& subscription, event_type_subscriptions->second)
            {
                subscription.second(e);
            }
            this->event_fired(e);
        }
    }
}

template<>
inline void basic_event_manager<std::wstring, go_boost::utility::placebo_mutex>::fire(const boost::shared_ptr<basic_event<std::wstring>>& e) const
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::wstring, event_subscription_type> subscriptions_type;
    if (e)
    {
        const go_boost::utility::placebo_mutex::scoped_lock lock(_events_guard);
        GO_BOOST_TYPENAME subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(e->event_type());
        if (event_type_subscriptions != _subscriptions.end())
        {
            BOOST_FOREACH(const GO_BOOST_TYPENAME event_subscription_type::value_type& subscription, event_type_subscriptions->second)
            {
                subscription.second(e);
            }
            this->event_fired(e);
        }
    }
}

template<class S, typename M>
inline void basic_event_manager<S, M>::fire(const boost::shared_ptr<basic_event<S>>& e) const
{
    typedef typename boost::function<void(const boost::shared_ptr<basic_event<S>>&)> event_signal_signature;
    typedef typename std::map<event_subscription_key_type, event_signal_signature> event_subscription_type;
    typedef typename std::map<S, event_subscription_type> subscriptions_type;
    if(e)
    {
        const typename mutex_type::scoped_lock lock(_events_guard);
        typename subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(e->event_type());
        if(event_type_subscriptions != _subscriptions.end())
        {
            BOOST_FOREACH(const typename event_subscription_type::value_type& subscription, event_type_subscriptions->second)
            {
                subscription.second(e);
            }
            this->event_fired(e);
        }
    }
}

template<>
inline void basic_event_manager<std::string, boost::recursive_mutex>::post(const boost::shared_ptr<basic_event<std::string>>& e, const bool keep_event_alive)
{
    if(e)
    {
        const boost::recursive_mutex::scoped_lock lock(_events_guard);
        _events.push_back(std::pair<boost::weak_ptr<basic_event<std::string>>, boost::shared_ptr<basic_event<std::string>>>(boost::weak_ptr<basic_event<std::string>>(e), keep_event_alive ? e : boost::shared_ptr<basic_event<std::string>>()));
    }
}

template<>
inline void basic_event_manager<std::wstring, boost::recursive_mutex>::post(const boost::shared_ptr<basic_event<std::wstring>>& e, const bool keep_event_alive)
{
    if(e)
    {
        const boost::recursive_mutex::scoped_lock lock(_events_guard);
        _events.push_back(std::pair<boost::weak_ptr<basic_event<std::wstring>>, boost::shared_ptr<basic_event<std::wstring>>>(boost::weak_ptr<basic_event<std::wstring>>(e), keep_event_alive ? e : boost::shared_ptr<basic_event<std::wstring>>()));
    }
}

template<>
inline void basic_event_manager<std::string, go_boost::utility::placebo_mutex>::post(const boost::shared_ptr<basic_event<std::string>>& e, const bool keep_event_alive)
{
    if (e)
    {
        const go_boost::utility::placebo_mutex::scoped_lock lock(_events_guard);
        _events.push_back(std::pair<boost::weak_ptr<basic_event<std::string>>, boost::shared_ptr<basic_event<std::string>>>(boost::weak_ptr<basic_event<std::string>>(e), keep_event_alive ? e : boost::shared_ptr<basic_event<std::string>>()));
    }
}

template<>
inline void basic_event_manager<std::wstring, go_boost::utility::placebo_mutex>::post(const boost::shared_ptr<basic_event<std::wstring>>& e, const bool keep_event_alive)
{
    if (e)
    {
        const go_boost::utility::placebo_mutex::scoped_lock lock(_events_guard);
        _events.push_back(std::pair<boost::weak_ptr<basic_event<std::wstring>>, boost::shared_ptr<basic_event<std::wstring>>>(boost::weak_ptr<basic_event<std::wstring>>(e), keep_event_alive ? e : boost::shared_ptr<basic_event<std::wstring>>()));
    }
}

template<class S, typename M>
inline void basic_event_manager<S, M>::post(const boost::shared_ptr<basic_event<S>>& e, const bool keep_event_alive)
{
    if(e)
    {
        const typename mutex_type::scoped_lock lock(_events_guard);
        _events.push_back(std::pair<boost::weak_ptr<basic_event<S>>, boost::shared_ptr<basic_event<S>>>(boost::weak_ptr<basic_event<S>>(e), keep_event_alive ? e : boost::shared_ptr<basic_event<S>>()));
    }
}

template<>
inline void basic_event_manager<std::string, boost::recursive_mutex>::fire_events()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_event<std::string>>, boost::shared_ptr<basic_event<std::string>>>> events_type;
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
inline void basic_event_manager<std::wstring, boost::recursive_mutex>::fire_events()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_event<std::wstring>>, boost::shared_ptr<basic_event<std::wstring>>>> events_type;
    std::deque<std::pair<boost::weak_ptr<basic_event<std::wstring>>, boost::shared_ptr<basic_event<std::wstring>>>> events;
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
inline void basic_event_manager<std::string, go_boost::utility::placebo_mutex>::fire_events()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_event<std::string>>, boost::shared_ptr<basic_event<std::string>>>> events_type;
    events_type events;
    {
        const go_boost::utility::placebo_mutex::scoped_lock lock(_events_guard);
        std::swap(events, _events);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME events_type::value_type& e, events)
    {
        fire(e.first.lock());
    }
}

template<>
inline void basic_event_manager<std::wstring, go_boost::utility::placebo_mutex>::fire_events()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_event<std::wstring>>, boost::shared_ptr<basic_event<std::wstring>>>> events_type;
    std::deque<std::pair<boost::weak_ptr<basic_event<std::wstring>>, boost::shared_ptr<basic_event<std::wstring>>>> events;
    {
        const go_boost::utility::placebo_mutex::scoped_lock lock(_events_guard);
        std::swap(events, _events);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME events_type::value_type& e, events)
    {
        fire(e.first.lock());
    }
}

template<class S, typename M>
inline void basic_event_manager<S, M>::fire_events()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_event<S>>, boost::shared_ptr<basic_event<S>>>> events_type;
    std::deque<std::pair<boost::weak_ptr<basic_event<S>>, boost::shared_ptr<basic_event<S>>>> events;
    {
        const typename mutex_type::scoped_lock lock(_events_guard);
        std::swap(events, _events);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME events_type::value_type& e, events)
    {
        fire(e.first.lock());
    }
}

template<>
inline size_t basic_event_manager<std::string, boost::recursive_mutex>::events() const
{
    const boost::recursive_mutex::scoped_lock lock(_events_guard);
    return _events.size();
}

template<>
inline size_t basic_event_manager<std::wstring, boost::recursive_mutex>::events() const
{
    const boost::recursive_mutex::scoped_lock lock(_events_guard);
    return _events.size();
}

template<>
inline size_t basic_event_manager<std::string, go_boost::utility::placebo_mutex>::events() const
{
    const go_boost::utility::placebo_mutex::scoped_lock lock(_events_guard);
    return _events.size();
}

template<>
inline size_t basic_event_manager<std::wstring, go_boost::utility::placebo_mutex>::events() const
{
    const go_boost::utility::placebo_mutex::scoped_lock lock(_events_guard);
    return _events.size();
}

template<class S, typename M>
inline size_t basic_event_manager<S, M>::events() const
{
    const typename mutex_type::scoped_lock lock(_events_guard);
    return _events.size();
}

template<class S, typename M>
inline boost::shared_ptr<basic_event_manager<S, M>> basic_event_manager<S, M>::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_BOOST_DEFAULT_CONSTRUCTOR
    };

    return boost::make_shared<make_shared_enabler>();
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_EVENT_MANAGER_HPP_INCLUDED
