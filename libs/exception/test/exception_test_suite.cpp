//
//  exception_test_suite.cpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_exception_test_suite, cpp11_not_supported) {}
#else

#include <string>
#include <go/exception.hpp>

namespace e = go::exception;

namespace
{

class derived_exception
    : public e::exception
{
public:
    typedef exception this_type;

public:
    virtual ~derived_exception() GO_NOEXCEPT_OR_NOTHROW GO_DEFAULT_DESTRUCTOR

    explicit derived_exception(const std::string& message)
        : e::exception(message)
    {
    }
};

class other_exception
{
public:
    typedef other_exception this_type;

public:
    virtual ~other_exception() GO_NOEXCEPT_OR_NOTHROW GO_DEFAULT_DESTRUCTOR

    other_exception()
    {
    }
};

TEST(std_exception_test_suite, test_catch_go_exception)
{
    const char* expected_exception_what = "AN ERROR MESSAGE";
    const std::string expected_exception_message(expected_exception_what);
    {
        try
        {
            throw e::exception(expected_exception_what);
        }
        catch(const e::exception& e)
        {
            EXPECT_EQ(expected_exception_message, e.message());
            EXPECT_STREQ(expected_exception_what, e.what());
        }
        catch(...)
        {
            EXPECT_TRUE(false);
        }
    }
    {
        try
        {
            throw e::exception(expected_exception_message);
        }
        catch(const e::exception& e)
        {
            EXPECT_EQ(expected_exception_message, e.message());
            EXPECT_STREQ(expected_exception_what, e.what());
        }
        catch(...)
        {
            EXPECT_TRUE(false);
        }
    }
}

TEST(std_exception_test_suite, test_catch_go_exception_as_std_exception)
{
    const char* expected_exception_what = "AN ERROR MESSAGE";
    const std::string expected_exception_message(expected_exception_what);
    {
        try
        {
            throw e::exception(expected_exception_what);
        }
        catch(const std::exception& e)
        {
            EXPECT_STREQ(expected_exception_what, e.what());
        }
        catch(...)
        {
            EXPECT_TRUE(false);
        }
    }
    {
        try
        {
            throw e::exception(expected_exception_message);
        }
        catch(const std::exception& e)
        {
            EXPECT_STREQ(expected_exception_what, e.what());
        }
        catch(...)
        {
            EXPECT_TRUE(false);
        }
    }
}

TEST(std_exception_test_suite, test_catch_derived_exception)
{
    const char* expected_exception_what = "AN ERROR MESSAGE";
    const std::string expected_exception_message(expected_exception_what);
    {
        try
        {
            throw derived_exception(expected_exception_what);
        }
        catch(const derived_exception& e)
        {
            EXPECT_EQ(expected_exception_message, e.message());
            EXPECT_STREQ(expected_exception_what, e.what());
        }
        catch(...)
        {
            EXPECT_TRUE(false);
        }
    }
    {
        try
        {
            throw derived_exception(expected_exception_message);
        }
        catch(const derived_exception& e)
        {
            EXPECT_EQ(expected_exception_message, e.message());
            EXPECT_STREQ(expected_exception_what, e.what());
        }
        catch(...)
        {
            EXPECT_TRUE(false);
        }
    }
}

TEST(std_exception_test_suite, test_catch_derived_exception_as_go_exception)
{
    const char* expected_exception_what = "AN ERROR MESSAGE";
    const std::string expected_exception_message(expected_exception_what);
    {
        try
        {
            throw derived_exception(expected_exception_what);
        }
        catch(const e::exception& e)
        {
            EXPECT_EQ(expected_exception_message, e.message());
            EXPECT_STREQ(expected_exception_what, e.what());
        }
        catch(...)
        {
            EXPECT_TRUE(false);
        }
    }
    {
        try
        {
            throw derived_exception(expected_exception_message);
        }
        catch(const e::exception& e)
        {
            EXPECT_EQ(expected_exception_message, e.message());
            EXPECT_STREQ(expected_exception_what, e.what());
        }
        catch(...)
        {
            EXPECT_TRUE(false);
        }
    }
}

TEST(std_exception_test_suite, test_catch_derived_exception_as_std_exception)
{
    const char* expected_exception_what = "AN ERROR MESSAGE";
    const std::string expected_exception_message(expected_exception_what);
    {
        try
        {
            throw derived_exception(expected_exception_what);
        }
        catch(const std::exception& e)
        {
            EXPECT_STREQ(expected_exception_what, e.what());
        }
        catch(...)
        {
            EXPECT_TRUE(false);
        }
    }
    {
        try
        {
            throw derived_exception(expected_exception_message);
        }
        catch(const std::exception& e)
        {
            EXPECT_STREQ(expected_exception_what, e.what());
        }
        catch(...)
        {
            EXPECT_TRUE(false);
        }
    }
}

TEST(std_exception_test_suite, test_catch_other_exception)
{
    try
    {
        throw other_exception();
    }
    catch(const derived_exception&)
    {
        EXPECT_TRUE(false);
    }
    catch(const e::exception&)
    {
        EXPECT_TRUE(false);
    }
    catch(const std::exception&)
    {
        EXPECT_TRUE(false);
    }
    catch(const other_exception&)
    {
        EXPECT_TRUE(true);
    }
    catch(...)
    {
        EXPECT_TRUE(false);
    }
}

}
 
#endif  // Required C++11 feature is not supported by this compiler
