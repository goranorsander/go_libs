#ifndef GO_DIAGNOSTICS_BENCHMARK_STOPWATCH_HPP_INCLUDED
#define GO_DIAGNOSTICS_BENCHMARK_STOPWATCH_HPP_INCLUDED

//
//  stopwatch.hpp
//
//  Copyright 2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <chrono>
#include <go/diagnostics/benchmark/exception.hpp>
#include <go/diagnostics/benchmark/stopwatch_guard.hpp>

namespace go
{
namespace diagnostics
{
namespace benchmark
{

template<class C, class D> class basic_stopwatch;
typedef basic_stopwatch<std::chrono::high_resolution_clock, std::chrono::microseconds> stopwatch;

typedef basic_stopwatch_guard<stopwatch> stopwatch_guard;

template<class C, class D>
class basic_stopwatch
{
public:
    using clock_type = C;
    using duration_type = D;
    using this_type = basic_stopwatch<C, D>;
    using time_point_type = std::chrono::time_point<C>;
    using count_type = std::size_t;

public:
    virtual ~basic_stopwatch() = default;

    basic_stopwatch()
        : _started(false)
        , _start_time()
        , _last_duration(duration_type::zero())
        , _total_duration(duration_type::zero())
        , _count(0)
    {
    }

    basic_stopwatch(const basic_stopwatch& other) = default;
    basic_stopwatch(basic_stopwatch&& other) = default;

    this_type& operator=(const this_type&) = default;
    this_type& operator=(this_type&&) = default;

    void start()
    {
        if (this->_started)
        {
            throw exception("Stopwatch already started");
        }
        this->_started = true;
        this->_start_time = clock_type::now();
    }

    void stop()
    {
        if (!this->_started)
        {
            throw exception("Stopwatch not started");
        }
        const time_point_type stop_time = clock_type::now();
        this->_last_duration = std::chrono::duration_cast<duration_type>(stop_time - this->_start_time);
        this->_total_duration += this->_last_duration;
        ++this->_count;
        this->_started = false;
    }

    void reset() noexcept
    {
        this->_started = false;
        this->_start_time = time_point_type();
        this->_last_duration = duration_type::zero();
        this->_total_duration = duration_type::zero();
        this->_count = 0;
    }

    constexpr bool started() const noexcept
    {
        return this->_started;
    }

    constexpr duration_type last_duration() const noexcept
    {
        return this->_last_duration;
    }

    constexpr duration_type total_duration() const noexcept
    {
        return this->_total_duration;
    }

    constexpr duration_type average_duration() const noexcept
    {
        if (this->_count > 0)
        {
            return duration_type(this->_total_duration.count() / this->_count);
        }
        return duration_type::zero();
    }

    constexpr count_type count() const noexcept
    {
        return this->_count;
    }

private:
    bool _started;
    time_point_type _start_time;
    duration_type _last_duration;
    duration_type _total_duration;
    count_type _count;
};

} // namespace benchmark
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_BENCHMARK_STOPWATCH_HPP_INCLUDED
