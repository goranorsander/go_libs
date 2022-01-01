//
//  container_size_test_suite.cpp
//
//  Copyright 2018-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#include <go_boost/namespace_alias.hpp>
#include <go_boost/utility/container/size.hpp>

#include <deque>
#include <list>
#include <vector>
#include <map>
#include <set>

#if defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <boost/assign.hpp>
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

namespace
{

TEST(boost_container_size_test_suite, test_size_on_deque)
{
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    std::deque<int> container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#else
    std::deque<int> container = boost::assign::list_of<int>(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, container.size());
    EXPECT_EQ(10u, uc::size(container));
}

TEST(boost_container_size_test_suite, test_size_on_list)
{
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    std::list<int> container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
#else
    std::list<int> container = boost::assign::list_of<int>(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, container.size());
    EXPECT_EQ(10u, uc::size(container));
}

TEST(boost_container_size_test_suite, test_size_on_vector)
{
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    std::vector<int> container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
#else
    std::vector<int> container = boost::assign::list_of<int>(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, container.size());
    EXPECT_EQ(10u, uc::size(container));
}

TEST(boost_container_size_test_suite, test_size_on_map)
{
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    std::map<int, int> container = { { 1, 11 }, { 2, 12 }, { 3, 13 }, { 4, 14 }, { 5, 15 }, { 6, 16 }, { 7, 17 }, { 8, 18 }, { 9, 19 }, { 10, 20 } };
#else
    std::map<int, int> container = boost::assign::map_list_of<int, int>(1, 11)(2, 12)(3, 13)(4, 14)(5, 15)(6, 16)(7, 17)(8, 18)(9, 19)(10, 20);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, container.size());
    EXPECT_EQ(10u, uc::size(container));
}

TEST(boost_container_size_test_suite, test_size_on_set)
{
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    std::set<int> container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
#else
    std::set<int> container = boost::assign::list_of<int>(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, container.size());
    EXPECT_EQ(10u, uc::size(container));
}

}
