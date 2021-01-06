#ifndef GO_BOOST_MVVM_TEST_SPLICE_AFTER_SINGLE_ELEMENT_IPP_INCLUDED
#define GO_BOOST_MVVM_TEST_SPLICE_AFTER_SINGLE_ELEMENT_IPP_INCLUDED

//
//  test_splice_after_single_element.ipp
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
inline void test_splice_after_single_element()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;

    // Test splice after single element
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer1;
    container_observer_type observer2;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    const int a2[] = { 1, 10, 20, 30, 2, 3, 4 };
    container2->assign(a2, a2 + 7);
    EXPECT_EQ(7u, container2->size());

    observer1.connect(container1);
    observer2.connect(container2);

    container_iterator it2 = container2->begin();
    std::advance(it2, 4);
    EXPECT_EQ(2, *it2);

    container_iterator it1 = container1->begin();
    container1->splice_after(it1, *container2, it2);
    EXPECT_EQ(1u, container1->size());
    EXPECT_EQ(6u, container2->size());
    // it1 is invalid
    // it2 is invalid

    it1 = container1->begin();
    EXPECT_EQ(3, *it1);
    ++it1;
    EXPECT_EQ(container1->end(), it1);

    it2 = container2->begin();
    EXPECT_EQ(1, *it2);
    ++it2;
    EXPECT_EQ(10, *it2);
    ++it2;
    EXPECT_EQ(20, *it2);
    ++it2;
    EXPECT_EQ(30, *it2);
    ++it2;
    EXPECT_EQ(2, *it2);
    ++it2;
    EXPECT_EQ(4, *it2);
    ++it2;
    EXPECT_EQ(container2->end(), it2);

    EXPECT_EQ(m::notify_container_changed_action_add, observer1.last_action());
    EXPECT_EQ(1u, observer1.action_add_count());
    EXPECT_EQ(0u, observer1.action_remove_count());
    EXPECT_EQ(0u, observer1.action_reset_count());
    EXPECT_EQ(0u, observer1.action_swap_count());
    EXPECT_EQ(1u, observer1.last_change_new_size());
    EXPECT_EQ(1u, observer1.last_change_added());
    EXPECT_EQ(0u, observer1.last_change_removed());
    EXPECT_EQ(1u, observer1.total_change_added());
    EXPECT_EQ(0u, observer1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action_remove, observer2.last_action());
    EXPECT_EQ(0u, observer2.action_add_count());
    EXPECT_EQ(1u, observer2.action_remove_count());
    EXPECT_EQ(0u, observer2.action_reset_count());
    EXPECT_EQ(0u, observer2.action_swap_count());
    EXPECT_EQ(6u, observer2.last_change_new_size());
    EXPECT_EQ(0u, observer2.last_change_added());
    EXPECT_EQ(1u, observer2.last_change_removed());
    EXPECT_EQ(0u, observer2.total_change_added());
    EXPECT_EQ(1u, observer2.total_change_removed());
}

}
}

#endif  // #ifndef GO_BOOST_MVVM_TEST_SPLICE_AFTER_SINGLE_ELEMENT_IPP_INCLUDED
