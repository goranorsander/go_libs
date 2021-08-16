#ifndef GO_MVVM_TEST_CREATE_IPP_INCLUDED
#define GO_MVVM_TEST_CREATE_IPP_INCLUDED

//
//  test_create.ipp
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
namespace array
{

template<class C>
inline void test_create()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;

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
    for (const int& i : *container)
    {
        EXPECT_EQ(static_cast<int>(count), i);
        ++count;
    }
    EXPECT_EQ(7u, count);

    EXPECT_EQ(m::notify_container_changed_action::undefined, observer.last_action());
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

#endif  // #if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT) || defined(GO_NO_CXX11_MUTEX))

#endif  // #ifndef GO_MVVM_TEST_CREATE_IPP_INCLUDED
