#ifndef GO_BOOST_TYPE_TRAITS_IS_WEAK_PTR_HPP_INCLUDED
#define GO_BOOST_TYPE_TRAITS_IS_WEAK_PTR_HPP_INCLUDED

//
//  is_weak_ptr.hpp
//
//  Copyright 2020-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/type_traits/integral_constant.hpp>
#include <boost/weak_ptr.hpp>
#include <memory>

namespace go_boost
{
namespace type_traits
{

template <typename T> struct is_weak_ptr
    : public boost::false_type
{
};

template <typename T> struct is_weak_ptr<boost::weak_ptr<T>>
    : public boost::true_type
{
};

#if !defined(GO_BOOST_NO_CXX11_NULLPTR)

template <typename T> struct is_std_weak_ptr
    : public boost::false_type
{
};

template <typename T> struct is_std_weak_ptr<std::weak_ptr<T>>
    : public boost::true_type
{
};

#endif  // #if !defined(GO_BOOST_NO_CXX11_NULLPTR)

}
}

#endif  // #ifndef GO_BOOST_TYPE_TRAITS_IS_WEAK_PTR_HPP_INCLUDED
