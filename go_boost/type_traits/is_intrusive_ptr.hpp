#ifndef GO_BOOST_TYPE_TRAITS_IS_INTRUSIVE_PTR_HPP_INCLUDED
#define GO_BOOST_TYPE_TRAITS_IS_INTRUSIVE_PTR_HPP_INCLUDED

//
//  is_intrusive_ptr.hpp
//
//  Copyright 2020-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/intrusive_ptr.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace go_boost
{
namespace type_traits
{

template <typename T> struct is_intrusive_ptr
    : public boost::false_type
{
};

template <typename T> struct is_intrusive_ptr<boost::intrusive_ptr<T>>
    : public boost::true_type
{
};

}
}

#endif  // #ifndef GO_BOOST_TYPE_TRAITS_IS_INTRUSIVE_PTR_HPP_INCLUDED
