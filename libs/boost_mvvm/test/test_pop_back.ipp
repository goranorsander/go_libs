#ifndef GO_BOOST_MVVM_TEST_POP_BACK_IPP_INCLUDED
#define GO_BOOST_MVVM_TEST_POP_BACK_IPP_INCLUDED

//
//  TEST_POP_BACK.ipp
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
namespace sequence
{

template<class C>
inline void test_pop_back()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;

    // Test pop back
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    container->assign(7, 47);
    EXPECT_EQ(7u, container->size());

    observer.connect(container);

    container->pop_back();
    EXPECT_EQ(6u, container->size());

    container->pop_back();
    EXPECT_EQ(5u, container->size());

    container->pop_back();
    EXPECT_EQ(4u, container->size());

    unsigned int count = 0u;
    BOOST_FOREACH(const int& i, *container)
    {
        ++count;
        EXPECT_EQ(47, i);
    }
    EXPECT_EQ(4u, count);

    EXPECT_EQ(m::notify_container_changed_action_remove, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(3u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(4u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(1u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(3u, observer.total_change_removed());
}

}
}

#endif  // #ifndef GO_BOOST_MVVM_TEST_POP_BACK_IPP_INCLUDED
