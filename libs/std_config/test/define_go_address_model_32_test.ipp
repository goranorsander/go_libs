//
//  define_go_address_model_32_test.ipp
//
//  Copyright 2018-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go_gtest/go_gtest.hpp>

namespace
{

TEST(std_define_go_address_model_test_suite, test_define_go_address_model_32)
{
    #if !defined(GO_ADDRESS_MODEL_32)
    EXPECT_TRUE(false);
    #endif
}

TEST(std_define_go_address_model_test_suite, test_not_define_go_address_model_64)
{
    #if defined(GO_ADDRESS_MODEL_64)
    EXPECT_TRUE(false);
    #endif
}

TEST(std_define_go_address_model_test_suite, test_pointer_size)
{
    const std::size_t p_size = sizeof(void*);
    EXPECT_EQ(p_size, 4u);
}

}
