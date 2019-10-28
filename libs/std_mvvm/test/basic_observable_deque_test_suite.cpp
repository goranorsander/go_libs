//
//  basic_observable_deque_test_suite.cpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_NOEXCEPT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_basic_observable_deque_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>
#include <go/namespace_alias.hpp>
#include <go/utility.hpp>

namespace
{

template<class T> class deque_observer
{
public:
    typedef deque_observer<T> this_type;
    typedef typename m::basic_observable_deque<T, u::u8string>::ptr observable_deque_ptr_type;

    virtual ~deque_observer() GO_DEFAULT_DESTRUCTOR

    deque_observer()
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

    void connect(observable_deque_ptr_type& c)
    {
        _on_container_changed_slot_key = c->container_changed.connect(std::bind(&this_type::on_container_changed, this, ph::_1, ph::_2));
        _on_property_changed_slot_key = c->property_changed.connect(std::bind(&this_type::on_property_changed, this, ph::_1, ph::_2));
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

TEST(std_basic_observable_deque_test_suite, test_assign_range)
{
    // Test assign range
    m::basic_observable_deque<int, u::u8string>::ptr d = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    EXPECT_EQ(0u, d->size());

    o.connect(d);

    d->assign(7, 47);
    EXPECT_EQ(7u, d->size());

    unsigned int count = 0u;
    for(const int& i : *d)
    {
        ++count;
        EXPECT_EQ(47, i);
    }
    EXPECT_EQ(7u, count);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_basic_observable_deque_test_suite, test_assign_initializer_list)
{
    // Test assign initializer list
    m::basic_observable_deque<int, u::u8string>::ptr d = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    EXPECT_EQ(0u, d->size());

    o.connect(d);

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    d->assign(a, a + 7);
    EXPECT_EQ(7u, d->size());

    unsigned int count = 0u;
    for(const int& i : *d)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i);
    }
    EXPECT_EQ(7u, count);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_basic_observable_deque_test_suite, test_assign_fill)
{
    // Test assign fill
    m::basic_observable_deque<int, u::u8string>::ptr d1 = m::basic_observable_deque<int, u::u8string>::create();
    m::basic_observable_deque<int, u::u8string>::ptr d2 = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    EXPECT_EQ(0u, d1->size());
    EXPECT_EQ(0u, d2->size());

    o.connect(d2);

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    d1->assign(a, a + 7);
    EXPECT_EQ(7u, d1->size());
    EXPECT_EQ(0u, d2->size());

    m::basic_observable_deque<int, u::u8string>::iterator it = d1->begin() + 1;

    d2->assign(it, d1->end() - 1);
    EXPECT_EQ(7u, d1->size());
    EXPECT_EQ(5u, d2->size());

    unsigned int count = 0u;
    for(const int& i : *d2)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count) + 1, i);
    }
    EXPECT_EQ(5u, count);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_basic_observable_deque_test_suite, test_push_back)
{
    // Test push back
    m::basic_observable_deque<int, u::u8string>::ptr d = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    EXPECT_EQ(0u, d->size());

    o.connect(d);

    d->push_back(1);
    EXPECT_EQ(1u, d->size());

    d->push_back(2);
    EXPECT_EQ(2u, d->size());

    d->push_back(3);
    EXPECT_EQ(3u, d->size());

    unsigned int count = 0u;
    for(const int& i : *d)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i);
    }
    EXPECT_EQ(3u, count);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_basic_observable_deque_test_suite, test_push_front)
{
    // Test push front
    m::basic_observable_deque<int, u::u8string>::ptr d = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    EXPECT_EQ(0u, d->size());

    o.connect(d);

    d->push_front(3);
    EXPECT_EQ(1u, d->size());

    d->push_front(2);
    EXPECT_EQ(2u, d->size());

    d->push_front(1);
    EXPECT_EQ(3u, d->size());

    unsigned int count = 0u;
    for(const int& i : *d)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i);
    }
    EXPECT_EQ(3u, count);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_basic_observable_deque_test_suite, test_pop_back)
{
    // Test pop back
    m::basic_observable_deque<int, u::u8string>::ptr d = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    EXPECT_EQ(0u, d->size());

    d->assign(7, 47);
    EXPECT_EQ(7u, d->size());

    o.connect(d);

    d->pop_back();
    EXPECT_EQ(6u, d->size());

    d->pop_back();
    EXPECT_EQ(5u, d->size());

    d->pop_back();
    EXPECT_EQ(4u, d->size());

    unsigned int count = 0u;
    for(const int& i : *d)
    {
        ++count;
        EXPECT_EQ(47, i);
    }
    EXPECT_EQ(4u, count);

    EXPECT_EQ(m::notify_container_changed_action::remove, o.last_action());
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

TEST(std_basic_observable_deque_test_suite, test_pop_front)
{
    // Test pop front
    m::basic_observable_deque<int, u::u8string>::ptr d = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    EXPECT_EQ(0u, d->size());

    d->assign(7, 47);
    EXPECT_EQ(7u, d->size());

    o.connect(d);

    d->pop_front();
    EXPECT_EQ(6u, d->size());

    d->pop_front();
    EXPECT_EQ(5u, d->size());

    d->pop_front();
    EXPECT_EQ(4u, d->size());

    unsigned int count = 0u;
    for(const int& i : *d)
    {
        ++count;
        EXPECT_EQ(47, i);
    }
    EXPECT_EQ(4u, count);

    EXPECT_EQ(m::notify_container_changed_action::remove, o.last_action());
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

TEST(std_basic_observable_deque_test_suite, test_insert_single_element)
{
    // Test insert single element
    m::basic_observable_deque<int, u::u8string>::ptr d = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    EXPECT_EQ(0u, d->size());
    const int a[] = {1, 2, 4, 5, 6, 7};
    d->assign(a, a + 6);
    EXPECT_EQ(6u, d->size());

    o.connect(d);

    m::basic_observable_deque<int, u::u8string>::iterator it = d->begin();
    d->insert(it + 2, 3);
    EXPECT_EQ(7u, d->size());

    unsigned int count = 0u;
    for(const int& i : *d)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i);
    }
    EXPECT_EQ(7u, count);

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

TEST(std_basic_observable_deque_test_suite, test_insert_fill)
{
    // Test insert fill
    m::basic_observable_deque<int, u::u8string>::ptr d = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    EXPECT_EQ(0u, d->size());

    d->assign(7, 47);
    EXPECT_EQ(7u, d->size());

    o.connect(d);

    m::basic_observable_deque<int, u::u8string>::iterator it = d->begin();
    d->insert(it + 3, 3, 74);
    EXPECT_EQ(10u, d->size());

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

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_basic_observable_deque_test_suite, test_insert_range)
{
    // Test insert range
    m::basic_observable_deque<int, u::u8string>::ptr d1 = m::basic_observable_deque<int, u::u8string>::create();
    m::basic_observable_deque<int, u::u8string>::ptr d2 = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    EXPECT_EQ(0u, d1->size());

    d1->assign(3, 74);
    EXPECT_EQ(3u, d1->size());

    EXPECT_EQ(0u, d2->size());
    d2->assign(7, 47);
    EXPECT_EQ(7u, d2->size());

    o.connect(d2);

    m::basic_observable_deque<int, u::u8string>::iterator it = d2->begin();
    d2->insert(it + 3, d1->begin(), d1->end());
    EXPECT_EQ(10u, d2->size());

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

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_basic_observable_deque_test_suite, test_erase_position)
{
    // Test erase position
    m::basic_observable_deque<int, u::u8string>::ptr d = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    EXPECT_EQ(0u, d->size());

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    d->assign(a, a + 7);
    EXPECT_EQ(7u, d->size());

    o.connect(d);

    m::basic_observable_deque<int, u::u8string>::iterator it1 = d->begin();
    m::basic_observable_deque<int, u::u8string>::iterator it2 = d->erase(it1 + 3);
    EXPECT_EQ(6u, d->size());

    d->erase(it2);
    EXPECT_EQ(5u, d->size());

    EXPECT_EQ(1, (*d)[0]);
    EXPECT_EQ(2, (*d)[1]);
    EXPECT_EQ(3, (*d)[2]);
    EXPECT_EQ(6, (*d)[3]);
    EXPECT_EQ(7, (*d)[4]);

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

TEST(std_basic_observable_deque_test_suite, test_erase_range)
{
    // Test erase range
    m::basic_observable_deque<int, u::u8string>::ptr d = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    EXPECT_EQ(0u, d->size());

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    d->assign(a, a + 7);
    EXPECT_EQ(7u, d->size());

    o.connect(d);

    d->erase(d->begin() + 1, d->end() - 1);
    EXPECT_EQ(2u, d->size());

    EXPECT_EQ(1, (*d)[0]);
    EXPECT_EQ(7, (*d)[1]);

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

TEST(std_basic_observable_deque_test_suite, test_swap)
{
    // Test swap
    m::basic_observable_deque<int, u::u8string>::ptr d1 = m::basic_observable_deque<int, u::u8string>::create();
    m::basic_observable_deque<int, u::u8string>::ptr d2 = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o1;
    deque_observer<int> o2;

    EXPECT_EQ(0u, d1->size());
    EXPECT_EQ(0u, d2->size());

    d1->assign(5, 1);
    d2->assign(7, 2);
    EXPECT_EQ(5u, d1->size());
    EXPECT_EQ(7u, d2->size());

    o1.connect(d1);
    o2.connect(d2);

    d1->swap(*d2);
    EXPECT_EQ(7u, d1->size());
    EXPECT_EQ(5u, d2->size());

    unsigned int count = 0u;
    for(const int& i : *d1)
    {
        ++count;
        EXPECT_EQ(2, i);
    }
    EXPECT_EQ(7u, count);

    count = 0;
    for(const int& i : *d2)
    {
        ++count;
        EXPECT_EQ(1, i);
    }
    EXPECT_EQ(5u, count);

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

TEST(std_basic_observable_deque_test_suite, test_clear)
{
    // Test clear
    m::basic_observable_deque<int, u::u8string>::ptr d = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    EXPECT_EQ(0u, d->size());

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    d->assign(a, a + 7);
    EXPECT_EQ(7u, d->size());

    o.connect(d);

    d->clear();
    EXPECT_EQ(0u, d->size());

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

TEST(std_basic_observable_deque_test_suite, test_emplace)
{
    // Test emplace
    m::basic_observable_deque<int, u::u8string>::ptr d = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    const int a[] = {1, 2, 3};
    d->assign(a, a + 3);
    EXPECT_EQ(3u, d->size());

    o.connect(d);

    m::basic_observable_deque<int, u::u8string>::iterator it = d->emplace(d->begin() + 1, 4);
    EXPECT_EQ(4, *it);

    d->emplace(it, 5);
    d->emplace(d->end(), 6);
    EXPECT_EQ(6u, d->size());

    EXPECT_EQ(1, (*d)[0]);
    EXPECT_EQ(5, (*d)[1]);
    EXPECT_EQ(4, (*d)[2]);
    EXPECT_EQ(2, (*d)[3]);
    EXPECT_EQ(3, (*d)[4]);
    EXPECT_EQ(6, (*d)[5]);

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

TEST(std_basic_observable_deque_test_suite, test_emplace_back)
{
    // Test emplace back
    m::basic_observable_deque<int, u::u8string>::ptr d = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    const int a[] = {1, 2, 3};
    d->assign(a, a + 3);
    EXPECT_EQ(3u, d->size());

    o.connect(d);

    d->emplace_back(4);
    d->emplace_back(5);
    d->emplace_back(6);
    EXPECT_EQ(6u, d->size());

    EXPECT_EQ(1, (*d)[0]);
    EXPECT_EQ(2, (*d)[1]);
    EXPECT_EQ(3, (*d)[2]);
    EXPECT_EQ(4, (*d)[3]);
    EXPECT_EQ(5, (*d)[4]);
    EXPECT_EQ(6, (*d)[5]);

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

TEST(std_basic_observable_deque_test_suite, test_emplace_front)
{
    // Test emplace front
    m::basic_observable_deque<int, u::u8string>::ptr d = m::basic_observable_deque<int, u::u8string>::create();
    deque_observer<int> o;

    const int a[] = {1, 2, 3};
    d->assign(a, a + 3);
    EXPECT_EQ(3u, d->size());

    o.connect(d);

    d->emplace_front(4);
    d->emplace_front(5);
    d->emplace_front(6);
    EXPECT_EQ(6u, d->size());

    EXPECT_EQ(6, (*d)[0]);
    EXPECT_EQ(5, (*d)[1]);
    EXPECT_EQ(4, (*d)[2]);
    EXPECT_EQ(1, (*d)[3]);
    EXPECT_EQ(2, (*d)[4]);
    EXPECT_EQ(3, (*d)[5]);

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
