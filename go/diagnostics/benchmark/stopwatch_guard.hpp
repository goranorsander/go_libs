#ifndef GO_DIAGNOSTICS_BENCHMARK_STOPWATCH_GUARD_HPP_INCLUDED
#define GO_DIAGNOSTICS_BENCHMARK_STOPWATCH_GUARD_HPP_INCLUDED

//
//  stopwatch_guard.hpp
//
//  Copyright 2019-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/utility/scope_guard.hpp>

namespace go
{
namespace diagnostics
{
namespace benchmark
{

template<class S>
class basic_stopwatch_guard
    : public go::utility::scope_guard
{
public:
#if !defined(GO_NO_CXX11_TYPE_ALIASES)

    using stopwatch_type = S;
    using this_type = basic_stopwatch_guard<S>;
    using base_type = go::utility::scope_guard;

#else

    typedef S stopwatch_type;
    typedef basic_stopwatch_guard<S> this_type;
    typedef go::utility::scope_guard base_type;

#endif  // #if !defined(GO_NO_CXX11_TYPE_ALIASES)

public:
    virtual ~basic_stopwatch_guard() GO_DEFAULT_DESTRUCTOR

    explicit basic_stopwatch_guard(stopwatch_type& stopwatch)
        : scope_guard(GO_NULLPTR)
        , _stopwatch(stopwatch)
    {
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
        set_on_scope_exit_function(on_scope_exit_function_type(std::tr1::bind(&this_type::on_destroy, this)));
#else
        set_on_scope_exit_function(on_scope_exit_function_type(std::bind(&this_type::on_destroy, this)));
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1600)
        if (!this->_stopwatch.started())
        {
            this->_stopwatch.start();
        }
    }

private:
    void on_destroy()
    {
        if(this->_stopwatch.started())
        {
            this->_stopwatch.stop();
        }
    }

private:
    stopwatch_type& _stopwatch;
};

}
}
}

#endif  // #ifndef GO_DIAGNOSTICS_BENCHMARK_STOPWATCH_GUARD_HPP_INCLUDED
