#ifndef GO_BOOST_MVVM_TEST_INSERT_INITIALIZER_LIST_IPP_INCLUDED
#define GO_BOOST_MVVM_TEST_INSERT_INITIALIZER_LIST_IPP_INCLUDED

//
//  test_insert_initializer_list.ipp
//
//  Copyright 2020-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/foreach.hpp>

#include <go_boost/mvvm.hpp>
#include <go_boost/utility.hpp>

#include "test_container_observer.ipp"

namespace go_boost_test
{
namespace associative
{
namespace map
{
namespace multi
{

template<class C>
inline void test_insert_initializer_list()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    // Test insert initializer list
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    const std::initializer_list<container_value_type> il1 =
    {
        container_value_type(1, 10),
        container_value_type(2, 20),
        container_value_type(5, 50),
        container_value_type(7, 70)
    };
    *container = il1;
    EXPECT_EQ(4u, container->size());

    const std::initializer_list<container_value_type> il2 =
    {
        container_value_type(3, 30),
        container_value_type(4, 40),
        container_value_type(6, 60)
    };
    EXPECT_EQ(3u, il2.size());

    observer.connect(container);

    container->insert(il2);
    EXPECT_EQ(7u, container->size());

    container_iterator it = container->begin();
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(10, it->second);
    ++it;
    EXPECT_EQ(2, it->first);
    EXPECT_EQ(20, it->second);
    ++it;
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(30, it->second);
    ++it;
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);
    ++it;
    EXPECT_EQ(5, it->first);
    EXPECT_EQ(50, it->second);
    ++it;
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);
    ++it;
    EXPECT_EQ(7, it->first);
    EXPECT_EQ(70, it->second);
    ++it;
    EXPECT_EQ(container->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(3u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
}

}
namespace unique
{

template<class C>
inline void test_insert_initializer_list()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    // Test insert initializer list
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    const std::initializer_list<container_value_type> il1 =
    {
        container_value_type(1, 10),
        container_value_type(2, 20),
        container_value_type(5, 50),
        container_value_type(7, 70)
    };
    *container = il1;
    EXPECT_EQ(4u, container->size());

    const std::initializer_list<container_value_type> il2 =
    {
        container_value_type(3, 30),
        container_value_type(4, 40),
        container_value_type(6, 60)
    };
    EXPECT_EQ(3u, il2.size());

    observer.connect(container);

    container->insert(il2);
    EXPECT_EQ(7u, container->size());

    container_iterator it = container->begin();
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(10, it->second);
    ++it;
    EXPECT_EQ(2, it->first);
    EXPECT_EQ(20, it->second);
    ++it;
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(30, it->second);
    ++it;
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);
    ++it;
    EXPECT_EQ(5, it->first);
    EXPECT_EQ(50, it->second);
    ++it;
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);
    ++it;
    EXPECT_EQ(7, it->first);
    EXPECT_EQ(70, it->second);
    ++it;
    EXPECT_EQ(container->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(3u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
}

}
}
namespace set
{
namespace multi
{

template<class C>
inline void test_insert_initializer_list()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    // Test insert initializer list
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    const std::initializer_list<int> il1 = { 1, 2, 5, 7 };
    *container = il1;
    EXPECT_EQ(4u, container->size());

    const std::initializer_list<int> il2 = { 3, 4, 6 };
    EXPECT_EQ(3u, il2.size());

    observer.connect(container);

    container->insert(il2);
    EXPECT_EQ(7u, container->size());

    container_iterator it = container->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(5, *it);
    ++it;
    EXPECT_EQ(6, *it);
    ++it;
    EXPECT_EQ(7, *it);
    ++it;
    EXPECT_EQ(container->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(3u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
}

}
namespace unique
{

template<class C>
inline void test_insert_initializer_list()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    // Test insert initializer list
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    const std::initializer_list<int> il1 = { 1, 2, 5, 7 };
    *container = il1;
    EXPECT_EQ(4u, container->size());

    const std::initializer_list<int> il2 = { 3, 4, 6 };
    EXPECT_EQ(3u, il2.size());

    observer.connect(container);

    container->insert(il2);
    EXPECT_EQ(7u, container->size());

    container_iterator it = container->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(5, *it);
    ++it;
    EXPECT_EQ(6, *it);
    ++it;
    EXPECT_EQ(7, *it);
    ++it;
    EXPECT_EQ(container->end(), it);

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(3u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
}

}
}
namespace unordered_map
{
namespace multi
{

template<class C>
inline void test_insert_initializer_list()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    // Test insert initializer list
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    const std::initializer_list<container_value_type> il1 =
    {
        container_value_type(1, 10),
        container_value_type(2, 20),
        container_value_type(5, 50),
        container_value_type(7, 70)
    };
    *container = il1;
    EXPECT_EQ(4u, container->size());

    const std::initializer_list<container_value_type> il2 =
    {
        container_value_type(3, 30),
        container_value_type(4, 40),
        container_value_type(6, 60)
    };
    EXPECT_EQ(3u, il2.size());

    observer.connect(container);

    container->insert(il2);
    EXPECT_EQ(7u, container->size());

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(3u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
}

}
namespace unique
{

template<class C>
inline void test_insert_initializer_list()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    // Test insert initializer list
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    const std::initializer_list<container_value_type> il1 =
    {
        container_value_type(1, 10),
        container_value_type(2, 20),
        container_value_type(5, 50),
        container_value_type(7, 70)
    };
    *container = il1;
    EXPECT_EQ(4u, container->size());

    const std::initializer_list<container_value_type> il2 =
    {
        container_value_type(3, 30),
        container_value_type(4, 40),
        container_value_type(6, 60)
    };
    EXPECT_EQ(3u, il2.size());

    observer.connect(container);

    container->insert(il2);
    EXPECT_EQ(7u, container->size());

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(3u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
}

}
}
namespace unordered_set
{
namespace multi
{

template<class C>
inline void test_insert_initializer_list()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    // Test insert initializer list
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    const std::initializer_list<int> il1 = { 1, 2, 5, 7 };
    *container = il1;
    EXPECT_EQ(4u, container->size());

    const std::initializer_list<int> il2 = { 3, 4, 6 };
    EXPECT_EQ(3u, il2.size());

    observer.connect(container);

    container->insert(il2);
    EXPECT_EQ(7u, container->size());

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(3u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
}

}
namespace unique
{

template<class C>
inline void test_insert_initializer_list()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    // Test insert initializer list
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    const std::initializer_list<int> il1 = { 1, 2, 5, 7 };
    *container = il1;
    EXPECT_EQ(4u, container->size());

    const std::initializer_list<int> il2 = { 3, 4, 6 };
    EXPECT_EQ(3u, il2.size());

    observer.connect(container);

    container->insert(il2);
    EXPECT_EQ(7u, container->size());

    EXPECT_EQ(m::notify_container_changed_action_add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(3u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
}

}
}
}
}

#endif  // #ifndef GO_BOOST_MVVM_TEST_INSERT_INITIALIZER_LIST_IPP_INCLUDED
