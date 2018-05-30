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

    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
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
//    test_container_type container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
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

    test_container_type container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
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

    test_container_type container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
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

    test_container_type container = { { 1, 11 },{ 2, 12 },{ 3, 13 },{ 4, 14 },{ 5, 15 },{ 6, 16 },{ 7, 17 },{ 8, 18 },{ 9, 19 },{ 10, 20 } };
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

    test_container_type container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
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
