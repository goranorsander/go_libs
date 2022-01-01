#ifndef GO_MVVM_TEST_INSERT_RANGE_IPP_INCLUDED
#define GO_MVVM_TEST_INSERT_RANGE_IPP_INCLUDED

//
//  test_insert_range.ipp
//
//  Copyright 2020-2022 Göran Orsander
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
inline void test_insert_range()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert range
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container1->insert(container_value_type(1, 10));
    container1->insert(container_value_type(2, 20));
    container1->insert(container_value_type(5, 50));
    container1->insert(container_value_type(7, 70));
    EXPECT_EQ(4u, container1->size());

    container2->insert(container_value_type(3, 30));
    container2->insert(container_value_type(4, 40));
    container2->insert(container_value_type(6, 60));
    EXPECT_EQ(3u, container2->size());

    observer.connect(container2);

    container2->insert(container1->begin(), container1->end());
    EXPECT_EQ(7u, container2->size());

    container_iterator it = container2->begin();
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
    EXPECT_EQ(container2->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(4u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_insert_range()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert range
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    (*container1)[1] = 10;
    (*container1)[2] = 20;
    (*container1)[5] = 50;
    (*container1)[7] = 70;
    EXPECT_EQ(4u, container1->size());

    (*container2)[3] = 30;
    (*container2)[4] = 40;
    (*container2)[6] = 60;
    EXPECT_EQ(3u, container2->size());

    observer.connect(container2);

    container2->insert(container1->begin(), container1->end());
    EXPECT_EQ(7u, container2->size());

    m::basic_observable_map<int, int, s::u8string>::iterator it = container2->begin();
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
    EXPECT_EQ(container2->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(4u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}
namespace set
{
namespace multi
{

template<class C>
inline void test_insert_range()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert range
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container1->insert(1);
    container1->insert(2);
    container1->insert(5);
    container1->insert(7);
    EXPECT_EQ(4u, container1->size());

    container2->insert(3);
    container2->insert(4);
    container2->insert(6);
    EXPECT_EQ(3u, container2->size());

    observer.connect(container2);

    container2->insert(container1->begin(), container1->end());
    EXPECT_EQ(7u, container2->size());

    container_iterator it = container2->begin();
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
    EXPECT_EQ(container2->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(4u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_insert_range()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert range
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container1->insert(1);
    container1->insert(2);
    container1->insert(5);
    container1->insert(7);
    EXPECT_EQ(4u, container1->size());

    container2->insert(3);
    container2->insert(4);
    container2->insert(6);
    EXPECT_EQ(3u, container2->size());

    observer.connect(container2);

    container2->insert(container1->begin(), container1->end());
    EXPECT_EQ(7u, container2->size());

    container_iterator it = container2->begin();
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
    EXPECT_EQ(container2->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(4u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}
namespace unordered_map
{
namespace multi
{

template<class C>
inline void test_insert_range()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert range
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container1->insert(container_value_type(1, 10));
    container1->insert(container_value_type(2, 20));
    container1->insert(container_value_type(5, 50));
    container1->insert(container_value_type(7, 70));
    EXPECT_EQ(4u, container1->size());

    container2->insert(container_value_type(3, 30));
    container2->insert(container_value_type(4, 40));
    container2->insert(container_value_type(6, 60));
    EXPECT_EQ(3u, container2->size());

    observer.connect(container2);

    container2->insert(container1->begin(), container1->end());
    EXPECT_EQ(7u, container2->size());

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(4u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_insert_range()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert range
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    (*container1)[1] = 10;
    (*container1)[2] = 20;
    (*container1)[5] = 50;
    (*container1)[7] = 70;
    EXPECT_EQ(4u, container1->size());

    (*container2)[3] = 30;
    (*container2)[4] = 40;
    (*container2)[6] = 60;
    EXPECT_EQ(3u, container2->size());

    observer.connect(container2);

    container2->insert(container1->begin(), container1->end());
    EXPECT_EQ(7u, container2->size());

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(4u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}
namespace unordered_set
{
namespace multi
{

template<class C>
inline void test_insert_range()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert range
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container1->insert(1);
    container1->insert(2);
    container1->insert(5);
    container1->insert(7);
    EXPECT_EQ(4u, container1->size());

    container2->insert(3);
    container2->insert(4);
    container2->insert(6);
    EXPECT_EQ(3u, container2->size());

    observer.connect(container2);

    container2->insert(container1->begin(), container1->end());
    EXPECT_EQ(7u, container2->size());

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(4u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
namespace unique
{

template<class C>
inline void test_insert_range()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;
    using container_value_type = typename container_type::value_type;

    // Test insert range
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container1->size());
    EXPECT_EQ(0u, container2->size());

    container1->insert(1);
    container1->insert(2);
    container1->insert(5);
    container1->insert(7);
    EXPECT_EQ(4u, container1->size());

    container2->insert(3);
    container2->insert(4);
    container2->insert(6);
    EXPECT_EQ(3u, container2->size());

    observer.connect(container2);

    container2->insert(container1->begin(), container1->end());
    EXPECT_EQ(7u, container2->size());

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(4u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}
}
namespace sequence
{
namespace indexed
{

template<class C>
inline void test_insert_range()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;

    // Test insert range
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container1->size());

    container1->assign(3, 74);
    EXPECT_EQ(3u, container1->size());

    EXPECT_EQ(0u, container2->size());
    container2->assign(7, 47);
    EXPECT_EQ(7u, container2->size());

    observer.connect(container2);

    container_iterator it = container2->begin();
    container2->insert(it + 3, container1->begin(), container1->end());
    EXPECT_EQ(10u, container2->size());

    EXPECT_EQ(47, (*container2)[0]);
    EXPECT_EQ(47, (*container2)[1]);
    EXPECT_EQ(47, (*container2)[2]);
    EXPECT_EQ(74, (*container2)[3]);
    EXPECT_EQ(74, (*container2)[4]);
    EXPECT_EQ(74, (*container2)[5]);
    EXPECT_EQ(47, (*container2)[6]);
    EXPECT_EQ(47, (*container2)[7]);
    EXPECT_EQ(47, (*container2)[8]);
    EXPECT_EQ(47, (*container2)[9]);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(10u, observer.last_change_new_size());
    EXPECT_EQ(3u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
namespace linked
{

template<class C>
inline void test_insert_range()
{
    using container_type = C;
    using string_type = typename container_type::string_type;
    using lockable_type = typename container_type::lockable_type;
    using container_observer_type = container_observer<container_type, string_type, lockable_type>;
    using container_iterator = typename container_type::iterator;
    using container_ptr = typename container_type::ptr;

    // Test insert range
    container_ptr container1 = container_type::create();
    container_ptr container2 = container_type::create();
    container_observer_type observer;

    EXPECT_EQ(0u, container1->size());

    container1->assign(3, 74);
    EXPECT_EQ(3u, container1->size());

    EXPECT_EQ(0u, container2->size());
    container2->assign(7, 47);
    EXPECT_EQ(7u, container2->size());

    observer.connect(container2);

    container_iterator it = container2->begin();
    std::advance(it, 3);
    container2->insert(it, container1->begin(), container1->end());
    EXPECT_EQ(10u, container2->size());

    it = container2->begin();
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(74, *it);
    ++it;
    EXPECT_EQ(74, *it);
    ++it;
    EXPECT_EQ(74, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(47, *it);
    ++it;
    EXPECT_EQ(container2->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(1u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(10u, observer.last_change_new_size());
    EXPECT_EQ(3u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());
}

}
}
}

#endif  // #if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT) || defined(GO_NO_CXX11_MUTEX))

#endif  // #ifndef GO_MVVM_TEST_INSERT_RANGE_IPP_INCLUDED
