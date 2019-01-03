//
//  basic_observable_forward_list_test_suite.cpp
//
//  Copyright 2018-2019 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_NOEXCEPT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_basic_observable_forward_list_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>
#include <go/utility.hpp>

namespace m = go::mvvm;
namespace ph = std::placeholders;
namespace s = go::signals;
namespace u = go::utility;
namespace us = go::utility::string;

namespace
{

template<class T> class forward_list_observer
{
public:
    typedef forward_list_observer<T> this_type;
    typedef typename m::basic_observable_forward_list<T, u::u8string>::ptr observable_forward_list_ptr_type;

    virtual ~forward_list_observer() GO_DEFAULT_DESTRUCTOR

    forward_list_observer()
        : _on_container_changed_slot_key()
        , _on_property_changed_slot_key()
        , _last_action(m::notify_container_changed_action::undefined)
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

    void connect(observable_forward_list_ptr_type& c)
    {
        _on_container_changed_slot_key = c->container_changed.connect(std::bind(&this_type::on_container_changed, this, ph::_1, ph::_2));
        _on_property_changed_slot_key = c->property_changed.connect(std::bind(&this_type::on_property_changed, this, ph::_1, ph::_2));
    }

    void disconnect(observable_forward_list_ptr_type& c)
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

    void on_property_changed(const m::object::ptr& o, const m::basic_property_changed_arguments<u::u8string>::ptr& a)
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
    s::slot_key _on_container_changed_slot_key;
    s::slot_key _on_property_changed_slot_key;

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

TEST(std_basic_observable_forward_list_test_suite, test_assign_range)
{
    // Test assign range
    m::basic_observable_forward_list<int, u::u8string>::ptr l = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    EXPECT_EQ(0, l->size());

    o.connect(l);

    l->assign(7, 47);
    EXPECT_EQ(7, l->size());

    int count = 0;
    for(const int& i : *l)
    {
        ++count;
        EXPECT_EQ(47, i);
    }
    EXPECT_EQ(7, count);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
    EXPECT_EQ(1, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(7, o.last_change_new_size());
    EXPECT_EQ(7, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(7, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

TEST(std_basic_observable_forward_list_test_suite, test_assign_initializer_list)
{
    // Test assign initializer forward_list
    m::basic_observable_forward_list<int, u::u8string>::ptr l = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    EXPECT_EQ(0, l->size());

    o.connect(l);

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    l->assign(a, a + 7);
    EXPECT_EQ(7, l->size());

    int count = 0;
    for(const int& i : *l)
    {
        ++count;
        EXPECT_EQ(count, i);
    }
    EXPECT_EQ(7, count);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
    EXPECT_EQ(1, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(7, o.last_change_new_size());
    EXPECT_EQ(7, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(7, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

TEST(std_basic_observable_forward_list_test_suite, test_assign_fill)
{
    // Test assign fill
    m::basic_observable_forward_list<int, u::u8string>::ptr l1 = m::basic_observable_forward_list<int, u::u8string>::create();
    m::basic_observable_forward_list<int, u::u8string>::ptr l2 = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    EXPECT_EQ(0, l1->size());
    EXPECT_EQ(0, l2->size());

    o.connect(l2);

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    l1->assign(a, a + 7);
    EXPECT_EQ(7, l1->size());
    EXPECT_EQ(0, l2->size());

    m::basic_observable_forward_list<int, u::u8string>::iterator begin = l1->begin();
    ++begin;
    m::basic_observable_forward_list<int, u::u8string>::iterator end = begin;
    std::advance(end, 5);

    l2->assign(begin, end);
    EXPECT_EQ(7, l1->size());
    EXPECT_EQ(5, l2->size());

    int count = 0;
    for(const int& i : *l2)
    {
        ++count;
        EXPECT_EQ(count + 1, i);
    }
    EXPECT_EQ(5, count);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
    EXPECT_EQ(1, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(5, o.last_change_new_size());
    EXPECT_EQ(5, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(5, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

TEST(std_basic_observable_forward_list_test_suite, test_push_front)
{
    // Test push front
    m::basic_observable_forward_list<int, u::u8string>::ptr l = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    EXPECT_EQ(0, l->size());

    o.connect(l);

    l->push_front(3);
    EXPECT_EQ(1, l->size());

    l->push_front(2);
    EXPECT_EQ(2, l->size());

    l->push_front(1);
    EXPECT_EQ(3, l->size());

    int count = 0;
    for(const int& i : *l)
    {
        ++count;
        EXPECT_EQ(count, i);
    }
    EXPECT_EQ(3, count);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
    EXPECT_EQ(3, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(3, o.last_change_new_size());
    EXPECT_EQ(1, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(3, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

TEST(std_basic_observable_forward_list_test_suite, test_pop_front)
{
    // Test pop front
    m::basic_observable_forward_list<int, u::u8string>::ptr l = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    EXPECT_EQ(0, l->size());

    l->assign(7, 47);
    EXPECT_EQ(7, l->size());

    o.connect(l);

    l->pop_front();
    EXPECT_EQ(6, l->size());

    l->pop_front();
    EXPECT_EQ(5, l->size());

    l->pop_front();
    EXPECT_EQ(4, l->size());

    int count = 0;
    for(const int& i : *l)
    {
        ++count;
        EXPECT_EQ(47, i);
    }
    EXPECT_EQ(4, count);

    EXPECT_EQ(m::notify_container_changed_action::remove, o.last_action());
    EXPECT_EQ(0, o.action_add_count());
    EXPECT_EQ(3, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(4, o.last_change_new_size());
    EXPECT_EQ(0, o.last_change_added());
    EXPECT_EQ(1, o.last_change_removed());
    EXPECT_EQ(0, o.total_change_added());
    EXPECT_EQ(3, o.total_change_removed());
}

TEST(std_basic_observable_forward_list_test_suite, test_insert_after_single_element)
{
    // Test insert after single element
    m::basic_observable_forward_list<int, u::u8string>::ptr l = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    EXPECT_EQ(0, l->size());
    const int a[] = {1, 2, 3, 5, 6, 7};
    l->assign(a, a + 6);
    EXPECT_EQ(6, l->size());

    o.connect(l);

    m::basic_observable_forward_list<int, u::u8string>::iterator it = l->begin();
    std::advance(it, 2);
    l->insert_after(it, 4);
    EXPECT_EQ(7, l->size());

    int count = 0;
    for(const int& i : *l)
    {
        ++count;
        EXPECT_EQ(count, i);
    }
    EXPECT_EQ(7, count);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_basic_observable_forward_list_test_suite, test_insert_after_fill)
{
    // Test insert after fill
    m::basic_observable_forward_list<int, u::u8string>::ptr l = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    EXPECT_EQ(0, l->size());

    l->assign(7, 47);
    EXPECT_EQ(7, l->size());

    o.connect(l);

    m::basic_observable_forward_list<int, u::u8string>::iterator it = l->begin();
    std::advance(it, 3);
    l->insert_after(it, 3, 74);
    EXPECT_EQ(10, l->size());

    it = l->begin();
    EXPECT_EQ(47, *it);
    ++it;
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
    EXPECT_EQ(l->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
    EXPECT_EQ(1, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(10, o.last_change_new_size());
    EXPECT_EQ(3, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(3, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

TEST(std_basic_observable_forward_list_test_suite, test_insert_after_range)
{
    // Test insert after range
    m::basic_observable_forward_list<int, u::u8string>::ptr l1 = m::basic_observable_forward_list<int, u::u8string>::create();
    m::basic_observable_forward_list<int, u::u8string>::ptr l2 = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    EXPECT_EQ(0, l1->size());

    l1->assign(3, 74);
    EXPECT_EQ(3, l1->size());

    EXPECT_EQ(0, l2->size());
    l2->assign(7, 47);
    EXPECT_EQ(7, l2->size());

    o.connect(l2);

    m::basic_observable_forward_list<int, u::u8string>::iterator it = l2->begin();
    std::advance(it, 3);
    l2->insert_after(it, l1->begin(), l1->end());
    EXPECT_EQ(10, l2->size());

    it = l2->begin();
    EXPECT_EQ(47, *it);
    ++it;
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
    EXPECT_EQ(l2->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
    EXPECT_EQ(1, o.action_add_count());
    EXPECT_EQ(0, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(10, o.last_change_new_size());
    EXPECT_EQ(3, o.last_change_added());
    EXPECT_EQ(0, o.last_change_removed());
    EXPECT_EQ(3, o.total_change_added());
    EXPECT_EQ(0, o.total_change_removed());
}

TEST(std_basic_observable_forward_list_test_suite, test_erase_position)
{
    // Test erase position
    m::basic_observable_forward_list<int, u::u8string>::ptr l = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    EXPECT_EQ(0, l->size());

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    l->assign(a, a + 7);
    EXPECT_EQ(7, l->size());

    o.connect(l);

    m::basic_observable_forward_list<int, u::u8string>::iterator it1 = l->begin();
    std::advance(it1, 3);
    m::basic_observable_forward_list<int, u::u8string>::iterator it2 = l->erase_after(it1);
    EXPECT_EQ(6, l->size());

    l->erase_after(it2);
    EXPECT_EQ(5, l->size());

    it1 = l->begin();
    EXPECT_EQ(1, *it1);
    ++it1;
    EXPECT_EQ(2, *it1);
    ++it1;
    EXPECT_EQ(3, *it1);
    ++it1;
    EXPECT_EQ(4, *it1);
    ++it1;
    EXPECT_EQ(6, *it1);
    ++it1;
    EXPECT_EQ(l->end(), it1);

    EXPECT_EQ(m::notify_container_changed_action::remove, o.last_action());
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

TEST(std_basic_observable_forward_list_test_suite, test_erase_range)
{
    // Test erase range
    m::basic_observable_forward_list<int, u::u8string>::ptr l = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    EXPECT_EQ(0, l->size());

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    l->assign(a, a + 7);
    EXPECT_EQ(7, l->size());

    o.connect(l);

    m::basic_observable_forward_list<int, u::u8string>::iterator begin = l->begin();
    ++begin;
    m::basic_observable_forward_list<int, u::u8string>::iterator end = begin;
    std::advance(end, 5);

    l->erase_after(begin, end);
    EXPECT_EQ(3, l->size());

    m::basic_observable_forward_list<int, u::u8string>::iterator it = l->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(7, *it);
    ++it;
    EXPECT_EQ(l->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::remove, o.last_action());
    EXPECT_EQ(0, o.action_add_count());
    EXPECT_EQ(1, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(3, o.last_change_new_size());
    EXPECT_EQ(0, o.last_change_added());
    EXPECT_EQ(4, o.last_change_removed());
    EXPECT_EQ(0, o.total_change_added());
    EXPECT_EQ(4, o.total_change_removed());
}

TEST(std_basic_observable_forward_list_test_suite, test_swap)
{
    // Test swap
    m::basic_observable_forward_list<int, u::u8string>::ptr l1 = m::basic_observable_forward_list<int, u::u8string>::create();
    m::basic_observable_forward_list<int, u::u8string>::ptr l2 = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o1;
    forward_list_observer<int> o2;

    EXPECT_EQ(0, l1->size());
    EXPECT_EQ(0, l2->size());

    l1->assign(5, 1);
    l2->assign(7, 2);
    EXPECT_EQ(5, l1->size());
    EXPECT_EQ(7, l2->size());

    o1.connect(l1);
    o2.connect(l2);

    l1->swap(*l2);
    EXPECT_EQ(7, l1->size());
    EXPECT_EQ(5, l2->size());

    int count = 0;
    for(const int& i : *l1)
    {
        ++count;
        EXPECT_EQ(2, i);
    }
    EXPECT_EQ(7, count);

    count = 0;
    for(const int& i : *l2)
    {
        ++count;
        EXPECT_EQ(1, i);
    }
    EXPECT_EQ(5, count);

    EXPECT_EQ(m::notify_container_changed_action::swap, o1.last_action());
    EXPECT_EQ(0, o1.action_add_count());
    EXPECT_EQ(0, o1.action_remove_count());
    EXPECT_EQ(0, o1.action_reset_count());
    EXPECT_EQ(1, o1.action_swap_count());
    EXPECT_EQ(7, o1.last_change_new_size());
    EXPECT_EQ(7, o1.last_change_added());
    EXPECT_EQ(5, o1.last_change_removed());
    EXPECT_EQ(7, o1.total_change_added());
    EXPECT_EQ(5, o1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::swap, o2.last_action());
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

TEST(std_basic_observable_forward_list_test_suite, test_clear)
{
    // Test clear
    m::basic_observable_forward_list<int, u::u8string>::ptr l = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    EXPECT_EQ(0, l->size());

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    l->assign(a, a + 7);
    EXPECT_EQ(7, l->size());

    o.connect(l);

    l->clear();
    EXPECT_EQ(0, l->size());

    EXPECT_EQ(m::notify_container_changed_action::reset, o.last_action());
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

TEST(std_basic_observable_forward_list_test_suite, test_emplace_after)
{
    // Test emplace after
    m::basic_observable_forward_list<int, u::u8string>::ptr l = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    const int a[] = {1, 2, 3};
    l->assign(a, a + 3);
    EXPECT_EQ(3, l->size());

    o.connect(l);

    m::basic_observable_forward_list<int, u::u8string>::iterator begin = l->begin();
    ++begin;
    m::basic_observable_forward_list<int, u::u8string>::iterator it = l->emplace_after(begin, 4);
    EXPECT_EQ(4, *it);

    it = l->emplace_after(it, 5);
    it = l->emplace_after(it, 6);
    EXPECT_EQ(6, l->size());

    it = l->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(5, *it);
    ++it;
    EXPECT_EQ(6, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(l->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_basic_observable_forward_list_test_suite, test_emplace_back)
{
    // Test emplace back
    m::basic_observable_forward_list<int, u::u8string>::ptr l = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    const int a[] = {1, 2, 3};
    l->assign(a, a + 3);
    EXPECT_EQ(3, l->size());

    o.connect(l);

    l->emplace_front(4);
    l->emplace_front(5);
    l->emplace_front(6);
    EXPECT_EQ(6, l->size());

    m::basic_observable_forward_list<int, u::u8string>::iterator it = l->begin();
    EXPECT_EQ(6, *it);
    ++it;
    EXPECT_EQ(5, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(l->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_basic_observable_forward_list_test_suite, test_emplace_front)
{
    // Test emplace front
    m::basic_observable_forward_list<int, u::u8string>::ptr l = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    const int a[] = {1, 2, 3};
    l->assign(a, a + 3);
    EXPECT_EQ(3, l->size());

    o.connect(l);

    l->emplace_front(4);
    l->emplace_front(5);
    l->emplace_front(6);
    EXPECT_EQ(6, l->size());

    m::basic_observable_forward_list<int, u::u8string>::iterator it = l->begin();
    EXPECT_EQ(6, *it);
    ++it;
    EXPECT_EQ(5, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(l->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_basic_observable_forward_list_test_suite, test_splice_after_entire_forward_list)
{
    // Test splice after entire forward_list
    m::basic_observable_forward_list<int, u::u8string>::ptr l1 = m::basic_observable_forward_list<int, u::u8string>::create();
    m::basic_observable_forward_list<int, u::u8string>::ptr l2 = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o1;
    forward_list_observer<int> o2;

    EXPECT_EQ(0, l1->size());
    EXPECT_EQ(0, l2->size());

    const int a1[] = {1, 2, 3, 4};
    l1->assign(a1, a1 + 4);
    EXPECT_EQ(4, l1->size());

    const int a2[] = {10, 20, 30};
    l2->assign(a2, a2 + 3);
    EXPECT_EQ(3, l2->size());

    o1.connect(l1);
    o2.connect(l2);

    m::basic_observable_forward_list<int, u::u8string>::iterator it1 = l1->begin();
    ++it1;
    EXPECT_EQ(2, *it1);

    l1->splice_after(it1, *l2);
    EXPECT_EQ(7, l1->size());
    EXPECT_EQ(0, l2->size());
    EXPECT_EQ(2, *it1);

    m::basic_observable_forward_list<int, u::u8string>::iterator it = l1->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(10, *it);
    ++it;
    EXPECT_EQ(20, *it);
    ++it;
    EXPECT_EQ(30, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(l1->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, o1.last_action());
    EXPECT_EQ(1, o1.action_add_count());
    EXPECT_EQ(0, o1.action_remove_count());
    EXPECT_EQ(0, o1.action_reset_count());
    EXPECT_EQ(0, o1.action_swap_count());
    EXPECT_EQ(7, o1.last_change_new_size());
    EXPECT_EQ(3, o1.last_change_added());
    EXPECT_EQ(0, o1.last_change_removed());
    EXPECT_EQ(3, o1.total_change_added());
    EXPECT_EQ(0, o1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::remove, o2.last_action());
    EXPECT_EQ(0, o2.action_add_count());
    EXPECT_EQ(1, o2.action_remove_count());
    EXPECT_EQ(0, o2.action_reset_count());
    EXPECT_EQ(0, o2.action_swap_count());
    EXPECT_EQ(0, o2.last_change_new_size());
    EXPECT_EQ(0, o2.last_change_added());
    EXPECT_EQ(3, o2.last_change_removed());
    EXPECT_EQ(0, o2.total_change_added());
    EXPECT_EQ(3, o2.total_change_removed());
}

TEST(std_basic_observable_forward_list_test_suite, test_splice_after_single_element)
{
    // Test splice after single element
    m::basic_observable_forward_list<int, u::u8string>::ptr l1 = m::basic_observable_forward_list<int, u::u8string>::create();
    m::basic_observable_forward_list<int, u::u8string>::ptr l2 = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o1;
    forward_list_observer<int> o2;

    EXPECT_EQ(0, l1->size());
    EXPECT_EQ(0, l2->size());

    const int a1[] = {1};
    l1->assign(a1, a1 + 1);
    EXPECT_EQ(1, l1->size());

    const int a2[] = {10, 20, 30, 2, 3, 4};
    l2->assign(a2, a2 + 6);
    EXPECT_EQ(6, l2->size());

    o1.connect(l1);
    o2.connect(l2);

    m::basic_observable_forward_list<int, u::u8string>::iterator it2 = l2->begin();
    std::advance(it2, 3);
    EXPECT_EQ(2, *it2);

    m::basic_observable_forward_list<int, u::u8string>::iterator it1 = l1->begin();
    l1->splice_after(it1, *l2, it2);
    EXPECT_EQ(2, l1->size());
    EXPECT_EQ(5, l2->size());
    // it1 is invalid
    // it2 is invalid

    it1 = l1->begin();
    EXPECT_EQ(1, *it1);
    ++it1;
    EXPECT_EQ(3, *it1);
    ++it1;
    EXPECT_EQ(l1->end(), it1);

    it2 = l2->begin();
    EXPECT_EQ(10, *it2);
    ++it2;
    EXPECT_EQ(20, *it2);
    ++it2;
    EXPECT_EQ(30, *it2);
    ++it2;
    EXPECT_EQ(2, *it2);
    ++it2;
    EXPECT_EQ(4, *it2);
    ++it2;
    EXPECT_EQ(l2->end(), it2);

    EXPECT_EQ(m::notify_container_changed_action::add, o1.last_action());
    EXPECT_EQ(1, o1.action_add_count());
    EXPECT_EQ(0, o1.action_remove_count());
    EXPECT_EQ(0, o1.action_reset_count());
    EXPECT_EQ(0, o1.action_swap_count());
    EXPECT_EQ(2, o1.last_change_new_size());
    EXPECT_EQ(1, o1.last_change_added());
    EXPECT_EQ(0, o1.last_change_removed());
    EXPECT_EQ(1, o1.total_change_added());
    EXPECT_EQ(0, o1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::remove, o2.last_action());
    EXPECT_EQ(0, o2.action_add_count());
    EXPECT_EQ(1, o2.action_remove_count());
    EXPECT_EQ(0, o2.action_reset_count());
    EXPECT_EQ(0, o2.action_swap_count());
    EXPECT_EQ(5, o2.last_change_new_size());
    EXPECT_EQ(0, o2.last_change_added());
    EXPECT_EQ(1, o2.last_change_removed());
    EXPECT_EQ(0, o2.total_change_added());
    EXPECT_EQ(1, o2.total_change_removed());
}

TEST(std_basic_observable_forward_list_test_suite, test_splice_after_element_range)
{
    // Test splice after element range
    m::basic_observable_forward_list<int, u::u8string>::ptr l1 = m::basic_observable_forward_list<int, u::u8string>::create();
    m::basic_observable_forward_list<int, u::u8string>::ptr l2 = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o1;
    forward_list_observer<int> o2;

    EXPECT_EQ(0, l1->size());
    EXPECT_EQ(0, l2->size());

    const int a1[] = {1, 2, 3, 4};
    l1->assign(a1, a1 + 4);
    EXPECT_EQ(4, l1->size());

    const int a2[] = {10, 20, 30, 40, 50};
    l2->assign(a2, a2 + 5);
    EXPECT_EQ(5, l2->size());

    o1.connect(l1);
    o2.connect(l2);

    m::basic_observable_forward_list<int, u::u8string>::iterator it1 = l1->begin();
    ++it1;
    EXPECT_EQ(2, *it1);

    m::basic_observable_forward_list<int, u::u8string>::iterator it2first = l2->begin();
    ++it2first;
    EXPECT_EQ(20, *it2first);

    m::basic_observable_forward_list<int, u::u8string>::iterator it2last = l2->begin();
    std::advance(it2last, 3);
    EXPECT_EQ(40, *it2last);

    l1->splice_after(it1, *l2, it2first, it2last);
    EXPECT_EQ(5, l1->size());
    EXPECT_EQ(4, l2->size());
    EXPECT_EQ(2, *it1);
    // it2first is invalid?
    // it2last is invalid?

    m::basic_observable_forward_list<int, u::u8string>::iterator it = l1->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(30, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(l1->end(), it);

    it = l2->begin();
    EXPECT_EQ(10, *it);
    ++it;
    EXPECT_EQ(20, *it);
    ++it;
    EXPECT_EQ(40, *it);
    ++it;
    EXPECT_EQ(50, *it);
    ++it;
    EXPECT_EQ(l2->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, o1.last_action());
    EXPECT_EQ(1, o1.action_add_count());
    EXPECT_EQ(0, o1.action_remove_count());
    EXPECT_EQ(0, o1.action_reset_count());
    EXPECT_EQ(0, o1.action_swap_count());
    EXPECT_EQ(5, o1.last_change_new_size());
    EXPECT_EQ(1, o1.last_change_added());
    EXPECT_EQ(0, o1.last_change_removed());
    EXPECT_EQ(1, o1.total_change_added());
    EXPECT_EQ(0, o1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::remove, o2.last_action());
    EXPECT_EQ(0, o2.action_add_count());
    EXPECT_EQ(1, o2.action_remove_count());
    EXPECT_EQ(0, o2.action_reset_count());
    EXPECT_EQ(0, o2.action_swap_count());
    EXPECT_EQ(4, o2.last_change_new_size());
    EXPECT_EQ(0, o2.last_change_added());
    EXPECT_EQ(1, o2.last_change_removed());
    EXPECT_EQ(0, o2.total_change_added());
    EXPECT_EQ(1, o2.total_change_removed());
}

TEST(std_basic_observable_forward_list_test_suite, test_remove)
{
    // Test remove
    m::basic_observable_forward_list<int, u::u8string>::ptr l = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    EXPECT_EQ(0, l->size());

    const int a[] = {10, 20, 47, 30, 47, 47, 40};
    l->assign(a, a + 7);
    EXPECT_EQ(7, l->size());

    o.connect(l);

    l->remove(47);
    EXPECT_EQ(4, l->size());

    m::basic_observable_forward_list<int, u::u8string>::iterator it = l->begin();
    EXPECT_EQ(10, *it);
    ++it;
    EXPECT_EQ(20, *it);
    ++it;
    EXPECT_EQ(30, *it);
    ++it;
    EXPECT_EQ(40, *it);
    ++it;
    EXPECT_EQ(l->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::remove, o.last_action());
    EXPECT_EQ(0, o.action_add_count());
    EXPECT_EQ(1, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(4, o.last_change_new_size());
    EXPECT_EQ(0, o.last_change_added());
    EXPECT_EQ(3, o.last_change_removed());
    EXPECT_EQ(0, o.total_change_added());
    EXPECT_EQ(3, o.total_change_removed());
}

struct is_odd
{
    bool operator()(const int& value) const
    {
        return (value % 2) == 1;
    }
};

TEST(std_basic_observable_forward_list_test_suite, test_remove_if)
{
    // Test remove if
    m::basic_observable_forward_list<int, u::u8string>::ptr l = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    EXPECT_EQ(0, l->size());

    const int a[] = {10, 20, 47, 30, 47, 47, 40};
    l->assign(a, a + 7);
    EXPECT_EQ(7, l->size());

    o.connect(l);

    l->remove_if(is_odd());
    EXPECT_EQ(4, l->size());

    m::basic_observable_forward_list<int, u::u8string>::iterator it = l->begin();
    EXPECT_EQ(10, *it);
    ++it;
    EXPECT_EQ(20, *it);
    ++it;
    EXPECT_EQ(30, *it);
    ++it;
    EXPECT_EQ(40, *it);
    ++it;
    EXPECT_EQ(l->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::remove, o.last_action());
    EXPECT_EQ(0, o.action_add_count());
    EXPECT_EQ(1, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(4, o.last_change_new_size());
    EXPECT_EQ(0, o.last_change_added());
    EXPECT_EQ(3, o.last_change_removed());
    EXPECT_EQ(0, o.total_change_added());
    EXPECT_EQ(3, o.total_change_removed());
}

TEST(std_basic_observable_forward_list_test_suite, test_unique)
{
    // Test unique
    m::basic_observable_forward_list<int, u::u8string>::ptr l = m::basic_observable_forward_list<int, u::u8string>::create();
    forward_list_observer<int> o;

    EXPECT_EQ(0, l->size());

    const int a[] = {10, 20, 47, 30, 47, 47, 40};
    l->assign(a, a + 7);
    EXPECT_EQ(7, l->size());

    o.connect(l);

    l->unique();
    EXPECT_EQ(6, l->size());

    m::basic_observable_forward_list<int, u::u8string>::iterator it = l->begin();
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
    EXPECT_EQ(5, l->size());

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

    EXPECT_EQ(m::notify_container_changed_action::remove, o.last_action());
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

bool same_integral_part(double first, double second)
{
    return (int(first) == int(second));
}

TEST(std_basic_observable_forward_list_test_suite, test_unique_binary_predicate)
{
    // Test unique binary predicate
    m::basic_observable_forward_list<double, u::u8string>::ptr l = m::basic_observable_forward_list<double, u::u8string>::create();
    forward_list_observer<double> o;

    EXPECT_EQ(0, l->size());

    const double a[] = {12.15, 2.72, 73.0, 12.77, 3.14, 12.77, 73.35, 72.25, 15.3, 72.25};
    l->assign(a, a + 10);
    EXPECT_EQ(10, l->size());

    l->sort();
    o.connect(l);

    l->unique();
    EXPECT_EQ(8, l->size());

    l->unique(same_integral_part);
    EXPECT_EQ(6, l->size());

    m::basic_observable_forward_list<double, u::u8string>::iterator it = l->begin();
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

    EXPECT_EQ(m::notify_container_changed_action::remove, o.last_action());
    EXPECT_EQ(0, o.action_add_count());
    EXPECT_EQ(2, o.action_remove_count());
    EXPECT_EQ(0, o.action_reset_count());
    EXPECT_EQ(0, o.action_swap_count());
    EXPECT_EQ(6, o.last_change_new_size());
    EXPECT_EQ(0, o.last_change_added());
    EXPECT_EQ(2, o.last_change_removed());
    EXPECT_EQ(0, o.total_change_added());
    EXPECT_EQ(4, o.total_change_removed());
}

TEST(std_basic_observable_forward_list_test_suite, test_merge)
{
    // Test merge
    m::basic_observable_forward_list<double, u::u8string>::ptr l1 = m::basic_observable_forward_list<double, u::u8string>::create();
    m::basic_observable_forward_list<double, u::u8string>::ptr l2 = m::basic_observable_forward_list<double, u::u8string>::create();
    forward_list_observer<double> o1;
    forward_list_observer<double> o2;

    EXPECT_EQ(0, l1->size());
    EXPECT_EQ(0, l2->size());

    const double a1[] = {3.1, 2.2, 2.9};
    l1->assign(a1, a1 + 3);
    EXPECT_EQ(3, l1->size());

    const double a2[] = {3.7, 7.1, 1.4};
    l2->assign(a2, a2 + 3);
    EXPECT_EQ(3, l2->size());

    o1.connect(l1);
    o2.connect(l2);

    l1->sort();
    l2->sort();

    l1->merge(*l2);
    EXPECT_EQ(6, l1->size());
    EXPECT_EQ(0, l2->size());

    m::basic_observable_forward_list<double, u::u8string>::iterator it = l1->begin();
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

    EXPECT_EQ(m::notify_container_changed_action::add, o1.last_action());
    EXPECT_EQ(1, o1.action_add_count());
    EXPECT_EQ(0, o1.action_remove_count());
    EXPECT_EQ(0, o1.action_reset_count());
    EXPECT_EQ(0, o1.action_swap_count());
    EXPECT_EQ(6, o1.last_change_new_size());
    EXPECT_EQ(3, o1.last_change_added());
    EXPECT_EQ(0, o1.last_change_removed());
    EXPECT_EQ(3, o1.total_change_added());
    EXPECT_EQ(0, o1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::remove, o2.last_action());
    EXPECT_EQ(0, o2.action_add_count());
    EXPECT_EQ(1, o2.action_remove_count());
    EXPECT_EQ(0, o2.action_reset_count());
    EXPECT_EQ(0, o2.action_swap_count());
    EXPECT_EQ(0, o2.last_change_new_size());
    EXPECT_EQ(0, o2.last_change_added());
    EXPECT_EQ(3, o2.last_change_removed());
    EXPECT_EQ(0, o2.total_change_added());
    EXPECT_EQ(3, o2.total_change_removed());
}

struct less_integral_part
{
    bool operator()(double first, double second) const
    {
        return int(first) < int(second);
    }
};

TEST(std_basic_observable_forward_list_test_suite, test_merge_compare_predicate)
{
    // Test merge compare predicate
    m::basic_observable_forward_list<double, u::u8string>::ptr l1 = m::basic_observable_forward_list<double, u::u8string>::create();
    m::basic_observable_forward_list<double, u::u8string>::ptr l2 = m::basic_observable_forward_list<double, u::u8string>::create();
    forward_list_observer<double> o1;
    forward_list_observer<double> o2;

    EXPECT_EQ(0, l1->size());
    EXPECT_EQ(0, l2->size());

    const double a1[] = {3.1, 2.2, 2.9, 3.7, 7.1, 1.4};
    l1->assign(a1, a1 + 6);
    EXPECT_EQ(6, l1->size());

    l2->push_front(2.1);
    EXPECT_EQ(1, l2->size());

    o1.connect(l1);
    o2.connect(l2);

    l1->sort();
    l2->sort();

    l1->merge(*l2, less_integral_part());
    EXPECT_EQ(7, l1->size());
    EXPECT_EQ(0, l2->size());

    m::basic_observable_forward_list<double, u::u8string>::iterator it = l1->begin();
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

    EXPECT_EQ(m::notify_container_changed_action::add, o1.last_action());
    EXPECT_EQ(1, o1.action_add_count());
    EXPECT_EQ(0, o1.action_remove_count());
    EXPECT_EQ(0, o1.action_reset_count());
    EXPECT_EQ(0, o1.action_swap_count());
    EXPECT_EQ(7, o1.last_change_new_size());
    EXPECT_EQ(1, o1.last_change_added());
    EXPECT_EQ(0, o1.last_change_removed());
    EXPECT_EQ(1, o1.total_change_added());
    EXPECT_EQ(0, o1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::remove, o2.last_action());
    EXPECT_EQ(0, o2.action_add_count());
    EXPECT_EQ(1, o2.action_remove_count());
    EXPECT_EQ(0, o2.action_reset_count());
    EXPECT_EQ(0, o2.action_swap_count());
    EXPECT_EQ(0, o2.last_change_new_size());
    EXPECT_EQ(0, o2.last_change_added());
    EXPECT_EQ(1, o2.last_change_removed());
    EXPECT_EQ(0, o2.total_change_added());
    EXPECT_EQ(1, o2.total_change_removed());
}

}

#endif  // Required C++11 feature is not supported by this compiler
