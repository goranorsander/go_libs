//
//  container_size_test_suite.cpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_RANGE_FOR_LOOP)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_container_size_test_suite, cpp11_not_supported) {}
#else

#include <go/namespace_alias.hpp>
#include <go/utility/container/size.hpp>

#include <deque>
#include <list>
#include <vector>
#include <map>
#include <set>

namespace
{

TEST(std_container_size_test_suite, test_size_on_deque)
{
#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
    std::deque<int> container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#else
    std::deque<int> container;
    container.push_back(1);
    container.push_back(2);
    container.push_back(3);
    container.push_back(4);
    container.push_back(5);
    container.push_back(6);
    container.push_back(7);
    container.push_back(8);
    container.push_back(9);
    container.push_back(10);
#endif  // #if !defined(GO_NO_CXX11_INITIALIZER_LISTS)

    EXPECT_EQ(10u, container.size());
    EXPECT_EQ(10u, uc::size(container));
}

TEST(std_container_size_test_suite, test_size_on_list)
{
#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
    std::list<int> container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
#else
    std::list<int> container;
    container.push_back(1);
    container.push_back(2);
    container.push_back(3);
    container.push_back(4);
    container.push_back(5);
    container.push_back(6);
    container.push_back(7);
    container.push_back(8);
    container.push_back(9);
    container.push_back(10);
#endif  // #if !defined(GO_NO_CXX11_INITIALIZER_LISTS)

    EXPECT_EQ(10u, container.size());
    EXPECT_EQ(10u, uc::size(container));
}

TEST(std_container_size_test_suite, test_size_on_vector)
{
#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
    std::vector<int> container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
#else
    std::vector<int> container;
    container.push_back(1);
    container.push_back(2);
    container.push_back(3);
    container.push_back(4);
    container.push_back(5);
    container.push_back(6);
    container.push_back(7);
    container.push_back(8);
    container.push_back(9);
    container.push_back(10);
#endif  // #if !defined(GO_NO_CXX11_INITIALIZER_LISTS)

    EXPECT_EQ(10u, container.size());
    EXPECT_EQ(10u, uc::size(container));
}

TEST(std_container_size_test_suite, test_size_on_map)
{
#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
    std::map<int, int> container = { { 1, 11 }, { 2, 12 }, { 3, 13 }, { 4, 14 }, { 5, 15 }, { 6, 16 }, { 7, 17 }, { 8, 18 }, { 9, 19 }, { 10, 20 } };
#else
    std::map<int, int> container;
    container.insert(std::map<int, int>::value_type(1, 11));
    container.insert(std::map<int, int>::value_type(2, 12));
    container.insert(std::map<int, int>::value_type(3, 13));
    container.insert(std::map<int, int>::value_type(4, 14));
    container.insert(std::map<int, int>::value_type(5, 15));
    container.insert(std::map<int, int>::value_type(6, 16));
    container.insert(std::map<int, int>::value_type(7, 17));
    container.insert(std::map<int, int>::value_type(8, 18));
    container.insert(std::map<int, int>::value_type(9, 19));
    container.insert(std::map<int, int>::value_type(10, 20));
#endif  // #if !defined(GO_NO_CXX11_INITIALIZER_LISTS)

    EXPECT_EQ(10u, container.size());
    EXPECT_EQ(10u, uc::size(container));
}

TEST(std_container_size_test_suite, test_size_on_set)
{
#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
    std::set<int> container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
#else
    std::set<int> container;
    container.insert(1);
    container.insert(2);
    container.insert(3);
    container.insert(4);
    container.insert(5);
    container.insert(6);
    container.insert(7);
    container.insert(8);
    container.insert(9);
    container.insert(10);
#endif  // #if !defined(GO_NO_CXX11_INITIALIZER_LISTS)

    EXPECT_EQ(10u, container.size());
    EXPECT_EQ(10u, uc::size(container));
}

}

#endif  // Required C++11 feature is not supported by this compiler
