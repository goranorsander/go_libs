//
//  circular_buffer_test_suite.cpp
//
//  Copyright 2019-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_STATIC_CONST_DATA_MEMBER_INSIDE_CLASS_DEFINITION)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_circular_buffer_test_suite, cpp11_not_supported) {}
#else

#include <go/namespace_alias.hpp>
#include <go/namespace_alias.hpp>
#include <go/utility/container/circular_buffer.hpp>
#include <go/utility/iterator/reverse.hpp>

namespace
{

TEST(std_circular_buffer_test_suite, test_constructor)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    {
        circular_buffer_type buffer;
        EXPECT_EQ(buffer.capacity(), GO_UL(0));
        EXPECT_EQ(buffer.size(), GO_UL(0));
        EXPECT_EQ(buffer.empty(), true);
        EXPECT_EQ(buffer.full(), true);
    }

    {
        const circular_buffer_type::capacity_type cap = 5;
        circular_buffer_type buffer(cap);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(0));
        EXPECT_EQ(buffer.empty(), true);
        EXPECT_EQ(buffer.full(), false);
    }

    {
        const circular_buffer_type::size_type count = 5;
        const circular_buffer_type::value_type value = 1;
        circular_buffer_type buffer(count, value);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer.at(0), 1);
        EXPECT_EQ(buffer.at(1), 1);
        EXPECT_EQ(buffer.at(2), 1);
        EXPECT_EQ(buffer.at(3), 1);
        EXPECT_EQ(buffer.at(4), 1);
    }

    {
        const circular_buffer_type::capacity_type cap = 10;
        const circular_buffer_type::size_type count = 5;
        const circular_buffer_type::value_type value = 1;
        circular_buffer_type buffer(cap, count, value);
        EXPECT_EQ(buffer.capacity(), GO_UL(10));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), false);
        EXPECT_EQ(buffer.at(0), 1);
        EXPECT_EQ(buffer.at(1), 1);
        EXPECT_EQ(buffer.at(2), 1);
        EXPECT_EQ(buffer.at(3), 1);
        EXPECT_EQ(buffer.at(4), 1);
    }

    {
        const std::vector<circular_buffer_type::value_type> values = { 1, 2, 3, 4, 5 };
        circular_buffer_type buffer(values.begin(), values.end());
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer.at(0), 1);
        EXPECT_EQ(buffer.at(1), 2);
        EXPECT_EQ(buffer.at(2), 3);
        EXPECT_EQ(buffer.at(3), 4);
        EXPECT_EQ(buffer.at(4), 5);
    }

    {
        const circular_buffer_type::capacity_type cap = 10;
        const std::vector<circular_buffer_type::value_type> values = { 1, 2, 3, 4, 5 };
        circular_buffer_type buffer(cap, values.begin(), values.end());
        EXPECT_EQ(buffer.capacity(), GO_UL(10));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), false);
        EXPECT_EQ(buffer.at(0), 1);
        EXPECT_EQ(buffer.at(1), 2);
        EXPECT_EQ(buffer.at(2), 3);
        EXPECT_EQ(buffer.at(3), 4);
        EXPECT_EQ(buffer.at(4), 5);
    }

    {
        const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };
        circular_buffer_type buffer(il);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer.at(0), 1);
        EXPECT_EQ(buffer.at(1), 2);
        EXPECT_EQ(buffer.at(2), 3);
        EXPECT_EQ(buffer.at(3), 4);
        EXPECT_EQ(buffer.at(4), 5);
    }

    {
        const circular_buffer_type::capacity_type cap = 10;
        const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };
        circular_buffer_type buffer(cap, il);
        EXPECT_EQ(buffer.capacity(), GO_UL(10));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), false);
        EXPECT_EQ(buffer.at(0), 1);
        EXPECT_EQ(buffer.at(1), 2);
        EXPECT_EQ(buffer.at(2), 3);
        EXPECT_EQ(buffer.at(3), 4);
        EXPECT_EQ(buffer.at(4), 5);
    }
}

TEST(std_circular_buffer_test_suite, test_assign_value)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    {
        const circular_buffer_type::capacity_type cap = 5;
        circular_buffer_type buffer(cap);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(0));
        EXPECT_EQ(buffer.empty(), true);
        EXPECT_EQ(buffer.full(), false);

        buffer.assign(GO_UL(3), 1);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(3));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), false);
        EXPECT_EQ(buffer.at(0), 1);
        EXPECT_EQ(buffer.at(1), 1);
        EXPECT_EQ(buffer.at(2), 1);

        buffer.assign(GO_UL(5), 2);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer.at(0), 2);
        EXPECT_EQ(buffer.at(1), 2);
        EXPECT_EQ(buffer.at(2), 2);
        EXPECT_EQ(buffer.at(3), 2);
        EXPECT_EQ(buffer.at(4), 2);

        buffer.assign(GO_UL(7), 3);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer.at(0), 3);
        EXPECT_EQ(buffer.at(1), 3);
        EXPECT_EQ(buffer.at(2), 3);
        EXPECT_EQ(buffer.at(3), 3);
        EXPECT_EQ(buffer.at(4), 3);
    }

    {
        const circular_buffer_type::capacity_type cap = 5;
        circular_buffer_type buffer(cap);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(0));
        EXPECT_EQ(buffer.empty(), true);
        EXPECT_EQ(buffer.full(), false);

        buffer.assign(GO_UL(3), GO_UL(3), 1);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(3));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), false);
        EXPECT_EQ(buffer.at(0), 1);
        EXPECT_EQ(buffer.at(1), 1);
        EXPECT_EQ(buffer.at(2), 1);

        buffer.assign(GO_UL(5), GO_UL(5), 2);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer.at(0), 2);
        EXPECT_EQ(buffer.at(1), 2);
        EXPECT_EQ(buffer.at(2), 2);
        EXPECT_EQ(buffer.at(3), 2);
        EXPECT_EQ(buffer.at(4), 2);

        buffer.assign(GO_UL(7), GO_UL(7), 3);
        EXPECT_EQ(buffer.capacity(), GO_UL(7));
        EXPECT_EQ(buffer.size(), GO_UL(7));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer.at(0), 3);
        EXPECT_EQ(buffer.at(1), 3);
        EXPECT_EQ(buffer.at(2), 3);
        EXPECT_EQ(buffer.at(3), 3);
        EXPECT_EQ(buffer.at(4), 3);
        EXPECT_EQ(buffer.at(5), 3);
        EXPECT_EQ(buffer.at(6), 3);
    }
}

TEST(std_circular_buffer_test_suite, test_iterator)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    {
        const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };
        circular_buffer_type buffer(il);

        size_t count = 0;
        circular_buffer_type::iterator it = buffer.begin();
        while (it != buffer.end())
        {
            ++count;
            EXPECT_EQ(static_cast<size_t>(*it), count);
            ++it;
        }
        EXPECT_EQ(count, GO_UL(5));
    }

    {
        const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };
        circular_buffer_type buffer(il);

        size_t count = 0;
        for (int i : buffer)
        {
            ++count;
            EXPECT_EQ(static_cast<size_t>(i), count);
        }
        EXPECT_EQ(count, GO_UL(5));
    }
}

TEST(std_circular_buffer_test_suite, test_const_iterator)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    {
        const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };
        const circular_buffer_type buffer(il);

        size_t count = 0;
        circular_buffer_type::const_iterator it = buffer.begin();
        while (it != buffer.end())
        {
            ++count;
            EXPECT_EQ(static_cast<size_t>(*it), count);
            ++it;
        }
        EXPECT_EQ(count, GO_UL(5));
    }

    {
        const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };
        const circular_buffer_type buffer(il);

        size_t count = 0;
        for (int i : buffer)
        {
            ++count;
            EXPECT_EQ(static_cast<size_t>(i), count);
        }
        EXPECT_EQ(count, GO_UL(5));
    }
}

TEST(std_circular_buffer_test_suite, test_reverse_iterator)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    {
        const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };
        circular_buffer_type buffer(il);

        size_t count = 0;
        int value = 5;
        circular_buffer_type::reverse_iterator it = buffer.rbegin();
        while (it != buffer.rend())
        {
            ++count;
            EXPECT_EQ(*it, value);
            --value;
            ++it;
        }
        EXPECT_EQ(count, GO_UL(5));
    }

#if !defined(GO_NO_CXX14_ARGUMENT_DEPENDENT_LOOKUP)
    {
        const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };
        circular_buffer_type buffer(il);

        size_t count = 0;
        int value = 5;
        for (int i : ui::reverse(buffer))
        {
            ++count;
            EXPECT_EQ(i, value);
            --value;
        }
        EXPECT_EQ(count, GO_UL(5));
    }
#endif  // #if !defined(GO_NO_CXX14_ARGUMENT_DEPENDENT_LOOKUP)
}

TEST(std_circular_buffer_test_suite, test_const_reverse_iterator)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    {
        const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };
        const circular_buffer_type buffer(il);

        size_t count = 0;
        int value = 5;
        circular_buffer_type::const_reverse_iterator it = buffer.rbegin();
        while (it != buffer.rend())
        {
            ++count;
            EXPECT_EQ(*it, value);
            --value;
            ++it;
        }
        EXPECT_EQ(count, GO_UL(5));
    }

#if !defined(GO_NO_CXX14_ARGUMENT_DEPENDENT_LOOKUP)
    {
        const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };
        const circular_buffer_type buffer(il);

        size_t count = 0;
        int value = 5;
        for (int i : ui::reverse(buffer))
        {
            ++count;
            EXPECT_EQ(i, value);
            --value;
        }
        EXPECT_EQ(count, GO_UL(5));
    }
#endif  // #if !defined(GO_NO_CXX14_ARGUMENT_DEPENDENT_LOOKUP)
}

TEST(std_circular_buffer_test_suite, test_push_back_to_capacity_pop_front_to_empty)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    const circular_buffer_type::capacity_type cap = 5;
    circular_buffer_type buffer(cap);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(0));
    EXPECT_EQ(buffer.empty(), true);
    EXPECT_EQ(buffer.full(), false);

    buffer.push_back(1);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(1));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 1);

    buffer.push_back(2);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(2));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);

    buffer.push_back(3);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);

    buffer.push_back(4);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
    EXPECT_EQ(buffer[3], 4);

    buffer.push_back(5);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
    EXPECT_EQ(buffer[3], 4);
    EXPECT_EQ(buffer[4], 5);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 2);
    EXPECT_EQ(buffer[1], 3);
    EXPECT_EQ(buffer[2], 4);
    EXPECT_EQ(buffer[3], 5);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 3);
    EXPECT_EQ(buffer[1], 4);
    EXPECT_EQ(buffer[2], 5);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(2));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 4);
    EXPECT_EQ(buffer[1], 5);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(1));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 5);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(0));
    EXPECT_EQ(buffer.empty(), true);
    EXPECT_EQ(buffer.full(), false);
}

TEST(std_circular_buffer_test_suite, test_push_back_pop_front_without_overflow)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    const circular_buffer_type::capacity_type cap = 5;
    const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4 };
    circular_buffer_type buffer(cap, il);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
    EXPECT_EQ(buffer[3], 4);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 2);
    EXPECT_EQ(buffer[1], 3);
    EXPECT_EQ(buffer[2], 4);

    buffer.push_back(5);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 2);
    EXPECT_EQ(buffer[1], 3);
    EXPECT_EQ(buffer[2], 4);
    EXPECT_EQ(buffer[3], 5);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 3);
    EXPECT_EQ(buffer[1], 4);
    EXPECT_EQ(buffer[2], 5);

    buffer.push_back(6);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 3);
    EXPECT_EQ(buffer[1], 4);
    EXPECT_EQ(buffer[2], 5);
    EXPECT_EQ(buffer[3], 6);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 4);
    EXPECT_EQ(buffer[1], 5);
    EXPECT_EQ(buffer[2], 6);

    buffer.push_back(7);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 4);
    EXPECT_EQ(buffer[1], 5);
    EXPECT_EQ(buffer[2], 6);
    EXPECT_EQ(buffer[3], 7);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 5);
    EXPECT_EQ(buffer[1], 6);
    EXPECT_EQ(buffer[2], 7);

    buffer.push_back(8);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 5);
    EXPECT_EQ(buffer[1], 6);
    EXPECT_EQ(buffer[2], 7);
    EXPECT_EQ(buffer[3], 8);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 6);
    EXPECT_EQ(buffer[1], 7);
    EXPECT_EQ(buffer[2], 8);

    buffer.push_back(9);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 6);
    EXPECT_EQ(buffer[1], 7);
    EXPECT_EQ(buffer[2], 8);
    EXPECT_EQ(buffer[3], 9);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 7);
    EXPECT_EQ(buffer[1], 8);
    EXPECT_EQ(buffer[2], 9);
}

TEST(std_circular_buffer_test_suite, test_push_back_pop_front_with_overflow)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    const circular_buffer_type::capacity_type cap = 5;
    const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };
    circular_buffer_type buffer(cap, il);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
    EXPECT_EQ(buffer[3], 4);
    EXPECT_EQ(buffer[4], 5);

    buffer.push_back(6);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer[0], 2);
    EXPECT_EQ(buffer[1], 3);
    EXPECT_EQ(buffer[2], 4);
    EXPECT_EQ(buffer[3], 5);
    EXPECT_EQ(buffer[4], 6);

    buffer.push_back(7);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer[0], 3);
    EXPECT_EQ(buffer[1], 4);
    EXPECT_EQ(buffer[2], 5);
    EXPECT_EQ(buffer[3], 6);
    EXPECT_EQ(buffer[4], 7);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 4);
    EXPECT_EQ(buffer[1], 5);
    EXPECT_EQ(buffer[2], 6);
    EXPECT_EQ(buffer[3], 7);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 5);
    EXPECT_EQ(buffer[1], 6);
    EXPECT_EQ(buffer[2], 7);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(2));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 6);
    EXPECT_EQ(buffer[1], 7);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(1));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 7);

    buffer.pop_front();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(0));
    EXPECT_EQ(buffer.empty(), true);
    EXPECT_EQ(buffer.full(), false);
}

TEST(std_circular_buffer_test_suite, test_push_front_to_capacity_pop_back_to_empty)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    const circular_buffer_type::capacity_type cap = 5;
    circular_buffer_type buffer(cap);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(0));
    EXPECT_EQ(buffer.empty(), true);
    EXPECT_EQ(buffer.full(), false);

    buffer.push_front(1);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(1));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 1);

    buffer.push_front(2);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(2));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 2);
    EXPECT_EQ(buffer[1], 1);

    buffer.push_front(3);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 3);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 1);

    buffer.push_front(4);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 4);
    EXPECT_EQ(buffer[1], 3);
    EXPECT_EQ(buffer[2], 2);
    EXPECT_EQ(buffer[3], 1);

    buffer.push_front(5);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer[0], 5);
    EXPECT_EQ(buffer[1], 4);
    EXPECT_EQ(buffer[2], 3);
    EXPECT_EQ(buffer[3], 2);
    EXPECT_EQ(buffer[4], 1);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 5);
    EXPECT_EQ(buffer[1], 4);
    EXPECT_EQ(buffer[2], 3);
    EXPECT_EQ(buffer[3], 2);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 5);
    EXPECT_EQ(buffer[1], 4);
    EXPECT_EQ(buffer[2], 3);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(2));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 5);
    EXPECT_EQ(buffer[1], 4);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(1));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 5);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(0));
    EXPECT_EQ(buffer.empty(), true);
    EXPECT_EQ(buffer.full(), false);
}

TEST(std_circular_buffer_test_suite, test_push_front_pop_back_without_overflow)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    const circular_buffer_type::capacity_type cap = 5;
    const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4 };
    circular_buffer_type buffer(cap, il);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
    EXPECT_EQ(buffer[3], 4);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);

    buffer.push_front(5);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 5);
    EXPECT_EQ(buffer[1], 1);
    EXPECT_EQ(buffer[2], 2);
    EXPECT_EQ(buffer[3], 3);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 5);
    EXPECT_EQ(buffer[1], 1);
    EXPECT_EQ(buffer[2], 2);

    buffer.push_front(6);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 6);
    EXPECT_EQ(buffer[1], 5);
    EXPECT_EQ(buffer[2], 1);
    EXPECT_EQ(buffer[3], 2);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 6);
    EXPECT_EQ(buffer[1], 5);
    EXPECT_EQ(buffer[2], 1);

    buffer.push_front(7);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 7);
    EXPECT_EQ(buffer[1], 6);
    EXPECT_EQ(buffer[2], 5);
    EXPECT_EQ(buffer[3], 1);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 7);
    EXPECT_EQ(buffer[1], 6);
    EXPECT_EQ(buffer[2], 5);

    buffer.push_front(8);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 8);
    EXPECT_EQ(buffer[1], 7);
    EXPECT_EQ(buffer[2], 6);
    EXPECT_EQ(buffer[3], 5);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 8);
    EXPECT_EQ(buffer[1], 7);
    EXPECT_EQ(buffer[2], 6);

    buffer.push_front(9);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 9);
    EXPECT_EQ(buffer[1], 8);
    EXPECT_EQ(buffer[2], 7);
    EXPECT_EQ(buffer[3], 6);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 9);
    EXPECT_EQ(buffer[1], 8);
    EXPECT_EQ(buffer[2], 7);

    buffer.push_front(10);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 10);
    EXPECT_EQ(buffer[1], 9);
    EXPECT_EQ(buffer[2], 8);
    EXPECT_EQ(buffer[3], 7);

    buffer.push_front(11);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer[0], 11);
    EXPECT_EQ(buffer[1], 10);
    EXPECT_EQ(buffer[2], 9);
    EXPECT_EQ(buffer[3], 8);
    EXPECT_EQ(buffer[4], 7);

    buffer.push_front(12);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer[0], 12);
    EXPECT_EQ(buffer[1], 11);
    EXPECT_EQ(buffer[2], 10);
    EXPECT_EQ(buffer[3], 9);
    EXPECT_EQ(buffer[4], 8);
}

TEST(std_circular_buffer_test_suite, test_push_front_pop_back_with_overflow)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    const circular_buffer_type::capacity_type cap = 5;
    const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };
    circular_buffer_type buffer(cap, il);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
    EXPECT_EQ(buffer[3], 4);
    EXPECT_EQ(buffer[4], 5);

    buffer.push_front(6);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer[0], 6);
    EXPECT_EQ(buffer[1], 1);
    EXPECT_EQ(buffer[2], 2);
    EXPECT_EQ(buffer[3], 3);
    EXPECT_EQ(buffer[4], 4);

    buffer.push_front(7);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer[0], 7);
    EXPECT_EQ(buffer[1], 6);
    EXPECT_EQ(buffer[2], 1);
    EXPECT_EQ(buffer[3], 2);
    EXPECT_EQ(buffer[4], 3);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 7);
    EXPECT_EQ(buffer[1], 6);
    EXPECT_EQ(buffer[2], 1);
    EXPECT_EQ(buffer[3], 2);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 7);
    EXPECT_EQ(buffer[1], 6);
    EXPECT_EQ(buffer[2], 1);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(2));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 7);
    EXPECT_EQ(buffer[1], 6);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(1));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer[0], 7);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(0));
    EXPECT_EQ(buffer.empty(), true);
    EXPECT_EQ(buffer.full(), false);
}

TEST(std_circular_buffer_test_suite, test_operator_at)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    const circular_buffer_type::capacity_type cap = 5;
    const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };

    {
        const circular_buffer_type buffer(cap, il);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer[0], 1);
        EXPECT_EQ(buffer[1], 2);
        EXPECT_EQ(buffer[2], 3);
        EXPECT_EQ(buffer[3], 4);
        EXPECT_EQ(buffer[4], 5);
    }

    {
        circular_buffer_type buffer(cap, il);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer[0], 1);
        EXPECT_EQ(buffer[1], 2);
        EXPECT_EQ(buffer[2], 3);
        EXPECT_EQ(buffer[3], 4);
        EXPECT_EQ(buffer[4], 5);

        buffer[0] = 6;
        buffer[1] += 5;
        ++buffer[2];
        buffer[3]++;
        buffer[4] = buffer[0];

        EXPECT_EQ(buffer[0], 6);
        EXPECT_EQ(buffer[1], 7);
        EXPECT_EQ(buffer[2], 4);
        EXPECT_EQ(buffer[3], 5);
        EXPECT_EQ(buffer[4], 6);
    }
}

TEST(std_circular_buffer_test_suite, test_at)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    const circular_buffer_type::capacity_type cap = 5;
    const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };

    {
        const circular_buffer_type buffer(cap, il);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer.at(0), 1);
        EXPECT_EQ(buffer.at(1), 2);
        EXPECT_EQ(buffer.at(2), 3);
        EXPECT_EQ(buffer.at(3), 4);
        EXPECT_EQ(buffer.at(4), 5);
    }

    {
        circular_buffer_type buffer(cap, il);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer.at(0), 1);
        EXPECT_EQ(buffer.at(1), 2);
        EXPECT_EQ(buffer.at(2), 3);
        EXPECT_EQ(buffer.at(3), 4);
        EXPECT_EQ(buffer.at(4), 5);

        buffer.at(0) = 6;
        buffer.at(1) += 5;
        ++buffer.at(2);
        buffer.at(3)++;
        buffer.at(4) = buffer.at(0);

        EXPECT_EQ(buffer.at(0), 6);
        EXPECT_EQ(buffer.at(1), 7);
        EXPECT_EQ(buffer.at(2), 4);
        EXPECT_EQ(buffer.at(3), 5);
        EXPECT_EQ(buffer.at(4), 6);
    }
}

TEST(std_circular_buffer_test_suite, test_front_back)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    const circular_buffer_type::capacity_type cap = 5;
    const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };

    {
        const circular_buffer_type buffer(cap, il);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer.front(), 1);
        EXPECT_EQ(buffer.back(), 5);
    }

    {
        circular_buffer_type buffer(cap, il);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer.front(), 1);
        EXPECT_EQ(buffer.back(), 5);

        buffer.front() = 6;
        buffer.back() += 5;
        ++buffer.at(2);

        EXPECT_EQ(buffer.front(), 6);
        EXPECT_EQ(buffer.back(), 10);
    }
}

TEST(std_circular_buffer_test_suite, test_resize)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    const circular_buffer_type::capacity_type cap = 5;
    const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };

    {
        circular_buffer_type buffer(cap, il);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer[0], 1);
        EXPECT_EQ(buffer[1], 2);
        EXPECT_EQ(buffer[2], 3);
        EXPECT_EQ(buffer[3], 4);
        EXPECT_EQ(buffer[4], 5);

        buffer.resize(5);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer[0], 1);
        EXPECT_EQ(buffer[1], 2);
        EXPECT_EQ(buffer[2], 3);
        EXPECT_EQ(buffer[3], 4);
        EXPECT_EQ(buffer[4], 5);
    }

    {
        circular_buffer_type buffer(cap, il);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer[0], 1);
        EXPECT_EQ(buffer[1], 2);
        EXPECT_EQ(buffer[2], 3);
        EXPECT_EQ(buffer[3], 4);
        EXPECT_EQ(buffer[4], 5);

        buffer.resize(0);
        EXPECT_EQ(buffer.capacity(), GO_UL(0));
        EXPECT_EQ(buffer.size(), GO_UL(0));
        EXPECT_EQ(buffer.empty(), true);
        EXPECT_EQ(buffer.full(), true);
    }

    {
        circular_buffer_type buffer;
        EXPECT_EQ(buffer.capacity(), GO_UL(0));
        EXPECT_EQ(buffer.size(), GO_UL(0));
        EXPECT_EQ(buffer.empty(), true);
        EXPECT_EQ(buffer.full(), true);

        buffer.resize(5);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(0));
        EXPECT_EQ(buffer.empty(), true);
        EXPECT_EQ(buffer.full(), false);
    }

    {
        circular_buffer_type buffer(cap, il);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer[0], 1);
        EXPECT_EQ(buffer[1], 2);
        EXPECT_EQ(buffer[2], 3);
        EXPECT_EQ(buffer[3], 4);
        EXPECT_EQ(buffer[4], 5);

        buffer.resize(3);
        EXPECT_EQ(buffer.capacity(), GO_UL(3));
        EXPECT_EQ(buffer.size(), GO_UL(3));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer[0], 3);
        EXPECT_EQ(buffer[1], 4);
        EXPECT_EQ(buffer[2], 5);
    }

    {
        circular_buffer_type buffer(cap, il);
        EXPECT_EQ(buffer.capacity(), GO_UL(5));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), true);
        EXPECT_EQ(buffer[0], 1);
        EXPECT_EQ(buffer[1], 2);
        EXPECT_EQ(buffer[2], 3);
        EXPECT_EQ(buffer[3], 4);
        EXPECT_EQ(buffer[4], 5);

        buffer.resize(7);
        EXPECT_EQ(buffer.capacity(), GO_UL(7));
        EXPECT_EQ(buffer.size(), GO_UL(5));
        EXPECT_EQ(buffer.empty(), false);
        EXPECT_EQ(buffer.full(), false);
        EXPECT_EQ(buffer[0], 1);
        EXPECT_EQ(buffer[1], 2);
        EXPECT_EQ(buffer[2], 3);
        EXPECT_EQ(buffer[3], 4);
        EXPECT_EQ(buffer[4], 5);
    }
}

TEST(std_circular_buffer_test_suite, test_swap)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    const circular_buffer_type::capacity_type cap_1 = 5;
    const std::initializer_list<circular_buffer_type::value_type> il_1 = { 1, 2, 3, 4, 5 };

    const circular_buffer_type::capacity_type cap_2 = 7;
    const std::initializer_list<circular_buffer_type::value_type> il_2 = { 6, 7, 8 };

    circular_buffer_type buffer_1(cap_1, il_1);
    EXPECT_EQ(buffer_1.capacity(), GO_UL(5));
    EXPECT_EQ(buffer_1.size(), GO_UL(5));
    EXPECT_EQ(buffer_1.empty(), false);
    EXPECT_EQ(buffer_1.full(), true);
    EXPECT_EQ(buffer_1[0], 1);
    EXPECT_EQ(buffer_1[1], 2);
    EXPECT_EQ(buffer_1[2], 3);
    EXPECT_EQ(buffer_1[3], 4);
    EXPECT_EQ(buffer_1[4], 5);

    circular_buffer_type buffer_2(cap_2, il_2);
    EXPECT_EQ(buffer_2.capacity(), GO_UL(7));
    EXPECT_EQ(buffer_2.size(), GO_UL(3));
    EXPECT_EQ(buffer_2.empty(), false);
    EXPECT_EQ(buffer_2.full(), false);
    EXPECT_EQ(buffer_2[0], 6);
    EXPECT_EQ(buffer_2[1], 7);
    EXPECT_EQ(buffer_2[2], 8);

    buffer_1.swap(buffer_2);

    EXPECT_EQ(buffer_1.capacity(), GO_UL(7));
    EXPECT_EQ(buffer_1.size(), GO_UL(3));
    EXPECT_EQ(buffer_1.empty(), false);
    EXPECT_EQ(buffer_1.full(), false);
    EXPECT_EQ(buffer_1[0], 6);
    EXPECT_EQ(buffer_1[1], 7);
    EXPECT_EQ(buffer_1[2], 8);

    EXPECT_EQ(buffer_2.capacity(), GO_UL(5));
    EXPECT_EQ(buffer_2.size(), GO_UL(5));
    EXPECT_EQ(buffer_2.empty(), false);
    EXPECT_EQ(buffer_2.full(), true);
    EXPECT_EQ(buffer_2[0], 1);
    EXPECT_EQ(buffer_2[1], 2);
    EXPECT_EQ(buffer_2[2], 3);
    EXPECT_EQ(buffer_2[3], 4);
    EXPECT_EQ(buffer_2[4], 5);
}

TEST(std_circular_buffer_test_suite, test_insert)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3 };

    circular_buffer_type buffer(5, il);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer.at(0), 1);
    EXPECT_EQ(buffer.at(1), 2);
    EXPECT_EQ(buffer.at(2), 3);

    circular_buffer_type::iterator ret_it = buffer.insert(buffer.end(), GO_UL(4));
    EXPECT_EQ(*ret_it, 4);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer.at(0), 1);
    EXPECT_EQ(buffer.at(1), 2);
    EXPECT_EQ(buffer.at(2), 3);
    EXPECT_EQ(buffer.at(3), 4);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer.at(0), 1);
    EXPECT_EQ(buffer.at(1), 2);
    EXPECT_EQ(buffer.at(2), 3);

    ret_it = buffer.insert(buffer.begin(), GO_UL(5));
    EXPECT_EQ(*ret_it, 5);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer.at(0), 5);
    EXPECT_EQ(buffer.at(1), 1);
    EXPECT_EQ(buffer.at(2), 2);
    EXPECT_EQ(buffer.at(3), 3);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer.at(0), 5);
    EXPECT_EQ(buffer.at(1), 1);
    EXPECT_EQ(buffer.at(2), 2);

    circular_buffer_type::iterator it = buffer.begin()++;
    ret_it = buffer.insert(it, 6);
    EXPECT_EQ(*ret_it, 6);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer.at(0), 5);
    EXPECT_EQ(buffer.at(1), 6);
    EXPECT_EQ(buffer.at(2), 1);
    EXPECT_EQ(buffer.at(3), 2);

    ret_it = buffer.insert(buffer.end(), 7);
    EXPECT_EQ(*ret_it, 7);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer.at(0), 5);
    EXPECT_EQ(buffer.at(1), 6);
    EXPECT_EQ(buffer.at(2), 1);
    EXPECT_EQ(buffer.at(3), 2);
    EXPECT_EQ(buffer.at(4), 7);

    ret_it = buffer.insert(buffer.begin(), 8);
    EXPECT_EQ(*ret_it, 8);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer.at(0), 8);
    EXPECT_EQ(buffer.at(1), 6);
    EXPECT_EQ(buffer.at(2), 1);
    EXPECT_EQ(buffer.at(3), 2);
    EXPECT_EQ(buffer.at(4), 7);

    it = buffer.begin()++;
    ret_it = buffer.insert(it, 9);
    EXPECT_EQ(*ret_it, 9);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer.at(0), 9);
    EXPECT_EQ(buffer.at(1), 6);
    EXPECT_EQ(buffer.at(2), 1);
    EXPECT_EQ(buffer.at(3), 2);
    EXPECT_EQ(buffer.at(4), 7);

    it = (buffer.begin()++)++;
    ret_it = buffer.insert(it, 10);
    EXPECT_EQ(*ret_it, 10);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer.at(0), 6);
    EXPECT_EQ(buffer.at(1), 10);
    EXPECT_EQ(buffer.at(2), 1);
    EXPECT_EQ(buffer.at(3), 2);
    EXPECT_EQ(buffer.at(4), 7);

    const circular_buffer_type::value_type val = 11;
    ret_it = buffer.insert(buffer.end(), val);
    EXPECT_EQ(*ret_it, 11);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer.at(0), 10);
    EXPECT_EQ(buffer.at(1), 1);
    EXPECT_EQ(buffer.at(2), 2);
    EXPECT_EQ(buffer.at(3), 7);
    EXPECT_EQ(buffer.at(4), 11);

    it = (buffer.end()--)--;
    ret_it = buffer.insert(it, 12);
    EXPECT_EQ(*ret_it, 12);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer.at(0), 1);
    EXPECT_EQ(buffer.at(1), 2);
    EXPECT_EQ(buffer.at(2), 12);
    EXPECT_EQ(buffer.at(3), 7);
    EXPECT_EQ(buffer.at(4), 11);

    ret_it = buffer.insert(ret_it);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer.at(0), 2);
    EXPECT_EQ(buffer.at(2), 12);
    EXPECT_EQ(buffer.at(3), 7);
    EXPECT_EQ(buffer.at(4), 11);
}

TEST(std_circular_buffer_test_suite, test_erase)
{
    using circular_buffer_type = uc::circular_buffer<int>;

    const std::initializer_list<circular_buffer_type::value_type> il = { 1, 2, 3, 4, 5 };

    circular_buffer_type buffer(5, il);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer.at(0), 1);
    EXPECT_EQ(buffer.at(1), 2);
    EXPECT_EQ(buffer.at(2), 3);
    EXPECT_EQ(buffer.at(3), 4);
    EXPECT_EQ(buffer.at(4), 5);

    circular_buffer_type::iterator it = buffer.end();
    circular_buffer_type::iterator ret_it = buffer.erase(it);
    EXPECT_EQ(buffer.end(), ret_it);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer.at(0), 1);
    EXPECT_EQ(buffer.at(1), 2);
    EXPECT_EQ(buffer.at(2), 3);
    EXPECT_EQ(buffer.at(3), 4);
    EXPECT_EQ(buffer.at(4), 5);

    it = buffer.begin();
    ret_it = buffer.erase(it);
    EXPECT_EQ(buffer.begin(), ret_it);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(4));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer.at(0), 2);
    EXPECT_EQ(buffer.at(1), 3);
    EXPECT_EQ(buffer.at(2), 4);
    EXPECT_EQ(buffer.at(3), 5);

    it = buffer.end()--;
    ret_it = buffer.erase(it);
    EXPECT_EQ(buffer.end(), ret_it);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(3));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), false);
    EXPECT_EQ(buffer.at(0), 2);
    EXPECT_EQ(buffer.at(1), 3);
    EXPECT_EQ(buffer.at(2), 4);

    buffer.push_front(1);
    buffer.push_back(5);
    EXPECT_EQ(buffer.capacity(), GO_UL(5));
    EXPECT_EQ(buffer.size(), GO_UL(5));
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.full(), true);
    EXPECT_EQ(buffer.at(0), 1);
    EXPECT_EQ(buffer.at(1), 2);
    EXPECT_EQ(buffer.at(2), 3);
    EXPECT_EQ(buffer.at(3), 4);
    EXPECT_EQ(buffer.at(4), 5);

    circular_buffer_type::size_type count = 0;
    it = buffer.begin();
    while (it != buffer.end())
    {
        ++count;
        EXPECT_EQ(*it, static_cast<int>(count));
        it = buffer.erase(it);
    }
    EXPECT_EQ(count, GO_UL(5));
}

}

#endif  // Required C++11 feature is not supported by this compiler
