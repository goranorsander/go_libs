//
//  stopwatch_test_suite.cpp
//
//  Copyright 2019 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <gtest/gtest.h>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_diagnostics_test_suite, cpp11_not_supported) {}
#else

#include <thread>
#include <go/diagnostics.hpp>

namespace b = go::diagnostics::benchmark;

namespace
{

TEST(std_stopwatch_test_suite, test_create_stopwatch)
{
    const b::stopwatch::duration_type zero_duration = b::stopwatch::duration_type::zero();

    b::stopwatch sw;
    EXPECT_FALSE(sw.started());
    EXPECT_EQ(0u, sw.count());
    EXPECT_EQ(zero_duration, sw.last_duration());
    EXPECT_EQ(zero_duration, sw.total_duration());
    EXPECT_EQ(zero_duration, sw.average_duration());
}

TEST(std_stopwatch_test_suite, test_stopwatch_start_stop)
{
    const b::stopwatch::duration_type zero_duration = b::stopwatch::duration_type::zero();

    b::stopwatch sw;
    EXPECT_FALSE(sw.started());

    sw.start();
    EXPECT_TRUE(sw.started());
    EXPECT_EQ(0u, sw.count());
    EXPECT_EQ(zero_duration, sw.last_duration());
    EXPECT_EQ(zero_duration, sw.total_duration());
    EXPECT_EQ(zero_duration, sw.average_duration());

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    sw.stop();
    EXPECT_FALSE(sw.started());
    EXPECT_EQ(1u, sw.count());
    EXPECT_NE(zero_duration, sw.last_duration());
    EXPECT_NE(zero_duration, sw.total_duration());
    EXPECT_NE(zero_duration, sw.average_duration());
}

TEST(std_stopwatch_test_suite, test_stopwatch_reset)
{
    const b::stopwatch::duration_type zero_duration = b::stopwatch::duration_type::zero();

    b::stopwatch sw;
    EXPECT_FALSE(sw.started());

    sw.start();
    EXPECT_TRUE(sw.started());
    EXPECT_EQ(0u, sw.count());
    EXPECT_EQ(zero_duration, sw.last_duration());
    EXPECT_EQ(zero_duration, sw.total_duration());
    EXPECT_EQ(zero_duration, sw.average_duration());

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    sw.stop();
    EXPECT_FALSE(sw.started());
    EXPECT_EQ(1u, sw.count());
    EXPECT_NE(zero_duration, sw.last_duration());
    EXPECT_NE(zero_duration, sw.total_duration());
    EXPECT_NE(zero_duration, sw.average_duration());

    sw.reset();
    EXPECT_FALSE(sw.started());
    EXPECT_EQ(0u, sw.count());
    EXPECT_EQ(zero_duration, sw.last_duration());
    EXPECT_EQ(zero_duration, sw.total_duration());
    EXPECT_EQ(zero_duration, sw.average_duration());
}

TEST(std_stopwatch_test_suite, test_stopwatch_guard)
{
    const b::stopwatch::duration_type zero_duration = b::stopwatch::duration_type::zero();

    b::stopwatch sw;
    EXPECT_FALSE(sw.started());

    {
        b::stopwatch_guard g(sw);
        EXPECT_TRUE(sw.started());
        EXPECT_EQ(0u, sw.count());
        EXPECT_EQ(zero_duration, sw.last_duration());
        EXPECT_EQ(zero_duration, sw.total_duration());
        EXPECT_EQ(zero_duration, sw.average_duration());

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    EXPECT_FALSE(sw.started());
    EXPECT_EQ(1u, sw.count());
    EXPECT_NE(zero_duration, sw.last_duration());
    EXPECT_NE(zero_duration, sw.total_duration());
    EXPECT_NE(zero_duration, sw.average_duration());
}

TEST(std_stopwatch_test_suite, test_stopwatch_start_stop_five_times)
{
    const b::stopwatch::duration_type zero_duration = b::stopwatch::duration_type::zero();

    b::stopwatch sw;
    EXPECT_FALSE(sw.started());

    b::stopwatch::duration_type total_duration = b::stopwatch::duration_type::zero();
    b::stopwatch::count_type i = 0;
    while (i < 5)
    {
        {
            b::stopwatch_guard g(sw);
            EXPECT_TRUE(sw.started());
            EXPECT_EQ(i, sw.count());

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        ++i;

        EXPECT_FALSE(sw.started());
        EXPECT_EQ(i, sw.count());
        EXPECT_TRUE(total_duration < sw.total_duration());

        total_duration = sw.total_duration();
    }

    EXPECT_FALSE(sw.started());
    EXPECT_EQ(5u, sw.count());
    EXPECT_NE(zero_duration, sw.last_duration());
    EXPECT_NE(zero_duration, sw.total_duration());
    EXPECT_NE(zero_duration, sw.average_duration());
}

}
 
#endif  // Required C++11 feature is not supported by this compiler
