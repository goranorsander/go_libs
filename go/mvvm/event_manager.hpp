#ifndef GO_MVVM_EVENT_MANAGER_HPP_INCLUDED
#define GO_MVVM_EVENT_MANAGER_HPP_INCLUDED

//
//  event_manager.hpp
//
//  Copyright 2016-2017 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <functional>
#include <list>
#include <map>
#include <mutex>
#include <go/mvvm/notify_event_firing_interface.hpp>

namespace go
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
    , public go::utility::noncopyable_nonmovable
{
public:
    typedef S string_type;
    typedef basic_event_manager<S> this_type;
    typedef typename std::shared_ptr<basic_event_manager<S>> ptr;
    typedef typename std::weak_ptr<basic_event_manager<S>> wptr;

public:
    virtual ~basic_event_manager();

protected:
    basic_event_manager();

public:
    static ptr create();

    event_subscription_key_type subscribe(const S& event_type, std::function<void(const std::shared_ptr<basic_event<S>>&)>&& fire_event_function);
    void unsubscribe(const S& event_type, const event_subscription_key_type& event_subscription_key);
    void unsubscribe_all(const S& event_type);
    void unsubscribe_all();

    void fire(const std::shared_ptr<basic_event<S>>& e) const;
    void post(const std::shared_ptr<basic_event<S>>& e, const bool keep_event_alive = true);
    void fire_events();

private:
    mutable std::recursive_mutex _events_guard;
    event_subscription_key_type _next_event_subscription_key;
    std::map<S, std::map<event_subscription_key_type, std::function<void(const std::shared_ptr<basic_event<S>>&)>>> _subscriptions;
    std::list<std::pair<std::weak_ptr<basic_event<S>>, std::shared_ptr<basic_event<S>>>> _events;
};

template<class S>
inline basic_event_manager<S>::~basic_event_manager()
{
    unsubscribe_all();
}

template<class S>
inline basic_event_manager<S>::basic_event_manager()
    : basic_notify_event_firing_interface<S>()
    , go::utility::noncopyable_nonmovable()
    , _events_guard()
    , _next_event_subscription_key(0)
    , _subscriptions()
    , _events()
{
}

template<class S>
inline std::shared_ptr<basic_event_manager<S>> basic_event_manager<S>::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler()
            : this_type()
        {
        }
    };

    return std::make_shared<make_shared_enabler>();
}

template<>
inline event_subscription_key_type basic_event_manager<std::string>::subscribe(const std::string& event_type, std::function<void(const std::shared_ptr<basic_event<std::string>>&)>&& fire_event_function)
{
    const std::lock_guard<std::recursive_mutex> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions == _subscriptions.end())
    {
        std::string key = event_type;
        auto value = std::map<event_subscription_key_type, std::function<void(const std::shared_ptr<basic_event<std::string>>&)>>();
        _subscriptions[key] = value;
        event_type_subscriptions = _subscriptions.find(event_type);
    }
    const event_subscription_key_type event_subscription_key = ++_next_event_subscription_key;
    event_type_subscriptions->second[event_subscription_key] = fire_event_function;
    return event_subscription_key;
}

template<>
inline event_subscription_key_type basic_event_manager<std::wstring>::subscribe(const std::wstring& event_type, std::function<void(const std::shared_ptr<basic_event<std::wstring>>&)>&& fire_event_function)
{
    const std::lock_guard<std::recursive_mutex> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions == _subscriptions.end())
    {
        std::wstring key = event_type;
        auto value = std::map<event_subscription_key_type, std::function<void(const std::shared_ptr<basic_event<std::wstring>>&)>>();
        _subscriptions[key] = value;
        event_type_subscriptions = _subscriptions.find(event_type);
    }
    const event_subscription_key_type event_subscription_key = ++_next_event_subscription_key;
    event_type_subscriptions->second[event_subscription_key] = fire_event_function;
    return event_subscription_key;
}

template<class S>
inline event_subscription_key_type basic_event_manager<S>::subscribe(const S& event_type, std::function<void(const std::shared_ptr<basic_event<S>>&)>&& fire_event_function)
{
    const std::lock_guard<std::recursive_mutex> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions == _subscriptions.end())
    {
        S key = event_type;
        auto value = std::map<event_subscription_key_type, std::function<void(const std::shared_ptr<basic_event<S>>&)>>();
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
    const std::lock_guard<std::recursive_mutex> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(event_subscription_key);
    }
}

template<>
inline void basic_event_manager<std::wstring>::unsubscribe(const std::wstring& event_type, const event_subscription_key_type& event_subscription_key)
{
    const std::lock_guard<std::recursive_mutex> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(event_subscription_key);
    }
}

template<class S>
inline void basic_event_manager<S>::unsubscribe(const S& event_type, const event_subscription_key_type& event_subscription_key)
{
    const std::lock_guard<std::recursive_mutex> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(event_subscription_key);
    }
}

template<>
inline void basic_event_manager<std::string>::unsubscribe_all(const std::string& event_type)
{
    const std::lock_guard<std::recursive_mutex> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<>
inline void basic_event_manager<std::wstring>::unsubscribe_all(const std::wstring& event_type)
{
    const std::lock_guard<std::recursive_mutex> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<class S>
inline void basic_event_manager<S>::unsubscribe_all(const S& event_type)
{
    const std::lock_guard<std::recursive_mutex> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<class S>
inline void basic_event_manager<S>::unsubscribe_all()
{
    const std::lock_guard<std::recursive_mutex> lock(_events_guard);
    _subscriptions.clear();
}

template<>
inline void basic_event_manager<std::string>::fire(const std::shared_ptr<basic_event<std::string>>& e) const
{
    if(e)
    {
        const std::lock_guard<std::recursive_mutex> lock(_events_guard);
        auto event_type_subscriptions = _subscriptions.find(e->event_type());
        if(event_type_subscriptions != _subscriptions.end())
        {
            for(auto& subscription : event_type_subscriptions->second)
            {
                auto f = subscription.second;
                auto s = std::bind(std::forward<std::function<void(const std::shared_ptr<basic_event<std::string>>&)>>(f), e);
                s();
            }
            event_fired(e);
        }
    }
}

template<>
inline void basic_event_manager<std::wstring>::fire(const std::shared_ptr<basic_event<std::wstring>>& e) const
{
    if(e)
    {
        const std::lock_guard<std::recursive_mutex> lock(_events_guard);
        auto event_type_subscriptions = _subscriptions.find(e->event_type());
        if(event_type_subscriptions != _subscriptions.end())
        {
            for(auto& subscription : event_type_subscriptions->second)
            {
                auto f = subscription.second;
                auto s = std::bind(std::forward<std::function<void(const std::shared_ptr<basic_event<std::wstring>>&)>>(f), e);
                s();
            }
            event_fired(e);
        }
    }
}

template<class S>
inline void basic_event_manager<S>::fire(const std::shared_ptr<basic_event<S>>& e) const
{
    if(e)
    {
        const std::lock_guard<std::recursive_mutex> lock(_events_guard);
        auto event_type_subscriptions = _subscriptions.find(e->event_type());
        if(event_type_subscriptions != _subscriptions.end())
        {
            for(auto& subscription : event_type_subscriptions->second)
            {
                auto f = subscription.second;
                auto s = std::bind(std::forward<std::function<void(const std::shared_ptr<basic_event<S>>&)>>(f), e);
                s();
            }
            event_fired(e);
        }
    }
}

template<>
inline void basic_event_manager<std::string>::post(const std::shared_ptr<basic_event<std::string>>& e, const bool keep_event_alive)
{
    if(e)
    {
        const std::lock_guard<std::recursive_mutex> lock(_events_guard);
        _events.push_back(std::pair<std::weak_ptr<basic_event<std::string>>, std::shared_ptr<basic_event<std::string>>>(std::weak_ptr<basic_event<std::string>>(e), keep_event_alive ? e : nullptr));
    }
}

template<>
inline void basic_event_manager<std::wstring>::post(const std::shared_ptr<basic_event<std::wstring>>& e, const bool keep_event_alive)
{
    if(e)
    {
        const std::lock_guard<std::recursive_mutex> lock(_events_guard);
        _events.push_back(std::pair<std::weak_ptr<basic_event<std::wstring>>, std::shared_ptr<basic_event<std::wstring>>>(std::weak_ptr<basic_event<std::wstring>>(e), keep_event_alive ? e : nullptr));
    }
}

template<class S>
inline void basic_event_manager<S>::post(const std::shared_ptr<basic_event<S>>& e, const bool keep_event_alive)
{
    if(e)
    {
        const std::lock_guard<std::recursive_mutex> lock(_events_guard);
        _events.push_back(std::pair<std::weak_ptr<basic_event<S>>, std::shared_ptr<basic_event<S>>>(std::weak_ptr<basic_event<S>>(e), keep_event_alive ? e : nullptr));
    }
}

template<>
inline void basic_event_manager<std::string>::fire_events()
{
    std::list<std::pair<std::weak_ptr<basic_event<std::string>>, std::shared_ptr<basic_event<std::string>>>> events;
    {
        const std::lock_guard<std::recursive_mutex> lock(_events_guard);
        std::swap(events, _events);
    }
    for(const auto& e : events)
    {
        fire(e.first.lock());
    }
}

template<>
inline void basic_event_manager<std::wstring>::fire_events()
{
    std::list<std::pair<std::weak_ptr<basic_event<std::wstring>>, std::shared_ptr<basic_event<std::wstring>>>> events;
    {
        const std::lock_guard<std::recursive_mutex> lock(_events_guard);
        std::swap(events, _events);
    }
    for(const auto& e : events)
    {
        fire(e.first.lock());
    }
}

template<class S>
inline void basic_event_manager<S>::fire_events()
{
    std::list<std::pair<std::weak_ptr<basic_event<S>>, std::shared_ptr<basic_event<S>>>> events;
    {
        const std::lock_guard<std::recursive_mutex> lock(_events_guard);
        std::swap(events, _events);
    }
    for(const auto& e : events)
    {
        fire(e.first.lock());
    }
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_EVENT_MANAGER_HPP_INCLUDED
