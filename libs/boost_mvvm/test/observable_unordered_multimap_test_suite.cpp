//
//  observable_unordered_multimap_test_suite.cpp
//
//  Copyright 2015-2019 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <gtest/gtest.h>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#include <go_boost/mvvm.hpp>

namespace m = go_boost::mvvm;

namespace
{

template<class K, class T> class unordered_multimap_observer
{
public:
    typedef unordered_multimap_observer<K, T> this_type;
    typedef typename m::observable_unordered_multimap<K, T>::ptr observable_unordered_multimap_ptr_type;

    virtual ~unordered_multimap_observer() GO_BOOST_DEFAULT_DESTRUCTOR

    unordered_multimap_observer()
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

    void connect(observable_unordered_multimap_ptr_type& c)
    {
        c->container_changed.connect(boost::bind(&this_type::on_container_changed, this, _1, _2));
        c->property_changed.connect(boost::bind(&this_type::on_property_changed, this, _1, _2));
    }

    void disconnect(observable_unordered_multimap_ptr_type& c)
    {
        c->container_changed.disconnect(boost::bind(&this_type::on_container_changed, this, _1, _2));
        c->property_changed.disconnect(boost::bind(&this_type::on_property_changed, this, _1, _2));
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

TEST(boost_observable_unordered_multimap_test_suite, test_insert_single_element)
{
    // Test insert single element
    m::observable_unordered_multimap<int, int>::ptr m = m::observable_unordered_multimap<int, int>::create();
    unordered_multimap_observer<int, int> o;

    // TODO: Find a way to test insert without using insert to prepare the test
    EXPECT_EQ(0u, m->size());
    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(4, 40));
    m->insert(m::observable_multimap<int, int>::value_type(5, 50));
    m->insert(m::observable_multimap<int, int>::value_type(6, 60));
    m->insert(m::observable_multimap<int, int>::value_type(7, 70));
    EXPECT_EQ(6u, m->size());

    o.connect(m);

    m->insert(m::observable_unordered_multimap<int, int>::value_type(3, 30));
    EXPECT_EQ(7u, m->size());

    typedef m::observable_unordered_multimap<int, int> observable_unordered_multimap_type;
    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const GO_BOOST_TYPENAME observable_unordered_multimap_type::value_type& i, *m)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(280, sum);

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

TEST(boost_observable_unordered_multimap_test_suite, test_insert_single_element_with_hint)
{
    // Test insert single element with hint
    m::observable_unordered_multimap<int, int>::ptr m = m::observable_unordered_multimap<int, int>::create();
    unordered_multimap_observer<int, int> o;

    EXPECT_EQ(0u, m->size());
    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(5, 50));
    m->insert(m::observable_multimap<int, int>::value_type(7, 70));
    EXPECT_EQ(4u, m->size());

    o.connect(m);

    m::observable_unordered_multimap<int, int>::iterator it = m->insert(m->begin(), m::observable_unordered_multimap<int, int>::value_type(3, 30));
    EXPECT_EQ(5u, m->size());

    it = m->insert(it, m::observable_unordered_multimap<int, int>::value_type(4, 40));
    EXPECT_EQ(6u, m->size());

    it = m->insert(it, m::observable_unordered_multimap<int, int>::value_type(4, 40));
    EXPECT_EQ(7u, m->size());

    it = m->insert(it, m::observable_unordered_multimap<int, int>::value_type(6, 60));
    EXPECT_EQ(8u, m->size());

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(4u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(8u, o.last_change_new_size());
    EXPECT_EQ(1u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(4u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

TEST(boost_observable_unordered_multimap_test_suite, test_insert_range)
{
    // Test insert range
    m::observable_unordered_multimap<int, int>::ptr m1 = m::observable_unordered_multimap<int, int>::create();
    m::observable_unordered_multimap<int, int>::ptr m2 = m::observable_unordered_multimap<int, int>::create();
    unordered_multimap_observer<int, int> o;

    EXPECT_EQ(0u, m1->size());
    EXPECT_EQ(0u, m2->size());

    m1->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m1->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m1->insert(m::observable_multimap<int, int>::value_type(5, 50));
    m1->insert(m::observable_multimap<int, int>::value_type(7, 70));
    EXPECT_EQ(4u, m1->size());

    m2->insert(m::observable_multimap<int, int>::value_type(3, 30));
    m2->insert(m::observable_multimap<int, int>::value_type(4, 40));
    m2->insert(m::observable_multimap<int, int>::value_type(6, 60));
    EXPECT_EQ(3u, m2->size());

    o.connect(m2);

    m2->insert(m1->begin(), m1->end());
    EXPECT_EQ(7u, m2->size());

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
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

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

TEST(boost_observable_unordered_multimap_test_suite, test_insert_initializer_list)
{
    // Test insert initializer list
    m::observable_unordered_multimap<int, int>::ptr m = m::observable_unordered_multimap<int, int>::create();
    unordered_multimap_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::observable_unordered_multimap<int, int>::value_type> il1 =
    {
        m::observable_unordered_multimap<int, int>::value_type(1, 10),
        m::observable_unordered_multimap<int, int>::value_type(2, 20),
        m::observable_unordered_multimap<int, int>::value_type(5, 50),
        m::observable_unordered_multimap<int, int>::value_type(7, 70)
    };
    *m = il1;
    EXPECT_EQ(4u, m->size());

    const std::initializer_list<m::observable_unordered_multimap<int, int>::value_type> il2 =
    {
        m::observable_unordered_multimap<int, int>::value_type(3, 30),
        m::observable_unordered_multimap<int, int>::value_type(4, 40),
        m::observable_unordered_multimap<int, int>::value_type(6, 60)
    };
    EXPECT_EQ(3u, il2.size());

    o.connect(m);

    m->insert(il2);
    EXPECT_EQ(7u, m->size());

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
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

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

TEST(boost_observable_unordered_multimap_test_suite, test_erase_position)
{
    // Test erase position
    m::observable_unordered_multimap<int, int>::ptr m = m::observable_unordered_multimap<int, int>::create();
    unordered_multimap_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(3, 30));
    m->insert(m::observable_multimap<int, int>::value_type(4, 40));
    m->insert(m::observable_multimap<int, int>::value_type(5, 50));
    m->insert(m::observable_multimap<int, int>::value_type(6, 60));
    m->insert(m::observable_multimap<int, int>::value_type(7, 70));
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m::observable_unordered_multimap<int, int>::iterator it1 = m->begin();
    std::advance(it1, 3);
    m::observable_unordered_multimap<int, int>::iterator it2 = m->erase(it1);
    EXPECT_EQ(6u, m->size());

    m->erase(it2);
    EXPECT_EQ(5u, m->size());

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

TEST(boost_observable_unordered_multimap_test_suite, test_erase_value)
{
    // Test erase value
    m::observable_unordered_multimap<int, int>::ptr m = m::observable_unordered_multimap<int, int>::create();
    unordered_multimap_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(3, 30));
    m->insert(m::observable_multimap<int, int>::value_type(4, 40));
    m->insert(m::observable_multimap<int, int>::value_type(5, 50));
    m->insert(m::observable_multimap<int, int>::value_type(6, 60));
    m->insert(m::observable_multimap<int, int>::value_type(7, 70));
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m->erase(4);
    EXPECT_EQ(6u, m->size());

    m->erase(5);
    EXPECT_EQ(5u, m->size());

    typedef m::observable_unordered_map<int, int> observable_unordered_map_type;
    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const GO_BOOST_TYPENAME observable_unordered_map_type::value_type& i, *m)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(5u, count);
    EXPECT_EQ(190, sum);

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

TEST(boost_observable_unordered_multimap_test_suite, test_erase_range)
{
    // Test erase range
    m::observable_unordered_multimap<int, int>::ptr m = m::observable_unordered_multimap<int, int>::create();
    unordered_multimap_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(3, 30));
    m->insert(m::observable_multimap<int, int>::value_type(4, 40));
    m->insert(m::observable_multimap<int, int>::value_type(5, 50));
    m->insert(m::observable_multimap<int, int>::value_type(6, 60));
    m->insert(m::observable_multimap<int, int>::value_type(7, 70));
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m::observable_unordered_multimap<int, int>::iterator begin = m->begin();
    ++begin;
    m::observable_unordered_multimap<int, int>::iterator end = begin;
    std::advance(end, 5);

    m->erase(begin, end);
    EXPECT_EQ(2u, m->size());

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

TEST(boost_observable_unordered_multimap_test_suite, test_swap)
{
    // Test swap
    m::observable_unordered_multimap<int, int>::ptr m1 = m::observable_unordered_multimap<int, int>::create();
    m::observable_unordered_multimap<int, int>::ptr m2 = m::observable_unordered_multimap<int, int>::create();
    unordered_multimap_observer<int, int> o1;
    unordered_multimap_observer<int, int> o2;

    EXPECT_EQ(0u, m1->size());
    EXPECT_EQ(0u, m2->size());

    m1->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m1->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m1->insert(m::observable_multimap<int, int>::value_type(3, 30));
    m1->insert(m::observable_multimap<int, int>::value_type(4, 40));
    m1->insert(m::observable_multimap<int, int>::value_type(5, 50));
    EXPECT_EQ(5u, m1->size());

    m2->insert(m::observable_multimap<int, int>::value_type(10, 100));
    m2->insert(m::observable_multimap<int, int>::value_type(20, 200));
    m2->insert(m::observable_multimap<int, int>::value_type(30, 300));
    m2->insert(m::observable_multimap<int, int>::value_type(40, 400));
    m2->insert(m::observable_multimap<int, int>::value_type(50, 500));
    m2->insert(m::observable_multimap<int, int>::value_type(60, 600));
    m2->insert(m::observable_multimap<int, int>::value_type(70, 700));
    EXPECT_EQ(7u, m2->size());

    o1.connect(m1);
    o2.connect(m2);

    m1->swap(*m2);
    EXPECT_EQ(7u, m1->size());
    EXPECT_EQ(5u, m2->size());

    typedef m::observable_unordered_multimap<int, int> observable_unordered_multimap_type;
    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const GO_BOOST_TYPENAME observable_unordered_multimap_type::value_type& i, *m1)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(2800, sum);

    count = 0;
    sum = 0;
    BOOST_FOREACH(const GO_BOOST_TYPENAME observable_unordered_multimap_type::value_type& i, *m2)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(5u, count);
    EXPECT_EQ(150, sum);

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

TEST(boost_observable_unordered_multimap_test_suite, test_clear)
{
    // Test clear
    m::observable_unordered_multimap<int, int>::ptr m = m::observable_unordered_multimap<int, int>::create();
    unordered_multimap_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(3, 30));
    m->insert(m::observable_multimap<int, int>::value_type(4, 40));
    m->insert(m::observable_multimap<int, int>::value_type(5, 50));
    m->insert(m::observable_multimap<int, int>::value_type(6, 60));
    m->insert(m::observable_multimap<int, int>::value_type(7, 70));
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m->clear();
    EXPECT_EQ(0u, m->size());

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

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

TEST(boost_observable_unordered_multimap_test_suite, test_emplace)
{
    // Test emplace
    m::observable_unordered_multimap<int, int>::ptr m = m::observable_unordered_multimap<int, int>::create();
    unordered_multimap_observer<int, int> o;

    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(3, 30));
    EXPECT_EQ(3u, m->size());

    o.connect(m);

    m::observable_unordered_multimap<int, int>::iterator it = m->emplace(m::observable_unordered_multimap<int, int>::value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = m->emplace(m::observable_unordered_multimap<int, int>::value_type(5, 50));
    EXPECT_EQ(5, it->first);
    EXPECT_EQ(50, it->second);

    it = m->emplace(m::observable_unordered_multimap<int, int>::value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = m->emplace(m::observable_unordered_multimap<int, int>::value_type(6, 60));
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);

    typedef m::observable_unordered_map<int, int> observable_unordered_map_type;
    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const GO_BOOST_TYPENAME observable_unordered_map_type::value_type& i, *m)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(250, sum);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(4u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(7u, o.last_change_new_size());
    EXPECT_EQ(1u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(4u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

#endif  // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

TEST(boost_observable_unordered_multimap_test_suite, test_emplace_hint)
{
    // Test emplace hint
    m::observable_unordered_multimap<int, int>::ptr m = m::observable_unordered_multimap<int, int>::create();
    unordered_multimap_observer<int, int> o;

    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(5, 50));
    EXPECT_EQ(3u, m->size());

    o.connect(m);

    m::observable_unordered_multimap<int, int>::iterator it = m->emplace_hint(m->begin(), m::observable_unordered_multimap<int, int>::value_type(3, 30));
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(30, it->second);

    it = m->emplace_hint(it, m::observable_unordered_multimap<int, int>::value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = m->emplace_hint(it, m::observable_unordered_multimap<int, int>::value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = m->emplace_hint(it, m::observable_unordered_multimap<int, int>::value_type(6, 60));
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);

    EXPECT_EQ(7u, m->size());

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(4u, o.action_add_count());
    EXPECT_EQ(0u, o.action_remove_count());
    EXPECT_EQ(0u, o.action_reset_count());
    EXPECT_EQ(0u, o.action_swap_count());
    EXPECT_EQ(7u, o.last_change_new_size());
    EXPECT_EQ(1u, o.last_change_added());
    EXPECT_EQ(0u, o.last_change_removed());
    EXPECT_EQ(4u, o.total_change_added());
    EXPECT_EQ(0u, o.total_change_removed());
}

#endif  // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

}
