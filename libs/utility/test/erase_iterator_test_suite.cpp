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
#include <go/utility/iterator/erase.hpp>

#include <deque>
#include <forward_list>
#include <list>
#include <vector>
#include <map>
#include <set>

namespace uc = go::utility::container;
namespace ui = go::utility::iterator;

namespace
{

TEST(std_container_size_test_suite, test_erase_iterator_on_deque)
{
    typedef std::deque<int> test_container_type;

#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
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

    EXPECT_EQ(10, uc::size(container));

    test_container_type::iterator it = container.begin();
    EXPECT_EQ(1, *it);

    std::advance(it, 3);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(4, *it);

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(8, *it);
    EXPECT_EQ(6, uc::size(container));

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it == container.end());
    EXPECT_EQ(3, uc::size(container));
}

//TEST(std_container_size_test_suite, test_erase_iterator_on_forward_list)
//{
//    typedef std::forward_list<int> test_container_type;
//
//#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
//    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//#else
//    test_container_type container;
//    container.push_back(1);
//    container.push_back(2);
//    container.push_back(3);
//    container.push_back(4);
//    container.push_back(5);
//    container.push_back(6);
//    container.push_back(7);
//    container.push_back(8);
//    container.push_back(9);
//    container.push_back(10);
//#endif  // #if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
//
//    EXPECT_EQ(10, uc::size(container));
//
//    test_container_type::iterator it = container.begin();
//    EXPECT_EQ(1, *it);
//
//    std::advance(it, 3);
//    EXPECT_EQ(true, it != container.end());
//    EXPECT_EQ(4, *it);
//
//    it = ui::erase(container, it, 4);
//    EXPECT_EQ(true, it != container.end());
//    EXPECT_EQ(8, *it);
//    EXPECT_EQ(6, uc::size(container));
//
//    it = ui::erase(container, it, 4);
//    EXPECT_EQ(true, it == container.end());
//    EXPECT_EQ(3, uc::size(container));
//}

TEST(std_container_size_test_suite, test_erase_iterator_on_list)
{
    typedef std::list<int> test_container_type;

#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
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

    EXPECT_EQ(10, uc::size(container));

    test_container_type::iterator it = container.begin();
    EXPECT_EQ(1, *it);

    std::advance(it, 3);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(4, *it);

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(8, *it);
    EXPECT_EQ(6, uc::size(container));

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it == container.end());
    EXPECT_EQ(3, uc::size(container));
}

TEST(std_container_size_test_suite, test_erase_iterator_on_vector)
{
    typedef std::vector<int> test_container_type;

#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
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

    EXPECT_EQ(10, uc::size(container));

    test_container_type::iterator it = container.begin();
    EXPECT_EQ(1, *it);

    std::advance(it, 3);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(4, *it);

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(8, *it);
    EXPECT_EQ(6, uc::size(container));

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it == container.end());
    EXPECT_EQ(3, uc::size(container));
}

TEST(std_container_size_test_suite, test_erase_iterator_on_map)
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

    EXPECT_EQ(10, uc::size(container));

    test_container_type::iterator it = container.begin();
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(11, it->second);

    std::advance(it, 3);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(14, it->second);

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(8, it->first);
    EXPECT_EQ(18, it->second);
    EXPECT_EQ(6, uc::size(container));

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it == container.end());
    EXPECT_EQ(3, uc::size(container));
}

TEST(std_container_size_test_suite, test_erase_iterator_on_set)
{
    typedef std::set<int> test_container_type;

#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#else
    test_container_type container;
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

    EXPECT_EQ(10, uc::size(container));

    test_container_type::iterator it = container.begin();
    EXPECT_EQ(1, *it);

    std::advance(it, 3);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(4, *it);

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(8, *it);
    EXPECT_EQ(6, uc::size(container));

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it == container.end());
    EXPECT_EQ(3, uc::size(container));
}

}

#endif  // Required C++11 feature is not supported by this compiler
