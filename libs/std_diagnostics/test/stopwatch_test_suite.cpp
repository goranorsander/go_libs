//
//  stopwatch_test_suite.cpp
//
//  Copyright 2019-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_diagnostics_test_suite, cpp11_not_supported) {}
#else

#include <thread>
#include <go/diagnostics.hpp>
#include <go/namespace_alias.hpp>

namespace
{

TEST(std_stopwatch_test_suite, test_create_stopwatch)
{
    const db::stopwatch::duration_type zero_duration = db::stopwatch::duration_type::zero();

    db::stopwatch sw;
    EXPECT_FALSE(sw.started());
    EXPECT_EQ(0u, sw.count());
    EXPECT_EQ(zero_duration, sw.last_duration());
    EXPECT_EQ(zero_duration, sw.total_duration());
    EXPECT_EQ(zero_duration, sw.average_duration());
}

TEST(std_stopwatch_test_suite, test_stopwatch_start_stop)
{
    const db::stopwatch::duration_type zero_duration = db::stopwatch::duration_type::zero();

    db::stopwatch sw;
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
    const db::stopwatch::duration_type zero_duration = db::stopwatch::duration_type::zero();

    db::stopwatch sw;
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
    const db::stopwatch::duration_type zero_duration = db::stopwatch::duration_type::zero();

    db::stopwatch sw;
    EXPECT_FALSE(sw.started());

    {
        db::stopwatch_guard g(sw);
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
    const db::stopwatch::duration_type zero_duration = db::stopwatch::duration_type::zero();

    db::stopwatch sw;
    EXPECT_FALSE(sw.started());

    db::stopwatch::duration_type total_duration = db::stopwatch::duration_type::zero();
    db::stopwatch::count_type i = 0;
    while (i < 5)
    {
        {
            db::stopwatch_guard g(sw);
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
