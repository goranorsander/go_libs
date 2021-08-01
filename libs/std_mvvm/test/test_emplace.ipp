#ifndef GO_MVVM_TEST_EMPLACE_IPP_INCLUDED
#define GO_MVVM_TEST_EMPLACE_IPP_INCLUDED

//
//  test_emplace.ipp
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

namespace go_test
{
namespace associative
{
namespace map
{
namespace multi
{

template<class C>
inline void test_emplace()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)

    // Test emplace
    container_ptr container = container_type::create();
    container_observer_type observer;

    container->insert(container_value_type(1, 10));
    container->insert(container_value_type(2, 20));
    container->insert(container_value_type(3, 30));
    EXPECT_EQ(3u, container->size());

    observer.connect(container);

    container_iterator it = container->emplace(container_value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = container->emplace(container_value_type(5, 50));
    EXPECT_EQ(5, it->first);
    EXPECT_EQ(50, it->second);

    it = container->emplace(container_value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = container->emplace(container_value_type(6, 60));
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);

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
    EXPECT_EQ(container->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(4u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
}

}
namespace unique
{

template<class C>
inline void test_emplace()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)

    // Test emplace
    container_ptr container = container_type::create();
    container_observer_type observer;

    (*container)[1] = 10;
    (*container)[2] = 20;
    (*container)[3] = 30;
    EXPECT_EQ(3u, container->size());

    observer.connect(container);

    auto ret = container->emplace(container_value_type(4, 40));
    EXPECT_EQ(4, ret.first->first);
    EXPECT_EQ(40, ret.first->second);
    EXPECT_TRUE(ret.second);

    ret = container->emplace(container_value_type(5, 50));
    EXPECT_EQ(5, ret.first->first);
    EXPECT_EQ(50, ret.first->second);
    EXPECT_TRUE(ret.second);

    ret = container->emplace(container_value_type(4, 40));
    EXPECT_EQ(4, ret.first->first);
    EXPECT_EQ(40, ret.first->second);
    EXPECT_FALSE(ret.second);

    ret = container->emplace(container_value_type(6, 60));
    EXPECT_EQ(6, ret.first->first);
    EXPECT_EQ(60, ret.first->second);
    EXPECT_TRUE(ret.second);

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
    EXPECT_EQ(container->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(3u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(6u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
}

}
}
namespace set
{
namespace multi
{

template<class C>
inline void test_emplace()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)

    // Test emplace
    container_ptr container = container_type::create();
    container_observer_type observer;

    container->insert(1);
    container->insert(2);
    container->insert(3);
    EXPECT_EQ(3u, container->size());

    observer.connect(container);

    container_iterator it = container->emplace(4);
    EXPECT_EQ(4, *it);

    it = container->emplace(5);
    EXPECT_EQ(5, *it);

    it = container->emplace(4);
    EXPECT_EQ(4, *it);

    it = container->emplace(6);
    EXPECT_EQ(6, *it);

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
    EXPECT_EQ(container->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(4u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
}

}
namespace unique
{

template<class C>
inline void test_emplace()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)

    // Test emplace
    container_ptr container = container_type::create();
    container_observer_type observer;

    container->insert(1);
    container->insert(2);
    container->insert(3);
    EXPECT_EQ(3u, container->size());

    observer.connect(container);

    auto ret = container->emplace(4);
    EXPECT_EQ(4, *(ret.first));
    EXPECT_TRUE(ret.second);

    ret = container->emplace(5);
    EXPECT_EQ(5, *(ret.first));
    EXPECT_TRUE(ret.second);

    ret = container->emplace(4);
    EXPECT_EQ(4, *(ret.first));
    EXPECT_FALSE(ret.second);

    ret = container->emplace(6);
    EXPECT_EQ(6, *(ret.first));
    EXPECT_TRUE(ret.second);

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
    EXPECT_EQ(container->end(), it);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(3u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(6u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
}

}
}
namespace unordered_map
{
namespace multi
{

template<class C>
inline void test_emplace()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)

    // Test emplace
    container_ptr container = container_type::create();
    container_observer_type observer;

    container->insert(container_value_type(1, 10));
    container->insert(container_value_type(2, 20));
    container->insert(container_value_type(3, 30));
    EXPECT_EQ(3u, container->size());

    observer.connect(container);

    container_iterator it = container->emplace(container_value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = container->emplace(container_value_type(5, 50));
    EXPECT_EQ(5, it->first);
    EXPECT_EQ(50, it->second);

    it = container->emplace(container_value_type(4, 40));
    EXPECT_EQ(4, it->first);
    EXPECT_EQ(40, it->second);

    it = container->emplace(container_value_type(6, 60));
    EXPECT_EQ(6, it->first);
    EXPECT_EQ(60, it->second);

    unsigned int count = 0u;
    int sum = 0;
    for (const container_value_type& i : *container)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(250, sum);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(4u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
}

}
namespace unique
{

template<class C>
inline void test_emplace()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)

    // Test emplace
    container_ptr container = container_type::create();
    container_observer_type observer;

    (*container)[1] = 10;
    (*container)[2] = 20;
    (*container)[3] = 30;
    EXPECT_EQ(3u, container->size());

    observer.connect(container);

    auto ret = container->emplace(container_value_type(4, 40));
    EXPECT_EQ(4, ret.first->first);
    EXPECT_EQ(40, ret.first->second);
    EXPECT_TRUE(ret.second);

    ret = container->emplace(container_value_type(5, 50));
    EXPECT_EQ(5, ret.first->first);
    EXPECT_EQ(50, ret.first->second);
    EXPECT_TRUE(ret.second);

    ret = container->emplace(container_value_type(4, 40));
    EXPECT_EQ(4, ret.first->first);
    EXPECT_EQ(40, ret.first->second);
    EXPECT_FALSE(ret.second);

    ret = container->emplace(container_value_type(6, 60));
    EXPECT_EQ(6, ret.first->first);
    EXPECT_EQ(60, ret.first->second);
    EXPECT_TRUE(ret.second);

    typedef container_type observable_unordered_map_type;
    unsigned int count = 0u;
    int sum = 0;
    for (const container_value_type & i : *container)
    {
        sum += i.second;
        ++count;
    }
    EXPECT_EQ(6u, count);
    EXPECT_EQ(210, sum);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(3u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(6u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
}

}
}
namespace unordered_set
{
namespace multi
{

template<class C>
inline void test_emplace()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)

    // Test emplace
    container_ptr container = container_type::create();
    container_observer_type observer;

    container->insert(1);
    container->insert(2);
    container->insert(3);
    EXPECT_EQ(3u, container->size());

    observer.connect(container);

    container_iterator it = container->emplace(4);
    EXPECT_EQ(4, *it);

    it = container->emplace(5);
    EXPECT_EQ(5, *it);

    it = container->emplace(4);
    EXPECT_EQ(4, *it);

    it = container->emplace(6);
    EXPECT_EQ(6, *it);

    unsigned int count = 0u;
    int sum = 0;
    for (const container_value_type& i : *container)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(7u, count);
    EXPECT_EQ(25, sum);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(4u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(7u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(4u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
}

}
namespace unique
{

template<class C>
inline void test_emplace()
{
    typedef C container_type;
    typedef typename container_type::string_type string_type;
    typedef typename container_type::lockable_type lockable_type;
    typedef container_observer<container_type, string_type, lockable_type> container_observer_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::ptr container_ptr;
    typedef typename container_type::value_type container_value_type;

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)

    // Test emplace
    container_ptr container = container_type::create();
    container_observer_type observer;

    container->insert(1);
    container->insert(2);
    container->insert(3);
    EXPECT_EQ(3u, container->size());

    observer.connect(container);

    auto ret = container->emplace(4);
    EXPECT_EQ(4, *(ret.first));
    EXPECT_TRUE(ret.second);

    ret = container->emplace(5);
    EXPECT_EQ(5, *(ret.first));
    EXPECT_TRUE(ret.second);

    ret = container->emplace(4);
    EXPECT_EQ(4, *(ret.first));
    EXPECT_FALSE(ret.second);

    ret = container->emplace(6);
    EXPECT_EQ(6, *(ret.first));
    EXPECT_TRUE(ret.second);

    typedef container_type observable_unordered_set_type;
    unsigned int count = 0u;
    int sum = 0;
    for (const GO_TYPENAME observable_unordered_set_type::value_type & i : *container)
    {
        sum += i;
        ++count;
    }
    EXPECT_EQ(6u, count);
    EXPECT_EQ(21, sum);

    EXPECT_EQ(m::notify_container_changed_action::add, observer.last_action());
    EXPECT_EQ(3u, observer.action_add_count());
    EXPECT_EQ(0u, observer.action_remove_count());
    EXPECT_EQ(0u, observer.action_reset_count());
    EXPECT_EQ(0u, observer.action_swap_count());
    EXPECT_EQ(6u, observer.last_change_new_size());
    EXPECT_EQ(1u, observer.last_change_added());
    EXPECT_EQ(0u, observer.last_change_removed());
    EXPECT_EQ(3u, observer.total_change_added());
    EXPECT_EQ(0u, observer.total_change_removed());

#endif  // !defined(GO_NO_CXX11_RVALUE_REFERENCES) && !defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
}

}
}
}
}

#endif  // #ifndef GO_MVVM_TEST_EMPLACE_IPP_INCLUDED
