//
//  observable_unordered_set_test_suite.cpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <gtest/gtest.h>
#include <boost/config.hpp>

#include <go_boost/mvvm.hpp>

namespace m = go_boost::mvvm;
namespace s = go_boost::signals;

namespace
{

template<class T> class set_observer
{
public:
    typedef set_observer<T> this_type;
    typedef typename m::observable_unordered_set<T>::ptr observable_unordered_set_ptr_type;

    virtual ~set_observer()
    {
    }

    set_observer()
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

    void connect(observable_unordered_set_ptr_type& c)
    {
        c->container_changed.connect(boost::bind(&this_type::on_container_changed, this, _1, _2));
        c->property_changed.connect(boost::bind(&this_type::on_property_changed, this, _1, _2));
    }

    void disconnect(observable_unordered_set_ptr_type& c)
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

TEST(boost_observable_unordered_set_test_suite, test_insert_single_element)
{
    // Test insert single element
    m::observable_unordered_set<int>::ptr s = m::observable_unordered_set<int>::create();
    set_observer<int> o;

    // TODO: Find a way to test insert without using insert to prepare the test
    EXPECT_EQ(0, s->size());
    s->insert(1);
    s->insert(2);
    s->insert(4);
    s->insert(5);
    s->insert(6);
    s->insert(7);
    EXPECT_EQ(6, s->size());

    o.connect(s);

    s->insert(3);
    EXPECT_EQ(7, s->size());

    int count = 0;
    int sum = 0;
    BOOST_FOREACH(const int& i, *s)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(7, count);
    EXPECT_EQ(28, sum);

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

TEST(boost_observable_unordered_set_test_suite, test_insert_single_element_with_hint)
{
    // Test insert single element with hint
    m::observable_unordered_set<int>::ptr s = m::observable_unordered_set<int>::create();
    set_observer<int> o;

    EXPECT_EQ(0, s->size());
    s->insert(1);
    s->insert(2);
    s->insert(5);
    s->insert(7);
    EXPECT_EQ(4, s->size());

    o.connect(s);

    m::observable_unordered_set<int>::iterator it = s->insert(s->begin(), 3);
    EXPECT_EQ(5, s->size());

    it = s->insert(it, 4);
    EXPECT_EQ(6, s->size());

    it = s->insert(it, 4);
    EXPECT_EQ(6, s->size());

    it = s->insert(it, 6);
    EXPECT_EQ(7, s->size());

    int count = 0;
    int sum = 0;
    BOOST_FOREACH(const int& i, *s)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(7, count);
    EXPECT_EQ(28, sum);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(3, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(7, o.last_change_new_size());
    EXPECT_EQ(1, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(3, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

TEST(boost_observable_unordered_set_test_suite, test_insert_range)
{
    // Test insert range
    m::observable_unordered_set<int>::ptr s1 = m::observable_unordered_set<int>::create();
    m::observable_unordered_set<int>::ptr s2 = m::observable_unordered_set<int>::create();
    set_observer<int> o;

    EXPECT_EQ(0, s1->size());
    EXPECT_EQ(0, s2->size());

    s1->insert(1);
    s1->insert(2);
    s1->insert(5);
    s1->insert(7);
    EXPECT_EQ(4, s1->size());

    s2->insert(3);
    s2->insert(4);
    s2->insert(6);
    EXPECT_EQ(3, s2->size());

    o.connect(s2);

    s2->insert(s1->begin(), s1->end());
    EXPECT_EQ(7, s2->size());

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

TEST(boost_observable_unordered_set_test_suite, test_insert_initializer_list)
{
    // Test insert initializer list
    m::observable_unordered_set<int>::ptr s = m::observable_unordered_set<int>::create();
    set_observer<int> o;

    EXPECT_EQ(0, s->size());

    const std::initializer_list<int> il1 = {1, 2, 5, 7};
    *s = il1;
    EXPECT_EQ(4, s->size());

    const std::initializer_list<int> il2 = {3, 4, 6};
    EXPECT_EQ(3, il2.size());

    o.connect(s);

    s->insert(il2);
    EXPECT_EQ(7, s->size());

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

TEST(boost_observable_unordered_set_test_suite, test_erase_position)
{
    // Test erase position
    m::observable_unordered_set<int>::ptr s = m::observable_unordered_set<int>::create();
    set_observer<int> o;

    EXPECT_EQ(0, s->size());

    s->insert(1);
    s->insert(2);
    s->insert(3);
    s->insert(4);
    s->insert(5);
    s->insert(6);
    s->insert(7);
    EXPECT_EQ(7, s->size());

    o.connect(s);

    m::observable_unordered_set<int>::iterator it1 = s->begin();
    std::advance(it1, 3);
    m::observable_unordered_set<int>::iterator it2 = s->erase(it1);
    EXPECT_EQ(6, s->size());

    s->erase(it2);
    EXPECT_EQ(5, s->size());

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

TEST(boost_observable_unordered_set_test_suite, test_erase_value)
{
    // Test erase value
    m::observable_unordered_set<int>::ptr s = m::observable_unordered_set<int>::create();
    set_observer<int> o;

    EXPECT_EQ(0, s->size());

    s->insert(1);
    s->insert(2);
    s->insert(3);
    s->insert(4);
    s->insert(5);
    s->insert(6);
    s->insert(7);
    EXPECT_EQ(7, s->size());

    o.connect(s);

    s->erase(4);
    EXPECT_EQ(6, s->size());

    s->erase(5);
    EXPECT_EQ(5, s->size());

    typedef m::observable_unordered_set<int> observable_unordered_set_type;
    int count = 0;
    int sum = 0;
    BOOST_FOREACH(const observable_unordered_set_type::value_type& i, *s)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(5, count);
    EXPECT_EQ(19, sum);

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

TEST(boost_observable_unordered_set_test_suite, test_erase_range)
{
    // Test erase range
    m::observable_unordered_set<int>::ptr s = m::observable_unordered_set<int>::create();
    set_observer<int> o;

    EXPECT_EQ(0, s->size());

    s->insert(1);
    s->insert(2);
    s->insert(3);
    s->insert(4);
    s->insert(5);
    s->insert(6);
    s->insert(7);
    EXPECT_EQ(7, s->size());

    o.connect(s);

    m::observable_unordered_set<int>::iterator begin = s->begin();
    ++begin;
    m::observable_unordered_set<int>::iterator end = begin;
    std::advance(end, 5);

    s->erase(begin, end);
    EXPECT_EQ(2, s->size());

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

TEST(boost_observable_unordered_set_test_suite, test_swap)
{
    // Test swap
    m::observable_unordered_set<int>::ptr s1 = m::observable_unordered_set<int>::create();
    m::observable_unordered_set<int>::ptr s2 = m::observable_unordered_set<int>::create();
    set_observer<int> o1;
    set_observer<int> o2;

    EXPECT_EQ(0, s1->size());
    EXPECT_EQ(0, s2->size());

    s1->insert(1);
    s1->insert(2);
    s1->insert(3);
    s1->insert(4);
    s1->insert(5);
    EXPECT_EQ(5, s1->size());

    s2->insert(10);
    s2->insert(20);
    s2->insert(30);
    s2->insert(40);
    s2->insert(50);
    s2->insert(60);
    s2->insert(70);
    EXPECT_EQ(7, s2->size());

    o1.connect(s1);
    o2.connect(s2);

    s1->swap(*s2);
    EXPECT_EQ(7, s1->size());
    EXPECT_EQ(5, s2->size());

    int count = 0;
    int sum = 0;
    BOOST_FOREACH(const int& i, *s1)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(7, count);
    EXPECT_EQ(280, sum);

    count = 0;
    sum = 0;
    BOOST_FOREACH(const int& i, *s2)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(5, count);
    EXPECT_EQ(15, sum);

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

TEST(boost_observable_unordered_set_test_suite, test_clear)
{
    // Test clear
    m::observable_unordered_set<int>::ptr s = m::observable_unordered_set<int>::create();
    set_observer<int> o;

    EXPECT_EQ(0, s->size());

    s->insert(1);
    s->insert(2);
    s->insert(3);
    s->insert(4);
    s->insert(5);
    s->insert(6);
    s->insert(7);
    EXPECT_EQ(7, s->size());

    o.connect(s);

    s->clear();
    EXPECT_EQ(0, s->size());

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

TEST(boost_observable_unordered_set_test_suite, test_emplace)
{
    // Test emplace
    m::observable_unordered_set<int>::ptr s = m::observable_unordered_set<int>::create();
    set_observer<int> o;

    s->insert(1);
    s->insert(2);
    s->insert(3);
    EXPECT_EQ(3, s->size());

    o.connect(s);

    auto ret = s->emplace(4);
    EXPECT_EQ(4, *(ret.first));
    EXPECT_TRUE(ret.second);

    ret = s->emplace(5);
    EXPECT_EQ(5, *(ret.first));
    EXPECT_TRUE(ret.second);

    ret = s->emplace(4);
    EXPECT_EQ(4, *(ret.first));
    EXPECT_FALSE(ret.second);

    ret = s->emplace(6);
    EXPECT_EQ(6, *(ret.first));
    EXPECT_TRUE(ret.second);

    typedef m::observable_unordered_set<int> observable_unordered_set_type;
    int count = 0;
    int sum = 0;
    BOOST_FOREACH(const observable_unordered_set_type::value_type& i, *s)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(6, count);
    EXPECT_EQ(21, sum);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(3, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(6, o.last_change_new_size());
    EXPECT_EQ(1, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(3, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

#endif  // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

TEST(boost_observable_unordered_set_test_suite, test_emplace_hint)
{
    // Test emplace hint
    m::observable_unordered_set<int>::ptr s = m::observable_unordered_set<int>::create();
    set_observer<int> o;

    s->insert(1);
    s->insert(2);
    s->insert(5);
    EXPECT_EQ(3, s->size());

    o.connect(s);

    m::observable_unordered_set<int>::iterator it = s->emplace_hint(s->begin(), 3);
    EXPECT_EQ(3, *it);

    it = s->emplace_hint(it, 4);
    EXPECT_EQ(4, *it);

    it = s->emplace_hint(it, 4);
    EXPECT_EQ(4, *it);

    it = s->emplace_hint(it, 6);
    EXPECT_EQ(6, *it);

    EXPECT_EQ(6, s->size());

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
    EXPECT_EQ(3, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(6, o.last_change_new_size());
    EXPECT_EQ(1, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(3, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

#endif  // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

}
