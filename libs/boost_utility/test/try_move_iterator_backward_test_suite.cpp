//
//  try_move_iterator_backward_test_suite.cpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <gtest/gtest.h>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#include <go_boost/utility/container/size.hpp>
#include <go_boost/utility/iterator/try_move_backward.hpp>

#include <deque>
#include <list>
#include <vector>

#include <map>
#include <set>

#include <boost/container/static_vector.hpp>
#include <boost/container/slist.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#if defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <boost/assign.hpp>
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

namespace uc = go_boost::utility::container;
namespace ui = go_boost::utility::iterator;

namespace
{

TEST(boost_try_move_iterator_backward_test_suite, test_try_move_backward_on_array)
{
    typedef boost::container::static_vector<int, 10> test_container_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#else
    test_container_type container = boost::assign::list_of<int>(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, uc::size(container));

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

TEST(boost_try_move_iterator_backward_test_suite, test_try_move_backward_on_deque)
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

#if !defined(GO_BOOST_COMP_MSVC_VC120) && !((BOOST_VERSION == 106900) || (BOOST_VERSION == 107000))
TEST(boost_try_move_iterator_backward_test_suite, test_try_move_backward_on_forward_list)
{
    typedef boost::container::slist<int> test_container_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#else
    test_container_type container = boost::assign::list_of<int>(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, uc::size(container));

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
#endif  // #if !defined(GO_BOOST_COMP_MSVC_VC120) && !((BOOST_VERSION == 106900) || (BOOST_VERSION == 107000))

TEST(boost_try_move_iterator_backward_test_suite, test_try_move_backward_on_list)
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

TEST(boost_try_move_iterator_backward_test_suite, test_try_move_backward_on_vector)
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

TEST(boost_try_move_iterator_backward_test_suite, test_try_move_backward_on_map)
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

TEST(boost_try_move_iterator_backward_test_suite, test_try_move_backward_on_set)
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

TEST(boost_try_move_iterator_backward_test_suite, test_try_move_backward_on_multimap)
{
    typedef std::multimap<int, int> test_container_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    test_container_type container = { { 1, 11 }, { 2, 12 }, { 3, 13 }, { 4, 14 }, { 5, 15 }, { 6, 16 }, { 7, 17 }, { 8, 18 }, { 9, 19 }, { 10, 20 } };
#else
    test_container_type container = boost::assign::map_list_of<int, int>(1, 11)(2, 12)(3, 13)(4, 14)(5, 15)(6, 16)(7, 17)(8, 18)(9, 19)(10, 20);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, uc::size(container));

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

TEST(boost_try_move_iterator_backward_test_suite, test_try_move_backward_on_multiset)
{
    typedef std::multiset<int> test_container_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#else
    test_container_type container = boost::assign::list_of<int>(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, uc::size(container));

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

TEST(boost_try_move_iterator_backward_test_suite, test_try_move_backward_on_unordered_map)
{
    typedef boost::unordered_map<int, int> test_container_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    test_container_type container = { { 1, 11 }, { 2, 12 }, { 3, 13 }, { 4, 14 }, { 5, 15 }, { 6, 16 }, { 7, 17 }, { 8, 18 }, { 9, 19 }, { 10, 20 } };
#else
    test_container_type container = boost::assign::map_list_of<int, int>(1, 11)(2, 12)(3, 13)(4, 14)(5, 15)(6, 16)(7, 17)(8, 18)(9, 19)(10, 20);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, uc::size(container));

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

TEST(boost_try_move_iterator_backward_test_suite, test_try_move_backward_on_unordered_set)
{
    typedef boost::unordered_set<int> test_container_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#else
    test_container_type container = boost::assign::list_of<int>(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, uc::size(container));

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

TEST(boost_try_move_iterator_backward_test_suite, test_try_move_backward_on_unordered_multimap)
{
    typedef boost::unordered_multimap<int, int> test_container_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    test_container_type container = { { 1, 11 }, { 2, 12 }, { 3, 13 }, { 4, 14 }, { 5, 15 }, { 6, 16 }, { 7, 17 }, { 8, 18 }, { 9, 19 }, { 10, 20 } };
#else
    test_container_type container = boost::assign::map_list_of<int, int>(1, 11)(2, 12)(3, 13)(4, 14)(5, 15)(6, 16)(7, 17)(8, 18)(9, 19)(10, 20);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, uc::size(container));

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

TEST(boost_try_move_iterator_backward_test_suite, test_try_move_backward_on_unordered_multiset)
{
    typedef boost::unordered_multiset<int> test_container_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    test_container_type container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#else
    test_container_type container = boost::assign::list_of<int>(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);
#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    EXPECT_EQ(10u, uc::size(container));

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
