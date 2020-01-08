#ifndef GO_BOOST_MVVM_EVENT_MANAGER_HPP_INCLUDED
#define GO_BOOST_MVVM_EVENT_MANAGER_HPP_INCLUDED

//
//  event_manager.hpp
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

#include <deque>
#include <map>
#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <go_boost/async/placebo_lockable.hpp>
#include <go_boost/mvvm/event_subscription_key.hpp>
#include <go_boost/mvvm/event.hpp>
#include <go_boost/mvvm/notify_event_firing_interface.hpp>
#include <go_boost/type_traits/noncopyable_nonmovable.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, class L> class basic_event_manager;
typedef basic_event_manager<std::string, boost::recursive_mutex> event_manager;
typedef basic_event_manager<std::wstring, boost::recursive_mutex> wevent_manager;

namespace single_threaded
{

typedef basic_event_manager<std::string, go_boost::async::placebo_lockable> event_manager;
typedef basic_event_manager<std::wstring, go_boost::async::placebo_lockable> wevent_manager;

}

template<class S, class L = boost::recursive_mutex>
class basic_event_manager
    : public basic_notify_event_firing_interface<S, L>
    , go_boost::type_traits::noncopyable_nonmovable
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_event_manager<S, L> this_type;
    typedef typename boost::shared_ptr<basic_event_manager<S, L>> ptr;
    typedef typename boost::weak_ptr<basic_event_manager<S, L>> wptr;

public:
    virtual ~basic_event_manager();

protected:
    basic_event_manager();

public:
    static ptr create();

    event_subscription_key subscribe(const S& event_type, const boost::function<void(const boost::shared_ptr<basic_event<S>>&)>& fire_event_function);
    void unsubscribe(const S& event_type, const event_subscription_key& key);
    void unsubscribe_all(const S& event_type);
    void unsubscribe_all();

    void fire(const boost::shared_ptr<basic_event<S>>& e) const;
    void post(const boost::shared_ptr<basic_event<S>>& e, const bool keep_event_alive = true);
    void fire_events();

    size_t events() const;

private:
    mutable lockable_type _events_guard;
    event_subscription_key _next_event_subscription_key;
    std::map<S, std::map<event_subscription_key, boost::function<void(const boost::shared_ptr<basic_event<S>>&)>>> _subscriptions;
    std::deque<std::pair<boost::weak_ptr<basic_event<S>>, boost::shared_ptr<basic_event<S>>>> _events;
};

template<class S, class L>
inline basic_event_manager<S, L>::~basic_event_manager()
{
    unsubscribe_all();
}

template<class S, class L>
inline basic_event_manager<S, L>::basic_event_manager()
    : basic_notify_event_firing_interface<S, L>()
    , go_boost::type_traits::noncopyable_nonmovable()
    , _events_guard()
    , _next_event_subscription_key(0)
    , _subscriptions()
    , _events()
{
}

template<>
inline event_subscription_key basic_event_manager<std::string, boost::recursive_mutex>::subscribe(const std::string& event_type, const boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)>& fire_event_function)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
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
    const event_subscription_key key = ++_next_event_subscription_key;
    event_type_subscriptions->second[key] = fire_event_function;
    return key;
}

template<>
inline event_subscription_key basic_event_manager<std::wstring, boost::recursive_mutex>::subscribe(const std::wstring& event_type, const boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)>& fire_event_function)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
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
    const event_subscription_key key = ++_next_event_subscription_key;
    event_type_subscriptions->second[key] = fire_event_function;
    return key;
}

template<>
inline event_subscription_key basic_event_manager<std::string, go_boost::async::placebo_lockable>::subscribe(const std::string& event_type, const boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)>& fire_event_function)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::string, event_subscription_type> subscriptions_type;
    const go_boost::async::placebo_lockable::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions == _subscriptions.end())
    {
        std::string key = event_type;
        event_subscription_type value = event_subscription_type();
        _subscriptions[key] = value;
        event_type_subscriptions = _subscriptions.find(event_type);
    }
    const event_subscription_key key = ++_next_event_subscription_key;
    event_type_subscriptions->second[key] = fire_event_function;
    return key;
}

template<>
inline event_subscription_key basic_event_manager<std::wstring, go_boost::async::placebo_lockable>::subscribe(const std::wstring& event_type, const boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)>& fire_event_function)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::wstring, event_subscription_type> subscriptions_type;
    const go_boost::async::placebo_lockable::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions == _subscriptions.end())
    {
        std::wstring key = event_type;
        event_subscription_type value = event_subscription_type();
        _subscriptions[key] = value;
        event_type_subscriptions = _subscriptions.find(event_type);
    }
    const event_subscription_key key = ++_next_event_subscription_key;
    event_type_subscriptions->second[key] = fire_event_function;
    return key;
}

template<class S, class L>
inline event_subscription_key basic_event_manager<S, L>::subscribe(const S& event_type, const boost::function<void(const boost::shared_ptr<basic_event<S>>&)>& fire_event_function)
{
    typedef typename boost::function<void(const boost::shared_ptr<basic_event<S>>&)> event_signal_signature;
    typedef typename std::map<event_subscription_key, event_signal_signature> event_subscription_type;
    typedef typename std::map<S, event_subscription_type> subscriptions_type;
    const typename lockable_type::scoped_lock lock(_events_guard);
    typename subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions == _subscriptions.end())
    {
        S key = event_type;
        event_subscription_type value = event_subscription_type();
        _subscriptions[key] = value;
        event_type_subscriptions = _subscriptions.find(event_type);
    }
    const event_subscription_key key = ++_next_event_subscription_key;
    event_type_subscriptions->second[key] = fire_event_function;
    return key;
}

template<>
inline void basic_event_manager<std::string, boost::recursive_mutex>::unsubscribe(const std::string& event_type, const event_subscription_key& key)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::string, event_subscription_type> subscriptions_type;
    const boost::recursive_mutex::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(key);
    }
}

template<>
inline void basic_event_manager<std::wstring, boost::recursive_mutex>::unsubscribe(const std::wstring& event_type, const event_subscription_key& key)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::wstring, event_subscription_type> subscriptions_type;
    const boost::recursive_mutex::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(key);
    }
}

template<>
inline void basic_event_manager<std::string, go_boost::async::placebo_lockable>::unsubscribe(const std::string& event_type, const event_subscription_key& key)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::string, event_subscription_type> subscriptions_type;
    const go_boost::async::placebo_lockable::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(key);
    }
}

template<>
inline void basic_event_manager<std::wstring, go_boost::async::placebo_lockable>::unsubscribe(const std::wstring& event_type, const event_subscription_key& key)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::wstring, event_subscription_type> subscriptions_type;
    const go_boost::async::placebo_lockable::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(key);
    }
}

template<class S, class L>
inline void basic_event_manager<S, L>::unsubscribe(const S& event_type, const event_subscription_key& key)
{
    typedef typename boost::function<void(const boost::shared_ptr<basic_event<S>>&)> event_signal_signature;
    typedef typename std::map<event_subscription_key, event_signal_signature> event_subscription_type;
    typedef typename std::map<S, event_subscription_type> subscriptions_type;
    const typename lockable_type::scoped_lock lock(_events_guard);
    typename subscriptions_type::iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(key);
    }
}

template<>
inline void basic_event_manager<std::string, boost::recursive_mutex>::unsubscribe_all(const std::string& event_type)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
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
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::wstring, event_subscription_type> subscriptions_type;
    const boost::recursive_mutex::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<>
inline void basic_event_manager<std::string, go_boost::async::placebo_lockable>::unsubscribe_all(const std::string& event_type)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::string, event_subscription_type> subscriptions_type;
    const go_boost::async::placebo_lockable::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<>
inline void basic_event_manager<std::wstring, go_boost::async::placebo_lockable>::unsubscribe_all(const std::wstring& event_type)
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::wstring, event_subscription_type> subscriptions_type;
    const go_boost::async::placebo_lockable::scoped_lock lock(_events_guard);
    GO_BOOST_TYPENAME subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<class S, class L>
inline void basic_event_manager<S, L>::unsubscribe_all(const S& event_type)
{
    typedef typename boost::function<void(const boost::shared_ptr<basic_event<S>>&)> event_signal_signature;
    typedef typename std::map<event_subscription_key, event_signal_signature> event_subscription_type;
    typedef typename std::map<S, event_subscription_type> subscriptions_type;
    const typename lockable_type::scoped_lock lock(_events_guard);
    typename subscriptions_type::const_iterator event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<class S, class L>
inline void basic_event_manager<S, L>::unsubscribe_all()
{
    const typename lockable_type::scoped_lock lock(this->_events_guard);
    this->_subscriptions.clear();
}

template<>
inline void basic_event_manager<std::string, boost::recursive_mutex>::fire(const boost::shared_ptr<basic_event<std::string>>& e) const
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
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
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
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
inline void basic_event_manager<std::string, go_boost::async::placebo_lockable>::fire(const boost::shared_ptr<basic_event<std::string>>& e) const
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::string>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::string, event_subscription_type> subscriptions_type;
    if (e)
    {
        const go_boost::async::placebo_lockable::scoped_lock lock(_events_guard);
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
inline void basic_event_manager<std::wstring, go_boost::async::placebo_lockable>::fire(const boost::shared_ptr<basic_event<std::wstring>>& e) const
{
    typedef GO_BOOST_TYPENAME boost::function<void(const boost::shared_ptr<basic_event<std::wstring>>&)> event_signal_signature;
    typedef GO_BOOST_TYPENAME std::map<event_subscription_key, event_signal_signature> event_subscription_type;
    typedef GO_BOOST_TYPENAME std::map<std::wstring, event_subscription_type> subscriptions_type;
    if (e)
    {
        const go_boost::async::placebo_lockable::scoped_lock lock(_events_guard);
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

template<class S, class L>
inline void basic_event_manager<S, L>::fire(const boost::shared_ptr<basic_event<S>>& e) const
{
    typedef typename boost::function<void(const boost::shared_ptr<basic_event<S>>&)> event_signal_signature;
    typedef typename std::map<event_subscription_key, event_signal_signature> event_subscription_type;
    typedef typename std::map<S, event_subscription_type> subscriptions_type;
    if(e)
    {
        const typename lockable_type::scoped_lock lock(_events_guard);
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
inline void basic_event_manager<std::string, go_boost::async::placebo_lockable>::post(const boost::shared_ptr<basic_event<std::string>>& e, const bool keep_event_alive)
{
    if (e)
    {
        const go_boost::async::placebo_lockable::scoped_lock lock(_events_guard);
        _events.push_back(std::pair<boost::weak_ptr<basic_event<std::string>>, boost::shared_ptr<basic_event<std::string>>>(boost::weak_ptr<basic_event<std::string>>(e), keep_event_alive ? e : boost::shared_ptr<basic_event<std::string>>()));
    }
}

template<>
inline void basic_event_manager<std::wstring, go_boost::async::placebo_lockable>::post(const boost::shared_ptr<basic_event<std::wstring>>& e, const bool keep_event_alive)
{
    if (e)
    {
        const go_boost::async::placebo_lockable::scoped_lock lock(_events_guard);
        _events.push_back(std::pair<boost::weak_ptr<basic_event<std::wstring>>, boost::shared_ptr<basic_event<std::wstring>>>(boost::weak_ptr<basic_event<std::wstring>>(e), keep_event_alive ? e : boost::shared_ptr<basic_event<std::wstring>>()));
    }
}

template<class S, class L>
inline void basic_event_manager<S, L>::post(const boost::shared_ptr<basic_event<S>>& e, const bool keep_event_alive)
{
    if(e)
    {
        const typename lockable_type::scoped_lock lock(_events_guard);
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
inline void basic_event_manager<std::string, go_boost::async::placebo_lockable>::fire_events()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_event<std::string>>, boost::shared_ptr<basic_event<std::string>>>> events_type;
    events_type events;
    {
        const go_boost::async::placebo_lockable::scoped_lock lock(_events_guard);
        std::swap(events, _events);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME events_type::value_type& e, events)
    {
        fire(e.first.lock());
    }
}

template<>
inline void basic_event_manager<std::wstring, go_boost::async::placebo_lockable>::fire_events()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_event<std::wstring>>, boost::shared_ptr<basic_event<std::wstring>>>> events_type;
    std::deque<std::pair<boost::weak_ptr<basic_event<std::wstring>>, boost::shared_ptr<basic_event<std::wstring>>>> events;
    {
        const go_boost::async::placebo_lockable::scoped_lock lock(_events_guard);
        std::swap(events, _events);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME events_type::value_type& e, events)
    {
        fire(e.first.lock());
    }
}

template<class S, class L>
inline void basic_event_manager<S, L>::fire_events()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_event<S>>, boost::shared_ptr<basic_event<S>>>> events_type;
    std::deque<std::pair<boost::weak_ptr<basic_event<S>>, boost::shared_ptr<basic_event<S>>>> events;
    {
        const typename lockable_type::scoped_lock lock(_events_guard);
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
inline size_t basic_event_manager<std::string, go_boost::async::placebo_lockable>::events() const
{
    const go_boost::async::placebo_lockable::scoped_lock lock(_events_guard);
    return _events.size();
}

template<>
inline size_t basic_event_manager<std::wstring, go_boost::async::placebo_lockable>::events() const
{
    const go_boost::async::placebo_lockable::scoped_lock lock(_events_guard);
    return _events.size();
}

template<class S, class L>
inline size_t basic_event_manager<S, L>::events() const
{
    const typename lockable_type::scoped_lock lock(_events_guard);
    return _events.size();
}

template<class S, class L>
inline boost::shared_ptr<basic_event_manager<S, L>> basic_event_manager<S, L>::create()
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
