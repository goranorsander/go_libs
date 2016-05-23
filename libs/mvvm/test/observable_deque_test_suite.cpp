//
//  observable_deque_test_suite.cpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <gtest/gtest.h>

#include <go/mvvm.hpp>
#include <go/property.hpp>

namespace m = go::mvvm;
namespace p = go::property;
namespace ph = std::placeholders;
namespace s = go::signals;

namespace
{

template<class T> class deque_observer
{
public:
    typedef typename m::observable_deque<T>::ptr observable_deque_ptr_type;

    virtual ~deque_observer()
    {
    }

    deque_observer()
        : _on_container_changed_slot_key(0)
        , _on_property_changed_slot_key(0)
        , _last_action(m::undefined_notify_container_changed_action)
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

    void connect(observable_deque_ptr_type& c)
    {
        _on_container_changed_slot_key = c->container_changed.connect(std::bind(&deque_observer::on_container_changed, this, ph::_1, ph::_2));
        _on_property_changed_slot_key = c->property_changed.connect(std::bind(&deque_observer::on_property_changed, this, ph::_1, ph::_2));
    }

    void disconnect(observable_deque_ptr_type& c)
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
    s::slot_key_type _on_container_changed_slot_key;
    s::slot_key_type _on_property_changed_slot_key;

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

TEST(std_observable_deque_test_suite, test_assign_range)
{
    // Test assign range
    m::observable_deque<int>::ptr d = m::observable_deque<int>::create();
    deque_observer<int> o;

    EXPECT_EQ(0, d->size());

    o.connect(d);

    d->assign(7, 47);
    EXPECT_EQ(7, d->size());

    int count = 0;
    for(const int& i : *d)
    {
        ++count;
        EXPECT_EQ(47, i);
    }
    EXPECT_EQ(7, count);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
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

TEST(std_observable_deque_test_suite, test_assign_initializer_list)
{
    // Test assign initializer list
    m::observable_deque<int>::ptr d = m::observable_deque<int>::create();
    deque_observer<int> o;

    EXPECT_EQ(0, d->size());

    o.connect(d);

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    d->assign(a, a + 7);
    EXPECT_EQ(7, d->size());

    int count = 0;
    for(const int& i : *d)
    {
        ++count;
        EXPECT_EQ(count, i);
    }
    EXPECT_EQ(7, count);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
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

TEST(std_observable_deque_test_suite, test_assign_fill)
{
    // Test assign fill
    m::observable_deque<int>::ptr d1 = m::observable_deque<int>::create();
    m::observable_deque<int>::ptr d2 = m::observable_deque<int>::create();
    deque_observer<int> o;

    EXPECT_EQ(0, d1->size());
    EXPECT_EQ(0, d2->size());

    o.connect(d2);

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    d1->assign(a, a + 7);
    EXPECT_EQ(7, d1->size());
    EXPECT_EQ(0, d2->size());

    m::observable_deque<int>::iterator it = d1->begin() + 1;

    d2->assign(it, d1->end() - 1);
    EXPECT_EQ(7, d1->size());
    EXPECT_EQ(5, d2->size());

    int count = 0;
    for(const int& i : *d2)
    {
        ++count;
        EXPECT_EQ(count + 1, i);
    }
    EXPECT_EQ(5, count);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
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

TEST(std_observable_deque_test_suite, test_push_back)
{
    // Test push back
    m::observable_deque<int>::ptr d = m::observable_deque<int>::create();
    deque_observer<int> o;

    EXPECT_EQ(0, d->size());

    o.connect(d);

    d->push_back(1);
    EXPECT_EQ(1, d->size());

    d->push_back(2);
    EXPECT_EQ(2, d->size());

    d->push_back(3);
    EXPECT_EQ(3, d->size());

    int count = 0;
    for(const int& i : *d)
    {
        ++count;
        EXPECT_EQ(count, i);
    }
    EXPECT_EQ(3, count);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
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

TEST(std_observable_deque_test_suite, test_push_front)
{
    // Test push front
    m::observable_deque<int>::ptr d = m::observable_deque<int>::create();
    deque_observer<int> o;

    EXPECT_EQ(0, d->size());

    o.connect(d);

    d->push_front(3);
    EXPECT_EQ(1, d->size());

    d->push_front(2);
    EXPECT_EQ(2, d->size());

    d->push_front(1);
    EXPECT_EQ(3, d->size());

    int count = 0;
    for(const int& i : *d)
    {
        ++count;
        EXPECT_EQ(count, i);
    }
    EXPECT_EQ(3, count);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
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

TEST(std_observable_deque_test_suite, test_pop_back)
{
    // Test pop back
    m::observable_deque<int>::ptr d = m::observable_deque<int>::create();
    deque_observer<int> o;

    EXPECT_EQ(0, d->size());

    d->assign(7, 47);
    EXPECT_EQ(7, d->size());

    o.connect(d);

    d->pop_back();
    EXPECT_EQ(6, d->size());

    d->pop_back();
    EXPECT_EQ(5, d->size());

    d->pop_back();
    EXPECT_EQ(4, d->size());

    int count = 0;
    for(const int& i : *d)
    {
        ++count;
        EXPECT_EQ(47, i);
    }
    EXPECT_EQ(4, count);

    EXPECT_EQ(m::notify_container_changed_action_remove, o.last_action());
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

TEST(std_observable_deque_test_suite, test_pop_front)
{
    // Test pop front
    m::observable_deque<int>::ptr d = m::observable_deque<int>::create();
    deque_observer<int> o;

    EXPECT_EQ(0, d->size());

    d->assign(7, 47);
    EXPECT_EQ(7, d->size());

    o.connect(d);

    d->pop_front();
    EXPECT_EQ(6, d->size());

    d->pop_front();
    EXPECT_EQ(5, d->size());

    d->pop_front();
    EXPECT_EQ(4, d->size());

    int count = 0;
    for(const int& i : *d)
    {
        ++count;
        EXPECT_EQ(47, i);
    }
    EXPECT_EQ(4, count);

    EXPECT_EQ(m::notify_container_changed_action_remove, o.last_action());
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

TEST(std_observable_deque_test_suite, test_observable_insert_single_element)
{
    // Test insert single element
    m::observable_deque<int>::ptr d = m::observable_deque<int>::create();
    deque_observer<int> o;

    EXPECT_EQ(0, d->size());
    const int a[] = {1, 2, 4, 5, 6, 7};
    d->assign(a, a + 6);
    EXPECT_EQ(6, d->size());

    o.connect(d);

    m::observable_deque<int>::iterator it = d->begin();
    d->insert(it + 2, 3);
    EXPECT_EQ(7, d->size());

    int count = 0;
    for(const int& i : *d)
    {
        ++count;
        EXPECT_EQ(count, i);
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

TEST(std_observable_deque_test_suite, test_observable_insert_fill)
{
    // Test insert fill
    m::observable_deque<int>::ptr d = m::observable_deque<int>::create();
    deque_observer<int> o;

    EXPECT_EQ(0, d->size());

    d->assign(7, 47);
    EXPECT_EQ(7, d->size());

    o.connect(d);

    m::observable_deque<int>::iterator it = d->begin();
    d->insert(it + 3, 3, 74);
    EXPECT_EQ(10, d->size());

    EXPECT_EQ(47, (*d)[0]);
    EXPECT_EQ(47, (*d)[1]);
    EXPECT_EQ(47, (*d)[2]);
    EXPECT_EQ(74, (*d)[3]);
    EXPECT_EQ(74, (*d)[4]);
    EXPECT_EQ(74, (*d)[5]);
    EXPECT_EQ(47, (*d)[6]);
    EXPECT_EQ(47, (*d)[7]);
    EXPECT_EQ(47, (*d)[8]);
    EXPECT_EQ(47, (*d)[9]);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
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

TEST(std_observable_deque_test_suite, test_observable_insert_range)
{
    // Test insert range
    m::observable_deque<int>::ptr d1 = m::observable_deque<int>::create();
    m::observable_deque<int>::ptr d2 = m::observable_deque<int>::create();
    deque_observer<int> o;

    EXPECT_EQ(0, d1->size());

    d1->assign(3, 74);
    EXPECT_EQ(3, d1->size());

    EXPECT_EQ(0, d2->size());
    d2->assign(7, 47);
    EXPECT_EQ(7, d2->size());

    o.connect(d2);

    m::observable_deque<int>::iterator it = d2->begin();
    d2->insert(it + 3, d1->begin(), d1->end());
    EXPECT_EQ(10, d2->size());

    EXPECT_EQ(47, (*d2)[0]);
    EXPECT_EQ(47, (*d2)[1]);
    EXPECT_EQ(47, (*d2)[2]);
    EXPECT_EQ(74, (*d2)[3]);
    EXPECT_EQ(74, (*d2)[4]);
    EXPECT_EQ(74, (*d2)[5]);
    EXPECT_EQ(47, (*d2)[6]);
    EXPECT_EQ(47, (*d2)[7]);
    EXPECT_EQ(47, (*d2)[8]);
    EXPECT_EQ(47, (*d2)[9]);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
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

TEST(std_observable_deque_test_suite, test_erase_position)
{
    // Test erase position
    m::observable_deque<int>::ptr d = m::observable_deque<int>::create();
    deque_observer<int> o;

    EXPECT_EQ(0, d->size());

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    d->assign(a, a + 7);
    EXPECT_EQ(7, d->size());

    o.connect(d);

    m::observable_deque<int>::iterator it1 = d->begin();
    m::observable_deque<int>::iterator it2 = d->erase(it1 + 3);
    EXPECT_EQ(6, d->size());

    d->erase(it2);
    EXPECT_EQ(5, d->size());

    EXPECT_EQ(1, (*d)[0]);
    EXPECT_EQ(2, (*d)[1]);
    EXPECT_EQ(3, (*d)[2]);
    EXPECT_EQ(6, (*d)[3]);
    EXPECT_EQ(7, (*d)[4]);

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

TEST(std_observable_deque_test_suite, test_erase_range)
{
    // Test erase range
    m::observable_deque<int>::ptr d = m::observable_deque<int>::create();
    deque_observer<int> o;

    EXPECT_EQ(0, d->size());

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    d->assign(a, a + 7);
    EXPECT_EQ(7, d->size());

    o.connect(d);

    d->erase(d->begin() + 1, d->end() - 1);
    EXPECT_EQ(2, d->size());

    EXPECT_EQ(1, (*d)[0]);
    EXPECT_EQ(7, (*d)[1]);

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

TEST(std_observable_deque_test_suite, test_swap)
{
    // Test swap
    m::observable_deque<int>::ptr d1 = m::observable_deque<int>::create();
    m::observable_deque<int>::ptr d2 = m::observable_deque<int>::create();
    deque_observer<int> o1;
    deque_observer<int> o2;

    EXPECT_EQ(0, d1->size());
    EXPECT_EQ(0, d2->size());

    d1->assign(5, 1);
    d2->assign(7, 2);
    EXPECT_EQ(5, d1->size());
    EXPECT_EQ(7, d2->size());

    o1.connect(d1);
    o2.connect(d2);

    d1->swap(*d2);
    EXPECT_EQ(7, d1->size());
    EXPECT_EQ(5, d2->size());

    int count = 0;
    for(const int& i : *d1)
    {
        ++count;
        EXPECT_EQ(2, i);
    }
    EXPECT_EQ(7, count);

    count = 0;
    for(const int& i : *d2)
    {
        ++count;
        EXPECT_EQ(1, i);
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

TEST(std_observable_deque_test_suite, test_clear)
{
    // Test clear
    m::observable_deque<int>::ptr d = m::observable_deque<int>::create();
    deque_observer<int> o;

    EXPECT_EQ(0, d->size());

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    d->assign(a, a + 7);
    EXPECT_EQ(7, d->size());

    o.connect(d);

    d->clear();
    EXPECT_EQ(0, d->size());

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

TEST(std_observable_deque_test_suite, test_observable_emplace)
{
    // Test emplace
    m::observable_deque<int>::ptr d = m::observable_deque<int>::create();
    deque_observer<int> o;

    const int a[] = {1, 2, 3};
    d->assign(a, a + 3);
    EXPECT_EQ(3, d->size());

    o.connect(d);

    m::observable_deque<int>::iterator it = d->emplace(d->begin() + 1, 4);
    EXPECT_EQ(4, *it);

    d->emplace(it, 5);
    d->emplace(d->end(), 6);
    EXPECT_EQ(6, d->size());

    EXPECT_EQ(1, (*d)[0]);
    EXPECT_EQ(5, (*d)[1]);
    EXPECT_EQ(4, (*d)[2]);
    EXPECT_EQ(2, (*d)[3]);
    EXPECT_EQ(3, (*d)[4]);
    EXPECT_EQ(6, (*d)[5]);

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

TEST(std_observable_deque_test_suite, test_observable_emplace_back)
{
    // Test emplace back
    m::observable_deque<int>::ptr d = m::observable_deque<int>::create();
    deque_observer<int> o;

    const int a[] = {1, 2, 3};
    d->assign(a, a + 3);
    EXPECT_EQ(3, d->size());

    o.connect(d);

    d->emplace_back(4);
    d->emplace_back(5);
    d->emplace_back(6);
    EXPECT_EQ(6, d->size());

    EXPECT_EQ(1, (*d)[0]);
    EXPECT_EQ(2, (*d)[1]);
    EXPECT_EQ(3, (*d)[2]);
    EXPECT_EQ(4, (*d)[3]);
    EXPECT_EQ(5, (*d)[4]);
    EXPECT_EQ(6, (*d)[5]);

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

TEST(std_observable_deque_test_suite, test_observable_emplace_front)
{
    // Test emplace front
    m::observable_deque<int>::ptr d = m::observable_deque<int>::create();
    deque_observer<int> o;

    const int a[] = {1, 2, 3};
    d->assign(a, a + 3);
    EXPECT_EQ(3, d->size());

    o.connect(d);

    d->emplace_front(4);
    d->emplace_front(5);
    d->emplace_front(6);
    EXPECT_EQ(6, d->size());

    EXPECT_EQ(6, (*d)[0]);
    EXPECT_EQ(5, (*d)[1]);
    EXPECT_EQ(4, (*d)[2]);
    EXPECT_EQ(1, (*d)[3]);
    EXPECT_EQ(2, (*d)[4]);
    EXPECT_EQ(3, (*d)[5]);

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

}
