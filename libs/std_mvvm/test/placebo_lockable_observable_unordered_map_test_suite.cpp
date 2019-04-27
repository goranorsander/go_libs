//
//  placebo_lockable_observable_unordered_map_test_suite.cpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <gtest/gtest.h>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_NOEXCEPT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_observable_unordered_map_placebo_lockable_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>

namespace i = go::mvvm::iterator;
namespace m = go::mvvm;
namespace mst = go::mvvm::single_threaded;
namespace ph = std::placeholders;
namespace s = go::signals;
namespace u = go::utility;

namespace
{

template<class K, class T> class unordered_map_observer
{
public:
    typedef unordered_map_observer<K, T> this_type;
    typedef typename m::observable_unordered_map<K, T, u::placebo_lockable>::ptr observable_unordered_map_ptr_type;

    virtual ~unordered_map_observer() GO_DEFAULT_DESTRUCTOR

    unordered_map_observer()
        : _on_container_changed_slot_key()
        , _on_property_changed_slot_key()
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

    void connect(observable_unordered_map_ptr_type& c)
    {
        _on_container_changed_slot_key = c->container_changed.connect(std::bind(&this_type::on_container_changed, this, ph::_1, ph::_2));
        _on_property_changed_slot_key = c->property_changed.connect(std::bind(&this_type::on_property_changed, this, ph::_1, ph::_2));
    }

    void disconnect(observable_unordered_map_ptr_type& c)
    {
        c->container_changed.disconnect(_on_container_changed_slot_key);
        c->property_changed.disconnect(_on_property_changed_slot_key);
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
            _action_add_count += a->action() == m::notify_container_changed_action::add ? 1 : 0;
            _action_remove_count += a->action() == m::notify_container_changed_action::remove ? 1 : 0;
            _action_reset_count += a->action() == m::notify_container_changed_action::reset ? 1 : 0;
            _action_swap_count += a->action() == m::notify_container_changed_action::swap ? 1 : 0;
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

    unsigned int last_change_added() const
    {
        return _last_change_added;
    }

    unsigned int last_change_removed() const
    {
        return _last_change_removed;
    }

    unsigned int last_change_new_size() const
    {
        return _last_change_new_size;
    }

    unsigned int total_change_added() const
    {
        return _total_change_added;
    }

    unsigned int total_change_removed() const
    {
        return _total_change_removed;
    }

    unsigned int action_add_count() const
    {
        return _action_add_count;
    }

    unsigned int action_remove_count() const
    {
        return _action_remove_count;
    }

    unsigned int action_reset_count() const
    {
        return _action_reset_count;
    }

    unsigned int action_swap_count() const
    {
        return _action_swap_count;
    }

private:
    s::slot_key _on_container_changed_slot_key;
    s::slot_key _on_property_changed_slot_key;

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

TEST(std_observable_unordered_map_placebo_lockable_test_suite, test_insert_single_element)
{
    // Test insert single element
    m::observable_unordered_map<int, int, u::placebo_lockable>::ptr m = m::observable_unordered_map<int, int, u::placebo_lockable>::create();
    unordered_map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());
    const std::initializer_list<m::observable_unordered_map<int, int, u::placebo_lockable>::value_type> il =
    {
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(1, 10),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(2, 20),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(4, 40),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(5, 50),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(6, 60),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(6u, m->size());

    o.connect(m);

    m->insert(m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(3, 30));
    EXPECT_EQ(7u, m->size());

    unsigned int count = 0u;
    int sum = 0;
    for(const m::observable_unordered_map<int, int, u::placebo_lockable>::value_type& i : *m)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(280, sum);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
    EXPECT_EQ(1u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(7u, o.last_change_new_size());
    EXPECT_EQ(1u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(1u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

TEST(std_observable_unordered_map_placebo_lockable_test_suite, test_insert_single_element_with_hint)
{
    // Test insert single element with hint
    m::observable_unordered_map<int, int, u::placebo_lockable>::ptr m = m::observable_unordered_map<int, int, u::placebo_lockable>::create();
    unordered_map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());
    const std::initializer_list<m::observable_unordered_map<int, int, u::placebo_lockable>::value_type> il =
    {
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(1, 10),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(2, 20),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(5, 50),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(4u, m->size());

    o.connect(m);

    m::observable_unordered_map<int, int, u::placebo_lockable>::iterator it = m->insert(m->begin(), m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(3, 30));
    EXPECT_EQ(5u, m->size());

    it = m->insert(it, m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(4, 40));
    EXPECT_EQ(6u, m->size());

    it = m->insert(it, m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(4, 40));
    EXPECT_EQ(6u, m->size());

    it = m->insert(it, m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(6, 60));
    EXPECT_EQ(7u, m->size());

    unsigned int count = 0u;
    int sum = 0;
    for(const m::observable_unordered_map<int, int, u::placebo_lockable>::value_type& i : *m)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(280, sum);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
    EXPECT_EQ(3u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(7u, o.last_change_new_size());
    EXPECT_EQ(1u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(3u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

TEST(std_observable_unordered_map_placebo_lockable_test_suite, test_insert_range)
{
    // Test insert range
    m::observable_unordered_map<int, int, u::placebo_lockable>::ptr m1 = m::observable_unordered_map<int, int, u::placebo_lockable>::create();
    m::observable_unordered_map<int, int, u::placebo_lockable>::ptr m2 = m::observable_unordered_map<int, int, u::placebo_lockable>::create();
    unordered_map_observer<int, int> o;

    EXPECT_EQ(0u, m1->size());
    EXPECT_EQ(0u, m2->size());

    const std::initializer_list<m::observable_unordered_map<int, int, u::placebo_lockable>::value_type> il1 =
    {
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(1, 10),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(2, 20),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(5, 50),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(7, 70)
    };
    *m1 = il1;
    EXPECT_EQ(4u, m1->size());

    const std::initializer_list<m::observable_unordered_map<int, int, u::placebo_lockable>::value_type> il2 =
    {
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(3, 30),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(4, 40),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(6, 60)
    };
    *m2 = il2;
    EXPECT_EQ(3u, m2->size());

    o.connect(m2);

    m2->insert(m1->begin(), m1->end());
    EXPECT_EQ(7u, m2->size());

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
    EXPECT_EQ(1u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(7u, o.last_change_new_size());
    EXPECT_EQ(4u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(4u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

TEST(std_observable_unordered_map_placebo_lockable_test_suite, test_insert_initializer_list)
{
    // Test insert initializer list
    m::observable_unordered_map<int, int, u::placebo_lockable>::ptr m = m::observable_unordered_map<int, int, u::placebo_lockable>::create();
    unordered_map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::observable_unordered_map<int, int, u::placebo_lockable>::value_type> il1 =
    {
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(1, 10),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(2, 20),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(5, 50),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(7, 70)
    };
    *m = il1;
    EXPECT_EQ(4u, m->size());

    const std::initializer_list<m::observable_unordered_map<int, int, u::placebo_lockable>::value_type> il2 =
    {
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(3, 30),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(4, 40),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(6, 60)
    };
    EXPECT_EQ(3u, il2.size());

    o.connect(m);

    m->insert(il2);
    EXPECT_EQ(7u, m->size());

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
    EXPECT_EQ(1u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(7u, o.last_change_new_size());
    EXPECT_EQ(3u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(3u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

TEST(std_observable_unordered_map_placebo_lockable_test_suite, test_erase_position)
{
    // Test erase position
    m::observable_unordered_map<int, int, u::placebo_lockable>::ptr m = m::observable_unordered_map<int, int, u::placebo_lockable>::create();
    unordered_map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::observable_unordered_map<int, int, u::placebo_lockable>::value_type> il =
    {
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(1, 10),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(2, 20),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(3, 30),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(4, 40),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(5, 50),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(6, 60),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m::observable_unordered_map<int, int, u::placebo_lockable>::iterator it1 = m->begin();
    std::advance(it1, 3);
    m::observable_unordered_map<int, int, u::placebo_lockable>::iterator it2 = m->erase(it1);
    EXPECT_EQ(6u, m->size());

    m->erase(it2);
    EXPECT_EQ(5u, m->size());

    EXPECT_EQ(m::notify_container_changed_action::remove, o.last_action());
    EXPECT_EQ(0u, o.action_add_count());
    EXPECT_EQ(2u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(5u, o.last_change_new_size());
    EXPECT_EQ(0u, o.last_change_added());
    EXPECT_EQ(1u, o.last_change_removed());
    EXPECT_EQ(0u, o.total_change_added());
    EXPECT_EQ(2u, o.total_change_removed());
}

TEST(std_observable_unordered_map_placebo_lockable_test_suite, test_erase_value)
{
    // Test erase value
    m::observable_unordered_map<int, int, u::placebo_lockable>::ptr m = m::observable_unordered_map<int, int, u::placebo_lockable>::create();
    unordered_map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::observable_unordered_map<int, int, u::placebo_lockable>::value_type> il =
    {
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(1, 10),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(2, 20),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(3, 30),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(4, 40),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(5, 50),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(6, 60),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m->erase(4);
    EXPECT_EQ(6u, m->size());

    m->erase(5);
    EXPECT_EQ(5u, m->size());

    unsigned int count = 0u;
    int sum = 0;
    for(const m::observable_unordered_map<int, int, u::placebo_lockable>::value_type& i : *m)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(5u, count);
    EXPECT_EQ(190, sum);

    EXPECT_EQ(m::notify_container_changed_action::remove, o.last_action());
    EXPECT_EQ(0u, o.action_add_count());
    EXPECT_EQ(2u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(5u, o.last_change_new_size());
    EXPECT_EQ(0u, o.last_change_added());
    EXPECT_EQ(1u, o.last_change_removed());
    EXPECT_EQ(0u, o.total_change_added());
    EXPECT_EQ(2u, o.total_change_removed());
}

TEST(std_observable_unordered_map_placebo_lockable_test_suite, test_erase_range)
{
    // Test erase range
    m::observable_unordered_map<int, int, u::placebo_lockable>::ptr m = m::observable_unordered_map<int, int, u::placebo_lockable>::create();
    unordered_map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::observable_unordered_map<int, int, u::placebo_lockable>::value_type> il =
    {
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(1, 10),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(2, 20),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(3, 30),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(4, 40),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(5, 50),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(6, 60),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m::observable_unordered_map<int, int, u::placebo_lockable>::iterator begin = m->begin();
    ++begin;
    m::observable_unordered_map<int, int, u::placebo_lockable>::iterator end = m->end();
    const bool moved_backward = i::try_move_backward<m::observable_unordered_map<int, int, u::placebo_lockable>::iterator>(m, end);
    EXPECT_EQ(moved_backward, true);

    m->erase(begin, end);
    EXPECT_EQ(2u, m->size());

    EXPECT_EQ(m::notify_container_changed_action::remove, o.last_action());
    EXPECT_EQ(0u, o.action_add_count());
    EXPECT_EQ(1u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(2u, o.last_change_new_size());
    EXPECT_EQ(0u, o.last_change_added());
    EXPECT_EQ(5u, o.last_change_removed());
    EXPECT_EQ(0u, o.total_change_added());
    EXPECT_EQ(5u, o.total_change_removed());
}

TEST(std_observable_unordered_map_placebo_lockable_test_suite, test_swap)
{
    // Test swap
    m::observable_unordered_map<int, int, u::placebo_lockable>::ptr m1 = m::observable_unordered_map<int, int, u::placebo_lockable>::create();
    m::observable_unordered_map<int, int, u::placebo_lockable>::ptr m2 = m::observable_unordered_map<int, int, u::placebo_lockable>::create();
    unordered_map_observer<int, int> o1;
    unordered_map_observer<int, int> o2;

    EXPECT_EQ(0u, m1->size());
    EXPECT_EQ(0u, m2->size());

    const std::initializer_list<m::observable_unordered_map<int, int, u::placebo_lockable>::value_type> il1 =
    {
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(1, 10),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(2, 20),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(3, 30),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(4, 40),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(5, 50)
    };
    const std::initializer_list<m::observable_unordered_map<int, int, u::placebo_lockable>::value_type> il2 =
    {
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(10, 100),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(20, 200),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(30, 300),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(40, 400),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(50, 500),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(60, 600),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(70, 700)
    };
    *m1 = il1;
    *m2 = il2;
    EXPECT_EQ(5u, m1->size());
    EXPECT_EQ(7u, m2->size());

    o1.connect(m1);
    o2.connect(m2);

    m1->swap(*m2);
    EXPECT_EQ(7u, m1->size());
    EXPECT_EQ(5u, m2->size());

    unsigned int count = 0u;
    int sum = 0;
    for(const m::observable_unordered_map<int, int, u::placebo_lockable>::value_type& i : *m1)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(2800, sum);

    count = 0;
    sum = 0;
    for(const m::observable_unordered_map<int, int, u::placebo_lockable>::value_type& i : *m2)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(5u, count);
    EXPECT_EQ(150, sum);

    EXPECT_EQ(m::notify_container_changed_action::swap, o1.last_action());
    EXPECT_EQ(0u, o1.action_add_count());
    EXPECT_EQ(0u, o1.action_remove_count());
    EXPECT_EQ(0u, o1.action_reset_count());
    EXPECT_EQ(1u, o1.action_swap_count());
    EXPECT_EQ(7u, o1.last_change_new_size());
    EXPECT_EQ(7u, o1.last_change_added());
    EXPECT_EQ(5u, o1.last_change_removed());
    EXPECT_EQ(7u, o1.total_change_added());
    EXPECT_EQ(5u, o1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::swap, o2.last_action());
    EXPECT_EQ(0u, o2.action_add_count());
    EXPECT_EQ(0u, o2.action_remove_count());
    EXPECT_EQ(0u, o2.action_reset_count());
    EXPECT_EQ(1u, o2.action_swap_count());
    EXPECT_EQ(5u, o2.last_change_new_size());
    EXPECT_EQ(5u, o2.last_change_added());
    EXPECT_EQ(7u, o2.last_change_removed());
    EXPECT_EQ(5u, o2.total_change_added());
    EXPECT_EQ(7u, o2.total_change_removed());
}

TEST(std_observable_unordered_map_placebo_lockable_test_suite, test_clear)
{
    // Test clear
    m::observable_unordered_map<int, int, u::placebo_lockable>::ptr m = m::observable_unordered_map<int, int, u::placebo_lockable>::create();
    unordered_map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::observable_unordered_map<int, int, u::placebo_lockable>::value_type> il =
    {
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(1, 10),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(2, 20),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(3, 30),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(4, 40),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(5, 50),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(6, 60),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m->clear();
    EXPECT_EQ(0u, m->size());

    EXPECT_EQ(m::notify_container_changed_action::reset, o.last_action());
    EXPECT_EQ(0u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(1u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(0u, o.last_change_new_size());
    EXPECT_EQ(0u, o.last_change_added());
    EXPECT_EQ(7u, o.last_change_removed());
    EXPECT_EQ(0u, o.total_change_added());
    EXPECT_EQ(7u, o.total_change_removed());
}

TEST(std_observable_unordered_map_placebo_lockable_test_suite, test_emplace)
{
    // Test emplace
    m::observable_unordered_map<int, int, u::placebo_lockable>::ptr m = m::observable_unordered_map<int, int, u::placebo_lockable>::create();
    unordered_map_observer<int, int> o;

    const std::initializer_list<m::observable_unordered_map<int, int, u::placebo_lockable>::value_type> il =
    {
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(1, 10),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(2, 20),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(3, 30)
    };
    *m = il;
    EXPECT_EQ(3u, m->size());

    o.connect(m);

    auto ret = m->emplace(m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(4, 40));
    EXPECT_EQ(4, ret.first->first);
    EXPECT_EQ(40, ret.first->second);
    EXPECT_TRUE(ret.second);

    ret = m->emplace(m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(5, 50));
    EXPECT_EQ(5, ret.first->first);
    EXPECT_EQ(50, ret.first->second);
    EXPECT_TRUE(ret.second);

    ret = m->emplace(m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(4, 40));
    EXPECT_EQ(4, ret.first->first);
    EXPECT_EQ(40, ret.first->second);
    EXPECT_FALSE(ret.second);

    ret = m->emplace(m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(6, 60));
    EXPECT_EQ(6, ret.first->first);
    EXPECT_EQ(60, ret.first->second);
    EXPECT_TRUE(ret.second);

    unsigned int count = 0u;
    int sum = 0;
    for(const m::observable_unordered_map<int, int, u::placebo_lockable>::value_type& i : *m)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(6u, count);
    EXPECT_EQ(210, sum);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
    EXPECT_EQ(3u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(6u, o.last_change_new_size());
    EXPECT_EQ(1u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(3u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

TEST(std_observable_unordered_map_placebo_lockable_test_suite, test_emplace_hint)
{
    // Test emplace hint
    m::observable_unordered_map<int, int, u::placebo_lockable>::ptr m = m::observable_unordered_map<int, int, u::placebo_lockable>::create();
    unordered_map_observer<int, int> o;

    const std::initializer_list<m::observable_unordered_map<int, int, u::placebo_lockable>::value_type> il =
    {
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(1, 10),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(2, 20),
        m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(5, 50)
    };
    *m = il;
    EXPECT_EQ(3u, m->size());

    o.connect(m);

    m::observable_unordered_map<int, int, u::placebo_lockable>::iterator it = m->emplace_hint(m->begin(), m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(3, 30));
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(30, it->second);

    it = m->emplace_hint(it, m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = m->emplace_hint(it, m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = m->emplace_hint(it, m::observable_unordered_map<int, int, u::placebo_lockable>::value_type(6, 60));
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);

    EXPECT_EQ(6u, m->size());

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
    EXPECT_EQ(3u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(6u, o.last_change_new_size());
    EXPECT_EQ(1u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(3u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

}

#endif  // Required C++11 feature is not supported by this compiler
