//
//  container_size_test_suite.cpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_container_size_test_suite, cpp11_not_supported) {}
#else

#include <go/utility/container/size.hpp>

#include <deque>
#include <list>
#include <vector>
#include <map>
#include <set>

namespace uc = go::utility::container;

namespace
{

TEST(std_container_size_test_suite, test_size_on_deque)
{
    std::deque<int> container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_EQ(10, container.size());
    EXPECT_EQ(10, uc::size(container));
}

TEST(std_container_size_test_suite, test_size_on_list)
{
    std::list<int> container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    EXPECT_EQ(10, container.size());
    EXPECT_EQ(10, uc::size(container));
}

TEST(std_container_size_test_suite, test_size_on_vector)
{
    std::vector<int> container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    EXPECT_EQ(10, container.size());
    EXPECT_EQ(10, uc::size(container));
}

TEST(std_container_size_test_suite, test_size_on_map)
{
    std::map<int, int> container = { { 1, 11 }, { 2, 12 }, { 3, 13 }, { 4, 14 }, { 5, 15 }, { 6, 16 }, { 7, 17 }, { 8, 18 }, { 9, 19 }, { 10, 20 } };
    EXPECT_EQ(10, container.size());
    EXPECT_EQ(10, uc::size(container));
}

TEST(std_container_size_test_suite, test_size_on_set)
{
    std::set<int> container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    EXPECT_EQ(10, container.size());
    EXPECT_EQ(10, uc::size(container));
}

}

#endif  // Required C++11 feature is not supported by this compiler
