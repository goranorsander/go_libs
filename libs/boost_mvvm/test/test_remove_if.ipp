#ifndef GO_BOOST_MVVM_TEST_REMOVE_IF_IPP_INCLUDED
#define GO_BOOST_MVVM_TEST_REMOVE_IF_IPP_INCLUDED

//
//  test_remove_if.ipp
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

struct is_odd
{
    bool operator()(const int& value) const
    {
        return (value % 2) == 1;
    }
};

template<class C>
inline void test_remove_if()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;

    // Test nnn
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    const int a[] = { 10, 20, 47, 30, 47, 47, 40 };
    container->assign(a, a + 7);
    EXPECT_EQ(7u, container->size());

    observer.connect(container);

    container->remove_if(is_odd());
    EXPECT_EQ(4u, container->size());

    container_iterator it = container->begin();
    EXPECT_EQ(10, *it);
    ++it;
    EXPECT_EQ(20, *it);
    ++it;
    EXPECT_EQ(30, *it);
    ++it;
    EXPECT_EQ(40, *it);
    ++it;
    EXPECT_EQ(container->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_remove, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(1u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(4u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(3u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(3u, observer.total_change_removed());
}

}
}

#endif  // #ifndef GO_BOOST_MVVM_TEST_REMOVE_IF_IPP_INCLUDED
