#ifndef GO_BOOST_UTILITY_EXCHANGE_HPP_INCLUDED
#define GO_BOOST_UTILITY_EXCHANGE_HPP_INCLUDED

//
//  exchange.hpp
//
//  Copyright 2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#include <utility>

namespace go_boost
{
namespace utility
{

#if !defined(GO_BOOST_NO_CXX11_R_VALUE_REFERENCES)
#if !defined(GO_BOOST_NO_CXX14_STD_EXCHANGE)
#if !defined(GO_BOOST_NO_CXX2A_CONSTEXPR_FOR_ALGORITHM_AND_UTILITY)

    template<class T, class U = T>
    T exchange(T& obj, U&& new_value)
    {
        return std::exchange<T, U>(obj, new_value);
    }

#else

    template<class T, class U = T>
    constexpr T exchange(T& obj, U&& new_value)
    {
        return std::exchange<T, U>(obj, new_value);
    }

#endif  // #if !defined(GO_BOOST_NO_CXX2A_CONSTEXPR_FOR_ALGORITHM_AND_UTILITY)
#else

template<class T, class U = T>
T exchange(T& obj, U&& new_value)
{
    const T old_value = std::move(obj);
    obj = std::forward<U>(new_value);
    return old_value;
}

#endif  // #if !defined(GO_BOOST_NO_CXX14_STD_EXCHANGE)
#else

template<class T, class U = T>
T exchange(T& obj, const U& new_value)
{
    const T old_value = obj;
    obj = new_value;
    return old_value;
}

#endif  // #if !defined(GO_BOOST_NO_CXX11_R_VALUE_REFERENCES)

}
}

#endif  // #ifndef GO_BOOST_UTILITY_EXCHANGE_HPP_INCLUDED
