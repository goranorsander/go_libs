//
//  placebo_lockable_observable_forward_list_test_suite.cpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "test_assign_fill.ipp"
#include "test_assign_initializer_list.ipp"
#include "test_assign_range.ipp"
#include "test_clear.ipp"
#include "test_erase_after_position.ipp"
#include "test_erase_after_range.ipp"
#include "test_insert_after_fill.ipp"
#include "test_insert_after_range.ipp"
#include "test_insert_after_single_element.ipp"
#include "test_merge.ipp"
#include "test_merge_compare_predicate.ipp"
#include "test_pop_front.ipp"
#include "test_push_front.ipp"
#include "test_remove.ipp"
#include "test_remove_if.ipp"
#include "test_splice_after_entire_container.ipp"
#include "test_splice_after_element_range.ipp"
#include "test_splice_after_single_element.ipp"
#include "test_swap.ipp"
#include "test_unique.ipp"
#include "test_unique_binary_predicate.ipp"

namespace
{

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT)
TEST(std_observable_forward_list_placebo_lockable_test_suite, required_cpp11_feature_not_supported) {}
#else

using container_type = m::observable_forward_list<int, a::placebo_lockable>;
using double_container_type = m::observable_forward_list<double, a::placebo_lockable>;

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_assign_range)
{
    go_test::sequence::test_assign_range<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_assign_initializer_list)
{
    go_test::sequence::test_assign_initializer_list<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_assign_fill)
{
    go_test::sequence::linked::test_assign_fill<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_push_front)
{
    go_test::sequence::test_push_front<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_pop_front)
{
    go_test::sequence::test_pop_front<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_insert_after_single_element)
{
    go_test::sequence::test_insert_after_single_element<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_insert_after_fill)
{
    go_test::sequence::test_insert_after_fill<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_insert_after_range)
{
    go_test::sequence::test_insert_after_range<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_erase_after_position)
{
    go_test::sequence::test_erase_after_position<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_erase_range)
{
    go_test::sequence::linked::test_erase_after_range<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_swap)
{
    go_test::sequence::test_swap<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_clear)
{
    go_test::sequence::test_clear<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_splice_after_entire_container)
{
    go_test::sequence::test_splice_after_entire_container<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_splice_after_single_element)
{
    go_test::sequence::test_splice_after_single_element<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_splice_after_element_range)
{
    go_test::sequence::test_splice_after_element_range<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_remove)
{
    go_test::sequence::test_remove<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_remove_if)
{
    go_test::sequence::test_remove_if<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_unique)
{
    go_test::sequence::test_unique<container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_unique_binary_predicate)
{
    go_test::sequence::test_unique_binary_predicate<double_container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_merge)
{
    go_test::sequence::test_merge<double_container_type>();
}

TEST(std_observable_forward_list_placebo_lockable_test_suite, test_merge_compare_predicate)
{
    go_test::sequence::test_merge_compare_predicate<double_container_type>();
}

#endif  // Required C++11 feature is not supported by this compiler

}
