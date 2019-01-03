//
//  exception_test_suite.cpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go_boost/config.hpp>

#include <string>
#include <go_boost/exception.hpp>

namespace e = go_boost::exception;

namespace
{

class derived_exception
    : public e::exception
{
public:
    typedef exception this_type;

public:
    virtual ~derived_exception() BOOST_NOEXCEPT_OR_NOTHROW GO_BOOST_DEFAULT_DESTRUCTOR

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
    virtual ~other_exception() BOOST_NOEXCEPT_OR_NOTHROW GO_BOOST_DEFAULT_DESTRUCTOR

    other_exception()
    {
    }
};

TEST(boost_exception_test_suite, test_catch_go_boost_exception)
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

TEST(boost_exception_test_suite, test_catch_go_boost_exception_as_boost_exception)
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

TEST(boost_exception_test_suite, test_catch_derived_exception)
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

TEST(boost_exception_test_suite, test_catch_derived_exception_as_go_boost_exception)
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

TEST(boost_exception_test_suite, test_catch_derived_exception_as_boost_exception)
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

TEST(boost_exception_test_suite, test_catch_other_exception)
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
