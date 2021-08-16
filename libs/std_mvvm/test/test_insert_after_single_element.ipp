#ifndef GO_MVVM_TEST_INSERT_AFTER_SINGLE_ELEMENT_IPP_INCLUDED
#define GO_MVVM_TEST_INSERT_AFTER_SINGLE_ELEMENT_IPP_INCLUDED

//
//  test_insert_after_single_element.ipp
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

#if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT) || defined(GO_NO_CXX11_MUTEX))

namespace go_test
{
namespace sequence
{

template<class C>
inline void test_insert_after_single_element()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;

    // Test insert after single element
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    const int a[] = { 1, 2, 3, 5, 6, 7 };
    container->assign(a, a + 6);
    EXPECT_EQ(6u, container->size());

    observer.connect(container);

    container_iterator it = container->begin();
    std::advance(it, 2);
    container->insert_after(it, 4);
    EXPECT_EQ(7u, container->size());

    unsigned int count = 0u;
    for (const int& i : *container)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i);
    }
    EXPECT_EQ(7u, count);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(1u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}

#endif  // #if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT) || defined(GO_NO_CXX11_MUTEX))

#endif  // #ifndef GO_MVVM_TEST_INSERT_AFTER_SINGLE_ELEMENT_IPP_INCLUDED
