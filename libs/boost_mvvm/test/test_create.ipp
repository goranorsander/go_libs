#ifndef GO_BOOST_MVVM_TEST_CREATE_IPP_INCLUDED
#define GO_BOOST_MVVM_TEST_CREATE_IPP_INCLUDED

//
//  test_create.ipp
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
namespace array
{

template<class C>
inline void test_create()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;

    // Test create
    container_ptr container = container_type::create();
    container_observer_type observer;
    observer.connect(container);

    EXPECT_EQ(7u, container->size());
    EXPECT_EQ(7u, container->max_size());

    for (int i = 0; i < 7; i++)
    {
        (*container)[i] = i;
    }

    for (int i = 0; i < 7; i++)
    {
        EXPECT_EQ((*container)[i], i);
    }

    unsigned int count = 0u;
    BOOST_FOREACH(const int& i, *container)
    {
        EXPECT_EQ(static_cast<int>(count), i);
        ++count;
    }
    EXPECT_EQ(7u, count);

    EXPECT_EQ(m::undefined_notify_container_changed_action, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(0u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}
}

#endif  // #ifndef GO_BOOST_MVVM_TEST_CREATE_IPP_INCLUDED
