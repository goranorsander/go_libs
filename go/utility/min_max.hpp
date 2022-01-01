#ifndef GO_UTILITY_MIN_MAX_HPP_INCLUDED
#define GO_UTILITY_MIN_MAX_HPP_INCLUDED

//
//  min_max.hpp
//
//  Copyright 2018-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <algorithm>

namespace go
{
namespace utility
{

template <typename T>
GO_CONSTEXPR const T& max_of(const T& lhs, const T& rhs)
{
    using namespace std;  // MSVC++ defines a macro max. It does not work well with std::max.
    return max(lhs, rhs);
}

template <typename T>
GO_CONSTEXPR const T& min_of(const T& lhs, const T& rhs)
{
    using namespace std;  // MSVC++ defines a macro min. It does not work well with std::min.
    return min(lhs, rhs);
}

}
}

#endif  // #ifndef GO_UTILITY_MIN_MAX_HPP_INCLUDED
