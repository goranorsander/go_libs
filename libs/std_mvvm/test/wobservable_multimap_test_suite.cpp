//
//  wobservable_multimap_test_suite.cpp
//
//  Copyright 2015-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_NOEXCEPT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_wobservable_multimap_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>
#include <go/namespace_alias.hpp>

namespace
{

template<class K, class T> class multimap_observer
{
public:
    typedef multimap_observer<K, T> this_type;
    typedef typename m::wobservable_multimap<K, T>::ptr wobservable_multimap_ptr_type;

    virtual ~multimap_observer() GO_DEFAULT_DESTRUCTOR

    multimap_observer()
        : _on_container_changed_connection()
        , _on_property_changed_connection()
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

    void connect(wobservable_multimap_ptr_type& c)
    {
        _on_container_changed_connection = c->container_changed.connect(std::bind(&this_type::on_container_changed, this, ph::_1, ph::_2));
        _on_property_changed_connection = c->property_changed.connect(std::bind(&this_type::on_property_changed, this, ph::_1, ph::_2));
    }

    void disconnect(wobservable_multimap_ptr_type& c)
    {
        c->container_changed.disconnect(_on_container_changed_connection);
        c->property_changed.disconnect(_on_property_changed_connection);
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
    si::connection _on_container_changed_connection;
    si::connection _on_property_changed_connection;

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

TEST(std_wobservable_multimap_test_suite, test_insert_single_element)
{
    // Test insert single element
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    EXPECT_EQ(0u, m->size());
    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il =
    {
        m::wobservable_multimap<int, int>::value_type(1, 10),
        m::wobservable_multimap<int, int>::value_type(2, 20),
        m::wobservable_multimap<int, int>::value_type(4, 40),
        m::wobservable_multimap<int, int>::value_type(5, 50),
        m::wobservable_multimap<int, int>::value_type(6, 60),
        m::wobservable_multimap<int, int>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(6u, m->size());

    o.connect(m);

    m->insert(m::wobservable_multimap<int, int>::value_type(3, 30));
    EXPECT_EQ(7u, m->size());

    unsigned int count = 0u;
    for(const m::wobservable_multimap<int, int>::value_type& i : *m)
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

TEST(std_wobservable_multimap_test_suite, test_insert_single_element_with_hint)
{
    // Test insert single element with hint
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    EXPECT_EQ(0u, m->size());
    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il =
    {
        m::wobservable_multimap<int, int>::value_type(1, 10),
        m::wobservable_multimap<int, int>::value_type(2, 20),
        m::wobservable_multimap<int, int>::value_type(5, 50),
        m::wobservable_multimap<int, int>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(4u, m->size());

    o.connect(m);

    m::wobservable_multimap<int, int>::iterator it = m->insert(m->begin(), m::wobservable_multimap<int, int>::value_type(3, 30));
    EXPECT_EQ(5u, m->size());

    it = m->insert(it, m::wobservable_multimap<int, int>::value_type(4, 40));
    EXPECT_EQ(6u, m->size());

    it = m->insert(it, m::wobservable_multimap<int, int>::value_type(4, 40));
    EXPECT_EQ(7u, m->size());

    it = m->insert(it, m::wobservable_multimap<int, int>::value_type(6, 60));
    EXPECT_EQ(8u, m->size());

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

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_wobservable_multimap_test_suite, test_insert_range)
{
    // Test insert range
    m::wobservable_multimap<int, int>::ptr m1 = m::wobservable_multimap<int, int>::create();
    m::wobservable_multimap<int, int>::ptr m2 = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    EXPECT_EQ(0u, m1->size());
    EXPECT_EQ(0u, m2->size());

    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il1 =
    {
        m::wobservable_multimap<int, int>::value_type(1, 10),
        m::wobservable_multimap<int, int>::value_type(2, 20),
        m::wobservable_multimap<int, int>::value_type(5, 50),
        m::wobservable_multimap<int, int>::value_type(7, 70)
    };
    *m1 = il1;
    EXPECT_EQ(4u, m1->size());

    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il2 =
    {
        m::wobservable_multimap<int, int>::value_type(3, 30),
        m::wobservable_multimap<int, int>::value_type(4, 40),
        m::wobservable_multimap<int, int>::value_type(6, 60)
    };
    *m2 = il2;
    EXPECT_EQ(3u, m2->size());

    o.connect(m2);

    m2->insert(m1->begin(), m1->end());
    EXPECT_EQ(7u, m2->size());

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

TEST(std_wobservable_multimap_test_suite, test_insert_initializer_list)
{
    // Test insert initializer list
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il1 =
    {
        m::wobservable_multimap<int, int>::value_type(1, 10),
        m::wobservable_multimap<int, int>::value_type(2, 20),
        m::wobservable_multimap<int, int>::value_type(5, 50),
        m::wobservable_multimap<int, int>::value_type(7, 70)
    };
    *m = il1;
    EXPECT_EQ(4u, m->size());

    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il2 =
    {
        m::wobservable_multimap<int, int>::value_type(3, 30),
        m::wobservable_multimap<int, int>::value_type(4, 40),
        m::wobservable_multimap<int, int>::value_type(6, 60)
    };
    EXPECT_EQ(3u, il2.size());

    o.connect(m);

    m->insert(il2);
    EXPECT_EQ(7u, m->size());

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

TEST(std_wobservable_multimap_test_suite, test_erase_position)
{
    // Test erase position
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il =
    {
        m::wobservable_multimap<int, int>::value_type(1, 10),
        m::wobservable_multimap<int, int>::value_type(2, 20),
        m::wobservable_multimap<int, int>::value_type(3, 30),
        m::wobservable_multimap<int, int>::value_type(4, 40),
        m::wobservable_multimap<int, int>::value_type(5, 50),
        m::wobservable_multimap<int, int>::value_type(6, 60),
        m::wobservable_multimap<int, int>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m::wobservable_multimap<int, int>::iterator it1 = m->begin();
    std::advance(it1, 3);
    m::wobservable_multimap<int, int>::iterator it2 = m->erase(it1);
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

TEST(std_wobservable_multimap_test_suite, test_erase_value)
{
    // Test erase value
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il =
    {
        m::wobservable_multimap<int, int>::value_type(1, 10),
        m::wobservable_multimap<int, int>::value_type(2, 20),
        m::wobservable_multimap<int, int>::value_type(3, 30),
        m::wobservable_multimap<int, int>::value_type(4, 40),
        m::wobservable_multimap<int, int>::value_type(5, 50),
        m::wobservable_multimap<int, int>::value_type(6, 60),
        m::wobservable_multimap<int, int>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m->erase(4);
    EXPECT_EQ(6u, m->size());

    m->erase(5);
    EXPECT_EQ(5u, m->size());

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

TEST(std_wobservable_multimap_test_suite, test_erase_range)
{
    // Test erase range
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il =
    {
        m::wobservable_multimap<int, int>::value_type(1, 10),
        m::wobservable_multimap<int, int>::value_type(2, 20),
        m::wobservable_multimap<int, int>::value_type(3, 30),
        m::wobservable_multimap<int, int>::value_type(4, 40),
        m::wobservable_multimap<int, int>::value_type(5, 50),
        m::wobservable_multimap<int, int>::value_type(6, 60),
        m::wobservable_multimap<int, int>::value_type(7, 70)
    };
    *m = il;
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m::wobservable_multimap<int, int>::iterator begin = m->begin();
    ++begin;
    m::wobservable_multimap<int, int>::iterator end = m->end();
    --end;

    m->erase(begin, end);
    EXPECT_EQ(2u, m->size());

    m::wobservable_multimap<int, int>::iterator it = m->begin();
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

TEST(std_wobservable_multimap_test_suite, test_swap)
{
    // Test swap
    m::wobservable_multimap<int, int>::ptr m1 = m::wobservable_multimap<int, int>::create();
    m::wobservable_multimap<int, int>::ptr m2 = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o1;
    multimap_observer<int, int> o2;

    EXPECT_EQ(0u, m1->size());
    EXPECT_EQ(0u, m2->size());

    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il1 =
    {
        m::wobservable_multimap<int, int>::value_type(1, 10),
        m::wobservable_multimap<int, int>::value_type(2, 20),
        m::wobservable_multimap<int, int>::value_type(3, 30),
        m::wobservable_multimap<int, int>::value_type(4, 40),
        m::wobservable_multimap<int, int>::value_type(5, 50)
    };
    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il2 =
    {
        m::wobservable_multimap<int, int>::value_type(10, 100),
        m::wobservable_multimap<int, int>::value_type(20, 200),
        m::wobservable_multimap<int, int>::value_type(30, 300),
        m::wobservable_multimap<int, int>::value_type(40, 400),
        m::wobservable_multimap<int, int>::value_type(50, 500),
        m::wobservable_multimap<int, int>::value_type(60, 600),
        m::wobservable_multimap<int, int>::value_type(70, 700)
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
    for(const m::wobservable_multimap<int, int>::value_type& i : *m1)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count)*10, i.first);
        EXPECT_EQ(static_cast<int>(count)*100, i.second);
    }
    EXPECT_EQ(7u, count);

    count = 0;
    for(const m::wobservable_multimap<int, int>::value_type& i : *m2)
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

TEST(std_wobservable_multimap_test_suite, test_clear)
{
    // Test clear
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il =
    {
        m::wobservable_multimap<int, int>::value_type(1, 10),
        m::wobservable_multimap<int, int>::value_type(2, 20),
        m::wobservable_multimap<int, int>::value_type(3, 30),
        m::wobservable_multimap<int, int>::value_type(4, 40),
        m::wobservable_multimap<int, int>::value_type(5, 50),
        m::wobservable_multimap<int, int>::value_type(6, 60),
        m::wobservable_multimap<int, int>::value_type(7, 70)
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

TEST(std_wobservable_multimap_test_suite, test_emplace)
{
    // Test emplace
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il =
    {
        m::wobservable_multimap<int, int>::value_type(1, 10),
        m::wobservable_multimap<int, int>::value_type(2, 20),
        m::wobservable_multimap<int, int>::value_type(3, 30)
    };
    *m = il;
    EXPECT_EQ(3u, m->size());

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

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

TEST(std_wobservable_multimap_test_suite, test_emplace_hint)
{
    // Test emplace hint
    m::wobservable_multimap<int, int>::ptr m = m::wobservable_multimap<int, int>::create();
    multimap_observer<int, int> o;

    const std::initializer_list<m::wobservable_multimap<int, int>::value_type> il =
    {
        m::wobservable_multimap<int, int>::value_type(1, 10),
        m::wobservable_multimap<int, int>::value_type(2, 20),
        m::wobservable_multimap<int, int>::value_type(5, 50)
    };
    *m = il;
    EXPECT_EQ(3u, m->size());

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

    EXPECT_EQ(m::notify_container_changed_action::add, o.last_action());
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

}

#endif  // Required C++11 feature is not supported by this compiler
