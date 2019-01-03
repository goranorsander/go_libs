//
//  try_move_iterator_backward_test_suite.cpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_RANGE_FOR_LOOP)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_try_move_iterator_backward_test_suite, cpp11_not_supported) {}
#else

#include <go/utility/container/size.hpp>
#include <go/utility/iterator/try_move_backward.hpp>

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>

#include <map>
#include <set>

#include <unordered_map>
#include <unordered_set>

namespace uc = go::utility::container;
namespace ui = go::utility::iterator;

namespace
{

TEST(std_try_move_iterator_backward_test_suite, test_try_move_backward_on_array)
{
    typedef std::array<int, 10> test_container_type;

    test_container_type container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    EXPECT_EQ(10, uc::size(container));

    test_container_type::iterator it = container.begin();
    EXPECT_EQ(1, *it);

    std::advance(it, 5);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(6, *it);

    bool moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(5, *it);

    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(1, *it);

    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(false, moved_backward);
    EXPECT_EQ(1, *it);
}

TEST(std_try_move_iterator_backward_test_suite, test_try_move_backward_on_deque)
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

    std::advance(it, 5);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(6, *it);

    bool moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(5, *it);

    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(1, *it);

    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(false, moved_backward);
    EXPECT_EQ(1, *it);
}

TEST(std_try_move_iterator_backward_test_suite, test_try_move_backward_on_forward_list)
{
    typedef std::forward_list<int> test_container_type;

#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)
    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#else
    test_container_type container;
    container.push_front(1);
    test_container_type::iterator pos = container.begin();
    pos = container.insert_after(pos, 2);
    pos = container.insert_after(pos, 3);
    pos = container.insert_after(pos, 4);
    pos = container.insert_after(pos, 5);
    pos = container.insert_after(pos, 6);
    pos = container.insert_after(pos, 7);
    pos = container.insert_after(pos, 8);
    pos = container.insert_after(pos, 9);
    pos = container.insert_after(pos, 10);
#endif  // #if !defined(GO_NO_CXX11_INITIALIZER_LISTS)

    EXPECT_EQ(10, uc::size(container));

    test_container_type::iterator it = container.begin();
    EXPECT_EQ(1, *it);

    std::advance(it, 5);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(6, *it);

    bool moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(5, *it);

    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(1, *it);

    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(false, moved_backward);
    EXPECT_EQ(1, *it);
}

TEST(std_try_move_iterator_backward_test_suite, test_try_move_backward_on_list)
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

    std::advance(it, 5);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(6, *it);

    bool moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(5, *it);

    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(1, *it);

    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(false, moved_backward);
    EXPECT_EQ(1, *it);
}

TEST(std_try_move_iterator_backward_test_suite, test_try_move_backward_on_vector)
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

    std::advance(it, 5);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(6, *it);

    bool moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(5, *it);

    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(1, *it);

    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(false, moved_backward);
    EXPECT_EQ(1, *it);
}

TEST(std_try_move_iterator_backward_test_suite, test_try_move_backward_on_map)
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

    std::advance(it, 5);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(16, it->second);

    bool moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(5, it->first);
    EXPECT_EQ(15, it->second);

    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(11, it->second);

    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(false, moved_backward);
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(11, it->second);
}

TEST(std_try_move_iterator_backward_test_suite, test_try_move_backward_on_set)
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

    std::advance(it, 5);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(6, *it);

    bool moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(5, *it);

    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(1, *it);

    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(false, moved_backward);
    EXPECT_EQ(1, *it);
}

TEST(std_try_move_iterator_backward_test_suite, test_try_move_backward_on_multimap)
{
    typedef std::multimap<int, int> test_container_type;

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

    std::advance(it, 5);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(16, it->second);

    bool moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(5, it->first);
    EXPECT_EQ(15, it->second);

    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(11, it->second);

    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(false, moved_backward);
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(11, it->second);
}

TEST(std_try_move_iterator_backward_test_suite, test_try_move_backward_on_multiset)
{
    typedef std::multiset<int> test_container_type;

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

    std::advance(it, 5);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(6, *it);

    bool moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(5, *it);

    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);
    EXPECT_EQ(1, *it);

    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(false, moved_backward);
    EXPECT_EQ(1, *it);
}

TEST(std_try_move_iterator_backward_test_suite, test_try_move_backward_on_unordered_map)
{
    typedef std::unordered_map<int, int> test_container_type;

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
    EXPECT_EQ(true, it != container.end());

    std::advance(it, 5);
    EXPECT_EQ(true, it != container.end());

    bool moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);

    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);

    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(false, moved_backward);
}

TEST(std_try_move_iterator_backward_test_suite, test_try_move_backward_on_unordered_set)
{
    typedef std::unordered_set<int> test_container_type;

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
    EXPECT_EQ(true, it != container.end());

    std::advance(it, 5);
    EXPECT_EQ(true, it != container.end());

    bool moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);

    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);

    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(false, moved_backward);
}

TEST(std_try_move_iterator_backward_test_suite, test_try_move_backward_on_unordered_multimap)
{
    typedef std::unordered_multimap<int, int> test_container_type;

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
    EXPECT_EQ(true, it != container.end());

    std::advance(it, 5);
    EXPECT_EQ(true, it != container.end());

    bool moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);

    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);

    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(false, moved_backward);
}

TEST(std_try_move_iterator_backward_test_suite, test_try_move_backward_on_unordered_multiset)
{
    typedef std::unordered_multiset<int> test_container_type;

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
    EXPECT_EQ(true, it != container.end());

    std::advance(it, 5);
    EXPECT_EQ(true, it != container.end());

    bool moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);

    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(true, moved_backward);

    moved_backward = ui::try_move_backward(container, it);
    EXPECT_EQ(false, moved_backward);
}

}

#endif  // Required C++11 feature is not supported by this compiler
