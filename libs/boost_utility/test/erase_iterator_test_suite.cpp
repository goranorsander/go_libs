//
//  erase_iterator_test_suite.cpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#include <go_boost/namespace_alias.hpp>
#include <go_boost/utility/container/size.hpp>
#include <go_boost/utility/iterator/erase.hpp>

#include <deque>
#include <list>
#include <vector>
#include <map>
#include <set>

#include <boost/container/slist.hpp>

#if defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <boost/assign.hpp>
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

namespace
{

TEST(boost_erase_iterator_test_suite, test_erase_iterator_on_deque)
{
    typedef std::deque<int> test_container_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#else
    test_container_type container = boost::assign::list_of<int>(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, uc::size(container));

    test_container_type::iterator it = container.begin();
    EXPECT_EQ(1, *it);

    std::advance(it, 3);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(4, *it);

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(8, *it);
    EXPECT_EQ(6u, uc::size(container));

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it == container.end());
    EXPECT_EQ(3u, uc::size(container));
}

//TEST(boost_erase_iterator_test_suite, test_erase_iterator_on_forward_list)
//{
//    typedef boost::container::slist<int> test_container_type;
//
//#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
//    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//#else
//    test_container_type container = boost::assign::list_of<int>(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);
//#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
//
//    EXPECT_EQ(10u, uc::size(container));
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
//    EXPECT_EQ(6u, uc::size(container));
//
//    it = ui::erase(container, it, 4);
//    EXPECT_EQ(true, it == container.end());
//    EXPECT_EQ(3u, uc::size(container));
//}

TEST(boost_erase_iterator_test_suite, test_erase_iterator_on_list)
{
    typedef std::list<int> test_container_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#else
    test_container_type container = boost::assign::list_of<int>(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, uc::size(container));

    test_container_type::iterator it = container.begin();
    EXPECT_EQ(1, *it);

    std::advance(it, 3);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(4, *it);

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(8, *it);
    EXPECT_EQ(6u, uc::size(container));

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it == container.end());
    EXPECT_EQ(3u, uc::size(container));
}

TEST(boost_erase_iterator_test_suite, test_erase_iterator_on_vector)
{
    typedef std::vector<int> test_container_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#else
    test_container_type container = boost::assign::list_of<int>(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, uc::size(container));

    test_container_type::iterator it = container.begin();
    EXPECT_EQ(1, *it);

    std::advance(it, 3);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(4, *it);

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(8, *it);
    EXPECT_EQ(6u, uc::size(container));

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it == container.end());
    EXPECT_EQ(3u, uc::size(container));
}

TEST(boost_erase_iterator_test_suite, test_erase_iterator_on_map)
{
    typedef std::map<int, int> test_container_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    test_container_type container = { { 1, 11 }, { 2, 12 }, { 3, 13 }, { 4, 14 }, { 5, 15 }, { 6, 16 }, { 7, 17 }, { 8, 18 }, { 9, 19 }, { 10, 20 } };
#else
    test_container_type container = boost::assign::map_list_of<int, int>(1, 11)(2, 12)(3, 13)(4, 14)(5, 15)(6, 16)(7, 17)(8, 18)(9, 19)(10, 20);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, uc::size(container));

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
    EXPECT_EQ(6u, uc::size(container));

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it == container.end());
    EXPECT_EQ(3u, uc::size(container));
}

TEST(boost_erase_iterator_test_suite, test_erase_iterator_on_set)
{
    typedef std::set<int> test_container_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#else
    test_container_type container = boost::assign::list_of<int>(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, uc::size(container));

    test_container_type::iterator it = container.begin();
    EXPECT_EQ(1, *it);

    std::advance(it, 3);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(4, *it);

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it != container.end());
    EXPECT_EQ(8, *it);
    EXPECT_EQ(6u, uc::size(container));

    it = ui::erase(container, it, 4);
    EXPECT_EQ(true, it == container.end());
    EXPECT_EQ(3u, uc::size(container));
}

}
