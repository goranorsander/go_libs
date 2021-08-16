//
//  placebo_lockable_observable_vector_test_suite.cpp
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
#include "test_erase_after_range.ipp"
#include "test_erase_position.ipp"
#include "test_insert_fill.ipp"
#include "test_insert_range.ipp"
#include "test_insert_single_element.ipp"
#include "test_pop_back.ipp"
#include "test_pop_front.ipp"
#include "test_push_back.ipp"
#include "test_push_front.ipp"
#include "test_swap.ipp"

namespace
{

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT)
TEST(std_observable_vector_placebo_lockable_test_suite, required_cpp11_feature_not_supported) {}
#else

using container_type = m::observable_vector<int, a::placebo_lockable>;

TEST(std_observable_vector_placebo_lockable_test_suite, test_assign_range)
{
    go_test::sequence::test_assign_range<container_type>();
}

TEST(std_observable_vector_placebo_lockable_test_suite, test_assign_initializer_list)
{
    go_test::sequence::test_assign_initializer_list<container_type>();
}

TEST(std_observable_vector_placebo_lockable_test_suite, test_assign_fill)
{
    go_test::sequence::indexed::test_assign_fill<container_type>();
}

TEST(std_observable_vector_placebo_lockable_test_suite, test_push_back)
{
    go_test::sequence::test_push_back<container_type>();
}

TEST(std_observable_vector_placebo_lockable_test_suite, test_pop_back)
{
    go_test::sequence::test_pop_back<container_type>();
}

TEST(std_observable_vector_placebo_lockable_test_suite, test_insert_single_element)
{
    go_test::sequence::test_insert_single_element<container_type>();
}

TEST(std_observable_vector_placebo_lockable_test_suite, test_insert_fill)
{
    go_test::sequence::indexed::test_insert_fill<container_type>();
}

TEST(std_observable_vector_placebo_lockable_test_suite, test_insert_range)
{
    go_test::sequence::indexed::test_insert_range<container_type>();
}

TEST(std_observable_vector_placebo_lockable_test_suite, test_erase_position)
{
    go_test::sequence::test_erase_position<container_type>();
}

TEST(std_observable_vector_placebo_lockable_test_suite, test_erase_range)
{
    go_test::sequence::indexed::test_erase_after_range<container_type>();
}

TEST(std_observable_vector_placebo_lockable_test_suite, test_swap)
{
    go_test::sequence::test_swap<container_type>();
}

TEST(std_observable_vector_placebo_lockable_test_suite, test_clear)
{
    go_test::sequence::test_clear<container_type>();
}

#endif  // Required C++11 feature is not supported by this compiler

}
