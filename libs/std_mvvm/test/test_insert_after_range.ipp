#ifndef GO_MVVM_TEST_INSERT_AFTER_RANGE_IPP_INCLUDED
#define GO_MVVM_TEST_INSERT_AFTER_RANGE_IPP_INCLUDED

//
//  test_insert_after_range.ipp
//
//  Copyright 2020-2021 G�ran Orsander
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

#if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT) || defined(GO_NO_CXX11_MUTEX))

namespace go_test
{
namespace sequence
{

template<class C>
inline void test_insert_after_range()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;

    // Test insert after range
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container1->size());

    container1->assign(3, 74);
    EXPECT_EQ(3u, container1->size());

    EXPECT_EQ(0u, container2->size());
    container2->assign(7, 47);
    EXPECT_EQ(7u, container2->size());

    observer.connect(container2);

    container_iterator it = container2->begin();
    std::advance(it, 3);
    container2->insert_after(it, container1->begin(), container1->end());
    EXPECT_EQ(10u, container2->size());

    it = container2->begin();
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(74, *it);
    ++it;
    EXPECT_EQ(74, *it);
    ++it;
    EXPECT_EQ(74, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(container2->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(10u, observer.last_change_new_size());
    EXPECT_EQ(3u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}

#endif  // #if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT) || defined(GO_NO_CXX11_MUTEX))

#endif  // #ifndef GO_MVVM_TEST_INSERT_AFTER_RANGE_IPP_INCLUDED