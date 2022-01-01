//
//  placebo_lockable_observable_array_test_suite.cpp
//
//  Copyright 2018-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "test_create.ipp"

namespace
{

typedef m::observable_array<int, 7, a::placebo_lockable> container_type;

TEST(boost_observable_array_placebo_lockable_test_suite, test_create)
{
    go_boost_test::sequence::array::test_create<container_type>();
}

}
