#ifndef GO_DIAGNOSTICS_LOG_DETAIL_TYPES_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_DETAIL_TYPES_HPP_INCLUDED

//
//  types.hpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <tuple>

namespace go
{
namespace diagnostics
{
namespace log
{
namespace detail
{

template <typename T, typename Tuple>
struct types_tuple_index;

template <typename T, typename ... Types>
struct types_tuple_index <T, std::tuple<T, Types...>>
{
    static GO_CONSTEXPR const std::size_t value = 0;
};

template <typename T, typename U, typename ... Types>
struct types_tuple_index <T, std::tuple<U, Types...>>
{
    static GO_CONSTEXPR const std::size_t value = 1 + types_tuple_index<T, std::tuple<Types...>>::value;
};

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_DETAIL_TYPES_HPP_INCLUDED
