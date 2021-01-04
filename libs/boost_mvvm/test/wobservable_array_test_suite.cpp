//
//  wobservable_array_test_suite.cpp
//
//  Copyright 2015-2020 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "test_create.ipp"

namespace
{

typedef m::wobservable_array<int, 7> container_type;

TEST(boost_wobservable_array_test_suite, test_create)
{
    go_boost_test::sequence::array::test_create<container_type>();
}

}
