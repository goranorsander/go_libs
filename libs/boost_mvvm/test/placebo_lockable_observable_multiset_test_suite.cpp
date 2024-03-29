//
//  placebo_lockable_observable_multiset_test_suite.cpp
//
//  Copyright 2018-2022 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "test_clear.ipp"
#include "test_emplace.ipp"
#include "test_emplace_hint.ipp"
#include "test_erase_position.ipp"
#include "test_erase_range.ipp"
#include "test_erase_value.ipp"
#include "test_insert_initializer_list.ipp"
#include "test_insert_range.ipp"
#include "test_insert_single_element.ipp"
#include "test_insert_single_element_with_hint.ipp"
#include "test_swap.ipp"

namespace
{

typedef m::observable_multiset<int, a::placebo_lockable> container_type;

TEST(boost_observable_multiset_placebo_lockable_test_suite, test_insert_single_element)
{
    go_boost_test::associative::set::multi::test_insert_single_element<container_type>();
}

TEST(boost_observable_multiset_placebo_lockable_test_suite, test_insert_single_element_with_hint)
{
    go_boost_test::associative::set::multi::test_insert_single_element_with_hint<container_type>();
}

TEST(boost_observable_multiset_placebo_lockable_test_suite, test_insert_range)
{
    go_boost_test::associative::set::multi::test_insert_range<container_type>();
}

TEST(boost_observable_multiset_placebo_lockable_test_suite, test_insert_initializer_list)
{
    go_boost_test::associative::set::multi::test_insert_initializer_list<container_type>();
}

TEST(boost_observable_multiset_placebo_lockable_test_suite, test_erase_position)
{
    go_boost_test::associative::set::multi::test_erase_position<container_type>();
}

TEST(boost_observable_multiset_placebo_lockable_test_suite, test_erase_value)
{
    go_boost_test::associative::set::multi::test_erase_value<container_type>();
}

TEST(boost_observable_multiset_placebo_lockable_test_suite, test_erase_range)
{
    go_boost_test::associative::set::multi::test_erase_range<container_type>();
}

TEST(boost_observable_multiset_placebo_lockable_test_suite, test_swap)
{
    go_boost_test::associative::set::multi::test_swap<container_type>();
}

TEST(boost_observable_multiset_placebo_lockable_test_suite, test_clear)
{
    go_boost_test::associative::set::multi::test_clear<container_type>();
}

TEST(boost_observable_multiset_placebo_lockable_test_suite, test_emplace)
{
    go_boost_test::associative::set::multi::test_emplace<container_type>();
}

TEST(boost_observable_multiset_placebo_lockable_test_suite, test_emplace_hint)
{
    go_boost_test::associative::set::multi::test_emplace_hint<container_type>();
}

}
