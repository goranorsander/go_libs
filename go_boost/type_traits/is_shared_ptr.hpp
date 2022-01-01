#ifndef GO_BOOST_TYPE_TRAITS_IS_SHARED_PTR_HPP_INCLUDED
#define GO_BOOST_TYPE_TRAITS_IS_SHARED_PTR_HPP_INCLUDED

//
//  is_shared_ptr.hpp
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

#include <boost/shared_ptr.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <memory>

namespace go_boost
{
namespace type_traits
{

template <typename T> struct is_shared_ptr
    : public boost::false_type
{
};

template <typename T> struct is_shared_ptr<boost::shared_ptr<T>>
    : public boost::true_type
{
};

#if !defined(GO_BOOST_NO_CXX11_NULLPTR)

template <typename T> struct is_std_shared_ptr
    : public boost::false_type
{
};

template <typename T> struct is_std_shared_ptr<std::shared_ptr<T>>
    : public boost::true_type
{
};

#endif  // #if !defined(GO_BOOST_NO_CXX11_NULLPTR)

}
}

#endif  // #ifndef GO_BOOST_TYPE_TRAITS_IS_SHARED_PTR_HPP_INCLUDED
