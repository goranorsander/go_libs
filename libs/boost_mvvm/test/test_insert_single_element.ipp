#ifndef GO_BOOST_MVVM_TEST_INSERT_SINGLE_ELEMENT_IPP_INCLUDED
#define GO_BOOST_MVVM_TEST_INSERT_SINGLE_ELEMENT_IPP_INCLUDED

//
//  test_insert_single_element.ipp
//
//  Copyright 2020-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/foreach.hpp>

#include <go_boost/mvvm.hpp>
#include <go_boost/utility.hpp>

#include "test_container_observer.ipp"

namespace go_boost_test
{
namespace associative
{
namespace map
{
namespace multi
{

template<class C>
inline void test_insert_single_element()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test insert single element
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());
    container->insert(container_value_type(1, 10));
    container->insert(container_value_type(2, 20));
    container->insert(container_value_type(4, 40));
    container->insert(container_value_type(5, 50));
    container->insert(container_value_type(6, 60));
    container->insert(container_value_type(7, 70));
    EXPECT_EQ(6u, container->size());

    observer.connect(container);

    container->insert(container_value_type(3, 30));
    EXPECT_EQ(7u, container->size());

    typedef container_type observable_multimap_type;
    unsigned int count = 0u;
    BOOST_FOREACH(const container_value_type & i, *container)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i.first);
        EXPECT_EQ(static_cast<int>(count) * 10, i.second);
    }
    EXPECT_EQ(7u, count);

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(1u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_insert_single_element()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test insert single element
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    (*container)[1] = 10;
    (*container)[2] = 20;
    (*container)[4] = 40;
    (*container)[5] = 50;
    (*container)[6] = 60;
    (*container)[7] = 70;
    EXPECT_EQ(6u, container->size());

    observer.connect(container);

    container->insert(container_value_type(3, 30));
    EXPECT_EQ(7u, container->size());

    unsigned int count = 0u;
    BOOST_FOREACH(const container_value_type& i, *container)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i.first);
        EXPECT_EQ(static_cast<int>(count) * 10, i.second);
    }
    EXPECT_EQ(7u, count);

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(1u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}
namespace set
{
namespace multi
{

template<class C>
inline void test_insert_single_element()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test insert single element
    container_ptr container = container_type::create();
    container_observer_type observer;

    // TODO: Find a way to test insert without using insert to prepare the test
    EXPECT_EQ(0u, container->size());
    container->insert(1);
    container->insert(2);
    container->insert(4);
    container->insert(5);
    container->insert(6);
    container->insert(7);
    EXPECT_EQ(6u, container->size());

    observer.connect(container);

    container->insert(3);
    EXPECT_EQ(7u, container->size());

    unsigned int count = 0u;
    BOOST_FOREACH(const int& i, *container)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i);
    }
    EXPECT_EQ(7u, count);

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(1u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_insert_single_element()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test insert single element
    container_ptr container = container_type::create();
    container_observer_type observer;

    // TODO: Find a way to test insert without using insert to prepare the test
    EXPECT_EQ(0u, container->size());
    container->insert(1);
    container->insert(2);
    container->insert(4);
    container->insert(5);
    container->insert(6);
    container->insert(7);
    EXPECT_EQ(6u, container->size());

    observer.connect(container);

    container->insert(3);
    EXPECT_EQ(7u, container->size());

    unsigned int count = 0u;
    BOOST_FOREACH(const int& i, *container)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i);
    }
    EXPECT_EQ(7u, count);

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(1u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}
namespace unordered_map
{
namespace multi
{

template<class C>
inline void test_insert_single_element()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test insert single element
    container_ptr container = container_type::create();
    container_observer_type observer;

    // TODO: Find a way to test insert without using insert to prepare the test
    EXPECT_EQ(0u, container->size());
    container->insert(container_value_type(1, 10));
    container->insert(container_value_type(2, 20));
    container->insert(container_value_type(4, 40));
    container->insert(container_value_type(5, 50));
    container->insert(container_value_type(6, 60));
    container->insert(container_value_type(7, 70));
    EXPECT_EQ(6u, container->size());

    observer.connect(container);

    container->insert(container_value_type(3, 30));
    EXPECT_EQ(7u, container->size());

    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const container_value_type& i, *container)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(280, sum);

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(1u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_insert_single_element()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test insert single element
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());
    (*container)[1] = 10;
    (*container)[2] = 20;
    (*container)[4] = 40;
    (*container)[5] = 50;
    (*container)[6] = 60;
    (*container)[7] = 70;
    EXPECT_EQ(6u, container->size());

    observer.connect(container);

    container->insert(container_value_type(3, 30));
    EXPECT_EQ(7u, container->size());

    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const container_value_type & i, *container)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(280, sum);

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(1u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}
namespace unordered_set
{
namespace multi
{

template<class C>
inline void test_insert_single_element()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test insert single element
    container_ptr container = container_type::create();
    container_observer_type observer;

    // TODO: Find a way to test insert without using insert to prepare the test
    EXPECT_EQ(0u, container->size());
    container->insert(1);
    container->insert(2);
    container->insert(4);
    container->insert(5);
    container->insert(6);
    container->insert(7);
    EXPECT_EQ(6u, container->size());

    observer.connect(container);

    container->insert(3);
    EXPECT_EQ(7u, container->size());

    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const container_value_type & i, *container)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(28, sum);

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(1u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_insert_single_element()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test insert single element
    container_ptr container = container_type::create();
    container_observer_type observer;

    // TODO: Find a way to test insert without using insert to prepare the test
    EXPECT_EQ(0u, container->size());
    container->insert(1);
    container->insert(2);
    container->insert(4);
    container->insert(5);
    container->insert(6);
    container->insert(7);
    EXPECT_EQ(6u, container->size());

    observer.connect(container);

    container->insert(3);
    EXPECT_EQ(7u, container->size());

    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const int& i, *container)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(28, sum);

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(1u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}
}
namespace sequence
{

template<class C>
inline void test_insert_single_element()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;

    // Test insert single element
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    const int a[] = { 1, 2, 4, 5, 6, 7 };
    container->assign(a, a + 6);
    EXPECT_EQ(6u, container->size());

    observer.connect(container);

    container_iterator it = container->begin();
    std::advance(it, 2);
    container->insert(it, 3);
    EXPECT_EQ(7u, container->size());

    unsigned int count = 0u;
    BOOST_FOREACH(const int& i, *container)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i);
    }
    EXPECT_EQ(7u, count);

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(1u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}

#endif  // #ifndef GO_BOOST_MVVM_TEST_INSERT_SINGLE_ELEMENT_IPP_INCLUDED
