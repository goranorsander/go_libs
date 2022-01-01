//
//  basic_observable_array_test_suite.cpp
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

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT)
TEST(std_basic_observable_array_test_suite, required_cpp11_feature_not_supported) {}
#else

using container_type = m::basic_observable_array<int, s::u8string, 7>;

TEST(std_basic_observable_array_test_suite, test_create)
{
    go_test::sequence::array::test_create<container_type>();
}

#endif  // Required C++11 feature is not supported by this compiler

}
