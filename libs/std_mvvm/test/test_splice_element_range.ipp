#ifndef GO_MVVM_TEST_SPLICE_ELEMENT_RANGE_IPP_INCLUDED
#define GO_MVVM_TEST_SPLICE_ELEMENT_RANGE_IPP_INCLUDED

//
//  test_splice_element_range.ipp
//
//  Copyright 2020-2022 Göran Orsander
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
inline void test_splice_element_range()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;

    // Test nnn
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer1;
    container_observer_type observer2;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    const int a1[] = { 1, 2, 3, 4 };
    container1->assign(a1, a1 + 4);
    EXPECT_EQ(4u, container1->size());

    const int a2[] = { 10, 20, 30, 40, 50 };
    container2->assign(a2, a2 + 5);
    EXPECT_EQ(5u, container2->size());

    observer1.connect(container1);
    observer2.connect(container2);

    container_iterator it1 = container1->begin();
    ++it1;
    EXPECT_EQ(2, *it1);

    container_iterator it2first = container2->begin();
    ++it2first;
    EXPECT_EQ(20, *it2first);

    container_iterator it2last = container2->begin();
    std::advance(it2last, 3);
    EXPECT_EQ(40, *it2last);

    container1->splice(it1, *container2, it2first, it2last);
    EXPECT_EQ(6u, container1->size());
    EXPECT_EQ(3u, container2->size());
    EXPECT_EQ(2, *it1);
    // it2first is invalid?
    // it2last is invalid?

    container_iterator it = container1->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(20, *it);
    ++it;
    EXPECT_EQ(30, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(container1->end(), it);

    it = container2->begin();
    EXPECT_EQ(10, *it);
    ++it;
    EXPECT_EQ(40, *it);
    ++it;
    EXPECT_EQ(50, *it);
    ++it;
    EXPECT_EQ(container2->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, observer1.last_action());
    EXPECT_EQ(1u, observer1.action_add_count());
    EXPECT_EQ(0u, observer1.action_remove_count());
    EXPECT_EQ(0u, observer1.action_reset_count());
    EXPECT_EQ(0u, observer1.action_swap_count());
    EXPECT_EQ(6u, observer1.last_change_new_size());
    EXPECT_EQ(2u, observer1.last_change_added());
    EXPECT_EQ(0u, observer1.last_change_removed());
    EXPECT_EQ(2u, observer1.total_change_added());
    EXPECT_EQ(0u, observer1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::remove, observer2.last_action());
    EXPECT_EQ(0u, observer2.action_add_count());
    EXPECT_EQ(1u, observer2.action_remove_count());
    EXPECT_EQ(0u, observer2.action_reset_count());
    EXPECT_EQ(0u, observer2.action_swap_count());
    EXPECT_EQ(3u, observer2.last_change_new_size());
    EXPECT_EQ(0u, observer2.last_change_added());
    EXPECT_EQ(2u, observer2.last_change_removed());
    EXPECT_EQ(0u, observer2.total_change_added());
    EXPECT_EQ(2u, observer2.total_change_removed());
}

}
}

#endif  // #if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT) || defined(GO_NO_CXX11_MUTEX))

#endif  // #ifndef GO_MVVM_TEST_SPLICE_ELEMENT_RANGE_IPP_INCLUDED
