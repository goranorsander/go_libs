//
//  scope_guard_new_test_suite.cpp
//
//  Copyright 2018-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_scope_guard_new_test_suite, cpp11_not_supported) {}
#else

#include <go/namespace_alias.hpp>
#include <go/utility/scope_guard_new.hpp>

namespace
{

class foo
{
public:
    static void* operator new(std::size_t sz)
    {
        ++_new_count;
        return ::operator new(sz);
    }

    static void operator delete(void* ptr)
    {
        ++_delete_count;
        ::operator delete(ptr);
    }

    static std::size_t calls_to_new()
    {
        return _new_count;
    }

    static std::size_t calls_to_delete()
    {
        return _delete_count;
    }

private:
    static std::size_t _new_count;
    static std::size_t _delete_count;
};

std::size_t foo::_new_count = 0;
std::size_t foo::_delete_count = 0;

TEST(std_scope_guard_new_test_suite, test_scope_guard_new)
{
    EXPECT_EQ(0u, foo::calls_to_new());
    EXPECT_EQ(0u, foo::calls_to_delete());
    {
        const u::scope_guard_new<foo> guard1(new foo);
        EXPECT_EQ(1u, foo::calls_to_new());
        EXPECT_EQ(0u, foo::calls_to_delete());
        {
            const u::scope_guard_new<foo> guard2(new foo);
            EXPECT_EQ(2u, foo::calls_to_new());
            EXPECT_EQ(0u, foo::calls_to_delete());
        }
        EXPECT_EQ(2u, foo::calls_to_new());
        EXPECT_EQ(1u, foo::calls_to_delete());
    }
    EXPECT_EQ(2u, foo::calls_to_new());
    EXPECT_EQ(2u, foo::calls_to_delete());
}

}

#endif  // Required C++11 feature is not supported by this compiler
