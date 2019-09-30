//
//  observable_map_test_suite.cpp
//
//  Copyright 2015-2019 Göran Orsander
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

namespace m = go_boost::mvvm;

namespace
{

template<class K, class T> class map_observer
{
public:
    typedef map_observer<K, T> this_type;
    typedef typename m::observable_map<K, T>::ptr observable_map_ptr_type;

    virtual ~map_observer() GO_BOOST_DEFAULT_DESTRUCTOR

    map_observer()
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

    void connect(observable_map_ptr_type& c)
    {
#if (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(6,1,0)) && (BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(6,3,0))
        c->container_changed.connect(boost::bind(&map_observer<K, T>::on_container_changed, this, _1, _2));
        c->property_changed.connect(boost::bind(&map_observer<K, T>::on_property_changed, this, _1, _2));
#else
        c->container_changed.connect(boost::bind(&this_type::on_container_changed, this, _1, _2));
        c->property_changed.connect(boost::bind(&this_type::on_property_changed, this, _1, _2));
#endif  // #if (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(6,1,0)) && (BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(6,3,0))
    }

    void disconnect(observable_map_ptr_type& c)
    {
#if (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(6,1,0)) && (BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(6,2,0))
        c->container_changed.disconnect(boost::bind(&map_observer<K, T>::on_container_changed, this, _1, _2));
        c->property_changed.disconnect(boost::bind(&map_observer<K, T>::on_property_changed, this, _1, _2));
#else
        c->container_changed.disconnect(boost::bind(&this_type::on_container_changed, this, _1, _2));
        c->property_changed.disconnect(boost::bind(&this_type::on_property_changed, this, _1, _2));
#endif  // #if (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(6,1,0)) && (BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(6,2,0))
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

TEST(boost_observable_map_test_suite, test_insert_single_element)
{
    // Test insert single element
    m::observable_map<int, int>::ptr m = m::observable_map<int, int>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());
    (*m)[1] = 10;
    (*m)[2] = 20;
    (*m)[4] = 40;
    (*m)[5] = 50;
    (*m)[6] = 60;
    (*m)[7] = 70;
    EXPECT_EQ(6u, m->size());

    o.connect(m);

    m->insert(m::observable_map<int, int>::value_type(3, 30));
    EXPECT_EQ(7u, m->size());

    typedef m::observable_map<int, int> observable_map_type;
    unsigned int count = 0u;
    BOOST_FOREACH(const GO_BOOST_TYPENAME observable_map_type::value_type& i, *m)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i.first);
        EXPECT_EQ(static_cast<int>(count)*10, i.second);
    }
    EXPECT_EQ(7u, count);

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

TEST(boost_observable_map_test_suite, test_insert_single_element_with_hint)
{
    // Test insert single element with hint
    m::observable_map<int, int>::ptr m = m::observable_map<int, int>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());
    (*m)[1] = 10;
    (*m)[2] = 20;
    (*m)[5] = 50;
    (*m)[7] = 70;
    EXPECT_EQ(4u, m->size());

    o.connect(m);

    m::observable_map<int, int>::iterator it = m->insert(m->begin(), m::observable_map<int, int>::value_type(3, 30));
    EXPECT_EQ(5u, m->size());

    it = m->insert(it, m::observable_map<int, int>::value_type(4, 40));
    EXPECT_EQ(6u, m->size());

    it = m->insert(it, m::observable_map<int, int>::value_type(4, 40));
    EXPECT_EQ(6u, m->size());

    it = m->insert(it, m::observable_map<int, int>::value_type(6, 60));
    EXPECT_EQ(7u, m->size());

    typedef m::observable_map<int, int> observable_map_type;
    unsigned int count = 0u;
    BOOST_FOREACH(const GO_BOOST_TYPENAME observable_map_type::value_type& i, *m)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i.first);
        EXPECT_EQ(static_cast<int>(count)*10, i.second);
    }
    EXPECT_EQ(7u, count);

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

TEST(boost_observable_map_test_suite, test_insert_range)
{
    // Test insert range
    m::observable_map<int, int>::ptr m1 = m::observable_map<int, int>::create();
    m::observable_map<int, int>::ptr m2 = m::observable_map<int, int>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m1->size());
    EXPECT_EQ(0u, m2->size());

    (*m1)[1] = 10;
    (*m1)[2] = 20;
    (*m1)[5] = 50;
    (*m1)[7] = 70;
    EXPECT_EQ(4u, m1->size());

    (*m2)[3] = 30;
    (*m2)[4] = 40;
    (*m2)[6] = 60;
    EXPECT_EQ(3u, m2->size());

    o.connect(m2);

    m2->insert(m1->begin(), m1->end());
    EXPECT_EQ(7u, m2->size());

    m::observable_map<int, int>::iterator it = m2->begin();
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

TEST(boost_observable_map_test_suite, test_insert_initializer_list)
{
    // Test insert initializer list
    m::observable_map<int, int>::ptr m = m::observable_map<int, int>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    const std::initializer_list<m::observable_map<int, int>::value_type> il1 =
    {
        m::observable_map<int, int>::value_type(1, 10),
        m::observable_map<int, int>::value_type(2, 20),
        m::observable_map<int, int>::value_type(5, 50),
        m::observable_map<int, int>::value_type(7, 70)
    };
    *m = il1;
    EXPECT_EQ(4u, m->size());

    const std::initializer_list<m::observable_map<int, int>::value_type> il2 =
    {
        m::observable_map<int, int>::value_type(3, 30),
        m::observable_map<int, int>::value_type(4, 40),
        m::observable_map<int, int>::value_type(6, 60)
    };
    EXPECT_EQ(3u, il2.size());

    o.connect(m);

    m->insert(il2);
    EXPECT_EQ(7u, m->size());

    m::observable_map<int, int>::iterator it = m->begin();
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

TEST(boost_observable_map_test_suite, test_erase_position)
{
    // Test erase position
    m::observable_map<int, int>::ptr m = m::observable_map<int, int>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    (*m)[1] = 10;
    (*m)[2] = 20;
    (*m)[3] = 30;
    (*m)[4] = 40;
    (*m)[5] = 50;
    (*m)[6] = 60;
    (*m)[7] = 70;
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m::observable_map<int, int>::iterator it1 = m->begin();
    std::advance(it1, 3);
    m::observable_map<int, int>::iterator it2 = m->erase(it1);
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

TEST(boost_observable_map_test_suite, test_erase_value)
{
    // Test erase value
    m::observable_map<int, int>::ptr m = m::observable_map<int, int>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    (*m)[1] = 10;
    (*m)[2] = 20;
    (*m)[3] = 30;
    (*m)[4] = 40;
    (*m)[5] = 50;
    (*m)[6] = 60;
    (*m)[7] = 70;
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m->erase(4);
    EXPECT_EQ(6u, m->size());

    m->erase(5);
    EXPECT_EQ(5u, m->size());

    m::observable_map<int, int>::iterator it = m->begin();
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

TEST(boost_observable_map_test_suite, test_erase_range)
{
    // Test erase range
    m::observable_map<int, int>::ptr m = m::observable_map<int, int>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    (*m)[1] = 10;
    (*m)[2] = 20;
    (*m)[3] = 30;
    (*m)[4] = 40;
    (*m)[5] = 50;
    (*m)[6] = 60;
    (*m)[7] = 70;
    EXPECT_EQ(7u, m->size());

    o.connect(m);

    m::observable_map<int, int>::iterator begin = m->begin();
    ++begin;
    m::observable_map<int, int>::iterator end = m->end();
    --end;

    m->erase(begin, end);
    EXPECT_EQ(2u, m->size());

    m::observable_map<int, int>::iterator it = m->begin();
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(10, it->second);
    ++it;
    EXPECT_EQ(7, it->first);
    EXPECT_EQ(70, it->second);
    ++it;
    EXPECT_EQ(m->end(), it);

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

TEST(boost_observable_map_test_suite, test_swap)
{
    // Test swap
    m::observable_map<int, int>::ptr m1 = m::observable_map<int, int>::create();
    m::observable_map<int, int>::ptr m2 = m::observable_map<int, int>::create();
    map_observer<int, int> o1;
    map_observer<int, int> o2;

    EXPECT_EQ(0u, m1->size());
    EXPECT_EQ(0u, m2->size());

    (*m1)[1] = 10;
    (*m1)[2] = 20;
    (*m1)[3] = 30;
    (*m1)[4] = 40;
    (*m1)[5] = 50;
    EXPECT_EQ(5u, m1->size());

    (*m2)[10] = 100;
    (*m2)[20] = 200;
    (*m2)[30] = 300;
    (*m2)[40] = 400;
    (*m2)[50] = 500;
    (*m2)[60] = 600;
    (*m2)[70] = 700;
    EXPECT_EQ(7u, m2->size());

    o1.connect(m1);
    o2.connect(m2);

    m1->swap(*m2);
    EXPECT_EQ(7u, m1->size());
    EXPECT_EQ(5u, m2->size());

    typedef m::observable_map<int, int> observable_map_type;
    unsigned int count = 0u;
    BOOST_FOREACH(const GO_BOOST_TYPENAME observable_map_type::value_type& i, *m1)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count)*10, i.first);
        EXPECT_EQ(static_cast<int>(count)*100, i.second);
    }
    EXPECT_EQ(7u, count);

    count = 0;
    BOOST_FOREACH(const GO_BOOST_TYPENAME observable_map_type::value_type& i, *m2)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i.first);
        EXPECT_EQ(static_cast<int>(count)*10, i.second);
    }
    EXPECT_EQ(5u, count);

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

TEST(boost_observable_map_test_suite, test_clear)
{
    // Test clear
    m::observable_map<int, int>::ptr m = m::observable_map<int, int>::create();
    map_observer<int, int> o;

    EXPECT_EQ(0u, m->size());

    (*m)[1] = 10;
    (*m)[2] = 20;
    (*m)[3] = 30;
    (*m)[4] = 40;
    (*m)[5] = 50;
    (*m)[6] = 60;
    (*m)[7] = 70;
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

TEST(boost_observable_map_test_suite, test_emplace)
{
    // Test emplace
    m::observable_map<int, int>::ptr m = m::observable_map<int, int>::create();
    map_observer<int, int> o;

    (*m)[1] = 10;
    (*m)[2] = 20;
    (*m)[3] = 30;
    EXPECT_EQ(3u, m->size());

    o.connect(m);

    auto ret = m->emplace(m::observable_map<int, int>::value_type(4, 40));
    EXPECT_EQ(4, ret.first->first);
    EXPECT_EQ(40, ret.first->second);
    EXPECT_TRUE(ret.second);

    ret = m->emplace(m::observable_map<int, int>::value_type(5, 50));
    EXPECT_EQ(5, ret.first->first);
    EXPECT_EQ(50, ret.first->second);
    EXPECT_TRUE(ret.second);

    ret = m->emplace(m::observable_map<int, int>::value_type(4, 40));
    EXPECT_EQ(4, ret.first->first);
    EXPECT_EQ(40, ret.first->second);
    EXPECT_FALSE(ret.second);

    ret = m->emplace(m::observable_map<int, int>::value_type(6, 60));
    EXPECT_EQ(6, ret.first->first);
    EXPECT_EQ(60, ret.first->second);
    EXPECT_TRUE(ret.second);

    m::observable_map<int, int>::iterator it = m->begin();
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

TEST(boost_observable_map_test_suite, test_emplace_hint)
{
    // Test emplace hint
    m::observable_map<int, int>::ptr m = m::observable_map<int, int>::create();
    map_observer<int, int> o;

    (*m)[1] = 10;
    (*m)[2] = 20;
    (*m)[5] = 50;
    EXPECT_EQ(3u, m->size());

    o.connect(m);

    m::observable_map<int, int>::iterator it = m->emplace_hint(m->begin(), m::observable_map<int, int>::value_type(3, 30));
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(30, it->second);

    it = m->emplace_hint(it, m::observable_map<int, int>::value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = m->emplace_hint(it, m::observable_map<int, int>::value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = m->emplace_hint(it, m::observable_map<int, int>::value_type(6, 60));
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
