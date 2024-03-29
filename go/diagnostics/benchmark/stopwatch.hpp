#ifndef GO_DIAGNOSTICS_BENCHMARK_STOPWATCH_HPP_INCLUDED
#define GO_DIAGNOSTICS_BENCHMARK_STOPWATCH_HPP_INCLUDED

//
//  stopwatch.hpp
//
//  Copyright 2019-2022 G�ran Orsander
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
#if defined(GO_NO_CXX11_TYPE_ALIASES)
typedef basic_stopwatch<std::chrono::high_resolution_clock, std::chrono::microseconds> stopwatch;
#else
using stopwatch = basic_stopwatch<std::chrono::high_resolution_clock, std::chrono::microseconds>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)

GO_USING(stopwatch_guard, basic_stopwatch_guard<stopwatch>);

template<class C, class D>
class basic_stopwatch
{
public:
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef basic_stopwatch<C, D> this_type;
#else
    using this_type = basic_stopwatch<C, D>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)
    GO_USING(clock_type, C);
    GO_USING(duration_type, D);
    GO_USING(time_point_type, std::chrono::time_point<C>);
    GO_USING(count_type, std::size_t);


public:
    virtual ~basic_stopwatch() GO_DEFAULT_DESTRUCTOR

    basic_stopwatch()
        : _started(false)
        , _start_time()
        , _last_duration(duration_type::zero())
        , _total_duration(duration_type::zero())
        , _count(0)
    {
    }

#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    basic_stopwatch(const basic_stopwatch& other) = default;

#else

    basic_stopwatch(const basic_stopwatch& other)
        : _started(other._started)
        , _start_time(other._start_time)
        , _last_duration(other._last_duration)
        , _total_duration(other._total_duration)
        , _count(other._count)
    {
    }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)
#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

    basic_stopwatch(basic_stopwatch&& other) = default;

#else

    basic_stopwatch(basic_stopwatch&& other)
        : _started(other._started)
        , _start_time(other._start_time)
        , _last_duration(other._last_duration)
        , _total_duration(other._total_duration)
        , _count(other._count)
    {
    }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)
#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

#if !defined(GO_NO_CXX11_DEFAULTED_COPY_ASSIGN_OPERATOR)

    this_type& operator=(const this_type&) noexcept = default;

#else

    this_type& operator=(const this_type& other) GO_NOEXCEPT_OR_NOTHROW
    {
        if (this != &other)
        {
            _started = other._started;
            _start_time = other._start_time;
            _last_duration = other._last_duration;
            _total_duration = other._total_duration;
            _count = other._count;
        }
        return *this;
    }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)
#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

    this_type& operator=(this_type&&) noexcept = default;

#else

    this_type& operator=(this_type&&) GO_NOEXCEPT_OR_NOTHROW
    {
        if (this != &other)
        {
            _started = std::move(other._started);
            _start_time = std::move(other._start_time);
            _last_duration = std::move(other._last_duration);
            _total_duration = std::move(other._total_duration);
            _count = std::move(other._count);
        }
        return *this;
    }

#endif  // #if !(defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) && defined(GO_COMP_MSVC_VC120))
#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

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

    void reset() GO_NOEXCEPT_OR_NOTHROW
    {
        this->_started = false;
        this->_start_time = time_point_type();
        this->_last_duration = duration_type::zero();
        this->_total_duration = duration_type::zero();
        this->_count = 0;
    }

    GO_CONSTEXPR bool started() const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_started;
    }

    GO_CONSTEXPR duration_type last_duration() const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_last_duration;
    }

    GO_CONSTEXPR duration_type total_duration() const GO_NOEXCEPT_OR_NOTHROW
    {
        return this->_total_duration;
    }

    duration_type average_duration() const GO_NOEXCEPT_OR_NOTHROW
    {
        if (this->_count > 0)
        {
            return duration_type(this->_total_duration.count() / this->_count);
        }
        return duration_type::zero();
    }

    GO_CONSTEXPR count_type count() const GO_NOEXCEPT_OR_NOTHROW
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
