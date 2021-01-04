#ifndef GO_BOOST_MVVM_TEST_ERASE_VALUE_IPP_INCLUDED
#define GO_BOOST_MVVM_TEST_ERASE_VALUE_IPP_INCLUDED

//
//  test_erase_value.ipp
//
//  Copyright 2020 Göran Orsander
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
inline void test_erase_value()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test erase value
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    container->insert(container_value_type(1, 10));
    container->insert(container_value_type(2, 20));
    container->insert(container_value_type(3, 30));
    container->insert(container_value_type(4, 40));
    container->insert(container_value_type(5, 50));
    container->insert(container_value_type(6, 60));
    container->insert(container_value_type(7, 70));
    EXPECT_EQ(7u, container->size());

    observer.connect(container);

    container->erase(4);
    EXPECT_EQ(6u, container->size());

    container->erase(5);
    EXPECT_EQ(5u, container->size());

    container_iterator it = container->begin();
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
    EXPECT_EQ(container->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_remove, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(2u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(5u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(1u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(2u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_erase_value()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test erase value
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    (*container)[1] = 10;
    (*container)[2] = 20;
    (*container)[3] = 30;
    (*container)[4] = 40;
    (*container)[5] = 50;
    (*container)[6] = 60;
    (*container)[7] = 70;
    EXPECT_EQ(7u, container->size());

    observer.connect(container);

    container->erase(4);
    EXPECT_EQ(6u, container->size());

    container->erase(5);
    EXPECT_EQ(5u, container->size());

    container_iterator it = container->begin();
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
    EXPECT_EQ(container->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_remove, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(2u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(5u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(1u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(2u, observer.total_change_removed());
}

}
}
namespace set
{
namespace multi
{

template<class C>
inline void test_erase_value()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test erase value
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    container->insert(1);
    container->insert(2);
    container->insert(3);
    container->insert(4);
    container->insert(5);
    container->insert(6);
    container->insert(7);
    EXPECT_EQ(7u, container->size());

    observer.connect(container);

    container->erase(4);
    EXPECT_EQ(6u, container->size());

    container->erase(5);
    EXPECT_EQ(5u, container->size());

    container_iterator it = container->begin();
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
    EXPECT_EQ(container->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_remove, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(2u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(5u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(1u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(2u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_erase_value()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test erase value
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    container->insert(1);
    container->insert(2);
    container->insert(3);
    container->insert(4);
    container->insert(5);
    container->insert(6);
    container->insert(7);
    EXPECT_EQ(7u, container->size());

    observer.connect(container);

    container->erase(4);
    EXPECT_EQ(6u, container->size());

    container->erase(5);
    EXPECT_EQ(5u, container->size());

    container_iterator it = container->begin();
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
    EXPECT_EQ(container->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_remove, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(2u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(5u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(1u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(2u, observer.total_change_removed());
}

}
}
namespace unordered_map
{
namespace multi
{

template<class C>
inline void test_erase_value()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test erase value
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    container->insert(container_value_type(1, 10));
    container->insert(container_value_type(2, 20));
    container->insert(container_value_type(3, 30));
    container->insert(container_value_type(4, 40));
    container->insert(container_value_type(5, 50));
    container->insert(container_value_type(6, 60));
    container->insert(container_value_type(7, 70));
    EXPECT_EQ(7u, container->size());

    observer.connect(container);

    container->erase(4);
    EXPECT_EQ(6u, container->size());

    container->erase(5);
    EXPECT_EQ(5u, container->size());

    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const container_value_type& i, *container)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(5u, count);
    EXPECT_EQ(190, sum);

    EXPECT_EQ(m::notify_container_changed_action_remove, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(2u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(5u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(1u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(2u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_erase_value()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test erase value
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    (*container)[1] = 10;
    (*container)[2] = 20;
    (*container)[3] = 30;
    (*container)[4] = 40;
    (*container)[5] = 50;
    (*container)[6] = 60;
    (*container)[7] = 70;
    EXPECT_EQ(7u, container->size());

    observer.connect(container);

    container->erase(4);
    EXPECT_EQ(6u, container->size());

    container->erase(5);
    EXPECT_EQ(5u, container->size());

    typedef container_type observable_unordered_map_type;
    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const container_value_type & i, *container)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(5u, count);
    EXPECT_EQ(190, sum);

    EXPECT_EQ(m::notify_container_changed_action_remove, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(2u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(5u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(1u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(2u, observer.total_change_removed());
}

}
}
namespace unordered_set
{
namespace multi
{

template<class C>
inline void test_erase_value()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test erase value
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    container->insert(1);
    container->insert(2);
    container->insert(3);
    container->insert(4);
    container->insert(5);
    container->insert(6);
    container->insert(7);
    EXPECT_EQ(7u, container->size());

    observer.connect(container);

    container->erase(4);
    EXPECT_EQ(6u, container->size());

    container->erase(5);
    EXPECT_EQ(5u, container->size());

    typedef container_type observable_unordered_multiset_type;
    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const container_value_type& i, *container)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(5u, count);
    EXPECT_EQ(19, sum);

    EXPECT_EQ(m::notify_container_changed_action_remove, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(2u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(5u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(1u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(2u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_erase_value()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test erase value
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    container->insert(1);
    container->insert(2);
    container->insert(3);
    container->insert(4);
    container->insert(5);
    container->insert(6);
    container->insert(7);
    EXPECT_EQ(7u, container->size());

    observer.connect(container);

    container->erase(4);
    EXPECT_EQ(6u, container->size());

    container->erase(5);
    EXPECT_EQ(5u, container->size());

    typedef container_type observable_unordered_set_type;
    unsigned int count = 0u;
    int sum = 0;
    BOOST_FOREACH(const GO_BOOST_TYPENAME observable_unordered_set_type::value_type & i, *container)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(5u, count);
    EXPECT_EQ(19, sum);

    EXPECT_EQ(m::notify_container_changed_action_remove, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(2u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(5u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(1u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(2u, observer.total_change_removed());
}

}
}
}
}

#endif  // #ifndef GO_BOOST_MVVM_TEST_ERASE_VALUE_IPP_INCLUDED
