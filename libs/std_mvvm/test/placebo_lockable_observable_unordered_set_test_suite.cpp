//
//  placebo_lockable_observable_unordered_set_test_suite.cpp
//
//  Copyright 2018-2022 Göran Orsander
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

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT)
TEST(std_observable_unordered_set_placebo_lockable_test_suite, required_cpp11_feature_not_supported) {}
#else

using container_type = m::observable_unordered_set<int, a::placebo_lockable>;

TEST(std_observable_unordered_set_placebo_lockable_test_suite, test_insert_single_element)
{
    go_test::associative::unordered_set::unique::test_insert_single_element<container_type>();
}

TEST(std_observable_unordered_set_placebo_lockable_test_suite, test_insert_single_element_with_hint)
{
    go_test::associative::unordered_set::unique::test_insert_single_element_with_hint<container_type>();
}

TEST(std_observable_unordered_set_placebo_lockable_test_suite, test_insert_range)
{
    go_test::associative::unordered_set::unique::test_insert_range<container_type>();
}

TEST(std_observable_unordered_set_placebo_lockable_test_suite, test_insert_initializer_list)
{
    go_test::associative::unordered_set::unique::test_insert_initializer_list<container_type>();
}

TEST(std_observable_unordered_set_placebo_lockable_test_suite, test_erase_position)
{
    go_test::associative::unordered_set::unique::test_erase_position<container_type>();
}

TEST(std_observable_unordered_set_placebo_lockable_test_suite, test_erase_value)
{
    go_test::associative::unordered_set::unique::test_erase_value<container_type>();
}

TEST(std_observable_unordered_set_placebo_lockable_test_suite, test_erase_range)
{
    go_test::associative::unordered_set::unique::test_erase_range<container_type>();
}

TEST(std_observable_unordered_set_placebo_lockable_test_suite, test_swap)
{
    go_test::associative::unordered_set::unique::test_swap<container_type>();
}

TEST(std_observable_unordered_set_placebo_lockable_test_suite, test_clear)
{
    go_test::associative::unordered_set::unique::test_clear<container_type>();
}

TEST(std_observable_unordered_set_placebo_lockable_test_suite, test_emplace)
{
    go_test::associative::unordered_set::unique::test_emplace<container_type>();
}

TEST(std_observable_unordered_set_placebo_lockable_test_suite, test_emplace_hint)
{
    go_test::associative::unordered_set::unique::test_emplace_hint<container_type>();
}

#endif  // Required C++11 feature is not supported by this compiler

}
