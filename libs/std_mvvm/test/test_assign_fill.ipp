#ifndef GO_MVVM_TEST_ASSIGN_FILL_IPP_INCLUDED
#define GO_MVVM_TEST_ASSIGN_FILL_IPP_INCLUDED

//
//  test_assign_fill.ipp
//
//  Copyright 2020-2022 G�ran Orsander
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
namespace indexed
{

template<class C>
inline void test_assign_fill()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;

    // Test assign fill
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    observer.connect(container2);

    const int a[] = { 1, 2, 3, 4, 5, 6, 7 };
    container1->assign(a, a + 7);
    EXPECT_EQ(7u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container_iterator it = container1->begin();
    ++it;

    container2->assign(it, container1->end() - 1);
    EXPECT_EQ(7u, container1->size());
    EXPECT_EQ(5u, container2->size());

    unsigned int count = 0u;
    for (const int& i : *container2)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count) + 1, i);
    }
    EXPECT_EQ(5u, count);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(5u, observer.last_change_new_size());
    EXPECT_EQ(5u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(5u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
namespace linked
{

template<class C>
inline void test_assign_fill()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;

    // Test assign fill
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    observer.connect(container2);

    const int a[] = { 1, 2, 3, 4, 5, 6, 7 };
    container1->assign(a, a + 7);
    EXPECT_EQ(7u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container_iterator begin = container1->begin();
    ++begin;
    container_iterator end = begin;
    std::advance(end, 5);

    container2->assign(begin, end);
    EXPECT_EQ(7u, container1->size());
    EXPECT_EQ(5u, container2->size());

    unsigned int count = 0u;
    for (const int& i : *container2)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count) + 1, i);
    }
    EXPECT_EQ(5u, count);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(5u, observer.last_change_new_size());
    EXPECT_EQ(5u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(5u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}
}

#endif  // #if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT) || defined(GO_NO_CXX11_MUTEX))

#endif  // #ifndef GO_MVVM_TEST_ASSIGN_FILL_IPP_INCLUDED
