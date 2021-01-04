//
//  observable_array_test_suite.cpp
//
//  Copyright 2015-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "test_create.ipp"

namespace
{

typedef m::observable_array<int, 7> container_type;

TEST(boost_observable_array_test_suite, test_create)
{
    go_boost_test::sequence::array::test_create<container_type>();
}

}
