#ifndef GO_BOOST_MVVM_TEST_CLEAR_IPP_INCLUDED
#define GO_BOOST_MVVM_TEST_CLEAR_IPP_INCLUDED

//
//  test_clear.ipp
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
inline void test_clear()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test clear
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

    container->clear();
    EXPECT_EQ(0u, container->size());

    EXPECT_EQ(m::notify_container_changed_action_reset, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(1u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(0u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(7u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(7u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_clear()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test clear
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

    container->clear();
    EXPECT_EQ(0u, container->size());

    EXPECT_EQ(m::notify_container_changed_action_reset, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(1u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(0u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(7u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(7u, observer.total_change_removed());
}

}
}
namespace set
{
namespace multi
{

template<class C>
inline void test_clear()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test clear
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

    container->clear();
    EXPECT_EQ(0u, container->size());

    EXPECT_EQ(m::notify_container_changed_action_reset, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(1u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(0u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(7u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(7u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_clear()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test clear
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

    container->clear();
    EXPECT_EQ(0u, container->size());

    EXPECT_EQ(m::notify_container_changed_action_reset, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(1u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(0u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(7u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(7u, observer.total_change_removed());
}

}
}
namespace unordered_map
{
namespace multi
{

template<class C>
inline void test_clear()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test clear
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

    container->clear();
    EXPECT_EQ(0u, container->size());

    EXPECT_EQ(m::notify_container_changed_action_reset, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(1u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(0u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(7u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(7u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_clear()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test clear
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

    container->clear();
    EXPECT_EQ(0u, container->size());

    EXPECT_EQ(m::notify_container_changed_action_reset, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(1u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(0u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(7u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(7u, observer.total_change_removed());
}

}
}
namespace unordered_set
{
namespace multi
{

template<class C>
inline void test_clear()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test clear
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

    container->clear();
    EXPECT_EQ(0u, container->size());

    EXPECT_EQ(m::notify_container_changed_action_reset, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(1u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(0u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(7u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(7u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_clear()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

    // Test clear
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

    container->clear();
    EXPECT_EQ(0u, container->size());

    EXPECT_EQ(m::notify_container_changed_action_reset, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(1u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(0u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(7u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(7u, observer.total_change_removed());
}

}
}
}
namespace sequence
{

template<class C>
inline void test_clear()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;

    // Test clear
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    const int a[] = { 1, 2, 3, 4, 5, 6, 7 };
    container->assign(a, a + 7);
    EXPECT_EQ(7u, container->size());

    observer.connect(container);

    container->clear();
    EXPECT_EQ(0u, container->size());

    EXPECT_EQ(m::notify_container_changed_action_reset, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(1u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(0u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(7u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(7u, observer.total_change_removed());
}

}
}

#endif  // #ifndef GO_BOOST_MVVM_TEST_CLEAR_IPP_INCLUDED
