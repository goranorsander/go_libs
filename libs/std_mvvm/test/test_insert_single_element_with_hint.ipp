#ifndef GO_MVVM_TEST_INSERT_SINGLE_ELEMENT_WITH_HINT_IPP_INCLUDED
#define GO_MVVM_TEST_INSERT_SINGLE_ELEMENT_WITH_HINT_IPP_INCLUDED

//
//  test_insert_single_element_with_hint.ipp
//
//  Copyright 2020-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_gtest.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#include <go/mvvm.hpp>
#include <go/utility.hpp>

#include "test_container_observer.ipp"

#if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT) || defined(GO_NO_CXX11_MUTEX))

namespace go_test
{
namespace associative
{
namespace map
{
namespace multi
{

template<class C>
inline void test_insert_single_element_with_hint()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert single element with hint
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());
    container->insert(container_value_type(1, 10));
    container->insert(container_value_type(2, 20));
    container->insert(container_value_type(5, 50));
    container->insert(container_value_type(7, 70));
    EXPECT_EQ(4u, container->size());

    observer.connect(container);

    container_iterator it = container->insert(container->begin(), container_value_type(3, 30));
    EXPECT_EQ(5u, container->size());

    it = container->insert(it, container_value_type(4, 40));
    EXPECT_EQ(6u, container->size());

    it = container->insert(it, container_value_type(4, 40));
    EXPECT_EQ(7u, container->size());

    it = container->insert(it, container_value_type(6, 60));
    EXPECT_EQ(8u, container->size());

    it = container->begin();
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

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(4u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(8u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_insert_single_element_with_hint()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert single element with hint
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());

    (*container)[1] = 10;
    (*container)[2] = 20;
    (*container)[5] = 50;
    (*container)[7] = 70;
    EXPECT_EQ(4u, container->size());

    observer.connect(container);

    container_iterator it = container->insert(container->begin(), container_value_type(3, 30));
    EXPECT_EQ(5u, container->size());

    it = container->insert(it, container_value_type(4, 40));
    EXPECT_EQ(6u, container->size());

    it = container->insert(it, container_value_type(4, 40));
    EXPECT_EQ(6u, container->size());

    it = container->insert(it, container_value_type(6, 60));
    EXPECT_EQ(7u, container->size());

    unsigned int count = 0u;
    for (const container_value_type& i : *container)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i.first);
        EXPECT_EQ(static_cast<int>(count) * 10, i.second);
    }
    EXPECT_EQ(7u, count);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(3u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}
namespace set
{
namespace multi
{

template<class C>
inline void test_insert_single_element_with_hint()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert single element with hint
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());
    container->insert(1);
    container->insert(2);
    container->insert(5);
    container->insert(7);
    EXPECT_EQ(4u, container->size());

    observer.connect(container);

    container_iterator it = container->insert(container->begin(), 3);
    EXPECT_EQ(5u, container->size());

    it = container->insert(it, 4);
    EXPECT_EQ(6u, container->size());

    it = container->insert(it, 4);
    EXPECT_EQ(7u, container->size());

    it = container->insert(it, 6);
    EXPECT_EQ(8u, container->size());

    it = container->begin();
    EXPECT_EQ(1, *it);
    ++it;
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(3, *it);
    ++it;
    EXPECT_EQ(4, *it);
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

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(4u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(8u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_insert_single_element_with_hint()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert single element with hint
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());
    container->insert(1);
    container->insert(2);
    container->insert(5);
    container->insert(7);
    EXPECT_EQ(4u, container->size());

    observer.connect(container);

    container_iterator it = container->insert(container->begin(), 3);
    EXPECT_EQ(5u, container->size());

    it = container->insert(it, 4);
    EXPECT_EQ(6u, container->size());

    it = container->insert(it, 4);
    EXPECT_EQ(6u, container->size());

    it = container->insert(it, 6);
    EXPECT_EQ(7u, container->size());

    unsigned int count = 0u;
    for (const int& i : *container)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i);
    }
    EXPECT_EQ(7u, count);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(3u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}
namespace unordered_map
{
namespace multi
{

template<class C>
inline void test_insert_single_element_with_hint()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert single element with hint
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());
    container->insert(container_value_type(1, 10));
    container->insert(container_value_type(2, 20));
    container->insert(container_value_type(5, 50));
    container->insert(container_value_type(7, 70));
    EXPECT_EQ(4u, container->size());

    observer.connect(container);

    container_iterator it = container->insert(container->begin(), container_value_type(3, 30));
    EXPECT_EQ(5u, container->size());

    it = container->insert(it, container_value_type(4, 40));
    EXPECT_EQ(6u, container->size());

    it = container->insert(it, container_value_type(4, 40));
    EXPECT_EQ(7u, container->size());

    it = container->insert(it, container_value_type(6, 60));
    EXPECT_EQ(8u, container->size());

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(4u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(8u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_insert_single_element_with_hint()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert single element with hint
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());
    (*container)[1] = 10;
    (*container)[2] = 20;
    (*container)[5] = 50;
    (*container)[7] = 70;
    EXPECT_EQ(4u, container->size());

    observer.connect(container);

    container_iterator it = container->insert(container->begin(), container_value_type(3, 30));
    EXPECT_EQ(5u, container->size());

    it = container->insert(it, container_value_type(4, 40));
    EXPECT_EQ(6u, container->size());

    it = container->insert(it, container_value_type(4, 40));
    EXPECT_EQ(6u, container->size());

    it = container->insert(it, container_value_type(6, 60));
    EXPECT_EQ(7u, container->size());

    unsigned int count = 0u;
    int sum = 0;
    for (const container_value_type & i : *container)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(280, sum);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(3u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}
namespace unordered_set
{
namespace multi
{

template<class C>
inline void test_insert_single_element_with_hint()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert single element with hint
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());
    container->insert(1);
    container->insert(2);
    container->insert(5);
    container->insert(7);
    EXPECT_EQ(4u, container->size());

    observer.connect(container);

    container_iterator it = container->insert(container->begin(), 3);
    EXPECT_EQ(5u, container->size());

    it = container->insert(it, 4);
    EXPECT_EQ(6u, container->size());

    it = container->insert(it, 4);
    EXPECT_EQ(7u, container->size());

    it = container->insert(it, 6);
    EXPECT_EQ(8u, container->size());

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(4u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(8u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_insert_single_element_with_hint()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert single element with hint
    container_ptr container = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container->size());
    container->insert(1);
    container->insert(2);
    container->insert(5);
    container->insert(7);
    EXPECT_EQ(4u, container->size());

    observer.connect(container);

    container_iterator it = container->insert(container->begin(), 3);
    EXPECT_EQ(5u, container->size());

    it = container->insert(it, 4);
    EXPECT_EQ(6u, container->size());

    it = container->insert(it, 4);
    EXPECT_EQ(6u, container->size());

    it = container->insert(it, 6);
    EXPECT_EQ(7u, container->size());

    unsigned int count = 0u;
    int sum = 0;
    for (const int& i : *container)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(28, sum);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(3u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}
}
}

#endif  // #if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT) || defined(GO_NO_CXX11_MUTEX))

#endif  // #ifndef GO_MVVM_TEST_INSERT_SINGLE_ELEMENT_WITH_HINT_IPP_INCLUDED
