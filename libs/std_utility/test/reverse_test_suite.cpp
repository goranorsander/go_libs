//
//  reverse_test_suite.cpp
//
//  Copyright 2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <gtest/gtest.h>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_reverse_test_suite, cpp11_not_supported) {}
#else

#include <go/utility/iterator/reverse.hpp>

#include <deque>
#include <list>
#include <vector>
#include <map>
#include <set>

namespace ui = go::utility::iterator;

namespace
{

TEST(std_reverse_test_suite, test_reverse_deque)
{
    typedef std::deque<int> test_container_type;

#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
    test_container_type container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
#else
    test_container_type container;
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

    size_t count = 0;
    int value = 10;
    for (int i : ui::reverse(container))
    {
        ++count;
        EXPECT_EQ(i, value);
        --value;
    }
    EXPECT_EQ(count, 10);
}

TEST(std_reverse_test_suite, test_reverse_list)
{
    typedef std::list<int> test_container_type;

#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
    test_container_type container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
#else
    test_container_type container;
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

    size_t count = 0;
    int value = 10;
    for (int i : ui::reverse(container))
    {
        ++count;
        EXPECT_EQ(i, value);
        --value;
    }
    EXPECT_EQ(count, 10);
}

TEST(std_reverse_test_suite, test_reverse_vector)
{
    typedef std::vector<int> test_container_type;

#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
    test_container_type container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
#else
    test_container_type container;
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

    size_t count = 0;
    int value = 10;
    for (int i : ui::reverse(container))
    {
        ++count;
        EXPECT_EQ(i, value);
        --value;
    }
    EXPECT_EQ(count, 10);
}

TEST(std_reverse_test_suite, test_reverse_map)
{
    typedef std::map<int, int> test_container_type;

#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
    test_container_type container = { { 1, 11 }, { 2, 12 }, { 3, 13 }, { 4, 14 }, { 5, 15 }, { 6, 16 }, { 7, 17 }, { 8, 18 }, { 9, 19 }, { 10, 20 } };
#else
    test_container_type container;
    container.insert(test_container_type::value_type(1, 11));
    container.insert(test_container_type::value_type(2, 12));
    container.insert(test_container_type::value_type(3, 13));
    container.insert(test_container_type::value_type(4, 14));
    container.insert(test_container_type::value_type(5, 15));
    container.insert(test_container_type::value_type(6, 16));
    container.insert(test_container_type::value_type(7, 17));
    container.insert(test_container_type::value_type(8, 18));
    container.insert(test_container_type::value_type(9, 19));
    container.insert(test_container_type::value_type(10, 20));
#endif  // #if !defined(GO_NO_CXX11_INITIALIZER_LISTS)

    size_t count = 0;
    int key = 10;
    int value = 20;
    for (test_container_type::value_type v : ui::reverse(container))
    {
        ++count;
        EXPECT_EQ(v.first, key);
        EXPECT_EQ(v.second, value);
        --key;
        --value;
    }
    EXPECT_EQ(count, 10);
}

TEST(std_reverse_test_suite, test_reverse_set)
{
    typedef std::set<int> test_container_type;

#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
    test_container_type container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
#else
    test_container_type container;
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

    size_t count = 0;
    int value = 10;
    for (int i : ui::reverse(container))
    {
        ++count;
        EXPECT_EQ(i, value);
        --value;
    }
    EXPECT_EQ(count, 10);
}

}

#endif  // Required C++11 feature is not supported by this compiler
