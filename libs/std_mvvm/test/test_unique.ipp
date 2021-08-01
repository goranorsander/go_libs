#ifndef GO_MVVM_TEST_UNIQUE_IPP_INCLUDED
#define GO_MVVM_TEST_UNIQUE_IPP_INCLUDED

//
//  test_unique.ipp
//
//  Copyright 2020-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#include <go/mvvm.hpp>
#include <go/utility.hpp>

#include "test_container_observer.ipp"

namespace go_test
{
namespace sequence
{

template<class C>
inline void test_unique()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;

    // Test unique
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    const int a[] = { 10, 20, 47, 30, 47, 47, 40 };
    container->assign(a, a + 7);
    EXPECT_EQ(7u, container->size());

    observer.connect(container);

    container->unique();
    EXPECT_EQ(6u, container->size());

    container_iterator it = container->begin();
    EXPECT_EQ(10, *it);
    ++it;
    EXPECT_EQ(20, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(30, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(40, *it);
    ++it;
    EXPECT_EQ(container->end(), it);

    container->sort();
    container->unique();
    EXPECT_EQ(5u, container->size());

    it = container->begin();
    EXPECT_EQ(10, *it);
    ++it;
    EXPECT_EQ(20, *it);
    ++it;
    EXPECT_EQ(30, *it);
    ++it;
    EXPECT_EQ(40, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(container->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::remove, observer.last_action());
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

#endif  // #ifndef GO_MVVM_TEST_UNIQUE_IPP_INCLUDED
