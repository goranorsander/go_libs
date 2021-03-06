#ifndef GO_MVVM_EVENT_MANAGER_HPP_INCLUDED
#define GO_MVVM_EVENT_MANAGER_HPP_INCLUDED

//
//  event_manager.hpp
//
//  Copyright 2016-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <deque>
#include <functional>
#include <map>
#include <mutex>
#include <go/async/placebo_lockable.hpp>
#include <go/mvvm/event_subscription_key.hpp>
#include <go/mvvm/notify_event_firing_interface.hpp>

namespace go
{
namespace mvvm
{

template<class S, class L> class basic_event_manager;
typedef basic_event_manager<std::string, std::recursive_mutex> event_manager;
typedef basic_event_manager<std::wstring, std::recursive_mutex> wevent_manager;

namespace single_threaded
{

typedef basic_event_manager<std::string, go::async::placebo_lockable> event_manager;
typedef basic_event_manager<std::wstring, go::async::placebo_lockable> wevent_manager;

}

template<class S, class L = std::recursive_mutex>
class basic_event_manager
    : public basic_notify_event_firing_interface<S, L>
    , public go::type_traits::noncopyable_nonmovable
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_event_manager<S, L> this_type;
    typedef typename std::shared_ptr<basic_event_manager<S, L>> ptr;
    typedef typename std::weak_ptr<basic_event_manager<S, L>> wptr;
    typedef typename std::shared_ptr<basic_event<S>> basic_event_ptr;
    typedef typename std::function<void(const std::shared_ptr<basic_event<S>>&)> basic_event_function_type;

public:
    virtual ~basic_event_manager();

protected:
    basic_event_manager();

public:
    static ptr create();

    event_subscription_key subscribe(const S& event_type, basic_event_function_type&& fire_event_function);
    void unsubscribe(const S& event_type, const event_subscription_key& key);
    void unsubscribe_all(const S& event_type);
    void unsubscribe_all();

    void fire(const std::shared_ptr<basic_event<S>>& e) const;
    void post(const std::shared_ptr<basic_event<S>>& e, const bool keep_event_alive = true);
    void fire_events();

    size_t events() const;

private:
    mutable lockable_type _events_guard;
    event_subscription_key _next_event_subscription_key;
    std::map<S, std::map<event_subscription_key, basic_event_function_type>> _subscriptions;
    std::deque<std::pair<std::weak_ptr<basic_event<S>>, std::shared_ptr<basic_event<S>>>> _events;
};

template<class S, class L>
inline basic_event_manager<S, L>::~basic_event_manager()
{
    unsubscribe_all();
}

template<class S, class L>
inline basic_event_manager<S, L>::basic_event_manager()
    : basic_notify_event_firing_interface<S, L>()
    , go::type_traits::noncopyable_nonmovable()
    , _events_guard()
    , _next_event_subscription_key(0)
    , _subscriptions()
    , _events()
{
}

template<>
inline event_subscription_key basic_event_manager<std::string, std::recursive_mutex>::subscribe(const std::string& event_type, std::function<void(const std::shared_ptr<basic_event<std::string>>&)>&& fire_event_function)
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions == _subscriptions.end())
    {
        std::string key = event_type;
        auto value = std::map<event_subscription_key, std::function<void(const std::shared_ptr<basic_event<std::string>>&)>>();
        _subscriptions[key] = value;
        event_type_subscriptions = _subscriptions.find(event_type);
    }
    const event_subscription_key key = ++_next_event_subscription_key;
    event_type_subscriptions->second[key] = fire_event_function;
    return key;
}

template<>
inline event_subscription_key basic_event_manager<std::wstring, std::recursive_mutex>::subscribe(const std::wstring& event_type, std::function<void(const std::shared_ptr<basic_event<std::wstring>>&)>&& fire_event_function)
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions == _subscriptions.end())
    {
        std::wstring key = event_type;
        auto value = std::map<event_subscription_key, std::function<void(const std::shared_ptr<basic_event<std::wstring>>&)>>();
        _subscriptions[key] = value;
        event_type_subscriptions = _subscriptions.find(event_type);
    }
    const event_subscription_key key = ++_next_event_subscription_key;
    event_type_subscriptions->second[key] = fire_event_function;
    return key;
}

template<>
inline event_subscription_key basic_event_manager<std::string, go::async::placebo_lockable>::subscribe(const std::string& event_type, std::function<void(const std::shared_ptr<basic_event<std::string>>&)>&& fire_event_function)
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions == _subscriptions.end())
    {
        std::string key = event_type;
        auto value = std::map<event_subscription_key, std::function<void(const std::shared_ptr<basic_event<std::string>>&)>>();
        _subscriptions[key] = value;
        event_type_subscriptions = _subscriptions.find(event_type);
    }
    const event_subscription_key key = ++_next_event_subscription_key;
    event_type_subscriptions->second[key] = fire_event_function;
    return key;
}

template<>
inline event_subscription_key basic_event_manager<std::wstring, go::async::placebo_lockable>::subscribe(const std::wstring& event_type, std::function<void(const std::shared_ptr<basic_event<std::wstring>>&)>&& fire_event_function)
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions == _subscriptions.end())
    {
        std::wstring key = event_type;
        auto value = std::map<event_subscription_key, std::function<void(const std::shared_ptr<basic_event<std::wstring>>&)>>();
        _subscriptions[key] = value;
        event_type_subscriptions = _subscriptions.find(event_type);
    }
    const event_subscription_key key = ++_next_event_subscription_key;
    event_type_subscriptions->second[key] = fire_event_function;
    return key;
}

template<class S, class L>
inline event_subscription_key basic_event_manager<S, L>::subscribe(const S& event_type, basic_event_function_type&& fire_event_function)
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions == _subscriptions.end())
    {
        S key = event_type;
        auto value = std::map<event_subscription_key, basic_event_function_type>();
        _subscriptions[key] = value;
        event_type_subscriptions = _subscriptions.find(event_type);
    }
    const event_subscription_key key = ++_next_event_subscription_key;
    event_type_subscriptions->second[key] = fire_event_function;
    return key;
}

template<>
inline void basic_event_manager<std::string, std::recursive_mutex>::unsubscribe(const std::string& event_type, const event_subscription_key& key)
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(key);
    }
}

template<>
inline void basic_event_manager<std::wstring, std::recursive_mutex>::unsubscribe(const std::wstring& event_type, const event_subscription_key& key)
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(key);
    }
}

template<>
inline void basic_event_manager<std::string, go::async::placebo_lockable>::unsubscribe(const std::string& event_type, const event_subscription_key& key)
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(key);
    }
}

template<>
inline void basic_event_manager<std::wstring, go::async::placebo_lockable>::unsubscribe(const std::wstring& event_type, const event_subscription_key& key)
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(key);
    }
}

template<class S, class L>
inline void basic_event_manager<S, L>::unsubscribe(const S& event_type, const event_subscription_key& key)
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        event_type_subscriptions->second.erase(key);
    }
}

template<>
inline void basic_event_manager<std::string, std::recursive_mutex>::unsubscribe_all(const std::string& event_type)
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<>
inline void basic_event_manager<std::wstring, std::recursive_mutex>::unsubscribe_all(const std::wstring& event_type)
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<>
inline void basic_event_manager<std::string, go::async::placebo_lockable>::unsubscribe_all(const std::string& event_type)
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<>
inline void basic_event_manager<std::wstring, go::async::placebo_lockable>::unsubscribe_all(const std::wstring& event_type)
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if (event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<class S, class L>
inline void basic_event_manager<S, L>::unsubscribe_all(const S& event_type)
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    auto event_type_subscriptions = _subscriptions.find(event_type);
    if(event_type_subscriptions != _subscriptions.end())
    {
        _subscriptions.erase(event_type_subscriptions);
    }
}

template<class S, class L>
inline void basic_event_manager<S, L>::unsubscribe_all()
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    _subscriptions.clear();
}

template<>
inline void basic_event_manager<std::string, std::recursive_mutex>::fire(const std::shared_ptr<basic_event<std::string>>& e) const
{
    if(e)
    {
        const std::lock_guard<lockable_type> lock(_events_guard);
        auto event_type_subscriptions = _subscriptions.find(e->event_type());
        if(event_type_subscriptions != _subscriptions.end())
        {
            for(auto& subscription : event_type_subscriptions->second)
            {
                auto f = subscription.second;
                auto s = std::bind(std::forward<std::function<void(const std::shared_ptr<basic_event<std::string>>&)>>(f), e);
                s();
            }
            this->event_fired(e);
        }
    }
}

template<>
inline void basic_event_manager<std::wstring, std::recursive_mutex>::fire(const std::shared_ptr<basic_event<std::wstring>>& e) const
{
    if(e)
    {
        const std::lock_guard<lockable_type> lock(_events_guard);
        auto event_type_subscriptions = _subscriptions.find(e->event_type());
        if(event_type_subscriptions != _subscriptions.end())
        {
            for(auto& subscription : event_type_subscriptions->second)
            {
                auto f = subscription.second;
                auto s = std::bind(std::forward<std::function<void(const std::shared_ptr<basic_event<std::wstring>>&)>>(f), e);
                s();
            }
            this->event_fired(e);
        }
    }
}

template<>
inline void basic_event_manager<std::string, go::async::placebo_lockable>::fire(const std::shared_ptr<basic_event<std::string>>& e) const
{
    if (e)
    {
        const std::lock_guard<lockable_type> lock(_events_guard);
        auto event_type_subscriptions = _subscriptions.find(e->event_type());
        if (event_type_subscriptions != _subscriptions.end())
        {
            for (auto& subscription : event_type_subscriptions->second)
            {
                auto f = subscription.second;
                auto s = std::bind(std::forward<std::function<void(const std::shared_ptr<basic_event<std::string>>&)>>(f), e);
                s();
            }
            this->event_fired(e);
        }
    }
}

template<>
inline void basic_event_manager<std::wstring, go::async::placebo_lockable>::fire(const std::shared_ptr<basic_event<std::wstring>>& e) const
{
    if (e)
    {
        const std::lock_guard<lockable_type> lock(_events_guard);
        auto event_type_subscriptions = _subscriptions.find(e->event_type());
        if (event_type_subscriptions != _subscriptions.end())
        {
            for (auto& subscription : event_type_subscriptions->second)
            {
                auto f = subscription.second;
                auto s = std::bind(std::forward<std::function<void(const std::shared_ptr<basic_event<std::wstring>>&)>>(f), e);
                s();
            }
            this->event_fired(e);
        }
    }
}

template<class S, class L>
inline void basic_event_manager<S, L>::fire(const std::shared_ptr<basic_event<S>>& e) const
{
    if(e)
    {
        const std::lock_guard<lockable_type> lock(_events_guard);
        auto event_type_subscriptions = _subscriptions.find(e->event_type());
        if(event_type_subscriptions != _subscriptions.end())
        {
            for(auto& subscription : event_type_subscriptions->second)
            {
                auto f = subscription.second;
                auto s = std::bind(std::forward<basic_event_function_type>(f), e);
                s();
            }
            this->event_fired(e);
        }
    }
}

template<>
inline void basic_event_manager<std::string, std::recursive_mutex>::post(const std::shared_ptr<basic_event<std::string>>& e, const bool keep_event_alive)
{
    if(e)
    {
        const std::lock_guard<lockable_type> lock(_events_guard);
        _events.push_back(std::pair<std::weak_ptr<basic_event<std::string>>, std::shared_ptr<basic_event<std::string>>>(std::weak_ptr<basic_event<std::string>>(e), keep_event_alive ? e : nullptr));
    }
}

template<>
inline void basic_event_manager<std::wstring, std::recursive_mutex>::post(const std::shared_ptr<basic_event<std::wstring>>& e, const bool keep_event_alive)
{
    if(e)
    {
        const std::lock_guard<lockable_type> lock(_events_guard);
        _events.push_back(std::pair<std::weak_ptr<basic_event<std::wstring>>, std::shared_ptr<basic_event<std::wstring>>>(std::weak_ptr<basic_event<std::wstring>>(e), keep_event_alive ? e : nullptr));
    }
}

template<>
inline void basic_event_manager<std::string, go::async::placebo_lockable>::post(const std::shared_ptr<basic_event<std::string>>& e, const bool keep_event_alive)
{
    if (e)
    {
        const std::lock_guard<lockable_type> lock(_events_guard);
        _events.push_back(std::pair<std::weak_ptr<basic_event<std::string>>, std::shared_ptr<basic_event<std::string>>>(std::weak_ptr<basic_event<std::string>>(e), keep_event_alive ? e : nullptr));
    }
}

template<>
inline void basic_event_manager<std::wstring, go::async::placebo_lockable>::post(const std::shared_ptr<basic_event<std::wstring>>& e, const bool keep_event_alive)
{
    if (e)
    {
        const std::lock_guard<lockable_type> lock(_events_guard);
        _events.push_back(std::pair<std::weak_ptr<basic_event<std::wstring>>, std::shared_ptr<basic_event<std::wstring>>>(std::weak_ptr<basic_event<std::wstring>>(e), keep_event_alive ? e : nullptr));
    }
}

template<class S, class L>
inline void basic_event_manager<S, L>::post(const std::shared_ptr<basic_event<S>>& e, const bool keep_event_alive)
{
    if(e)
    {
        const std::lock_guard<lockable_type> lock(_events_guard);
        _events.push_back(std::pair<std::weak_ptr<basic_event<S>>, std::shared_ptr<basic_event<S>>>(std::weak_ptr<basic_event<S>>(e), keep_event_alive ? e : nullptr));
    }
}

template<>
inline void basic_event_manager<std::string, std::recursive_mutex>::fire_events()
{
    std::deque<std::pair<std::weak_ptr<basic_event<std::string>>, std::shared_ptr<basic_event<std::string>>>> events;
    {
        const std::lock_guard<lockable_type> lock(_events_guard);
        std::swap(events, _events);
    }
    for(const auto& e : events)
    {
        fire(e.first.lock());
    }
}

template<>
inline void basic_event_manager<std::wstring, std::recursive_mutex>::fire_events()
{
    std::deque<std::pair<std::weak_ptr<basic_event<std::wstring>>, std::shared_ptr<basic_event<std::wstring>>>> events;
    {
        const std::lock_guard<lockable_type> lock(_events_guard);
        std::swap(events, _events);
    }
    for(const auto& e : events)
    {
        fire(e.first.lock());
    }
}

template<>
inline void basic_event_manager<std::string, go::async::placebo_lockable>::fire_events()
{
    std::deque<std::pair<std::weak_ptr<basic_event<std::string>>, std::shared_ptr<basic_event<std::string>>>> events;
    {
        const std::lock_guard<lockable_type> lock(_events_guard);
        std::swap(events, _events);
    }
    for (const auto& e : events)
    {
        fire(e.first.lock());
    }
}

template<>
inline void basic_event_manager<std::wstring, go::async::placebo_lockable>::fire_events()
{
    std::deque<std::pair<std::weak_ptr<basic_event<std::wstring>>, std::shared_ptr<basic_event<std::wstring>>>> events;
    {
        const std::lock_guard<lockable_type> lock(_events_guard);
        std::swap(events, _events);
    }
    for (const auto& e : events)
    {
        fire(e.first.lock());
    }
}

template<class S, class L>
inline void basic_event_manager<S, L>::fire_events()
{
    std::deque<std::pair<std::weak_ptr<basic_event<S>>, std::shared_ptr<basic_event<S>>>> events;
    {
        const std::lock_guard<lockable_type> lock(_events_guard);
        std::swap(events, _events);
    }
    for(const auto& e : events)
    {
        fire(e.first.lock());
    }
}

template<>
inline size_t basic_event_manager<std::string, std::recursive_mutex>::events() const
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    return _events.size();
}

template<>
inline size_t basic_event_manager<std::wstring, std::recursive_mutex>::events() const
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    return _events.size();
}

template<>
inline size_t basic_event_manager<std::string, go::async::placebo_lockable>::events() const
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    return _events.size();
}

template<>
inline size_t basic_event_manager<std::wstring, go::async::placebo_lockable>::events() const
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    return _events.size();
}

template<class S, class L>
inline size_t basic_event_manager<S, L>::events() const
{
    const std::lock_guard<lockable_type> lock(_events_guard);
    return _events.size();
}

template<class S, class L>
inline std::shared_ptr<basic_event_manager<S, L>> basic_event_manager<S, L>::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
    };

    return std::make_shared<make_shared_enabler>();
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_EVENT_MANAGER_HPP_INCLUDED
