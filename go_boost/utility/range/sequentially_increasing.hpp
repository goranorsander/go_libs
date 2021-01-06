#ifndef GO_BOOST_UTILITY_RANGE_SEQUENTIALLY_INCREASING_HPP_INCLUDED
#define GO_BOOST_UTILITY_RANGE_SEQUENTIALLY_INCREASING_HPP_INCLUDED

//
//  sequentially_increasing.hpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

namespace go_boost
{
namespace utility
{
namespace range
{

template <typename T>
class sequentially_increasing
{
public:
    typedef T value_type;
    typedef sequentially_increasing<T> this_type;

    ~sequentially_increasing() GO_BOOST_DEFAULT_DESTRUCTOR
    sequentially_increasing(const value_type& start_at, const value_type& increment)
        : _increment(increment)
        , _at(start_at)
    {
    }

    value_type operator()()
    {
        const value_type at = _at;
        _at += _increment;
        return at;
    }

private:
    const value_type _increment;
    value_type _at;
};

}
}
}

#endif  // #ifndef GO_BOOST_UTILITY_RANGE_SEQUENTIALLY_INCREASING_HPP_INCLUDED
