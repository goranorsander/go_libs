#ifndef GO_MVVM_TEST_CONTAINER_OBSERVER_IPP_INCLUDED
#define GO_MVVM_TEST_CONTAINER_OBSERVER_IPP_INCLUDED

//
//  test_container_observer.ipp
//
//  Copyright 2020-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <go/mvvm/notify_container_changed_action.hpp>
#include <go/namespace_alias.hpp>
#include <go/property.hpp>
#include <go/signals/connections.hpp>

namespace go_test
{

template<class C, class S, class L = std::recursive_mutex>
class container_observer
{
public:
    typedef container_observer<C, S, L> this_type;
    typedef C container_type;
    typedef S string_type;
    typedef L lockable_type;
    typedef typename container_type::ptr container_ptr;
    typedef typename m::container_changed_arguments container_changed_arguments_type;
    typedef typename container_changed_arguments_type::ptr container_changed_arguments_ptr;
    typedef typename m::basic_property_changed_arguments<string_type> property_changed_arguments_type;
    typedef typename property_changed_arguments_type::ptr property_changed_arguments_ptr;

    virtual ~container_observer() GO_DEFAULT_DESTRUCTOR

    container_observer()
        : _container_changed_connections()
        , _property_changed_connections()
        , _last_action(m::notify_container_changed_action::undefined)
        , _last_change_added(0u)
        , _last_change_removed(0u)
        , _last_change_new_size(0u)
        , _total_change_added(0u)
        , _total_change_removed(0u)
        , _action_add_count(0u)
        , _action_remove_count(0u)
        , _action_reset_count(0u)
        , _action_swap_count(0u)
    {
    }

    void connect(container_ptr& c)
    {
        if (c)
        {
            _container_changed_connections.connect(c, c->container_changed, std::bind(&this_type::on_container_changed, this, std::placeholders::_1, std::placeholders::_2));
            _property_changed_connections.connect(c, c->property_changed, std::bind(&this_type::on_property_changed, this, std::placeholders::_1, std::placeholders::_2));
        }
    }

    void disconnect(container_ptr& c)
    {
        if (c)
        {
            _container_changed_connections.disconnect(c, c->container_changed);
            _property_changed_connections.disconnect(c, c->property_changed);
        }
    }

    void on_container_changed(const m::object::ptr& o, const container_changed_arguments_ptr& a)
    {
        if(o && a)
        {
            _last_action = a->action();
            _last_change_added = static_cast<int>(a->added_elements());
            _last_change_removed = static_cast<int>(a->removed_elements());
            _last_change_new_size = static_cast<int>(a->new_size());
            _total_change_added += static_cast<int>(a->added_elements());
            _total_change_removed += static_cast<int>(a->removed_elements());
            _action_add_count += a->action() == m::notify_container_changed_action::add ? 1 : 0;
            _action_remove_count += a->action() == m::notify_container_changed_action::remove ? 1 : 0;
            _action_reset_count += a->action() == m::notify_container_changed_action::reset ? 1 : 0;
            _action_swap_count += a->action() == m::notify_container_changed_action::swap ? 1 : 0;
        }
    }

    void on_property_changed(const m::object::ptr& o, const property_changed_arguments_ptr& a)
    {
        if(o && a)
        {
        }
    }

    GO_CONSTEXPR m::notify_container_changed_action last_action() const
    {
        return _last_action;
    }

    GO_CONSTEXPR unsigned int last_change_added() const
    {
        return _last_change_added;
    }

    GO_CONSTEXPR unsigned int last_change_removed() const
    {
        return _last_change_removed;
    }

    GO_CONSTEXPR unsigned int last_change_new_size() const
    {
        return _last_change_new_size;
    }

    GO_CONSTEXPR unsigned int total_change_added() const
    {
        return _total_change_added;
    }

    GO_CONSTEXPR unsigned int total_change_removed() const
    {
        return _total_change_removed;
    }

    GO_CONSTEXPR unsigned int action_add_count() const
    {
        return _action_add_count;
    }

    GO_CONSTEXPR unsigned int action_remove_count() const
    {
        return _action_remove_count;
    }

    GO_CONSTEXPR unsigned int action_reset_count() const
    {
        return _action_reset_count;
    }

    GO_CONSTEXPR unsigned int action_swap_count() const
    {
        return _action_swap_count;
    }

private:
    typedef si::connections<container_ptr, void(const m::object::ptr&, const container_changed_arguments_ptr&)> container_changed_connections_type;
    typedef si::connections<container_ptr, void(const m::object::ptr&, const property_changed_arguments_ptr&)> property_changed_connections_type;

    container_changed_connections_type _container_changed_connections;
    property_changed_connections_type _property_changed_connections;

    m::notify_container_changed_action _last_action;
    unsigned int _last_change_added;
    unsigned int _last_change_removed;
    unsigned int _last_change_new_size;

    unsigned int _total_change_added;
    unsigned int _total_change_removed;

    unsigned int _action_add_count;
    unsigned int _action_remove_count;
    unsigned int _action_reset_count;
    unsigned int _action_swap_count;
};

}

#endif  // #ifndef GO_MVVM_TEST_CONTAINER_OBSERVER_IPP_INCLUDED
