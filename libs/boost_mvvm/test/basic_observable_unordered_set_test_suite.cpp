//
//  basic_observable_unordered_set_test_suite.cpp
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

#include <go_boost/mvvm.hpp>
#include <go_boost/namespace_alias.hpp>
#include <go_boost/utility.hpp>

namespace
{

template<class T> class set_observer
{
public:
    typedef set_observer<T> this_type;
    typedef typename m::basic_observable_unordered_set<T, s::u8string>::ptr observable_unordered_set_ptr_type;

    virtual ~set_observer() GO_BOOST_DEFAULT_DESTRUCTOR

    set_observer()
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

    void connect(observable_unordered_set_ptr_type& c)
    {
        c->container_changed.connect(boost::bind(&this_type::on_container_changed, this, boost::placeholders::_1, boost::placeholders::_2));
        c->property_changed.connect(boost::bind(&this_type::on_property_changed, this, boost::placeholders::_1, boost::placeholders::_2));
    }

    void disconnect(observable_unordered_set_ptr_type& c)
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

TEST(boost_basic_observable_unordered_set_test_suite, test_insert_single_element)
{
    // Test insert single element
    m::basic_observable_unordered_set<int, s::u8string>::ptr s = m::basic_observable_unordered_set<int, s::u8string>::create();
    set_observer<int> o;

    // TODO: Find a way to test insert without using insert to prepare the test
    EXPECT_EQ(0u, s->size());
    s->insert(1);
    s->insert(2);
    s->insert(4);
    s->insert(5);
    s->insert(6);
    s->insert(7);
    EXPECT_EQ(6u, s->size());

    o.connect(s);

    s->insert(3);
    EXPECT_EQ(7u, s->size());

    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const int& i, *s)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(28, sum);

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

TEST(boost_basic_observable_unordered_set_test_suite, test_insert_single_element_with_hint)
{
    // Test insert single element with hint
    m::basic_observable_unordered_set<int, s::u8string>::ptr s = m::basic_observable_unordered_set<int, s::u8string>::create();
    set_observer<int> o;

    EXPECT_EQ(0u, s->size());
    s->insert(1);
    s->insert(2);
    s->insert(5);
    s->insert(7);
    EXPECT_EQ(4u, s->size());

    o.connect(s);

    m::basic_observable_unordered_set<int, s::u8string>::iterator it = s->insert(s->begin(), 3);
    EXPECT_EQ(5u, s->size());

    it = s->insert(it, 4);
    EXPECT_EQ(6u, s->size());

    it = s->insert(it, 4);
    EXPECT_EQ(6u, s->size());

    it = s->insert(it, 6);
    EXPECT_EQ(7u, s->size());

    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const int& i, *s)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(28, sum);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
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

TEST(boost_basic_observable_unordered_set_test_suite, test_insert_range)
{
    // Test insert range
    m::basic_observable_unordered_set<int, s::u8string>::ptr s1 = m::basic_observable_unordered_set<int, s::u8string>::create();
    m::basic_observable_unordered_set<int, s::u8string>::ptr s2 = m::basic_observable_unordered_set<int, s::u8string>::create();
    set_observer<int> o;

    EXPECT_EQ(0u, s1->size());
    EXPECT_EQ(0u, s2->size());

    s1->insert(1);
    s1->insert(2);
    s1->insert(5);
    s1->insert(7);
    EXPECT_EQ(4u, s1->size());

    s2->insert(3);
    s2->insert(4);
    s2->insert(6);
    EXPECT_EQ(3u, s2->size());

    o.connect(s2);

    s2->insert(s1->begin(), s1->end());
    EXPECT_EQ(7u, s2->size());

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

TEST(boost_basic_observable_unordered_set_test_suite, test_insert_initializer_list)
{
    // Test insert initializer list
    m::basic_observable_unordered_set<int, s::u8string>::ptr s = m::basic_observable_unordered_set<int, s::u8string>::create();
    set_observer<int> o;

    EXPECT_EQ(0u, s->size());

    const std::initializer_list<int> il1 = {1, 2, 5, 7};
    *s = il1;
    EXPECT_EQ(4u, s->size());

    const std::initializer_list<int> il2 = {3, 4, 6};
    EXPECT_EQ(3u, il2.size());

    o.connect(s);

    s->insert(il2);
    EXPECT_EQ(7u, s->size());

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

TEST(boost_basic_observable_unordered_set_test_suite, test_erase_position)
{
    // Test erase position
    m::basic_observable_unordered_set<int, s::u8string>::ptr s = m::basic_observable_unordered_set<int, s::u8string>::create();
    set_observer<int> o;

    EXPECT_EQ(0u, s->size());

    s->insert(1);
    s->insert(2);
    s->insert(3);
    s->insert(4);
    s->insert(5);
    s->insert(6);
    s->insert(7);
    EXPECT_EQ(7u, s->size());

    o.connect(s);

    m::basic_observable_unordered_set<int, s::u8string>::iterator it1 = s->begin();
    std::advance(it1, 3);
    m::basic_observable_unordered_set<int, s::u8string>::iterator it2 = s->erase(it1);
    EXPECT_EQ(6u, s->size());

    s->erase(it2);
    EXPECT_EQ(5u, s->size());

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

TEST(boost_basic_observable_unordered_set_test_suite, test_erase_value)
{
    // Test erase value
    m::basic_observable_unordered_set<int, s::u8string>::ptr s = m::basic_observable_unordered_set<int, s::u8string>::create();
    set_observer<int> o;

    EXPECT_EQ(0u, s->size());

    s->insert(1);
    s->insert(2);
    s->insert(3);
    s->insert(4);
    s->insert(5);
    s->insert(6);
    s->insert(7);
    EXPECT_EQ(7u, s->size());

    o.connect(s);

    s->erase(4);
    EXPECT_EQ(6u, s->size());

    s->erase(5);
    EXPECT_EQ(5u, s->size());

    typedef m::basic_observable_unordered_set<int, s::u8string> observable_unordered_set_type;
    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const GO_BOOST_TYPENAME observable_unordered_set_type::value_type& i, *s)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(5u, count);
    EXPECT_EQ(19, sum);

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

TEST(boost_basic_observable_unordered_set_test_suite, test_erase_range)
{
    // Test erase range
    m::basic_observable_unordered_set<int, s::u8string>::ptr s = m::basic_observable_unordered_set<int, s::u8string>::create();
    set_observer<int> o;

    EXPECT_EQ(0u, s->size());

    s->insert(1);
    s->insert(2);
    s->insert(3);
    s->insert(4);
    s->insert(5);
    s->insert(6);
    s->insert(7);
    EXPECT_EQ(7u, s->size());

    o.connect(s);

    m::basic_observable_unordered_set<int, s::u8string>::iterator begin = s->begin();
    ++begin;
    m::basic_observable_unordered_set<int, s::u8string>::iterator end = begin;
    std::advance(end, 5);

    s->erase(begin, end);
    EXPECT_EQ(2u, s->size());

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

TEST(boost_basic_observable_unordered_set_test_suite, test_swap)
{
    // Test swap
    m::basic_observable_unordered_set<int, s::u8string>::ptr s1 = m::basic_observable_unordered_set<int, s::u8string>::create();
    m::basic_observable_unordered_set<int, s::u8string>::ptr s2 = m::basic_observable_unordered_set<int, s::u8string>::create();
    set_observer<int> o1;
    set_observer<int> o2;

    EXPECT_EQ(0u, s1->size());
    EXPECT_EQ(0u, s2->size());

    s1->insert(1);
    s1->insert(2);
    s1->insert(3);
    s1->insert(4);
    s1->insert(5);
    EXPECT_EQ(5u, s1->size());

    s2->insert(10);
    s2->insert(20);
    s2->insert(30);
    s2->insert(40);
    s2->insert(50);
    s2->insert(60);
    s2->insert(70);
    EXPECT_EQ(7u, s2->size());

    o1.connect(s1);
    o2.connect(s2);

    s1->swap(*s2);
    EXPECT_EQ(7u, s1->size());
    EXPECT_EQ(5u, s2->size());

    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const int& i, *s1)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(280, sum);

    count = 0;
    sum = 0;
    BOOST_FOREACH(const int& i, *s2)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(5u, count);
    EXPECT_EQ(15, sum);

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

TEST(boost_basic_observable_unordered_set_test_suite, test_clear)
{
    // Test clear
    m::basic_observable_unordered_set<int, s::u8string>::ptr s = m::basic_observable_unordered_set<int, s::u8string>::create();
    set_observer<int> o;

    EXPECT_EQ(0u, s->size());

    s->insert(1);
    s->insert(2);
    s->insert(3);
    s->insert(4);
    s->insert(5);
    s->insert(6);
    s->insert(7);
    EXPECT_EQ(7u, s->size());

    o.connect(s);

    s->clear();
    EXPECT_EQ(0u, s->size());

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

TEST(boost_basic_observable_unordered_set_test_suite, test_emplace)
{
    // Test emplace
    m::basic_observable_unordered_set<int, s::u8string>::ptr s = m::basic_observable_unordered_set<int, s::u8string>::create();
    set_observer<int> o;

    s->insert(1);
    s->insert(2);
    s->insert(3);
    EXPECT_EQ(3u, s->size());

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

    typedef m::basic_observable_unordered_set<int, s::u8string> observable_unordered_set_type;
    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const GO_BOOST_TYPENAME observable_unordered_set_type::value_type& i, *s)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(6u, count);
    EXPECT_EQ(21, sum);

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
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

#endif  // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

TEST(boost_basic_observable_unordered_set_test_suite, test_emplace_hint)
{
    // Test emplace hint
    m::basic_observable_unordered_set<int, s::u8string>::ptr s = m::basic_observable_unordered_set<int, s::u8string>::create();
    set_observer<int> o;

    s->insert(1);
    s->insert(2);
    s->insert(5);
    EXPECT_EQ(3u, s->size());

    o.connect(s);

    m::basic_observable_unordered_set<int, s::u8string>::iterator it = s->emplace_hint(s->begin(), 3);
    EXPECT_EQ(3, *it);

    it = s->emplace_hint(it, 4);
    EXPECT_EQ(4, *it);

    it = s->emplace_hint(it, 4);
    EXPECT_EQ(4, *it);

    it = s->emplace_hint(it, 6);
    EXPECT_EQ(6, *it);

    EXPECT_EQ(6u, s->size());

    EXPECT_EQ(m::notify_container_changed_action_add, o.last_action());
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

#endif  // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

}
