#ifndef GO_MVVM_TEST_ERASE_AFTER_POSITION_IPP_INCLUDED
#define GO_MVVM_TEST_ERASE_AFTER_POSITION_IPP_INCLUDED

//
//  test_erase_after_position.ipp
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
inline void test_erase_after_position()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;

    // Test erase position
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    const int a[] = { 1, 2, 3, 4, 5, 6, 7 };
    container->assign(a, a + 7);
    EXPECT_EQ(7u, container->size());

    observer.connect(container);

    container_iterator it1 = container->begin();
    std::advance(it1, 3);
    container_iterator it2 = container->erase_after(it1);
    EXPECT_EQ(6u, container->size());

    container->erase_after(it2);
    EXPECT_EQ(5u, container->size());

    it1 = container->begin();
    EXPECT_EQ(1, *it1);
    ++it1;
    EXPECT_EQ(2, *it1);
    ++it1;
    EXPECT_EQ(3, *it1);
    ++it1;
    EXPECT_EQ(4, *it1);
    ++it1;
    EXPECT_EQ(6, *it1);
    ++it1;
    EXPECT_EQ(container->end(), it1);

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

#endif  // #ifndef GO_MVVM_TEST_ERASE_AFTER_POSITION_IPP_INCLUDED
