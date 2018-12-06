#ifndef GO_BOOST_UTILITY_MIN_MAX_HPP_INCLUDED
#define GO_BOOST_UTILITY_MIN_MAX_HPP_INCLUDED

//
//  min_max.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#include <algorithm>

namespace go_boost
{
namespace utility
{

template <typename T>
GO_BOOST_CONSTEXPR const T& max_of(const T& t1, const T& t2)
{
    using namespace std;  // MSVC++ defines a macro max. It does not work well with std::max.
    return max(t1, t2);
}

template <typename T>
GO_BOOST_CONSTEXPR const T& min_of(const T& t1, const T& t2)
{
    using namespace std;  // MSVC++ defines a macro min. It does not work well with std::min.
    return min(t1, t2);
}

}
}

#endif  // #ifndef GO_BOOST_UTILITY_MIN_MAX_HPP_INCLUDED