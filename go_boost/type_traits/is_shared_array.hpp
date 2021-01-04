#ifndef GO_BOOST_TYPE_TRAITS_IS_SHARED_ARRAY_HPP_INCLUDED
#define GO_BOOST_TYPE_TRAITS_IS_SHARED_ARRAY_HPP_INCLUDED

//
//  is_shared_array.hpp
//
//  Copyright 2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/shared_array.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <memory>

namespace go_boost
{
namespace type_traits
{

template <typename T> struct is_shared_array
    : public boost::false_type
{
};

template <typename T> struct is_shared_array<boost::shared_array<T>>
    : public boost::true_type
{
};

}
}

#endif  // #ifndef GO_BOOST_TYPE_TRAITS_IS_SHARED_ARRAY_HPP_INCLUDED
