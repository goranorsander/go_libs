#ifndef GO_UTILITY_RANGE_SEQUENTIALLY_INCREASING_HPP_INCLUDED
#define GO_UTILITY_RANGE_SEQUENTIALLY_INCREASING_HPP_INCLUDED

//
//  sequentially_increasing.hpp
//
//  Copyright 2018-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11_RANGE_FOR_LOOP)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

namespace go
{
namespace utility
{
namespace range
{

template <typename T>
class sequentially_increasing
{
public:
    using value_type = T;
    using this_type = sequentially_increasing<T>;

    ~sequentially_increasing() GO_DEFAULT_DESTRUCTOR
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

#endif  // #if defined(GO_NO_CXX11_RANGE_FOR_LOOP)

#endif  // #ifndef GO_UTILITY_RANGE_SEQUENTIALLY_INCREASING_HPP_INCLUDED
