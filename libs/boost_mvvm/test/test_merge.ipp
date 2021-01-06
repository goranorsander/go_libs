#ifndef GO_BOOST_MVVM_TEST_MERGE_IPP_INCLUDED
#define GO_BOOST_MVVM_TEST_MERGE_IPP_INCLUDED

//
//  test_merge.ipp
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
namespace sequence
{

template<class C>
inline void test_merge()
{
    typedef C test_container_type;
    typedef typename test_container_type::string_type string_type;
    typedef typename test_container_type::lockable_type lockable_type;
    typedef container_observer<test_container_type, string_type, lockable_type> container_observer_type;
    typedef typename test_container_type::iterator container_iterator;
    typedef typename test_container_type::ptr container_ptr;

    // Test merge
    container_ptr container1 = test_container_type::create();
    container_ptr container2 = test_container_type::create();
    container_observer_type observer1;
    container_observer_type observer2;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    const double a1[] = { 3.1, 2.2, 2.9 };
    container1->assign(a1, a1 + 3);
    EXPECT_EQ(3u, container1->size());

    const double a2[] = { 3.7, 7.1, 1.4 };
    container2->assign(a2, a2 + 3);
    EXPECT_EQ(3u, container2->size());

    observer1.connect(container1);
    observer2.connect(container2);

    container1->sort();
    container2->sort();

    container1->merge(*container2);
    EXPECT_EQ(6u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container_iterator it = container1->begin();
    EXPECT_EQ(1.4, *it);
    ++it;
    EXPECT_EQ(2.2, *it);
    ++it;
    EXPECT_EQ(2.9, *it);
    ++it;
    EXPECT_EQ(3.1, *it);
    ++it;
    EXPECT_EQ(3.7, *it);
    ++it;
    EXPECT_EQ(7.1, *it);
    ++it;
    EXPECT_EQ(container1->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, observer1.last_action());
    EXPECT_EQ(1u, observer1.action_add_count());
    EXPECT_EQ(0u, observer1.action_remove_count());
    EXPECT_EQ(0u, observer1.action_reset_count());
    EXPECT_EQ(0u, observer1.action_swap_count());
    EXPECT_EQ(6u, observer1.last_change_new_size());
    EXPECT_EQ(3u, observer1.last_change_added());
    EXPECT_EQ(0u, observer1.last_change_removed());
    EXPECT_EQ(3u, observer1.total_change_added());
    EXPECT_EQ(0u, observer1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action_remove, observer2.last_action());
    EXPECT_EQ(0u, observer2.action_add_count());
    EXPECT_EQ(1u, observer2.action_remove_count());
    EXPECT_EQ(0u, observer2.action_reset_count());
    EXPECT_EQ(0u, observer2.action_swap_count());
    EXPECT_EQ(0u, observer2.last_change_new_size());
    EXPECT_EQ(0u, observer2.last_change_added());
    EXPECT_EQ(3u, observer2.last_change_removed());
    EXPECT_EQ(0u, observer2.total_change_added());
    EXPECT_EQ(3u, observer2.total_change_removed());
}

}
}

#endif  // #ifndef GO_BOOST_MVVM_TEST_MERGE_IPP_INCLUDED
