#ifndef GO_BOOST_DIAGNOSTICS_BENCHMARK_STOPWATCH_GUARD_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_BENCHMARK_STOPWATCH_GUARD_HPP_INCLUDED

//
//  stopwatch_guard.hpp
//
//  Copyright 2019-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/bind.hpp>
#include <go_boost/utility/scope_guard.hpp>

namespace go_boost
{
namespace diagnostics
{
namespace benchmark
{

template<class S>
class basic_stopwatch_guard
    : public go_boost::utility::scope_guard
{
public:
    typedef S stopwatch_type;
    typedef basic_stopwatch_guard<S> this_type;
    typedef go_boost::utility::scope_guard base_type;

public:
    virtual ~basic_stopwatch_guard() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit basic_stopwatch_guard(stopwatch_type& stopwatch)
        : scope_guard(NULL)
        , _stopwatch(stopwatch)
    {
        set_on_scope_exit_function(on_scope_exit_function_type(boost::bind(&this_type::on_destroy, this)));
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

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_BENCHMARK_STOPWATCH_GUARD_HPP_INCLUDED
