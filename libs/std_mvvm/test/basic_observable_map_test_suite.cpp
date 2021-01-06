//
//  basic_observable_map_test_suite.cpp
//
//  Copyright 2018-2021 Göran Orsander
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
TEST(std_basic_observable_map_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>
#include <go/namespace_alias.hpp>
#include <go/utility.hpp>

namespace
{

template<class K, class T> class map_observer
{
public:
    typedef map_observer<K, T> this_type;
    typedef typename m::basic_observable_map<K, T, s::u8string>::ptr observable_map_ptr_type;

    virtual ~map_observer() GO_DEFAULT_DESTRUCTOR

    map_observer()
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

    void connect(observable_map_ptr_type& c)
    {
        _on_container_changed_slot_key = c->container_changed.connect(std::bind(&this_type::on_container_changed, this, ph::_1, ph::_2));
        _on_property_changed_slot_key = c->property_changed.connect(std::bind(&this_type::on_property_changed, this, ph::_1, ph::_2));
    }

    void disconnect(observable_map_ptr_type& c)
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
    si::slot_key _on_container_changed_slot_key;
    si::slot_key _on_property_changed_slot_key;

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

TEST(std_basic_observable_map_test_suite, test_insert_single_element)
{
    // Test insert single element
    m::basic_observable_map<int, int, s::u8string>::ptr m = m::basic_observable_map<int, int, s::u8string>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());
    const std::initializer_list<m::basic_observable_map<int, int, s::u8string>::value_type> il =
    {
        m::basic_observable_map<int, int, s::u8string>::value_type(1, 10),
        m::basic_observable_map<int, int, s::u8string>::value_type(2, 20),
        m::basic_observable_map<int, int, s::u8string>::value_type(4, 40),
        m::basic_observable_map<int, int, s::u8string>::value_type(5, 50),
        m::basic_observable_map<int, int, s::u8string>::value_type(6, 60),
        m::basic_observable_map<int, int, s::u8string>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(6u, m->size());

    o.connect(m);

    m->insert(m::basic_observable_map<int, int, s::u8string>::value_type(3, 30));
    EXPECT_EQ(7u, m->size());

    unsigned int count = 0u;
    for(const m::basic_observable_map<int, int, s::u8string>::value_type& i : *m)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i.first);
        EXPECT_EQ(static_cast<int>(count)*10, i.second);
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

TEST(std_basic_observable_map_test_suite, test_insert_single_element_with_hint)
{
    // Test insert single element with hint
    m::basic_observable_map<int, int, s::u8string>::ptr m = m::basic_observable_map<int, int, s::u8string>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());
    const std::initializer_list<m::basic_observable_map<int, int, s::u8string>::value_type> il =
    {
        m::basic_observable_map<int, int, s::u8string>::value_type(1, 10),
        m::basic_observable_map<int, int, s::u8string>::value_type(2, 20),
        m::basic_observable_map<int, int, s::u8string>::value_type(5, 50),
        m::basic_observable_map<int, int, s::u8string>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(4u, m->size());

    o.connect(m);

    m::basic_observable_map<int, int, s::u8string>::iterator it = m->insert(m->begin(), m::basic_observable_map<int, int, s::u8string>::value_type(3, 30));
    EXPECT_EQ(5u, m->size());

    it = m->insert(it, m::basic_observable_map<int, int, s::u8string>::value_type(4, 40));
    EXPECT_EQ(6u, m->size());

    it = m->insert(it, m::basic_observable_map<int, int, s::u8string>::value_type(4, 40));
    EXPECT_EQ(6u, m->size());

    it = m->insert(it, m::basic_observable_map<int, int, s::u8string>::value_type(6, 60));
    EXPECT_EQ(7u, m->size());

    unsigned int count = 0u;
    for(const m::basic_observable_map<int, int, s::u8string>::value_type& i : *m)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i.first);
        EXPECT_EQ(static_cast<int>(count)*10, i.second);
    }
    EXPECT_EQ(7u, count);

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

TEST(std_basic_observable_map_test_suite, test_insert_range)
{
    // Test insert range
    m::basic_observable_map<int, int, s::u8string>::ptr m1 = m::basic_observable_map<int, int, s::u8string>::create();
    m::basic_observable_map<int, int, s::u8string>::ptr m2 = m::basic_observable_map<int, int, s::u8string>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m1->size());
    EXPECT_EQ(0u, m2->size());

    const std::initializer_list<m::basic_observable_map<int, int, s::u8string>::value_type> il1 =
    {
        m::basic_observable_map<int, int, s::u8string>::value_type(1, 10),
        m::basic_observable_map<int, int, s::u8string>::value_type(2, 20),
        m::basic_observable_map<int, int, s::u8string>::value_type(5, 50),
        m::basic_observable_map<int, int, s::u8string>::value_type(7, 70)
    };
    *m1 = il1;
    EXPECT_EQ(4u, m1->size());

    const std::initializer_list<m::basic_observable_map<int, int, s::u8string>::value_type> il2 =
    {
        m::basic_observable_map<int, int, s::u8string>::value_type(3, 30),
        m::basic_observable_map<int, int, s::u8string>::value_type(4, 40),
        m::basic_observable_map<int, int, s::u8string>::value_type(6, 60)
    };
    *m2 = il2;
    EXPECT_EQ(3u, m2->size());

    o.connect(m2);

    m2->insert(m1->begin(), m1->end());
    EXPECT_EQ(7u, m2->size());

    m::basic_observable_map<int, int, s::u8string>::iterator it = m2->begin();
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

TEST(std_basic_observable_map_test_suite, test_insert_initializer_list)
{
    // Test insert initializer list
    m::basic_observable_map<int, int, s::u8string>::ptr m = m::basic_observable_map<int, int, s::u8string>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::basic_observable_map<int, int, s::u8string>::value_type> il1 =
    {
        m::basic_observable_map<int, int, s::u8string>::value_type(1, 10),
        m::basic_observable_map<int, int, s::u8string>::value_type(2, 20),
        m::basic_observable_map<int, int, s::u8string>::value_type(5, 50),
        m::basic_observable_map<int, int, s::u8string>::value_type(7, 70)
    };
    *m = il1;
    EXPECT_EQ(4u, m->size());

    const std::initializer_list<m::basic_observable_map<int, int, s::u8string>::value_type> il2 =
    {
        m::basic_observable_map<int, int, s::u8string>::value_type(3, 30),
        m::basic_observable_map<int, int, s::u8string>::value_type(4, 40),
        m::basic_observable_map<int, int, s::u8string>::value_type(6, 60)
    };
    EXPECT_EQ(3u, il2.size());

    o.connect(m);

    m->insert(il2);
    EXPECT_EQ(7u, m->size());

    m::basic_observable_map<int, int, s::u8string>::iterator it = m->begin();
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

TEST(std_basic_observable_map_test_suite, test_erase_position)
{
    // Test erase position
    m::basic_observable_map<int, int, s::u8string>::ptr m = m::basic_observable_map<int, int, s::u8string>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::basic_observable_map<int, int, s::u8string>::value_type> il =
    {
        m::basic_observable_map<int, int, s::u8string>::value_type(1, 10),
        m::basic_observable_map<int, int, s::u8string>::value_type(2, 20),
        m::basic_observable_map<int, int, s::u8string>::value_type(3, 30),
        m::basic_observable_map<int, int, s::u8string>::value_type(4, 40),
        m::basic_observable_map<int, int, s::u8string>::value_type(5, 50),
        m::basic_observable_map<int, int, s::u8string>::value_type(6, 60),
        m::basic_observable_map<int, int, s::u8string>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m::basic_observable_map<int, int, s::u8string>::iterator it1 = m->begin();
    std::advance(it1, 3);
    m::basic_observable_map<int, int, s::u8string>::iterator it2 = m->erase(it1);
    EXPECT_EQ(6u, m->size());

    m->erase(it2);
    EXPECT_EQ(5u, m->size());

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

TEST(std_basic_observable_map_test_suite, test_erase_value)
{
    // Test erase value
    m::basic_observable_map<int, int, s::u8string>::ptr m = m::basic_observable_map<int, int, s::u8string>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::basic_observable_map<int, int, s::u8string>::value_type> il =
    {
        m::basic_observable_map<int, int, s::u8string>::value_type(1, 10),
        m::basic_observable_map<int, int, s::u8string>::value_type(2, 20),
        m::basic_observable_map<int, int, s::u8string>::value_type(3, 30),
        m::basic_observable_map<int, int, s::u8string>::value_type(4, 40),
        m::basic_observable_map<int, int, s::u8string>::value_type(5, 50),
        m::basic_observable_map<int, int, s::u8string>::value_type(6, 60),
        m::basic_observable_map<int, int, s::u8string>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m->erase(4);
    EXPECT_EQ(6u, m->size());

    m->erase(5);
    EXPECT_EQ(5u, m->size());

    m::basic_observable_map<int, int, s::u8string>::iterator it = m->begin();
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

TEST(std_basic_observable_map_test_suite, test_erase_range)
{
    // Test erase range
    m::basic_observable_map<int, int, s::u8string>::ptr m = m::basic_observable_map<int, int, s::u8string>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::basic_observable_map<int, int, s::u8string>::value_type> il =
    {
        m::basic_observable_map<int, int, s::u8string>::value_type(1, 10),
        m::basic_observable_map<int, int, s::u8string>::value_type(2, 20),
        m::basic_observable_map<int, int, s::u8string>::value_type(3, 30),
        m::basic_observable_map<int, int, s::u8string>::value_type(4, 40),
        m::basic_observable_map<int, int, s::u8string>::value_type(5, 50),
        m::basic_observable_map<int, int, s::u8string>::value_type(6, 60),
        m::basic_observable_map<int, int, s::u8string>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m::basic_observable_map<int, int, s::u8string>::iterator begin = m->begin();
    ++begin;
    m::basic_observable_map<int, int, s::u8string>::iterator end = m->end();
    --end;

    m->erase(begin, end);
    EXPECT_EQ(2u, m->size());

    m::basic_observable_map<int, int, s::u8string>::iterator it = m->begin();
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(10, it->second);
    ++it;
    EXPECT_EQ(7, it->first);
    EXPECT_EQ(70, it->second);
    ++it;
    EXPECT_EQ(m->end(), it);

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

TEST(std_basic_observable_map_test_suite, test_swap)
{
    // Test swap
    m::basic_observable_map<int, int, s::u8string>::ptr m1 = m::basic_observable_map<int, int, s::u8string>::create();
    m::basic_observable_map<int, int, s::u8string>::ptr m2 = m::basic_observable_map<int, int, s::u8string>::create();
    map_observer<int, int> o1;
    map_observer<int, int> o2;

    EXPECT_EQ(0u, m1->size());
    EXPECT_EQ(0u, m2->size());

    const std::initializer_list<m::basic_observable_map<int, int, s::u8string>::value_type> il1 =
    {
        m::basic_observable_map<int, int, s::u8string>::value_type(1, 10),
        m::basic_observable_map<int, int, s::u8string>::value_type(2, 20),
        m::basic_observable_map<int, int, s::u8string>::value_type(3, 30),
        m::basic_observable_map<int, int, s::u8string>::value_type(4, 40),
        m::basic_observable_map<int, int, s::u8string>::value_type(5, 50)
    };
    const std::initializer_list<m::basic_observable_map<int, int, s::u8string>::value_type> il2 =
    {
        m::basic_observable_map<int, int, s::u8string>::value_type(10, 100),
        m::basic_observable_map<int, int, s::u8string>::value_type(20, 200),
        m::basic_observable_map<int, int, s::u8string>::value_type(30, 300),
        m::basic_observable_map<int, int, s::u8string>::value_type(40, 400),
        m::basic_observable_map<int, int, s::u8string>::value_type(50, 500),
        m::basic_observable_map<int, int, s::u8string>::value_type(60, 600),
        m::basic_observable_map<int, int, s::u8string>::value_type(70, 700)
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
    for(const m::basic_observable_map<int, int, s::u8string>::value_type& i : *m1)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count)*10, i.first);
        EXPECT_EQ(static_cast<int>(count)*100, i.second);
    }
    EXPECT_EQ(7u, count);

    count = 0;
    for(const m::basic_observable_map<int, int, s::u8string>::value_type& i : *m2)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i.first);
        EXPECT_EQ(static_cast<int>(count)*10, i.second);
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

TEST(std_basic_observable_map_test_suite, test_clear)
{
    // Test clear
    m::basic_observable_map<int, int, s::u8string>::ptr m = m::basic_observable_map<int, int, s::u8string>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::basic_observable_map<int, int, s::u8string>::value_type> il =
    {
        m::basic_observable_map<int, int, s::u8string>::value_type(1, 10),
        m::basic_observable_map<int, int, s::u8string>::value_type(2, 20),
        m::basic_observable_map<int, int, s::u8string>::value_type(3, 30),
        m::basic_observable_map<int, int, s::u8string>::value_type(4, 40),
        m::basic_observable_map<int, int, s::u8string>::value_type(5, 50),
        m::basic_observable_map<int, int, s::u8string>::value_type(6, 60),
        m::basic_observable_map<int, int, s::u8string>::value_type(7, 70)
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

TEST(std_basic_observable_map_test_suite, test_emplace)
{
    // Test emplace
    m::basic_observable_map<int, int, s::u8string>::ptr m = m::basic_observable_map<int, int, s::u8string>::create();
    map_observer<int, int> o;

    const std::initializer_list<m::basic_observable_map<int, int, s::u8string>::value_type> il =
    {
        m::basic_observable_map<int, int, s::u8string>::value_type(1, 10),
        m::basic_observable_map<int, int, s::u8string>::value_type(2, 20),
        m::basic_observable_map<int, int, s::u8string>::value_type(3, 30)
    };
    *m = il;
    EXPECT_EQ(3u, m->size());

    o.connect(m);

    auto ret = m->emplace(m::basic_observable_map<int, int, s::u8string>::value_type(4, 40));
    EXPECT_EQ(4, ret.first->first);
    EXPECT_EQ(40, ret.first->second);
    EXPECT_TRUE(ret.second);

    ret = m->emplace(m::basic_observable_map<int, int, s::u8string>::value_type(5, 50));
    EXPECT_EQ(5, ret.first->first);
    EXPECT_EQ(50, ret.first->second);
    EXPECT_TRUE(ret.second);

    ret = m->emplace(m::basic_observable_map<int, int, s::u8string>::value_type(4, 40));
    EXPECT_EQ(4, ret.first->first);
    EXPECT_EQ(40, ret.first->second);
    EXPECT_FALSE(ret.second);

    ret = m->emplace(m::basic_observable_map<int, int, s::u8string>::value_type(6, 60));
    EXPECT_EQ(6, ret.first->first);
    EXPECT_EQ(60, ret.first->second);
    EXPECT_TRUE(ret.second);

    m::basic_observable_map<int, int, s::u8string>::iterator it = m->begin();
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
    EXPECT_EQ(m->end(), it);

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

TEST(std_basic_observable_map_test_suite, test_emplace_hint)
{
    // Test emplace hint
    m::basic_observable_map<int, int, s::u8string>::ptr m = m::basic_observable_map<int, int, s::u8string>::create();
    map_observer<int, int> o;

    const std::initializer_list<m::basic_observable_map<int, int, s::u8string>::value_type> il =
    {
        m::basic_observable_map<int, int, s::u8string>::value_type(1, 10),
        m::basic_observable_map<int, int, s::u8string>::value_type(2, 20),
        m::basic_observable_map<int, int, s::u8string>::value_type(5, 50)
    };
    *m = il;
    EXPECT_EQ(3u, m->size());

    o.connect(m);

    m::basic_observable_map<int, int, s::u8string>::iterator it = m->emplace_hint(m->begin(), m::basic_observable_map<int, int, s::u8string>::value_type(3, 30));
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(30, it->second);

    it = m->emplace_hint(it, m::basic_observable_map<int, int, s::u8string>::value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = m->emplace_hint(it, m::basic_observable_map<int, int, s::u8string>::value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = m->emplace_hint(it, m::basic_observable_map<int, int, s::u8string>::value_type(6, 60));
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
    EXPECT_EQ(5, it->first);
    EXPECT_EQ(50, it->second);
    ++it;
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);
    ++it;
    EXPECT_EQ(m->end(), it);

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
