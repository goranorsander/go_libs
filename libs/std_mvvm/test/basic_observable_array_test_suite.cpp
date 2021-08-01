//
//  basic_observable_array_test_suite.cpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "test_create.ipp"

namespace
{

typedef m::basic_observable_array<int, s::u8string, 7> container_type;

TEST(std_basic_observable_array_test_suite, test_create)
{
    go_test::sequence::array::test_create<container_type>();
}

}
