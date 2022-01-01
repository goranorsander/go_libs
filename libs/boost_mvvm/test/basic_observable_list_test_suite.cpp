//
//  basic_observable_list_test_suite.cpp
//
//  Copyright 2018-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "test_assign_fill.ipp"
#include "test_assign_initializer_list.ipp"
#include "test_assign_range.ipp"
#include "test_clear.ipp"
#include "test_erase_position.ipp"
#include "test_erase_range.ipp"
#include "test_insert_fill.ipp"
#include "test_insert_range.ipp"
#include "test_insert_single_element.ipp"
#include "test_merge.ipp"
#include "test_merge_compare_predicate.ipp"
#include "test_pop_back.ipp"
#include "test_pop_front.ipp"
#include "test_push_back.ipp"
#include "test_push_front.ipp"
#include "test_remove.ipp"
#include "test_remove_if.ipp"
#include "test_splice_element_range.ipp"
#include "test_splice_entire_container.ipp"
#include "test_splice_single_element.ipp"
#include "test_swap.ipp"
#include "test_unique.ipp"
#include "test_unique_binary_predicate.ipp"

namespace
{

typedef m::basic_observable_list<int, s::u8string> container_type;
typedef m::basic_observable_list<double, s::u8string> double_container_type;

TEST(boost_basic_observable_list_test_suite, test_assign_range)
{
    go_boost_test::sequence::test_assign_range<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_assign_initializer_list)
{
    go_boost_test::sequence::test_assign_initializer_list<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_assign_fill)
{
    go_boost_test::sequence::linked::test_assign_fill<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_push_back)
{
    go_boost_test::sequence::test_push_back<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_push_front)
{
    go_boost_test::sequence::test_push_front<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_pop_back)
{
    go_boost_test::sequence::test_pop_back<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_pop_front)
{
    go_boost_test::sequence::test_pop_front<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_insert_single_element)
{
    go_boost_test::sequence::test_insert_single_element<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_insert_fill)
{
    go_boost_test::sequence::linked::test_insert_fill<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_insert_range)
{
    go_boost_test::sequence::linked::test_insert_range<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_erase_position)
{
    go_boost_test::sequence::test_erase_position<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_erase_range)
{
    go_boost_test::sequence::test_erase_range<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_swap)
{
    go_boost_test::sequence::test_swap<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_clear)
{
    go_boost_test::sequence::test_clear<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_splice_entire_container)
{
    go_boost_test::sequence::test_splice_entire_container<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_splice_single_element)
{
    go_boost_test::sequence::test_splice_single_element<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_splice_element_range)
{
    go_boost_test::sequence::test_splice_element_range<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_remove)
{
    go_boost_test::sequence::test_remove<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_remove_if)
{
    go_boost_test::sequence::test_remove_if<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_unique)
{
    go_boost_test::sequence::test_unique<container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_unique_binary_predicate)
{
    go_boost_test::sequence::test_unique_binary_predicate<double_container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_merge)
{
    go_boost_test::sequence::test_merge<double_container_type>();
}

TEST(boost_basic_observable_list_test_suite, test_merge_compare_predicate)
{
    go_boost_test::sequence::test_merge_compare_predicate<double_container_type>();
}

}
