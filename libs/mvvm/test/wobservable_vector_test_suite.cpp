//
//  wobservable_vector_test_suite.cpp
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

template<class T> class vector_observer
{
public:
    typedef typename m::wobservable_vector<T>::ptr wobservable_vector_ptr_type;

    virtual ~vector_observer()
    {
    }

    vector_observer()
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

    void connect(wobservable_vector_ptr_type& c)
    {
        _on_container_changed_slot_key = c->container_changed.connect(std::bind(&vector_observer::on_container_changed, this, ph::_1, ph::_2));
        _on_property_changed_slot_key = c->property_changed.connect(std::bind(&vector_observer::on_property_changed, this, ph::_1, ph::_2));
    }

    void disconnect(wobservable_vector_ptr_type& c)
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

TEST(std_wobservable_vector_test_suite, test_wobservable_vector_assign_range)
{
    // Test assign range
    m::wobservable_vector<int>::ptr v = m::wobservable_vector<int>::create();
    vector_observer<int> o;

    EXPECT_EQ(0, v->size());

    o.connect(v);

    v->assign(7, 47);
    EXPECT_EQ(7, v->size());

    int count = 0;
    for(const int& i : *v)
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

TEST(std_wobservable_vector_test_suite, test_wobservable_vector_assign_initializer_list)
{
    // Test assign initializer list
    m::wobservable_vector<int>::ptr v = m::wobservable_vector<int>::create();
    vector_observer<int> o;

    EXPECT_EQ(0, v->size());

    o.connect(v);

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    v->assign(a, a + 7);
    EXPECT_EQ(7, v->size());

    int count = 0;
    for(const int& i : *v)
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

TEST(std_wobservable_vector_test_suite, test_wobservable_vector_assign_fill)
{
    // Test assign fill
    m::wobservable_vector<int>::ptr v1 = m::wobservable_vector<int>::create();
    m::wobservable_vector<int>::ptr v2 = m::wobservable_vector<int>::create();
    vector_observer<int> o;

    EXPECT_EQ(0, v1->size());
    EXPECT_EQ(0, v2->size());

    o.connect(v2);

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    v1->assign(a, a + 7);
    EXPECT_EQ(7, v1->size());
    EXPECT_EQ(0, v2->size());

    m::wobservable_vector<int>::iterator it = v1->begin() + 1;

    v2->assign(it, v1->end() - 1);
    EXPECT_EQ(7, v1->size());
    EXPECT_EQ(5, v2->size());

    int count = 0;
    for(const int& i : *v2)
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

TEST(std_wobservable_vector_test_suite, test_wobservable_vector_push_back)
{
    // Test push back
    m::wobservable_vector<int>::ptr v = m::wobservable_vector<int>::create();
    vector_observer<int> o;

    EXPECT_EQ(0, v->size());

    o.connect(v);

    v->push_back(1);
    EXPECT_EQ(1, v->size());

    v->push_back(2);
    EXPECT_EQ(2, v->size());

    v->push_back(3);
    EXPECT_EQ(3, v->size());

    int count = 0;
    for(const int& i : *v)
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

TEST(std_wobservable_vector_test_suite, test_wobservable_vector_pop_back)
{
    // Test pop back
    m::wobservable_vector<int>::ptr v = m::wobservable_vector<int>::create();
    vector_observer<int> o;

    EXPECT_EQ(0, v->size());

    v->assign(7, 47);
    EXPECT_EQ(7, v->size());

    o.connect(v);

    v->pop_back();
    EXPECT_EQ(6, v->size());

    v->pop_back();
    EXPECT_EQ(5, v->size());

    v->pop_back();
    EXPECT_EQ(4, v->size());

    int count = 0;
    for(const int& i : *v)
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

TEST(std_wobservable_vector_test_suite, test_observable_insert_single_element)
{
    // Test insert single element
    m::wobservable_vector<int>::ptr v = m::wobservable_vector<int>::create();
    vector_observer<int> o;

    EXPECT_EQ(0, v->size());
    const int a[] = {1, 2, 4, 5, 6, 7};
    v->assign(a, a + 6);
    EXPECT_EQ(6, v->size());

    o.connect(v);

    m::wobservable_vector<int>::iterator it = v->begin();
    v->insert(it + 2, 3);
    EXPECT_EQ(7, v->size());

    int count = 0;
    for(const int& i : *v)
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

TEST(std_wobservable_vector_test_suite, test_observable_insert_fill)
{
    // Test insert fill
    m::wobservable_vector<int>::ptr v = m::wobservable_vector<int>::create();
    vector_observer<int> o;

    EXPECT_EQ(0, v->size());

    v->assign(7, 47);
    EXPECT_EQ(7, v->size());

    o.connect(v);

    m::wobservable_vector<int>::iterator it = v->begin();
    v->insert(it + 3, 3, 74);
    EXPECT_EQ(10, v->size());

    EXPECT_EQ(47, (*v)[0]);
    EXPECT_EQ(47, (*v)[1]);
    EXPECT_EQ(47, (*v)[2]);
    EXPECT_EQ(74, (*v)[3]);
    EXPECT_EQ(74, (*v)[4]);
    EXPECT_EQ(74, (*v)[5]);
    EXPECT_EQ(47, (*v)[6]);
    EXPECT_EQ(47, (*v)[7]);
    EXPECT_EQ(47, (*v)[8]);
    EXPECT_EQ(47, (*v)[9]);

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

TEST(std_wobservable_vector_test_suite, test_observable_insert_range)
{
    // Test insert range
    m::wobservable_vector<int>::ptr v1 = m::wobservable_vector<int>::create();
    m::wobservable_vector<int>::ptr v2 = m::wobservable_vector<int>::create();
    vector_observer<int> o;

    EXPECT_EQ(0, v1->size());

    v1->assign(3, 74);
    EXPECT_EQ(3, v1->size());

    EXPECT_EQ(0, v2->size());
    v2->assign(7, 47);
    EXPECT_EQ(7, v2->size());

    o.connect(v2);

    m::wobservable_vector<int>::iterator it = v2->begin();
    v2->insert(it + 3, v1->begin(), v1->end());
    EXPECT_EQ(10, v2->size());

    EXPECT_EQ(47, (*v2)[0]);
    EXPECT_EQ(47, (*v2)[1]);
    EXPECT_EQ(47, (*v2)[2]);
    EXPECT_EQ(74, (*v2)[3]);
    EXPECT_EQ(74, (*v2)[4]);
    EXPECT_EQ(74, (*v2)[5]);
    EXPECT_EQ(47, (*v2)[6]);
    EXPECT_EQ(47, (*v2)[7]);
    EXPECT_EQ(47, (*v2)[8]);
    EXPECT_EQ(47, (*v2)[9]);

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

TEST(std_wobservable_vector_test_suite, test_wobservable_vector_erase_position)
{
    // Test erase position
    m::wobservable_vector<int>::ptr v = m::wobservable_vector<int>::create();
    vector_observer<int> o;

    EXPECT_EQ(0, v->size());

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    v->assign(a, a + 7);
    EXPECT_EQ(7, v->size());

    o.connect(v);

    m::wobservable_vector<int>::iterator it1 = v->begin();
    m::wobservable_vector<int>::iterator it2 = v->erase(it1 + 3);
    EXPECT_EQ(6, v->size());

    v->erase(it2);
    EXPECT_EQ(5, v->size());

    EXPECT_EQ(1, (*v)[0]);
    EXPECT_EQ(2, (*v)[1]);
    EXPECT_EQ(3, (*v)[2]);
    EXPECT_EQ(6, (*v)[3]);
    EXPECT_EQ(7, (*v)[4]);

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

TEST(std_wobservable_vector_test_suite, test_wobservable_vector_erase_range)
{
    // Test erase range
    m::wobservable_vector<int>::ptr v = m::wobservable_vector<int>::create();
    vector_observer<int> o;

    EXPECT_EQ(0, v->size());

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    v->assign(a, a + 7);
    EXPECT_EQ(7, v->size());

    o.connect(v);

    v->erase(v->begin() + 1, v->end() - 1);
    EXPECT_EQ(2, v->size());

    EXPECT_EQ(1, (*v)[0]);
    EXPECT_EQ(7, (*v)[1]);

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

TEST(std_wobservable_vector_test_suite, test_wobservable_vector_swap)
{
    // Test swap
    m::wobservable_vector<int>::ptr v1 = m::wobservable_vector<int>::create();
    m::wobservable_vector<int>::ptr v2 = m::wobservable_vector<int>::create();
    vector_observer<int> o1;
    vector_observer<int> o2;

    EXPECT_EQ(0, v1->size());
    EXPECT_EQ(0, v2->size());

    v1->assign(5, 1);
    v2->assign(7, 2);
    EXPECT_EQ(5, v1->size());
    EXPECT_EQ(7, v2->size());

    o1.connect(v1);
    o2.connect(v2);

    v1->swap(*v2);
    EXPECT_EQ(7, v1->size());
    EXPECT_EQ(5, v2->size());

    int count = 0;
    for(const int& i : *v1)
    {
        ++count;
        EXPECT_EQ(2, i);
    }
    EXPECT_EQ(7, count);

    count = 0;
    for(const int& i : *v2)
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

TEST(std_wobservable_vector_test_suite, test_wobservable_vector_clear)
{
    // Test clear
    m::wobservable_vector<int>::ptr v = m::wobservable_vector<int>::create();
    vector_observer<int> o;

    EXPECT_EQ(0, v->size());

    const int a[] = {1, 2, 3, 4, 5, 6, 7};
    v->assign(a, a + 7);
    EXPECT_EQ(7, v->size());

    o.connect(v);

    v->clear();
    EXPECT_EQ(0, v->size());

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

TEST(std_wobservable_vector_test_suite, test_observable_emplace)
{
    // Test emplace
    m::wobservable_vector<int>::ptr v = m::wobservable_vector<int>::create();
    vector_observer<int> o;

    const int a[] = {1, 2, 3};
    v->assign(a, a + 3);
    EXPECT_EQ(3, v->size());

    o.connect(v);

    m::wobservable_vector<int>::iterator it = v->emplace(v->begin() + 1, 4);
    EXPECT_EQ(4, *it);

    v->emplace(it, 5);
    v->emplace(v->end(), 6);
    EXPECT_EQ(6, v->size());

    EXPECT_EQ(1, (*v)[0]);
    EXPECT_EQ(5, (*v)[1]);
    EXPECT_EQ(4, (*v)[2]);
    EXPECT_EQ(2, (*v)[3]);
    EXPECT_EQ(3, (*v)[4]);
    EXPECT_EQ(6, (*v)[5]);

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

TEST(std_wobservable_vector_test_suite, test_observable_emplace_back)
{
    // Test emplace back
    m::wobservable_vector<int>::ptr v = m::wobservable_vector<int>::create();
    vector_observer<int> o;

    const int a[] = {1, 2, 3};
    v->assign(a, a + 3);
    EXPECT_EQ(3, v->size());

    o.connect(v);

    v->emplace_back(4);
    v->emplace_back(5);
    v->emplace_back(6);
    EXPECT_EQ(6, v->size());

    EXPECT_EQ(1, (*v)[0]);
    EXPECT_EQ(2, (*v)[1]);
    EXPECT_EQ(3, (*v)[2]);
    EXPECT_EQ(4, (*v)[3]);
    EXPECT_EQ(5, (*v)[4]);
    EXPECT_EQ(6, (*v)[5]);

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
