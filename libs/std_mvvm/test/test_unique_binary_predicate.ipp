#ifndef GO_MVVM_TEST_UNIQUE_BINARY_PREDICATE_IPP_INCLUDED
#define GO_MVVM_TEST_UNIQUE_BINARY_PREDICATE_IPP_INCLUDED

//
//  test_unique_binary_predicate.ipp
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

struct same_integral_part
{
    bool operator()(double first, double second) const
    {
        return int(first) == int(second);
    }
};

template<class C>
inline void test_unique_binary_predicate()
{
    typedef C test_container_type;
    typedef typename test_container_type::string_type string_type;
    typedef typename test_container_type::lockable_type lockable_type;
    typedef container_observer<test_container_type, string_type, lockable_type> container_observer_type;
    typedef typename test_container_type::iterator container_iterator;
    typedef typename test_container_type::ptr container_ptr;

    // Test unique binary predicate
    container_ptr container = test_container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    const double a[] = { 12.15, 2.72, 73.0, 12.77, 3.14, 12.77, 73.35, 72.25, 15.3, 72.25 };
    container->assign(a, a + 10);
    EXPECT_EQ(10u, container->size());

    container->sort();
    observer.connect(container);

    container->unique();
    EXPECT_EQ(8u, container->size());

    container->unique(same_integral_part());
    EXPECT_EQ(6u, container->size());

    container_iterator it = container->begin();
    EXPECT_EQ(2.72, *it);
    ++it;
    EXPECT_EQ(3.14, *it);
    ++it;
    EXPECT_EQ(12.15, *it);
    ++it;
    EXPECT_EQ(15.3, *it);
    ++it;
    EXPECT_EQ(72.25, *it);
    ++it;
    EXPECT_EQ(73.0, *it);
    ++it;
    EXPECT_EQ(container->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::remove, observer.last_action());
    EXPECT_EQ(0u, observer.action_add_count());
    EXPECT_EQ(2u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(6u, observer.last_change_new_size());
    EXPECT_EQ(0u, observer.last_change_added());
    EXPECT_EQ(2u, observer.last_change_removed());
    EXPECT_EQ(0u, observer.total_change_added());
    EXPECT_EQ(4u, observer.total_change_removed());
}

}
}

#endif  // #ifndef GO_MVVM_TEST_UNIQUE_BINARY_PREDICATE_IPP_INCLUDED
