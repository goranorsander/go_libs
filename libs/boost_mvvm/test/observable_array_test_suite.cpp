//
//  observable_array_test_suite.cpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <gtest/gtest.h>

#include <boost/foreach.hpp>

#include <go_boost/mvvm.hpp>
#include <go_boost/property.hpp>

namespace m = go_boost::mvvm;
namespace p = go_boost::property;
namespace s = go_boost::signals;

namespace
{

template<class T, size_t N> class array_observer
{
public:
    typedef typename m::observable_array<T, N>::ptr observable_array_ptr_type;

    virtual ~array_observer()
    {
    }

    array_observer()
        : _last_action(m::undefined_notify_container_changed_action)
        , _last_change_added(0)
        , _last_change_removed(0)
        , _last_change_new_size(0)
        , _total_change_added(0)
        , _total_change_removed(0)
        , _action_add_count(0)
        , _action_remove_count(0)
        , _action_reset_count(0)
        , _action_swap_count(0)
    {
    }

    void connect(observable_array_ptr_type& c)
    {
        c->container_changed.connect(boost::bind(&array_observer::on_container_changed, this, _1, _2));
        c->property_changed.connect(boost::bind(&array_observer::on_property_changed, this, _1, _2));
    }

    void disconnect(observable_array_ptr_type& c)
    {
        c->container_changed.disconnect(boost::bind(&array_observer::on_container_changed, this, _1, _2));
        c->property_changed.disconnect(boost::bind(&array_observer::on_property_changed, this, _1, _2));
    }

    void on_container_changed(const m::object::ptr& o, const m::container_changed_arguments::ptr& a)
    {
        if(o && a)
        {
            _last_action = a->action();
            _last_change_added = static_cast<int>(a->added_elements());
            _last_change_removed = static_cast<int>(a->removed_elements());
            _last_change_new_size = static_cast<int>(a->new_size());
            _total_change_added += static_cast<int>(a->added_elements());
            _total_change_removed += static_cast<int>(a->removed_elements());
            _action_add_count += a->action() == m::notify_container_changed_action_add ? 1 : 0;
            _action_remove_count += a->action() == m::notify_container_changed_action_remove ? 1 : 0;
            _action_reset_count += a->action() == m::notify_container_changed_action_reset ? 1 : 0;
            _action_swap_count += a->action() == m::notify_container_changed_action_swap ? 1 : 0;
        }
    }

    void on_property_changed(const m::object::ptr& o, const m::property_changed_arguments::ptr& a)
    {
        if(o && a)
        {
        }
    }

    m::notify_container_changed_action last_action() const
    {
        return _last_action;
    }

    int last_change_added() const
    {
        return _last_change_added;
    }

    int last_change_removed() const
    {
        return _last_change_removed;
    }

    int last_change_new_size() const
    {
        return _last_change_new_size;
    }

    int total_change_added() const
    {
        return _total_change_added;
    }

    int total_change_removed() const
    {
        return _total_change_removed;
    }

    int action_add_count() const
    {
        return _action_add_count;
    }

    int action_remove_count() const
    {
        return _action_remove_count;
    }

    int action_reset_count() const
    {
        return _action_reset_count;
    }

    int action_swap_count() const
    {
        return _action_swap_count;
    }

private:
    m::notify_container_changed_action _last_action;
    int _last_change_added;
    int _last_change_removed;
    int _last_change_new_size;

    int _total_change_added;
    int _total_change_removed;

    int _action_add_count;
    int _action_remove_count;
    int _action_reset_count;
    int _action_swap_count;
};

TEST(boost_observable_array_test_suite, test_create)
{
    m::observable_array<int, 7>::ptr a = m::observable_array<int, 7>::create();
    array_observer<int, 7> o;
    o.connect(a);

    EXPECT_EQ(7, a->size());
    EXPECT_EQ(7, a->max_size());

    for(int i = 0; i < 7; i++)
    {
        (*a)[i] = i;
    }

    for(int i = 0; i < 7; i++)
    {
        EXPECT_EQ((*a)[i], i);
    }

    int count = 0;
    BOOST_FOREACH(const int& i, *a)
    {
        EXPECT_EQ(count, i);
        ++count;
    }
    EXPECT_EQ(7, count);

    EXPECT_EQ(m::undefined_notify_container_changed_action, o.last_action());
    EXPECT_EQ(0, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(0, o.last_change_new_size());
    EXPECT_EQ(0, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(0, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

}
