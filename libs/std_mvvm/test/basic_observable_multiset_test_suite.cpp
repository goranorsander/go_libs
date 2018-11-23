//
//  basic_observable_multiset_test_suite.cpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_NOEXCEPT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_basic_observable_multiset_test_suite, cpp11_not_supported) {}
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

template<class T> class multiset_observer
{
public:
    typedef multiset_observer<T> this_type;
    typedef typename m::basic_observable_multiset<T, u::u8string>::ptr observable_multiset_ptr_type;

    virtual ~multiset_observer() GO_DEFAULT_DESTRUCTOR

    multiset_observer()
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

    void connect(observable_multiset_ptr_type& c)
    {
        _on_container_changed_slot_key = c->container_changed.connect(std::bind(&this_type::on_container_changed, this, ph::_1, ph::_2));
        _on_property_changed_slot_key = c->property_changed.connect(std::bind(&this_type::on_property_changed, this, ph::_1, ph::_2));
    }

    void disconnect(observable_multiset_ptr_type& c)
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

TEST(std_basic_observable_multiset_test_suite, test_insert_single_element)
{
    // Test insert single element
    m::basic_observable_multiset<int, u::u8string>::ptr s = m::basic_observable_multiset<int, u::u8string>::create();
    multiset_observer<int> o;

    EXPECT_EQ(0, s->size());
    const std::initializer_list<int> il = {1, 2, 4, 5, 6, 7};
    *s = il;
    EXPECT_EQ(6, s->size());

    o.connect(s);

    s->insert(3);
    EXPECT_EQ(7, s->size());

    int count = 0;
    for(const int& i : *s)
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

TEST(std_basic_observable_multiset_test_suite, test_insert_single_element_with_hint)
{
    // Test insert single element with hint
    m::basic_observable_multiset<int, u::u8string>::ptr s = m::basic_observable_multiset<int, u::u8string>::create();
    multiset_observer<int> o;

    EXPECT_EQ(0, s->size());
    const std::initializer_list<int> il = {1, 2, 5, 7};
    *s = il;
    EXPECT_EQ(4, s->size());

    o.connect(s);

    m::basic_observable_multiset<int, u::u8string>::iterator it = s->insert(s->begin(), 3);
    EXPECT_EQ(5, s->size());

    it = s->insert(it, 4);
    EXPECT_EQ(6, s->size());

    it = s->insert(it, 4);
    EXPECT_EQ(7, s->size());

    it = s->insert(it, 6);
    EXPECT_EQ(8, s->size());

    it = s->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(5, *it);
    ++it;
    EXPECT_EQ(6, *it);
    ++it;
    EXPECT_EQ(7, *it);
    ++it;
    EXPECT_EQ(s->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_basic_observable_multiset_test_suite, test_insert_range)
{
    // Test insert range
    m::basic_observable_multiset<int, u::u8string>::ptr s1 = m::basic_observable_multiset<int, u::u8string>::create();
    m::basic_observable_multiset<int, u::u8string>::ptr s2 = m::basic_observable_multiset<int, u::u8string>::create();
    multiset_observer<int> o;

    EXPECT_EQ(0, s1->size());
    EXPECT_EQ(0, s2->size());

    const std::initializer_list<int> il1 = {1, 2, 5, 7};
    *s1 = il1;
    EXPECT_EQ(4, s1->size());

    const std::initializer_list<int> il2 = {3, 4, 6};
    *s2 = il2;
    EXPECT_EQ(3, s2->size());

    o.connect(s2);

    s2->insert(s1->begin(), s1->end());
    EXPECT_EQ(7, s2->size());

    m::basic_observable_multiset<int, u::u8string>::iterator it = s2->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(5, *it);
    ++it;
    EXPECT_EQ(6, *it);
    ++it;
    EXPECT_EQ(7, *it);
    ++it;
    EXPECT_EQ(s2->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_basic_observable_multiset_test_suite, test_insert_initializer_list)
{
    // Test insert initializer list
    m::basic_observable_multiset<int, u::u8string>::ptr s = m::basic_observable_multiset<int, u::u8string>::create();
    multiset_observer<int> o;

    EXPECT_EQ(0, s->size());

    const std::initializer_list<int> il1 = {1, 2, 5, 7};
    *s = il1;
    EXPECT_EQ(4, s->size());

    const std::initializer_list<int> il2 = {3, 4, 6};
    EXPECT_EQ(3, il2.size());

    o.connect(s);

    s->insert(il2);
    EXPECT_EQ(7, s->size());

    m::basic_observable_multiset<int, u::u8string>::iterator it = s->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(5, *it);
    ++it;
    EXPECT_EQ(6, *it);
    ++it;
    EXPECT_EQ(7, *it);
    ++it;
    EXPECT_EQ(s->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_basic_observable_multiset_test_suite, test_erase_position)
{
    // Test erase position
    m::basic_observable_multiset<int, u::u8string>::ptr s = m::basic_observable_multiset<int, u::u8string>::create();
    multiset_observer<int> o;

    EXPECT_EQ(0, s->size());

    const std::initializer_list<int> il = {1, 2, 3, 4, 5, 6, 7};
    *s = il;
    EXPECT_EQ(7, s->size());

    o.connect(s);

    m::basic_observable_multiset<int, u::u8string>::iterator it1 = s->begin();
    std::advance(it1, 3);
    m::basic_observable_multiset<int, u::u8string>::iterator it2 = s->erase(it1);
    EXPECT_EQ(6, s->size());

    s->erase(it2);
    EXPECT_EQ(5, s->size());

    it1 = s->begin();
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
    EXPECT_EQ(s->end(), it1);

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

TEST(std_basic_observable_multiset_test_suite, test_erase_value)
{
    // Test erase value
    m::basic_observable_multiset<int, u::u8string>::ptr s = m::basic_observable_multiset<int, u::u8string>::create();
    multiset_observer<int> o;

    EXPECT_EQ(0, s->size());

    const std::initializer_list<int> il = {1, 2, 3, 4, 5, 6, 7};
    *s = il;
    EXPECT_EQ(7, s->size());

    o.connect(s);

    s->erase(4);
    EXPECT_EQ(6, s->size());

    s->erase(5);
    EXPECT_EQ(5, s->size());

    m::basic_observable_multiset<int, u::u8string>::iterator it = s->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(6, *it);
    ++it;
    EXPECT_EQ(7, *it);
    ++it;
    EXPECT_EQ(s->end(), it);

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

TEST(std_basic_observable_multiset_test_suite, test_erase_range)
{
    // Test erase range
    m::basic_observable_multiset<int, u::u8string>::ptr s = m::basic_observable_multiset<int, u::u8string>::create();
    multiset_observer<int> o;

    EXPECT_EQ(0, s->size());

    const std::initializer_list<int> il = {1, 2, 3, 4, 5, 6, 7};
    *s = il;
    EXPECT_EQ(7, s->size());

    o.connect(s);

    m::basic_observable_multiset<int, u::u8string>::iterator begin = s->begin();
    ++begin;
    m::basic_observable_multiset<int, u::u8string>::iterator end = s->end();
    --end;

    s->erase(begin, end);
    EXPECT_EQ(2, s->size());

    m::basic_observable_multiset<int, u::u8string>::iterator it = s->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(7, *it);
    ++it;
    EXPECT_EQ(s->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::remove, o.last_action());
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

TEST(std_basic_observable_multiset_test_suite, test_swap)
{
    // Test swap
    m::basic_observable_multiset<int, u::u8string>::ptr s1 = m::basic_observable_multiset<int, u::u8string>::create();
    m::basic_observable_multiset<int, u::u8string>::ptr s2 = m::basic_observable_multiset<int, u::u8string>::create();
    multiset_observer<int> o1;
    multiset_observer<int> o2;

    EXPECT_EQ(0, s1->size());
    EXPECT_EQ(0, s2->size());

    const std::initializer_list<int> il1 = {1, 2, 3, 4, 5};
    const std::initializer_list<int> il2 = {10, 20, 30, 40, 50, 60, 70};
    *s1 = il1;
    *s2 = il2;
    EXPECT_EQ(5, s1->size());
    EXPECT_EQ(7, s2->size());

    o1.connect(s1);
    o2.connect(s2);

    s1->swap(*s2);
    EXPECT_EQ(7, s1->size());
    EXPECT_EQ(5, s2->size());

    int count = 0;
    for(const int& i : *s1)
    {
        ++count;
        EXPECT_EQ(count*10, i);
    }
    EXPECT_EQ(7, count);

    count = 0;
    for(const int& i : *s2)
    {
        ++count;
        EXPECT_EQ(count, i);
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

TEST(std_basic_observable_multiset_test_suite, test_clear)
{
    // Test clear
    m::basic_observable_multiset<int, u::u8string>::ptr s = m::basic_observable_multiset<int, u::u8string>::create();
    multiset_observer<int> o;

    EXPECT_EQ(0, s->size());

    const std::initializer_list<int> il = {1, 2, 3, 4, 5, 6, 7};
    *s = il;
    EXPECT_EQ(7, s->size());

    o.connect(s);

    s->clear();
    EXPECT_EQ(0, s->size());

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

TEST(std_basic_observable_multiset_test_suite, test_emplace)
{
    // Test emplace
    m::basic_observable_multiset<int, u::u8string>::ptr s = m::basic_observable_multiset<int, u::u8string>::create();
    multiset_observer<int> o;

    const std::initializer_list<int> il = {1, 2, 3};
    *s = il;
    EXPECT_EQ(3, s->size());

    o.connect(s);

    m::basic_observable_multiset<int, u::u8string>::iterator it = s->emplace(4);
    EXPECT_EQ(4, *it);

    it = s->emplace(5);
    EXPECT_EQ(5, *it);

    it = s->emplace(4);
    EXPECT_EQ(4, *it);

    it = s->emplace(6);
    EXPECT_EQ(6, *it);

    it = s->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(5, *it);
    ++it;
    EXPECT_EQ(6, *it);
    ++it;
    EXPECT_EQ(s->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_basic_observable_multiset_test_suite, test_emplace_hint)
{
    // Test emplace hint
    m::basic_observable_multiset<int, u::u8string>::ptr s = m::basic_observable_multiset<int, u::u8string>::create();
    multiset_observer<int> o;

    const std::initializer_list<int> il = {1, 2, 5};
    *s = il;
    EXPECT_EQ(3, s->size());

    o.connect(s);

    m::basic_observable_multiset<int, u::u8string>::iterator it = s->emplace_hint(s->begin(), 3);
    EXPECT_EQ(3, *it);

    it = s->emplace_hint(it, 4);
    EXPECT_EQ(4, *it);

    it = s->emplace_hint(it, 4);
    EXPECT_EQ(4, *it);

    it = s->emplace_hint(it, 6);
    EXPECT_EQ(6, *it);

    it = s->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(5, *it);
    ++it;
    EXPECT_EQ(6, *it);
    ++it;
    EXPECT_EQ(s->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

}

#endif  // Required C++11 feature is not supported by this compiler
