//
//  basic_observable_list_test_suite.cpp
//
//  Copyright 2018-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#include <boost/foreach.hpp>

#include <go_boost/mvvm.hpp>
#include <go_boost/namespace_alias.hpp>
#include <go_boost/property.hpp>
#include <go_boost/utility.hpp>

namespace
{

template<class T> class list_observer
{
public:
    typedef list_observer<T> this_type;
    typedef typename m::basic_observable_list<T, s::u8string>::ptr observable_list_ptr_type;

    virtual ~list_observer() GO_BOOST_DEFAULT_DESTRUCTOR

    list_observer()
        : _last_action(m::undefined_notify_container_changed_action)
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

    void connect(observable_list_ptr_type& c)
    {
        c->container_changed.connect(boost::bind(&this_type::on_container_changed, this, boost::placeholders::_1, boost::placeholders::_2));
        c->property_changed.connect(boost::bind(&this_type::on_property_changed, this, boost::placeholders::_1, boost::placeholders::_2));
    }

    void disconnect(observable_list_ptr_type& c)
    {
        c->container_changed.disconnect(boost::bind(&this_type::on_container_changed, this, boost::placeholders::_1, boost::placeholders::_2));
        c->property_changed.disconnect(boost::bind(&this_type::on_property_changed, this, boost::placeholders::_1, boost::placeholders::_2));
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

    void on_property_changed(const m::object::ptr& o, const m::basic_property_changed_arguments<s::u8string>::ptr& a)
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

TEST(boost_basic_observable_list_test_suite, test_assign_range)
{
    // Test assign range
    m::basic_observable_list<int, s::u8string>::ptr l = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l->size());

    o.connect(l);

    l->assign(7, 47);
    EXPECT_EQ(7u, l->size());

    unsigned int count = 0u;
    BOOST_FOREACH(const int& i, *l)
    {
        ++count;
        EXPECT_EQ(47, i);
    }
    EXPECT_EQ(7u, count);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(1u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(7u, o.last_change_new_size());
    EXPECT_EQ(7u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(7u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

TEST(boost_basic_observable_list_test_suite, test_assign_initializer_list)
{
    // Test assign initializer list
    m::basic_observable_list<int, s::u8string>::ptr l = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l->size());

    o.connect(l);

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    l->assign(a, a + 7);
    EXPECT_EQ(7u, l->size());

    unsigned int count = 0u;
    BOOST_FOREACH(const int& i, *l)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i);
    }
    EXPECT_EQ(7u, count);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(1u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(7u, o.last_change_new_size());
    EXPECT_EQ(7u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(7u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

TEST(boost_basic_observable_list_test_suite, test_assign_fill)
{
    // Test assign fill
    m::basic_observable_list<int, s::u8string>::ptr l1 = m::basic_observable_list<int, s::u8string>::create();
    m::basic_observable_list<int, s::u8string>::ptr l2 = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l1->size());
    EXPECT_EQ(0u, l2->size());

    o.connect(l2);

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    l1->assign(a, a + 7);
    EXPECT_EQ(7u, l1->size());
    EXPECT_EQ(0u, l2->size());

    m::basic_observable_list<int, s::u8string>::iterator begin = l1->begin();
    ++begin;
    m::basic_observable_list<int, s::u8string>::iterator end = l1->end();
    --end;

    l2->assign(begin, end);
    EXPECT_EQ(7u, l1->size());
    EXPECT_EQ(5u, l2->size());

    unsigned int count = 0u;
    BOOST_FOREACH(const int& i, *l2)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count) + 1, i);
    }
    EXPECT_EQ(5u, count);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(1u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(5u, o.last_change_new_size());
    EXPECT_EQ(5u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(5u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

TEST(boost_basic_observable_list_test_suite, test_push_back)
{
    // Test push back
    m::basic_observable_list<int, s::u8string>::ptr l = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l->size());

    o.connect(l);

    l->push_back(1);
    EXPECT_EQ(1u, l->size());

    l->push_back(2);
    EXPECT_EQ(2u, l->size());

    l->push_back(3);
    EXPECT_EQ(3u, l->size());

    unsigned int count = 0u;
    BOOST_FOREACH(const int& i, *l)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i);
    }
    EXPECT_EQ(3u, count);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(3u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(3u, o.last_change_new_size());
    EXPECT_EQ(1u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(3u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

TEST(boost_basic_observable_list_test_suite, test_push_front)
{
    // Test push front
    m::basic_observable_list<int, s::u8string>::ptr l = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l->size());

    o.connect(l);

    l->push_front(3);
    EXPECT_EQ(1u, l->size());

    l->push_front(2);
    EXPECT_EQ(2u, l->size());

    l->push_front(1);
    EXPECT_EQ(3u, l->size());

    unsigned int count = 0u;
    BOOST_FOREACH(const int& i, *l)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i);
    }
    EXPECT_EQ(3u, count);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(3u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(3u, o.last_change_new_size());
    EXPECT_EQ(1u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(3u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

TEST(boost_basic_observable_list_test_suite, test_pop_back)
{
    // Test pop back
    m::basic_observable_list<int, s::u8string>::ptr l = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l->size());

    l->assign(7, 47);
    EXPECT_EQ(7u, l->size());

    o.connect(l);

    l->pop_back();
    EXPECT_EQ(6u, l->size());

    l->pop_back();
    EXPECT_EQ(5u, l->size());

    l->pop_back();
    EXPECT_EQ(4u, l->size());

    unsigned int count = 0u;
    BOOST_FOREACH(const int& i, *l)
    {
        ++count;
        EXPECT_EQ(47, i);
    }
    EXPECT_EQ(4u, count);

    EXPECT_EQ(m::notify_container_changed_action_remove, o.last_action());
    EXPECT_EQ(0u, o.action_add_count());
    EXPECT_EQ(3u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(4u, o.last_change_new_size());
    EXPECT_EQ(0u, o.last_change_added());
    EXPECT_EQ(1u, o.last_change_removed());
    EXPECT_EQ(0u, o.total_change_added());
    EXPECT_EQ(3u, o.total_change_removed());
}

TEST(boost_basic_observable_list_test_suite, test_pop_front)
{
    // Test pop front
    m::basic_observable_list<int, s::u8string>::ptr l = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l->size());

    l->assign(7, 47);
    EXPECT_EQ(7u, l->size());

    o.connect(l);

    l->pop_front();
    EXPECT_EQ(6u, l->size());

    l->pop_front();
    EXPECT_EQ(5u, l->size());

    l->pop_front();
    EXPECT_EQ(4u, l->size());

    unsigned int count = 0u;
    BOOST_FOREACH(const int& i, *l)
    {
        ++count;
        EXPECT_EQ(47, i);
    }
    EXPECT_EQ(4u, count);

    EXPECT_EQ(m::notify_container_changed_action_remove, o.last_action());
    EXPECT_EQ(0u, o.action_add_count());
    EXPECT_EQ(3u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(4u, o.last_change_new_size());
    EXPECT_EQ(0u, o.last_change_added());
    EXPECT_EQ(1u, o.last_change_removed());
    EXPECT_EQ(0u, o.total_change_added());
    EXPECT_EQ(3u, o.total_change_removed());
}

TEST(boost_basic_observable_list_test_suite, test_insert_single_element)
{
    // Test insert single element
    m::basic_observable_list<int, s::u8string>::ptr l = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l->size());
    const int a[] = {1, 2, 4, 5, 6, 7};
    l->assign(a, a + 6);
    EXPECT_EQ(6u, l->size());

    o.connect(l);

    m::basic_observable_list<int, s::u8string>::iterator it = l->begin();
    std::advance(it, 2);
    l->insert(it, 3);
    EXPECT_EQ(7u, l->size());

    unsigned int count = 0u;
    BOOST_FOREACH(const int& i, *l)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i);
    }
    EXPECT_EQ(7u, count);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
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

TEST(boost_basic_observable_list_test_suite, test_insert_fill)
{
    // Test insert fill
    m::basic_observable_list<int, s::u8string>::ptr l = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l->size());

    l->assign(7, 47);
    EXPECT_EQ(7u, l->size());

    o.connect(l);

    m::basic_observable_list<int, s::u8string>::iterator it = l->begin();
    std::advance(it, 3);
    l->insert(it, 3, 74);
    EXPECT_EQ(10u, l->size());

    it = l->begin();
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(74, *it);
    ++it;
    EXPECT_EQ(74, *it);
    ++it;
    EXPECT_EQ(74, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(l->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(1u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(10u, o.last_change_new_size());
    EXPECT_EQ(3u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(3u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

TEST(boost_basic_observable_list_test_suite, test_insert_range)
{
    // Test insert range
    m::basic_observable_list<int, s::u8string>::ptr l1 = m::basic_observable_list<int, s::u8string>::create();
    m::basic_observable_list<int, s::u8string>::ptr l2 = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l1->size());

    l1->assign(3, 74);
    EXPECT_EQ(3u, l1->size());

    EXPECT_EQ(0u, l2->size());
    l2->assign(7, 47);
    EXPECT_EQ(7u, l2->size());

    o.connect(l2);

    m::basic_observable_list<int, s::u8string>::iterator it = l2->begin();
    std::advance(it, 3);
    l2->insert(it, l1->begin(), l1->end());
    EXPECT_EQ(10u, l2->size());

    it = l2->begin();
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(74, *it);
    ++it;
    EXPECT_EQ(74, *it);
    ++it;
    EXPECT_EQ(74, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(l2->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(1u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(10u, o.last_change_new_size());
    EXPECT_EQ(3u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(3u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

TEST(boost_basic_observable_list_test_suite, test_erase_position)
{
    // Test erase position
    m::basic_observable_list<int, s::u8string>::ptr l = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l->size());

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    l->assign(a, a + 7);
    EXPECT_EQ(7u, l->size());

    o.connect(l);

    m::basic_observable_list<int, s::u8string>::iterator it1 = l->begin();
    std::advance(it1, 3);
    m::basic_observable_list<int, s::u8string>::iterator it2 = l->erase(it1);
    EXPECT_EQ(6u, l->size());

    l->erase(it2);
    EXPECT_EQ(5u, l->size());

    it1 = l->begin();
    EXPECT_EQ(1, *it1);
    ++it1;
    EXPECT_EQ(2, *it1);
    ++it1;
    EXPECT_EQ(3, *it1);
    ++it1;
    EXPECT_EQ(6, *it1);
    ++it1;
    EXPECT_EQ(7, *it1);
    ++it1;
    EXPECT_EQ(l->end(), it1);

    EXPECT_EQ(m::notify_container_changed_action_remove, o.last_action());
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

TEST(boost_basic_observable_list_test_suite, test_erase_range)
{
    // Test erase range
    m::basic_observable_list<int, s::u8string>::ptr l = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l->size());

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    l->assign(a, a + 7);
    EXPECT_EQ(7u, l->size());

    o.connect(l);

    m::basic_observable_list<int, s::u8string>::iterator begin = l->begin();
    ++begin;
    m::basic_observable_list<int, s::u8string>::iterator end = l->end();
    --end;

    l->erase(begin, end);
    EXPECT_EQ(2u, l->size());

    m::basic_observable_list<int, s::u8string>::iterator it = l->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(7, *it);
    ++it;
    EXPECT_EQ(l->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_remove, o.last_action());
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

TEST(boost_basic_observable_list_test_suite, test_swap)
{
    // Test swap
    m::basic_observable_list<int, s::u8string>::ptr l1 = m::basic_observable_list<int, s::u8string>::create();
    m::basic_observable_list<int, s::u8string>::ptr l2 = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o1;
    list_observer<int> o2;

    EXPECT_EQ(0u, l1->size());
    EXPECT_EQ(0u, l2->size());

    l1->assign(5, 1);
    l2->assign(7, 2);
    EXPECT_EQ(5u, l1->size());
    EXPECT_EQ(7u, l2->size());

    o1.connect(l1);
    o2.connect(l2);

    l1->swap(*l2);
    EXPECT_EQ(7u, l1->size());
    EXPECT_EQ(5u, l2->size());

    unsigned int count = 0u;
    BOOST_FOREACH(const int& i, *l1)
    {
        ++count;
        EXPECT_EQ(2, i);
    }
    EXPECT_EQ(7u, count);

    count = 0;
    BOOST_FOREACH(const int& i, *l2)
    {
        ++count;
        EXPECT_EQ(1, i);
    }
    EXPECT_EQ(5u, count);

    EXPECT_EQ(m::notify_container_changed_action_swap, o1.last_action());
    EXPECT_EQ(0u, o1.action_add_count());
    EXPECT_EQ(0u, o1.action_remove_count());
    EXPECT_EQ(0u, o1.action_reset_count());
    EXPECT_EQ(1u, o1.action_swap_count());
    EXPECT_EQ(7u, o1.last_change_new_size());
    EXPECT_EQ(7u, o1.last_change_added());
    EXPECT_EQ(5u, o1.last_change_removed());
    EXPECT_EQ(7u, o1.total_change_added());
    EXPECT_EQ(5u, o1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action_swap, o2.last_action());
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

TEST(boost_basic_observable_list_test_suite, test_clear)
{
    // Test clear
    m::basic_observable_list<int, s::u8string>::ptr l = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l->size());

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    l->assign(a, a + 7);
    EXPECT_EQ(7u, l->size());

    o.connect(l);

    l->clear();
    EXPECT_EQ(0u, l->size());

    EXPECT_EQ(m::notify_container_changed_action_reset, o.last_action());
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

TEST(boost_basic_observable_list_test_suite, test_splice_entire_list)
{
    // Test splice entire list
    m::basic_observable_list<int, s::u8string>::ptr l1 = m::basic_observable_list<int, s::u8string>::create();
    m::basic_observable_list<int, s::u8string>::ptr l2 = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o1;
    list_observer<int> o2;

    EXPECT_EQ(0u, l1->size());
    EXPECT_EQ(0u, l2->size());

    const int a1[] = {1, 2, 3, 4};
    l1->assign(a1, a1 + 4);
    EXPECT_EQ(4u, l1->size());

    const int a2[] = {10, 20, 30};
    l2->assign(a2, a2 + 3);
    EXPECT_EQ(3u, l2->size());

    o1.connect(l1);
    o2.connect(l2);

    m::basic_observable_list<int, s::u8string>::iterator it1 = l1->begin();
    ++it1;
    EXPECT_EQ(2, *it1);

    l1->splice(it1, *l2);
    EXPECT_EQ(7u, l1->size());
    EXPECT_EQ(0u, l2->size());
    EXPECT_EQ(2, *it1);

    m::basic_observable_list<int, s::u8string>::iterator it = l1->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(10, *it);
    ++it;
    EXPECT_EQ(20, *it);
    ++it;
    EXPECT_EQ(30, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(l1->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, o1.last_action());
    EXPECT_EQ(1u, o1.action_add_count());
    EXPECT_EQ(0u, o1.action_remove_count());
    EXPECT_EQ(0u, o1.action_reset_count());
    EXPECT_EQ(0u, o1.action_swap_count());
    EXPECT_EQ(7u, o1.last_change_new_size());
    EXPECT_EQ(3u, o1.last_change_added());
    EXPECT_EQ(0u, o1.last_change_removed());
    EXPECT_EQ(3u, o1.total_change_added());
    EXPECT_EQ(0u, o1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action_remove, o2.last_action());
    EXPECT_EQ(0u, o2.action_add_count());
    EXPECT_EQ(1u, o2.action_remove_count());
    EXPECT_EQ(0u, o2.action_reset_count());
    EXPECT_EQ(0u, o2.action_swap_count());
    EXPECT_EQ(0u, o2.last_change_new_size());
    EXPECT_EQ(0u, o2.last_change_added());
    EXPECT_EQ(3u, o2.last_change_removed());
    EXPECT_EQ(0u, o2.total_change_added());
    EXPECT_EQ(3u, o2.total_change_removed());
}

TEST(boost_basic_observable_list_test_suite, test_splice_single_element)
{
    // Test splice single element
    m::basic_observable_list<int, s::u8string>::ptr l1 = m::basic_observable_list<int, s::u8string>::create();
    m::basic_observable_list<int, s::u8string>::ptr l2 = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o1;
    list_observer<int> o2;

    EXPECT_EQ(0u, l1->size());
    EXPECT_EQ(0u, l2->size());

    const int a2[] = {1, 10, 20, 30, 2, 3, 4};
    l2->assign(a2, a2 + 7);
    EXPECT_EQ(7u, l2->size());

    o1.connect(l1);
    o2.connect(l2);

    m::basic_observable_list<int, s::u8string>::iterator it2 = l2->begin();
    std::advance(it2, 4);
    EXPECT_EQ(2, *it2);

    m::basic_observable_list<int, s::u8string>::iterator it1 = l1->begin();
    l1->splice(it1, *l2, it2);
    EXPECT_EQ(1u, l1->size());
    EXPECT_EQ(6u, l2->size());
    // it1 is invalid
    // it2 is invalid

    it1 = l1->begin();
    EXPECT_EQ(2, *it1);
    ++it1;
    EXPECT_EQ(l1->end(), it1);

    it2 = l2->begin();
    EXPECT_EQ(1, *it2);
    ++it2;
    EXPECT_EQ(10, *it2);
    ++it2;
    EXPECT_EQ(20, *it2);
    ++it2;
    EXPECT_EQ(30, *it2);
    ++it2;
    EXPECT_EQ(3, *it2);
    ++it2;
    EXPECT_EQ(4, *it2);
    ++it2;
    EXPECT_EQ(l2->end(), it2);

    EXPECT_EQ(m::notify_container_changed_action_add, o1.last_action());
    EXPECT_EQ(1u, o1.action_add_count());
    EXPECT_EQ(0u, o1.action_remove_count());
    EXPECT_EQ(0u, o1.action_reset_count());
    EXPECT_EQ(0u, o1.action_swap_count());
    EXPECT_EQ(1u, o1.last_change_new_size());
    EXPECT_EQ(1u, o1.last_change_added());
    EXPECT_EQ(0u, o1.last_change_removed());
    EXPECT_EQ(1u, o1.total_change_added());
    EXPECT_EQ(0u, o1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action_remove, o2.last_action());
    EXPECT_EQ(0u, o2.action_add_count());
    EXPECT_EQ(1u, o2.action_remove_count());
    EXPECT_EQ(0u, o2.action_reset_count());
    EXPECT_EQ(0u, o2.action_swap_count());
    EXPECT_EQ(6u, o2.last_change_new_size());
    EXPECT_EQ(0u, o2.last_change_added());
    EXPECT_EQ(1u, o2.last_change_removed());
    EXPECT_EQ(0u, o2.total_change_added());
    EXPECT_EQ(1u, o2.total_change_removed());
}

TEST(boost_basic_observable_list_test_suite, test_splice_element_range)
{
    // Test splice element range
    m::basic_observable_list<int, s::u8string>::ptr l1 = m::basic_observable_list<int, s::u8string>::create();
    m::basic_observable_list<int, s::u8string>::ptr l2 = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o1;
    list_observer<int> o2;

    EXPECT_EQ(0u, l1->size());
    EXPECT_EQ(0u, l2->size());

    const int a1[] = {1, 2, 3, 4};
    l1->assign(a1, a1 + 4);
    EXPECT_EQ(4u, l1->size());

    const int a2[] = {10, 20, 30, 40, 50};
    l2->assign(a2, a2 + 5);
    EXPECT_EQ(5u, l2->size());

    o1.connect(l1);
    o2.connect(l2);

    m::basic_observable_list<int, s::u8string>::iterator it1 = l1->begin();
    ++it1;
    EXPECT_EQ(2, *it1);

    m::basic_observable_list<int, s::u8string>::iterator it2first = l2->begin();
    ++it2first;
    EXPECT_EQ(20, *it2first);

    m::basic_observable_list<int, s::u8string>::iterator it2last = l2->begin();
    std::advance(it2last, 3);
    EXPECT_EQ(40, *it2last);

    l1->splice(it1, *l2, it2first, it2last);
    EXPECT_EQ(6u, l1->size());
    EXPECT_EQ(3u, l2->size());
    EXPECT_EQ(2, *it1);
    // it2first is invalid?
    // it2last is invalid?

    m::basic_observable_list<int, s::u8string>::iterator it = l1->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(20, *it);
    ++it;
    EXPECT_EQ(30, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(l1->end(), it);

    it = l2->begin();
    EXPECT_EQ(10, *it);
    ++it;
    EXPECT_EQ(40, *it);
    ++it;
    EXPECT_EQ(50, *it);
    ++it;
    EXPECT_EQ(l2->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, o1.last_action());
    EXPECT_EQ(1u, o1.action_add_count());
    EXPECT_EQ(0u, o1.action_remove_count());
    EXPECT_EQ(0u, o1.action_reset_count());
    EXPECT_EQ(0u, o1.action_swap_count());
    EXPECT_EQ(6u, o1.last_change_new_size());
    EXPECT_EQ(2u, o1.last_change_added());
    EXPECT_EQ(0u, o1.last_change_removed());
    EXPECT_EQ(2u, o1.total_change_added());
    EXPECT_EQ(0u, o1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action_remove, o2.last_action());
    EXPECT_EQ(0u, o2.action_add_count());
    EXPECT_EQ(1u, o2.action_remove_count());
    EXPECT_EQ(0u, o2.action_reset_count());
    EXPECT_EQ(0u, o2.action_swap_count());
    EXPECT_EQ(3u, o2.last_change_new_size());
    EXPECT_EQ(0u, o2.last_change_added());
    EXPECT_EQ(2u, o2.last_change_removed());
    EXPECT_EQ(0u, o2.total_change_added());
    EXPECT_EQ(2u, o2.total_change_removed());
}

TEST(boost_basic_observable_list_test_suite, test_remove)
{
    // Test remove
    m::basic_observable_list<int, s::u8string>::ptr l = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l->size());

    const int a[] = {10, 20, 47, 30, 47, 47, 40};
    l->assign(a, a + 7);
    EXPECT_EQ(7u, l->size());

    o.connect(l);

    l->remove(47);
    EXPECT_EQ(4u, l->size());

    m::basic_observable_list<int, s::u8string>::iterator it = l->begin();
    EXPECT_EQ(10, *it);
    ++it;
    EXPECT_EQ(20, *it);
    ++it;
    EXPECT_EQ(30, *it);
    ++it;
    EXPECT_EQ(40, *it);
    ++it;
    EXPECT_EQ(l->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_remove, o.last_action());
    EXPECT_EQ(0u, o.action_add_count());
    EXPECT_EQ(1u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(4u, o.last_change_new_size());
    EXPECT_EQ(0u, o.last_change_added());
    EXPECT_EQ(3u, o.last_change_removed());
    EXPECT_EQ(0u, o.total_change_added());
    EXPECT_EQ(3u, o.total_change_removed());
}

struct is_odd
{
    bool operator()(const int& value) const
    {
        return (value % 2) == 1;
    }
};

TEST(boost_basic_observable_list_test_suite, test_remove_if)
{
    // Test remove if
    m::basic_observable_list<int, s::u8string>::ptr l = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l->size());

    const int a[] = {10, 20, 47, 30, 47, 47, 40};
    l->assign(a, a + 7);
    EXPECT_EQ(7u, l->size());

    o.connect(l);

    l->remove_if(is_odd());
    EXPECT_EQ(4u, l->size());

    m::basic_observable_list<int, s::u8string>::iterator it = l->begin();
    EXPECT_EQ(10, *it);
    ++it;
    EXPECT_EQ(20, *it);
    ++it;
    EXPECT_EQ(30, *it);
    ++it;
    EXPECT_EQ(40, *it);
    ++it;
    EXPECT_EQ(l->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_remove, o.last_action());
    EXPECT_EQ(0u, o.action_add_count());
    EXPECT_EQ(1u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(4u, o.last_change_new_size());
    EXPECT_EQ(0u, o.last_change_added());
    EXPECT_EQ(3u, o.last_change_removed());
    EXPECT_EQ(0u, o.total_change_added());
    EXPECT_EQ(3u, o.total_change_removed());
}

TEST(boost_basic_observable_list_test_suite, test_unique)
{
    // Test unique
    m::basic_observable_list<int, s::u8string>::ptr l = m::basic_observable_list<int, s::u8string>::create();
    list_observer<int> o;

    EXPECT_EQ(0u, l->size());

    const int a[] = {10, 20, 47, 30, 47, 47, 40};
    l->assign(a, a + 7);
    EXPECT_EQ(7u, l->size());

    o.connect(l);

    l->unique();
    EXPECT_EQ(6u, l->size());

    m::basic_observable_list<int, s::u8string>::iterator it = l->begin();
    EXPECT_EQ(10, *it);
    ++it;
    EXPECT_EQ(20, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(30, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(40, *it);
    ++it;
    EXPECT_EQ(l->end(), it);

    l->sort();
    l->unique();
    EXPECT_EQ(5u, l->size());

    it = l->begin();
    EXPECT_EQ(10, *it);
    ++it;
    EXPECT_EQ(20, *it);
    ++it;
    EXPECT_EQ(30, *it);
    ++it;
    EXPECT_EQ(40, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(l->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_remove, o.last_action());
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

struct same_integral_part
{
    bool operator()(double first, double second) const
    {
        return int(first) == int(second);
    }
};

TEST(boost_basic_observable_list_test_suite, test_unique_binary_predicate)
{
    // Test unique binary predicate
    m::basic_observable_list<double, s::u8string>::ptr l = m::basic_observable_list<double, s::u8string>::create();
    list_observer<double> o;

    EXPECT_EQ(0u, l->size());

    const double a[] = {12.15, 2.72, 73.0, 12.77, 3.14, 12.77, 73.35, 72.25, 15.3, 72.25};
    l->assign(a, a + 10);
    EXPECT_EQ(10u, l->size());

    l->sort();
    o.connect(l);

    l->unique();
    EXPECT_EQ(8u, l->size());

    l->unique(same_integral_part());
    EXPECT_EQ(6u, l->size());

    m::basic_observable_list<double, s::u8string>::iterator it = l->begin();
    EXPECT_EQ(2.72, *it);
    ++it;
    EXPECT_EQ(3.14, *it);
    ++it;
    EXPECT_EQ(12.15, *it);
    ++it;
    EXPECT_EQ(15.3, *it);
    ++it;
    EXPECT_EQ(72.25, *it);
    ++it;
    EXPECT_EQ(73.0, *it);
    ++it;
    EXPECT_EQ(l->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_remove, o.last_action());
    EXPECT_EQ(0u, o.action_add_count());
    EXPECT_EQ(2u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(6u, o.last_change_new_size());
    EXPECT_EQ(0u, o.last_change_added());
    EXPECT_EQ(2u, o.last_change_removed());
    EXPECT_EQ(0u, o.total_change_added());
    EXPECT_EQ(4u, o.total_change_removed());
}

TEST(boost_basic_observable_list_test_suite, test_merge)
{
    // Test merge
    m::basic_observable_list<double, s::u8string>::ptr l1 = m::basic_observable_list<double, s::u8string>::create();
    m::basic_observable_list<double, s::u8string>::ptr l2 = m::basic_observable_list<double, s::u8string>::create();
    list_observer<double> o1;
    list_observer<double> o2;

    EXPECT_EQ(0u, l1->size());
    EXPECT_EQ(0u, l2->size());

    const double a1[] = {3.1, 2.2, 2.9};
    l1->assign(a1, a1 + 3);
    EXPECT_EQ(3u, l1->size());

    const double a2[] = {3.7, 7.1, 1.4};
    l2->assign(a2, a2 + 3);
    EXPECT_EQ(3u, l2->size());

    o1.connect(l1);
    o2.connect(l2);

    l1->sort();
    l2->sort();

    l1->merge(*l2);
    EXPECT_EQ(6u, l1->size());
    EXPECT_EQ(0u, l2->size());

    m::basic_observable_list<double, s::u8string>::iterator it = l1->begin();
    EXPECT_EQ(1.4, *it);
    ++it;
    EXPECT_EQ(2.2, *it);
    ++it;
    EXPECT_EQ(2.9, *it);
    ++it;
    EXPECT_EQ(3.1, *it);
    ++it;
    EXPECT_EQ(3.7, *it);
    ++it;
    EXPECT_EQ(7.1, *it);
    ++it;
    EXPECT_EQ(l1->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, o1.last_action());
    EXPECT_EQ(1u, o1.action_add_count());
    EXPECT_EQ(0u, o1.action_remove_count());
    EXPECT_EQ(0u, o1.action_reset_count());
    EXPECT_EQ(0u, o1.action_swap_count());
    EXPECT_EQ(6u, o1.last_change_new_size());
    EXPECT_EQ(3u, o1.last_change_added());
    EXPECT_EQ(0u, o1.last_change_removed());
    EXPECT_EQ(3u, o1.total_change_added());
    EXPECT_EQ(0u, o1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action_remove, o2.last_action());
    EXPECT_EQ(0u, o2.action_add_count());
    EXPECT_EQ(1u, o2.action_remove_count());
    EXPECT_EQ(0u, o2.action_reset_count());
    EXPECT_EQ(0u, o2.action_swap_count());
    EXPECT_EQ(0u, o2.last_change_new_size());
    EXPECT_EQ(0u, o2.last_change_added());
    EXPECT_EQ(3u, o2.last_change_removed());
    EXPECT_EQ(0u, o2.total_change_added());
    EXPECT_EQ(3u, o2.total_change_removed());
}

struct less_integral_part
{
    bool operator()(double first, double second) const
    {
        return int(first) < int(second);
    }
};

TEST(boost_basic_observable_list_test_suite, test_merge_compare_predicate)
{
    // Test merge compare predicate
    m::basic_observable_list<double, s::u8string>::ptr l1 = m::basic_observable_list<double, s::u8string>::create();
    m::basic_observable_list<double, s::u8string>::ptr l2 = m::basic_observable_list<double, s::u8string>::create();
    list_observer<double> o1;
    list_observer<double> o2;

    EXPECT_EQ(0u, l1->size());
    EXPECT_EQ(0u, l2->size());

    const double a1[] = {3.1, 2.2, 2.9, 3.7, 7.1, 1.4};
    l1->assign(a1, a1 + 6);
    EXPECT_EQ(6u, l1->size());

    l2->push_back(2.1);
    EXPECT_EQ(1u, l2->size());

    o1.connect(l1);
    o2.connect(l2);

    l1->sort();
    l2->sort();

    l1->merge(*l2, less_integral_part());
    EXPECT_EQ(7u, l1->size());
    EXPECT_EQ(0u, l2->size());

    m::basic_observable_list<double, s::u8string>::iterator it = l1->begin();
    EXPECT_EQ(1.4, *it);
    ++it;
    EXPECT_EQ(2.2, *it);
    ++it;
    EXPECT_EQ(2.9, *it);
    ++it;
    EXPECT_EQ(2.1, *it);
    ++it;
    EXPECT_EQ(3.1, *it);
    ++it;
    EXPECT_EQ(3.7, *it);
    ++it;
    EXPECT_EQ(7.1, *it);
    ++it;
    EXPECT_EQ(l1->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, o1.last_action());
    EXPECT_EQ(1u, o1.action_add_count());
    EXPECT_EQ(0u, o1.action_remove_count());
    EXPECT_EQ(0u, o1.action_reset_count());
    EXPECT_EQ(0u, o1.action_swap_count());
    EXPECT_EQ(7u, o1.last_change_new_size());
    EXPECT_EQ(1u, o1.last_change_added());
    EXPECT_EQ(0u, o1.last_change_removed());
    EXPECT_EQ(1u, o1.total_change_added());
    EXPECT_EQ(0u, o1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action_remove, o2.last_action());
    EXPECT_EQ(0u, o2.action_add_count());
    EXPECT_EQ(1u, o2.action_remove_count());
    EXPECT_EQ(0u, o2.action_reset_count());
    EXPECT_EQ(0u, o2.action_swap_count());
    EXPECT_EQ(0u, o2.last_change_new_size());
    EXPECT_EQ(0u, o2.last_change_added());
    EXPECT_EQ(1u, o2.last_change_removed());
    EXPECT_EQ(0u, o2.total_change_added());
    EXPECT_EQ(1u, o2.total_change_removed());
}

}
