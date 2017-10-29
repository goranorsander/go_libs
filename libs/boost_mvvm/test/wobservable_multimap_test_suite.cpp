//
//  wobservable_multimap_test_suite.cpp
//
//  Copyright 2015-2017 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go_boost/config.hpp>

#include <go_boost/mvvm.hpp>

namespace m = go_boost::mvvm;
namespace s = go_boost::signals;

namespace
{

template<class K, class T> class multimap_observer
{
public:
    typedef multimap_observer<K, T> this_type;
    typedef typename m::wobservable_multimap<K, T>::ptr wobservable_multimap_ptr_type;

    virtual ~multimap_observer() GO_BOOST_DEFAULT_DESTRUCTOR

    multimap_observer()
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

    void connect(wobservable_multimap_ptr_type& c)
    {
        c->container_changed.connect(boost::bind(&this_type::on_container_changed, this, _1, _2));
        c->property_changed.connect(boost::bind(&this_type::on_property_changed, this, _1, _2));
    }

    void disconnect(wobservable_multimap_ptr_type& c)
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

    void on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a)
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

TEST(boost_wobservable_multimap_test_suite, test_insert_single_element)
{
    // Test insert single element
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    // TODO: Find a way to test insert without using insert to prepare the test
    EXPECT_EQ(0, m->size());
    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(4, 40));
    m->insert(m::observable_multimap<int, int>::value_type(5, 50));
    m->insert(m::observable_multimap<int, int>::value_type(6, 60));
    m->insert(m::observable_multimap<int, int>::value_type(7, 70));
    EXPECT_EQ(6, m->size());

    o.connect(m);

    m->insert(m::wobservable_multimap<int, int>::value_type(3, 30));
    EXPECT_EQ(7, m->size());

    typedef m::wobservable_multimap<int, int> wobservable_multimap_type;
    int count = 0;
    BOOST_FOREACH(const GO_BOOST_TYPENAME wobservable_multimap_type::value_type& i, *m)
    {
        ++count;
        EXPECT_EQ(count, i.first);
        EXPECT_EQ(count*10, i.second);
    }
    EXPECT_EQ(7, count);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(1, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(7, o.last_change_new_size());
    EXPECT_EQ(1, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(1, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

TEST(boost_wobservable_multimap_test_suite, test_insert_single_element_with_hint)
{
    // Test insert single element with hint
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    EXPECT_EQ(0, m->size());
    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(5, 50));
    m->insert(m::observable_multimap<int, int>::value_type(7, 70));
    EXPECT_EQ(4, m->size());

    o.connect(m);

    m::wobservable_multimap<int, int>::iterator it = m->insert(m->begin(), m::wobservable_multimap<int, int>::value_type(3, 30));
    EXPECT_EQ(5, m->size());

    it = m->insert(it, m::wobservable_multimap<int, int>::value_type(4, 40));
    EXPECT_EQ(6, m->size());

    it = m->insert(it, m::wobservable_multimap<int, int>::value_type(4, 40));
    EXPECT_EQ(7, m->size());

    it = m->insert(it, m::wobservable_multimap<int, int>::value_type(6, 60));
    EXPECT_EQ(8, m->size());

    it = m->begin();
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(10, it->second);
    ++it;
    EXPECT_EQ(2, it->first);
    EXPECT_EQ(20, it->second);
    ++it;
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(30, it->second);
    ++it;
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);
    ++it;
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);
    ++it;
    EXPECT_EQ(5, it->first);
    EXPECT_EQ(50, it->second);
    ++it;
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);
    ++it;
    EXPECT_EQ(7, it->first);
    EXPECT_EQ(70, it->second);
    ++it;
    EXPECT_EQ(m->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(4, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(8, o.last_change_new_size());
    EXPECT_EQ(1, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(4, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

TEST(boost_wobservable_multimap_test_suite, test_insert_range)
{
    // Test insert range
    m::wobservable_multimap<int, int>::ptr m1 = m::wobservable_multimap<int, int>::create();
    m::wobservable_multimap<int, int>::ptr m2 = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    EXPECT_EQ(0, m1->size());
    EXPECT_EQ(0, m2->size());

    m1->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m1->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m1->insert(m::observable_multimap<int, int>::value_type(5, 50));
    m1->insert(m::observable_multimap<int, int>::value_type(7, 70));
    EXPECT_EQ(4, m1->size());

    m2->insert(m::observable_multimap<int, int>::value_type(3, 30));
    m2->insert(m::observable_multimap<int, int>::value_type(4, 40));
    m2->insert(m::observable_multimap<int, int>::value_type(6, 60));
    EXPECT_EQ(3, m2->size());

    o.connect(m2);

    m2->insert(m1->begin(), m1->end());
    EXPECT_EQ(7, m2->size());

    m::wobservable_multimap<int, int>::iterator it = m2->begin();
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(10, it->second);
    ++it;
    EXPECT_EQ(2, it->first);
    EXPECT_EQ(20, it->second);
    ++it;
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(30, it->second);
    ++it;
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);
    ++it;
    EXPECT_EQ(5, it->first);
    EXPECT_EQ(50, it->second);
    ++it;
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);
    ++it;
    EXPECT_EQ(7, it->first);
    EXPECT_EQ(70, it->second);
    ++it;
    EXPECT_EQ(m2->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(1, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(7, o.last_change_new_size());
    EXPECT_EQ(4, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(4, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

TEST(boost_wobservable_multimap_test_suite, test_insert_initializer_list)
{
    // Test insert initializer list
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    EXPECT_EQ(0, m->size());

    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il1 =
    {
        m::wobservable_multimap<int, int>::value_type(1, 10),
        m::wobservable_multimap<int, int>::value_type(2, 20),
        m::wobservable_multimap<int, int>::value_type(5, 50),
        m::wobservable_multimap<int, int>::value_type(7, 70)
    };
    *m = il1;
    EXPECT_EQ(4, m->size());

    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il2 =
    {
        m::wobservable_multimap<int, int>::value_type(3, 30),
        m::wobservable_multimap<int, int>::value_type(4, 40),
        m::wobservable_multimap<int, int>::value_type(6, 60)
    };
    EXPECT_EQ(3, il2.size());

    o.connect(m);

    m->insert(il2);
    EXPECT_EQ(7, m->size());

    m::wobservable_multimap<int, int>::iterator it = m->begin();
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(10, it->second);
    ++it;
    EXPECT_EQ(2, it->first);
    EXPECT_EQ(20, it->second);
    ++it;
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(30, it->second);
    ++it;
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);
    ++it;
    EXPECT_EQ(5, it->first);
    EXPECT_EQ(50, it->second);
    ++it;
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);
    ++it;
    EXPECT_EQ(7, it->first);
    EXPECT_EQ(70, it->second);
    ++it;
    EXPECT_EQ(m->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(1, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(7, o.last_change_new_size());
    EXPECT_EQ(3, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(3, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

TEST(boost_wobservable_multimap_test_suite, test_erase_position)
{
    // Test erase position
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    EXPECT_EQ(0, m->size());

    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(3, 30));
    m->insert(m::observable_multimap<int, int>::value_type(4, 40));
    m->insert(m::observable_multimap<int, int>::value_type(5, 50));
    m->insert(m::observable_multimap<int, int>::value_type(6, 60));
    m->insert(m::observable_multimap<int, int>::value_type(7, 70));
    EXPECT_EQ(7, m->size());

    o.connect(m);

    m::wobservable_multimap<int, int>::iterator it1 = m->begin();
    std::advance(it1, 3);
    m::wobservable_multimap<int, int>::iterator it2 = m->erase(it1);
    EXPECT_EQ(6, m->size());

    m->erase(it2);
    EXPECT_EQ(5, m->size());

    it1 = m->begin();
    EXPECT_EQ(1, it1->first);
    EXPECT_EQ(10, it1->second);
    ++it1;
    EXPECT_EQ(2, it1->first);
    EXPECT_EQ(20, it1->second);
    ++it1;
    EXPECT_EQ(3, it1->first);
    EXPECT_EQ(30, it1->second);
    ++it1;
    EXPECT_EQ(6, it1->first);
    EXPECT_EQ(60, it1->second);
    ++it1;
    EXPECT_EQ(7, it1->first);
    EXPECT_EQ(70, it1->second);
    ++it1;
    EXPECT_EQ(m->end(), it1);

    EXPECT_EQ(m::notify_container_changed_action_remove, o.last_action());
    EXPECT_EQ(0, o.action_add_count());
    EXPECT_EQ(2, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(5, o.last_change_new_size());
    EXPECT_EQ(0, o.last_change_added());
    EXPECT_EQ(1, o.last_change_removed());
    EXPECT_EQ(0, o.total_change_added());
    EXPECT_EQ(2, o.total_change_removed());
}

TEST(boost_wobservable_multimap_test_suite, test_erase_value)
{
    // Test erase value
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    EXPECT_EQ(0, m->size());

    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(3, 30));
    m->insert(m::observable_multimap<int, int>::value_type(4, 40));
    m->insert(m::observable_multimap<int, int>::value_type(5, 50));
    m->insert(m::observable_multimap<int, int>::value_type(6, 60));
    m->insert(m::observable_multimap<int, int>::value_type(7, 70));
    EXPECT_EQ(7, m->size());

    o.connect(m);

    m->erase(4);
    EXPECT_EQ(6, m->size());

    m->erase(5);
    EXPECT_EQ(5, m->size());

    m::wobservable_multimap<int, int>::iterator it = m->begin();
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(10, it->second);
    ++it;
    EXPECT_EQ(2, it->first);
    EXPECT_EQ(20, it->second);
    ++it;
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(30, it->second);
    ++it;
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);
    ++it;
    EXPECT_EQ(7, it->first);
    EXPECT_EQ(70, it->second);
    ++it;
    EXPECT_EQ(m->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_remove, o.last_action());
    EXPECT_EQ(0, o.action_add_count());
    EXPECT_EQ(2, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(5, o.last_change_new_size());
    EXPECT_EQ(0, o.last_change_added());
    EXPECT_EQ(1, o.last_change_removed());
    EXPECT_EQ(0, o.total_change_added());
    EXPECT_EQ(2, o.total_change_removed());
}

TEST(boost_wobservable_multimap_test_suite, test_erase_range)
{
    // Test erase range
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    EXPECT_EQ(0, m->size());

    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(3, 30));
    m->insert(m::observable_multimap<int, int>::value_type(4, 40));
    m->insert(m::observable_multimap<int, int>::value_type(5, 50));
    m->insert(m::observable_multimap<int, int>::value_type(6, 60));
    m->insert(m::observable_multimap<int, int>::value_type(7, 70));
    EXPECT_EQ(7, m->size());

    o.connect(m);

    m::wobservable_multimap<int, int>::iterator begin = m->begin();
    ++begin;
    m::wobservable_multimap<int, int>::iterator end = m->end();
    --end;

    m->erase(begin, end);
    EXPECT_EQ(2, m->size());

    m::wobservable_multimap<int, int>::iterator it = m->begin();
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(10, it->second);
    ++it;
    EXPECT_EQ(7, it->first);
    EXPECT_EQ(70, it->second);
    ++it;
    EXPECT_EQ(m->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_remove, o.last_action());
    EXPECT_EQ(0, o.action_add_count());
    EXPECT_EQ(1, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(2, o.last_change_new_size());
    EXPECT_EQ(0, o.last_change_added());
    EXPECT_EQ(5, o.last_change_removed());
    EXPECT_EQ(0, o.total_change_added());
    EXPECT_EQ(5, o.total_change_removed());
}

TEST(boost_wobservable_multimap_test_suite, test_swap)
{
    // Test swap
    m::wobservable_multimap<int, int>::ptr m1 = m::wobservable_multimap<int, int>::create();
    m::wobservable_multimap<int, int>::ptr m2 = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o1;
    multimap_observer<int, int> o2;

    EXPECT_EQ(0, m1->size());
    EXPECT_EQ(0, m2->size());

    m1->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m1->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m1->insert(m::observable_multimap<int, int>::value_type(3, 30));
    m1->insert(m::observable_multimap<int, int>::value_type(4, 40));
    m1->insert(m::observable_multimap<int, int>::value_type(5, 50));
    EXPECT_EQ(5, m1->size());

    m2->insert(m::observable_multimap<int, int>::value_type(10, 100));
    m2->insert(m::observable_multimap<int, int>::value_type(20, 200));
    m2->insert(m::observable_multimap<int, int>::value_type(30, 300));
    m2->insert(m::observable_multimap<int, int>::value_type(40, 400));
    m2->insert(m::observable_multimap<int, int>::value_type(50, 500));
    m2->insert(m::observable_multimap<int, int>::value_type(60, 600));
    m2->insert(m::observable_multimap<int, int>::value_type(70, 700));
    EXPECT_EQ(7, m2->size());

    o1.connect(m1);
    o2.connect(m2);

    m1->swap(*m2);
    EXPECT_EQ(7, m1->size());
    EXPECT_EQ(5, m2->size());

    typedef m::wobservable_multimap<int, int> wobservable_multimap_type;
    int count = 0;
    BOOST_FOREACH(const GO_BOOST_TYPENAME wobservable_multimap_type::value_type& i, *m1)
    {
        ++count;
        EXPECT_EQ(count*10, i.first);
        EXPECT_EQ(count*100, i.second);
    }
    EXPECT_EQ(7, count);

    count = 0;
    BOOST_FOREACH(const GO_BOOST_TYPENAME wobservable_multimap_type::value_type& i, *m2)
    {
        ++count;
        EXPECT_EQ(count, i.first);
        EXPECT_EQ(count*10, i.second);
    }
    EXPECT_EQ(5, count);

    EXPECT_EQ(m::notify_container_changed_action_swap, o1.last_action());
    EXPECT_EQ(0, o1.action_add_count());
    EXPECT_EQ(0, o1.action_remove_count());
    EXPECT_EQ(0, o1.action_reset_count());
    EXPECT_EQ(1, o1.action_swap_count());
    EXPECT_EQ(7, o1.last_change_new_size());
    EXPECT_EQ(7, o1.last_change_added());
    EXPECT_EQ(5, o1.last_change_removed());
    EXPECT_EQ(7, o1.total_change_added());
    EXPECT_EQ(5, o1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action_swap, o2.last_action());
    EXPECT_EQ(0, o2.action_add_count());
    EXPECT_EQ(0, o2.action_remove_count());
    EXPECT_EQ(0, o2.action_reset_count());
    EXPECT_EQ(1, o2.action_swap_count());
    EXPECT_EQ(5, o2.last_change_new_size());
    EXPECT_EQ(5, o2.last_change_added());
    EXPECT_EQ(7, o2.last_change_removed());
    EXPECT_EQ(5, o2.total_change_added());
    EXPECT_EQ(7, o2.total_change_removed());
}

TEST(boost_wobservable_multimap_test_suite, test_clear)
{
    // Test clear
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    EXPECT_EQ(0, m->size());

    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(3, 30));
    m->insert(m::observable_multimap<int, int>::value_type(4, 40));
    m->insert(m::observable_multimap<int, int>::value_type(5, 50));
    m->insert(m::observable_multimap<int, int>::value_type(6, 60));
    m->insert(m::observable_multimap<int, int>::value_type(7, 70));
    EXPECT_EQ(7, m->size());

    o.connect(m);

    m->clear();
    EXPECT_EQ(0, m->size());

    EXPECT_EQ(m::notify_container_changed_action_reset, o.last_action());
    EXPECT_EQ(0, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(1, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(0, o.last_change_new_size());
    EXPECT_EQ(0, o.last_change_added());
    EXPECT_EQ(7, o.last_change_removed());
    EXPECT_EQ(0, o.total_change_added());
    EXPECT_EQ(7, o.total_change_removed());
}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

TEST(boost_wobservable_multimap_test_suite, test_emplace)
{
    // Test emplace
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(3, 30));
    EXPECT_EQ(3, m->size());

    o.connect(m);

    m::wobservable_multimap<int, int>::iterator it = m->emplace(m::wobservable_multimap<int, int>::value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = m->emplace(m::wobservable_multimap<int, int>::value_type(5, 50));
    EXPECT_EQ(5, it->first);
    EXPECT_EQ(50, it->second);

    it = m->emplace(m::wobservable_multimap<int, int>::value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = m->emplace(m::wobservable_multimap<int, int>::value_type(6, 60));
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);

    it = m->begin();
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(10, it->second);
    ++it;
    EXPECT_EQ(2, it->first);
    EXPECT_EQ(20, it->second);
    ++it;
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(30, it->second);
    ++it;
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);
    ++it;
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);
    ++it;
    EXPECT_EQ(5, it->first);
    EXPECT_EQ(50, it->second);
    ++it;
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);
    ++it;
    EXPECT_EQ(m->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(4, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(7, o.last_change_new_size());
    EXPECT_EQ(1, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(4, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

#endif  // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

TEST(boost_wobservable_multimap_test_suite, test_emplace_hint)
{
    // Test emplace hint
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    m->insert(m::observable_multimap<int, int>::value_type(1, 10));
    m->insert(m::observable_multimap<int, int>::value_type(2, 20));
    m->insert(m::observable_multimap<int, int>::value_type(5, 50));
    EXPECT_EQ(3, m->size());

    o.connect(m);

    m::wobservable_multimap<int, int>::iterator it = m->emplace_hint(m->begin(), m::wobservable_multimap<int, int>::value_type(3, 30));
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(30, it->second);

    it = m->emplace_hint(it, m::wobservable_multimap<int, int>::value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = m->emplace_hint(it, m::wobservable_multimap<int, int>::value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = m->emplace_hint(it, m::wobservable_multimap<int, int>::value_type(6, 60));
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);

    it = m->begin();
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(10, it->second);
    ++it;
    EXPECT_EQ(2, it->first);
    EXPECT_EQ(20, it->second);
    ++it;
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(30, it->second);
    ++it;
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);
    ++it;
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);
    ++it;
    EXPECT_EQ(5, it->first);
    EXPECT_EQ(50, it->second);
    ++it;
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);
    ++it;
    EXPECT_EQ(m->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(4, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(7, o.last_change_new_size());
    EXPECT_EQ(1, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(4, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

#endif  // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

}
