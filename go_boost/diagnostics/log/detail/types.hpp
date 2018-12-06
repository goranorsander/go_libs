#ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_TYPES_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_DETAIL_TYPES_HPP_INCLUDED

//
//  types.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#if defined(BOOST_NO_CXX11_HDR_TUPLE) || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#define FUSION_MAX_VECTOR_SIZE 16

#include <boost/fusion/tuple.hpp>

#else

#include <tuple>

#endif  // #if defined(BOOST_NO_CXX11_HDR_TUPLE) || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

namespace go_boost
{
namespace diagnostics
{
namespace log
{
namespace detail
{

template <typename T, typename Tuple>
struct types_tuple_index;

#if defined(BOOST_NO_CXX11_HDR_TUPLE) || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#define GO_BOOST_DIAGNOSTICS_LOG_DETAIL_TYPES_TEMPLATE_TYPE_PARAMETERS typename Type0, typename Type1, typename Type2, typename Type3, typename Type4, typename Type5, typename Type6, typename Type7, typename Type8, typename Type9, typename Type10, typename Type11, typename Type12, typename Type13, typename Type14

template <typename T, GO_BOOST_DIAGNOSTICS_LOG_DETAIL_TYPES_TEMPLATE_TYPE_PARAMETERS>
struct types_tuple_index <T, boost::fusion::tuple<T, GO_BOOST_DIAGNOSTICS_LOG_DETAIL_TYPES_TEMPLATE_TYPE_PARAMETERS>>
{
    static GO_BOOST_CONSTEXPR const std::size_t value = 0;
};

template <typename T, typename U, GO_BOOST_DIAGNOSTICS_LOG_DETAIL_TYPES_TEMPLATE_TYPE_PARAMETERS>
struct types_tuple_index <T, boost::fusion::tuple<U, GO_BOOST_DIAGNOSTICS_LOG_DETAIL_TYPES_TEMPLATE_TYPE_PARAMETERS>>
{
    static GO_BOOST_CONSTEXPR const std::size_t value = 1 + types_tuple_index<T, boost::fusion::tuple<GO_BOOST_DIAGNOSTICS_LOG_DETAIL_TYPES_TEMPLATE_TYPE_PARAMETERS>>::value;
};

#else

template <typename T, typename ... Types>
struct types_tuple_index <T, std::tuple<T, Types...>>
{
    static GO_BOOST_CONSTEXPR const std::size_t value = 0;
};

template <typename T, typename U, typename ... Types>
struct types_tuple_index <T, std::tuple<U, Types...>>
{
    static GO_BOOST_CONSTEXPR const std::size_t value = 1 + types_tuple_index<T, std::tuple<Types...>>::value;
};

#endif  // #if defined(BOOST_NO_CXX11_HDR_TUPLE) || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_TYPES_HPP_INCLUDED
