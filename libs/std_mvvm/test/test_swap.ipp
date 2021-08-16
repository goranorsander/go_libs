#ifndef GO_MVVM_TEST_SWAP_IPP_INCLUDED
#define GO_MVVM_TEST_SWAP_IPP_INCLUDED

//
//  test_swap.ipp
//
//  Copyright 2020-2021 Göran Orsander
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
inline void test_swap()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test swap
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer1;
    container_observer_type observer2;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container1->insert(container_value_type(1, 10));
    container1->insert(container_value_type(2, 20));
    container1->insert(container_value_type(3, 30));
    container1->insert(container_value_type(4, 40));
    container1->insert(container_value_type(5, 50));
    EXPECT_EQ(5u, container1->size());

    container2->insert(container_value_type(10, 100));
    container2->insert(container_value_type(20, 200));
    container2->insert(container_value_type(30, 300));
    container2->insert(container_value_type(40, 400));
    container2->insert(container_value_type(50, 500));
    container2->insert(container_value_type(60, 600));
    container2->insert(container_value_type(70, 700));
    EXPECT_EQ(7u, container2->size());

    observer1.connect(container1);
    observer2.connect(container2);

    container1->swap(*container2);
    EXPECT_EQ(7u, container1->size());
    EXPECT_EQ(5u, container2->size());

    using observable_multimap_type = container_type;
    unsigned int count = 0u;
    for (const container_value_type & i : *container1)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count) * 10, i.first);
        EXPECT_EQ(static_cast<int>(count) * 100, i.second);
    }
    EXPECT_EQ(7u, count);

    count = 0;
    for (const container_value_type & i : *container2)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i.first);
        EXPECT_EQ(static_cast<int>(count) * 10, i.second);
    }
    EXPECT_EQ(5u, count);

    EXPECT_EQ(m::notify_container_changed_action::swap, observer1.last_action());
    EXPECT_EQ(0u, observer1.action_add_count());
    EXPECT_EQ(0u, observer1.action_remove_count());
    EXPECT_EQ(0u, observer1.action_reset_count());
    EXPECT_EQ(1u, observer1.action_swap_count());
    EXPECT_EQ(7u, observer1.last_change_new_size());
    EXPECT_EQ(7u, observer1.last_change_added());
    EXPECT_EQ(5u, observer1.last_change_removed());
    EXPECT_EQ(7u, observer1.total_change_added());
    EXPECT_EQ(5u, observer1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::swap, observer2.last_action());
    EXPECT_EQ(0u, observer2.action_add_count());
    EXPECT_EQ(0u, observer2.action_remove_count());
    EXPECT_EQ(0u, observer2.action_reset_count());
    EXPECT_EQ(1u, observer2.action_swap_count());
    EXPECT_EQ(5u, observer2.last_change_new_size());
    EXPECT_EQ(5u, observer2.last_change_added());
    EXPECT_EQ(7u, observer2.last_change_removed());
    EXPECT_EQ(5u, observer2.total_change_added());
    EXPECT_EQ(7u, observer2.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_swap()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test swap
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer1;
    container_observer_type observer2;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    (*container1)[1] = 10;
    (*container1)[2] = 20;
    (*container1)[3] = 30;
    (*container1)[4] = 40;
    (*container1)[5] = 50;
    EXPECT_EQ(5u, container1->size());

    (*container2)[10] = 100;
    (*container2)[20] = 200;
    (*container2)[30] = 300;
    (*container2)[40] = 400;
    (*container2)[50] = 500;
    (*container2)[60] = 600;
    (*container2)[70] = 700;
    EXPECT_EQ(7u, container2->size());

    observer1.connect(container1);
    observer2.connect(container2);

    container1->swap(*container2);
    EXPECT_EQ(7u, container1->size());
    EXPECT_EQ(5u, container2->size());

    unsigned int count = 0u;
    for (const container_value_type& i : *container1)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count) * 10, i.first);
        EXPECT_EQ(static_cast<int>(count) * 100, i.second);
    }
    EXPECT_EQ(7u, count);

    count = 0;
    for (const container_value_type& i : *container2)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i.first);
        EXPECT_EQ(static_cast<int>(count) * 10, i.second);
    }
    EXPECT_EQ(5u, count);

    EXPECT_EQ(m::notify_container_changed_action::swap, observer1.last_action());
    EXPECT_EQ(0u, observer1.action_add_count());
    EXPECT_EQ(0u, observer1.action_remove_count());
    EXPECT_EQ(0u, observer1.action_reset_count());
    EXPECT_EQ(1u, observer1.action_swap_count());
    EXPECT_EQ(7u, observer1.last_change_new_size());
    EXPECT_EQ(7u, observer1.last_change_added());
    EXPECT_EQ(5u, observer1.last_change_removed());
    EXPECT_EQ(7u, observer1.total_change_added());
    EXPECT_EQ(5u, observer1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::swap, observer2.last_action());
    EXPECT_EQ(0u, observer2.action_add_count());
    EXPECT_EQ(0u, observer2.action_remove_count());
    EXPECT_EQ(0u, observer2.action_reset_count());
    EXPECT_EQ(1u, observer2.action_swap_count());
    EXPECT_EQ(5u, observer2.last_change_new_size());
    EXPECT_EQ(5u, observer2.last_change_added());
    EXPECT_EQ(7u, observer2.last_change_removed());
    EXPECT_EQ(5u, observer2.total_change_added());
    EXPECT_EQ(7u, observer2.total_change_removed());
}

}
}
namespace set
{
namespace multi
{

template<class C>
inline void test_swap()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test swap
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer1;
    container_observer_type observer2;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container1->insert(1);
    container1->insert(2);
    container1->insert(3);
    container1->insert(4);
    container1->insert(5);
    EXPECT_EQ(5u, container1->size());

    container2->insert(10);
    container2->insert(20);
    container2->insert(30);
    container2->insert(40);
    container2->insert(50);
    container2->insert(60);
    container2->insert(70);
    EXPECT_EQ(7u, container2->size());

    observer1.connect(container1);
    observer2.connect(container2);

    container1->swap(*container2);
    EXPECT_EQ(7u, container1->size());
    EXPECT_EQ(5u, container2->size());

    unsigned int count = 0u;
    for (const int& i : *container1)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count) * 10, i);
    }
    EXPECT_EQ(7u, count);

    count = 0;
    for (const int& i : *container2)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i);
    }
    EXPECT_EQ(5u, count);

    EXPECT_EQ(m::notify_container_changed_action::swap, observer1.last_action());
    EXPECT_EQ(0u, observer1.action_add_count());
    EXPECT_EQ(0u, observer1.action_remove_count());
    EXPECT_EQ(0u, observer1.action_reset_count());
    EXPECT_EQ(1u, observer1.action_swap_count());
    EXPECT_EQ(7u, observer1.last_change_new_size());
    EXPECT_EQ(7u, observer1.last_change_added());
    EXPECT_EQ(5u, observer1.last_change_removed());
    EXPECT_EQ(7u, observer1.total_change_added());
    EXPECT_EQ(5u, observer1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::swap, observer2.last_action());
    EXPECT_EQ(0u, observer2.action_add_count());
    EXPECT_EQ(0u, observer2.action_remove_count());
    EXPECT_EQ(0u, observer2.action_reset_count());
    EXPECT_EQ(1u, observer2.action_swap_count());
    EXPECT_EQ(5u, observer2.last_change_new_size());
    EXPECT_EQ(5u, observer2.last_change_added());
    EXPECT_EQ(7u, observer2.last_change_removed());
    EXPECT_EQ(5u, observer2.total_change_added());
    EXPECT_EQ(7u, observer2.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_swap()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test swap
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer1;
    container_observer_type observer2;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container1->insert(1);
    container1->insert(2);
    container1->insert(3);
    container1->insert(4);
    container1->insert(5);
    EXPECT_EQ(5u, container1->size());

    container2->insert(10);
    container2->insert(20);
    container2->insert(30);
    container2->insert(40);
    container2->insert(50);
    container2->insert(60);
    container2->insert(70);
    EXPECT_EQ(7u, container2->size());

    observer1.connect(container1);
    observer2.connect(container2);

    container1->swap(*container2);
    EXPECT_EQ(7u, container1->size());
    EXPECT_EQ(5u, container2->size());

    unsigned int count = 0u;
    for (const int& i : *container1)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count) * 10, i);
    }
    EXPECT_EQ(7u, count);

    count = 0;
    for (const int& i : *container2)
    {
        ++count;
        EXPECT_EQ(static_cast<int>(count), i);
    }
    EXPECT_EQ(5u, count);

    EXPECT_EQ(m::notify_container_changed_action::swap, observer1.last_action());
    EXPECT_EQ(0u, observer1.action_add_count());
    EXPECT_EQ(0u, observer1.action_remove_count());
    EXPECT_EQ(0u, observer1.action_reset_count());
    EXPECT_EQ(1u, observer1.action_swap_count());
    EXPECT_EQ(7u, observer1.last_change_new_size());
    EXPECT_EQ(7u, observer1.last_change_added());
    EXPECT_EQ(5u, observer1.last_change_removed());
    EXPECT_EQ(7u, observer1.total_change_added());
    EXPECT_EQ(5u, observer1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::swap, observer2.last_action());
    EXPECT_EQ(0u, observer2.action_add_count());
    EXPECT_EQ(0u, observer2.action_remove_count());
    EXPECT_EQ(0u, observer2.action_reset_count());
    EXPECT_EQ(1u, observer2.action_swap_count());
    EXPECT_EQ(5u, observer2.last_change_new_size());
    EXPECT_EQ(5u, observer2.last_change_added());
    EXPECT_EQ(7u, observer2.last_change_removed());
    EXPECT_EQ(5u, observer2.total_change_added());
    EXPECT_EQ(7u, observer2.total_change_removed());
}

}
}
namespace unordered_map
{
namespace multi
{

template<class C>
inline void test_swap()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test swap
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer1;
    container_observer_type observer2;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container1->insert(container_value_type(1, 10));
    container1->insert(container_value_type(2, 20));
    container1->insert(container_value_type(3, 30));
    container1->insert(container_value_type(4, 40));
    container1->insert(container_value_type(5, 50));
    EXPECT_EQ(5u, container1->size());

    container2->insert(container_value_type(10, 100));
    container2->insert(container_value_type(20, 200));
    container2->insert(container_value_type(30, 300));
    container2->insert(container_value_type(40, 400));
    container2->insert(container_value_type(50, 500));
    container2->insert(container_value_type(60, 600));
    container2->insert(container_value_type(70, 700));
    EXPECT_EQ(7u, container2->size());

    observer1.connect(container1);
    observer2.connect(container2);

    container1->swap(*container2);
    EXPECT_EQ(7u, container1->size());
    EXPECT_EQ(5u, container2->size());

    unsigned int count = 0u;
    int sum = 0;
    for (const container_value_type& i : *container1)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(2800, sum);

    count = 0;
    sum = 0;
    for (const container_value_type& i : *container2)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(5u, count);
    EXPECT_EQ(150, sum);

    EXPECT_EQ(m::notify_container_changed_action::swap, observer1.last_action());
    EXPECT_EQ(0u, observer1.action_add_count());
    EXPECT_EQ(0u, observer1.action_remove_count());
    EXPECT_EQ(0u, observer1.action_reset_count());
    EXPECT_EQ(1u, observer1.action_swap_count());
    EXPECT_EQ(7u, observer1.last_change_new_size());
    EXPECT_EQ(7u, observer1.last_change_added());
    EXPECT_EQ(5u, observer1.last_change_removed());
    EXPECT_EQ(7u, observer1.total_change_added());
    EXPECT_EQ(5u, observer1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::swap, observer2.last_action());
    EXPECT_EQ(0u, observer2.action_add_count());
    EXPECT_EQ(0u, observer2.action_remove_count());
    EXPECT_EQ(0u, observer2.action_reset_count());
    EXPECT_EQ(1u, observer2.action_swap_count());
    EXPECT_EQ(5u, observer2.last_change_new_size());
    EXPECT_EQ(5u, observer2.last_change_added());
    EXPECT_EQ(7u, observer2.last_change_removed());
    EXPECT_EQ(5u, observer2.total_change_added());
    EXPECT_EQ(7u, observer2.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_swap()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test swap
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer1;
    container_observer_type observer2;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    (*container1)[1] = 10;
    (*container1)[2] = 20;
    (*container1)[3] = 30;
    (*container1)[4] = 40;
    (*container1)[5] = 50;
    EXPECT_EQ(5u, container1->size());

    (*container2)[10] = 100;
    (*container2)[20] = 200;
    (*container2)[30] = 300;
    (*container2)[40] = 400;
    (*container2)[50] = 500;
    (*container2)[60] = 600;
    (*container2)[70] = 700;
    EXPECT_EQ(7u, container2->size());

    observer1.connect(container1);
    observer2.connect(container2);

    container1->swap(*container2);
    EXPECT_EQ(7u, container1->size());
    EXPECT_EQ(5u, container2->size());

    using observable_unordered_map_type = container_type;
    unsigned int count = 0u;
    int sum = 0;
    for (const container_value_type & i : *container1)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(2800, sum);

    count = 0;
    sum = 0;
    for (const container_value_type & i : *container2)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(5u, count);
    EXPECT_EQ(150, sum);

    EXPECT_EQ(m::notify_container_changed_action::swap, observer1.last_action());
    EXPECT_EQ(0u, observer1.action_add_count());
    EXPECT_EQ(0u, observer1.action_remove_count());
    EXPECT_EQ(0u, observer1.action_reset_count());
    EXPECT_EQ(1u, observer1.action_swap_count());
    EXPECT_EQ(7u, observer1.last_change_new_size());
    EXPECT_EQ(7u, observer1.last_change_added());
    EXPECT_EQ(5u, observer1.last_change_removed());
    EXPECT_EQ(7u, observer1.total_change_added());
    EXPECT_EQ(5u, observer1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::swap, observer2.last_action());
    EXPECT_EQ(0u, observer2.action_add_count());
    EXPECT_EQ(0u, observer2.action_remove_count());
    EXPECT_EQ(0u, observer2.action_reset_count());
    EXPECT_EQ(1u, observer2.action_swap_count());
    EXPECT_EQ(5u, observer2.last_change_new_size());
    EXPECT_EQ(5u, observer2.last_change_added());
    EXPECT_EQ(7u, observer2.last_change_removed());
    EXPECT_EQ(5u, observer2.total_change_added());
    EXPECT_EQ(7u, observer2.total_change_removed());
}

}
}
namespace unordered_set
{
namespace multi
{

template<class C>
inline void test_swap()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test swap
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer1;
    container_observer_type observer2;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container1->insert(1);
    container1->insert(2);
    container1->insert(3);
    container1->insert(4);
    container1->insert(5);
    EXPECT_EQ(5u, container1->size());

    container2->insert(10);
    container2->insert(20);
    container2->insert(30);
    container2->insert(40);
    container2->insert(50);
    container2->insert(60);
    container2->insert(70);
    EXPECT_EQ(7u, container2->size());

    observer1.connect(container1);
    observer2.connect(container2);

    container1->swap(*container2);
    EXPECT_EQ(7u, container1->size());
    EXPECT_EQ(5u, container2->size());

    unsigned int count = 0u;
    int sum = 0;
    for (const int& i : *container1)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(280, sum);

    count = 0;
    sum = 0;
    for (const int& i : *container2)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(5u, count);
    EXPECT_EQ(15, sum);

    EXPECT_EQ(m::notify_container_changed_action::swap, observer1.last_action());
    EXPECT_EQ(0u, observer1.action_add_count());
    EXPECT_EQ(0u, observer1.action_remove_count());
    EXPECT_EQ(0u, observer1.action_reset_count());
    EXPECT_EQ(1u, observer1.action_swap_count());
    EXPECT_EQ(7u, observer1.last_change_new_size());
    EXPECT_EQ(7u, observer1.last_change_added());
    EXPECT_EQ(5u, observer1.last_change_removed());
    EXPECT_EQ(7u, observer1.total_change_added());
    EXPECT_EQ(5u, observer1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::swap, observer2.last_action());
    EXPECT_EQ(0u, observer2.action_add_count());
    EXPECT_EQ(0u, observer2.action_remove_count());
    EXPECT_EQ(0u, observer2.action_reset_count());
    EXPECT_EQ(1u, observer2.action_swap_count());
    EXPECT_EQ(5u, observer2.last_change_new_size());
    EXPECT_EQ(5u, observer2.last_change_added());
    EXPECT_EQ(7u, observer2.last_change_removed());
    EXPECT_EQ(5u, observer2.total_change_added());
    EXPECT_EQ(7u, observer2.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_swap()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test swap
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer1;
    container_observer_type observer2;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container1->insert(1);
    container1->insert(2);
    container1->insert(3);
    container1->insert(4);
    container1->insert(5);
    EXPECT_EQ(5u, container1->size());

    container2->insert(10);
    container2->insert(20);
    container2->insert(30);
    container2->insert(40);
    container2->insert(50);
    container2->insert(60);
    container2->insert(70);
    EXPECT_EQ(7u, container2->size());

    observer1.connect(container1);
    observer2.connect(container2);

    container1->swap(*container2);
    EXPECT_EQ(7u, container1->size());
    EXPECT_EQ(5u, container2->size());

    unsigned int count = 0u;
    int sum = 0;
    for (const int& i : *container1)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(280, sum);

    count = 0;
    sum = 0;
    for (const int& i : *container2)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(5u, count);
    EXPECT_EQ(15, sum);

    EXPECT_EQ(m::notify_container_changed_action::swap, observer1.last_action());
    EXPECT_EQ(0u, observer1.action_add_count());
    EXPECT_EQ(0u, observer1.action_remove_count());
    EXPECT_EQ(0u, observer1.action_reset_count());
    EXPECT_EQ(1u, observer1.action_swap_count());
    EXPECT_EQ(7u, observer1.last_change_new_size());
    EXPECT_EQ(7u, observer1.last_change_added());
    EXPECT_EQ(5u, observer1.last_change_removed());
    EXPECT_EQ(7u, observer1.total_change_added());
    EXPECT_EQ(5u, observer1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::swap, observer2.last_action());
    EXPECT_EQ(0u, observer2.action_add_count());
    EXPECT_EQ(0u, observer2.action_remove_count());
    EXPECT_EQ(0u, observer2.action_reset_count());
    EXPECT_EQ(1u, observer2.action_swap_count());
    EXPECT_EQ(5u, observer2.last_change_new_size());
    EXPECT_EQ(5u, observer2.last_change_added());
    EXPECT_EQ(7u, observer2.last_change_removed());
    EXPECT_EQ(5u, observer2.total_change_added());
    EXPECT_EQ(7u, observer2.total_change_removed());
}

}
}
}
namespace sequence
{

template<class C>
inline void test_swap()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;

    // Test swap
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer1;
    container_observer_type observer2;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container1->assign(5, 1);
    container2->assign(7, 2);
    EXPECT_EQ(5u, container1->size());
    EXPECT_EQ(7u, container2->size());

    observer1.connect(container1);
    observer2.connect(container2);

    container1->swap(*container2);
    EXPECT_EQ(7u, container1->size());
    EXPECT_EQ(5u, container2->size());

    unsigned int count = 0u;
    for (const int& i : *container1)
    {
        ++count;
        EXPECT_EQ(2, i);
    }
    EXPECT_EQ(7u, count);

    count = 0;
    for (const int& i : *container2)
    {
        ++count;
        EXPECT_EQ(1, i);
    }
    EXPECT_EQ(5u, count);

    EXPECT_EQ(m::notify_container_changed_action::swap, observer1.last_action());
    EXPECT_EQ(0u, observer1.action_add_count());
    EXPECT_EQ(0u, observer1.action_remove_count());
    EXPECT_EQ(0u, observer1.action_reset_count());
    EXPECT_EQ(1u, observer1.action_swap_count());
    EXPECT_EQ(7u, observer1.last_change_new_size());
    EXPECT_EQ(7u, observer1.last_change_added());
    EXPECT_EQ(5u, observer1.last_change_removed());
    EXPECT_EQ(7u, observer1.total_change_added());
    EXPECT_EQ(5u, observer1.total_change_removed());

    EXPECT_EQ(m::notify_container_changed_action::swap, observer2.last_action());
    EXPECT_EQ(0u, observer2.action_add_count());
    EXPECT_EQ(0u, observer2.action_remove_count());
    EXPECT_EQ(0u, observer2.action_reset_count());
    EXPECT_EQ(1u, observer2.action_swap_count());
    EXPECT_EQ(5u, observer2.last_change_new_size());
    EXPECT_EQ(5u, observer2.last_change_added());
    EXPECT_EQ(7u, observer2.last_change_removed());
    EXPECT_EQ(5u, observer2.total_change_added());
    EXPECT_EQ(7u, observer2.total_change_removed());
}

}
}

#endif  // #if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT) || defined(GO_NO_CXX11_MUTEX))

#endif  // #ifndef GO_MVVM_TEST_SWAP_IPP_INCLUDED
