#ifndef GO_BOOST_TYPE_TRAITS_IS_SMART_PTR_HPP_INCLUDED
#define GO_BOOST_TYPE_TRAITS_IS_SMART_PTR_HPP_INCLUDED

//
//  is_smart_ptr.hpp
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
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/weak_ptr.hpp>
#include <memory>

namespace go_boost
{
namespace type_traits
{

template <typename T> struct is_smart_ptr
    : public boost::false_type
{
};

template <typename T> struct is_smart_ptr<boost::intrusive_ptr<T>>
    : public boost::true_type
{
};

template <typename T> struct is_smart_ptr<boost::scoped_array<T>>
    : public boost::true_type
{
};

template <typename T> struct is_smart_ptr<boost::scoped_ptr<T>>
    : public boost::true_type
{
};

template <typename T> struct is_smart_ptr<boost::shared_array<T>>
    : public boost::true_type
{
};

template <typename T> struct is_smart_ptr<boost::shared_ptr<T>>
    : public boost::true_type
{
};

template <typename T> struct is_smart_ptr<boost::weak_ptr<T>>
    : public boost::true_type
{
};

#if !defined(GO_BOOST_NO_STD_AUTO_PTR)

template <typename T> struct is_smart_ptr<std::auto_ptr<T>>
    : public boost::true_type
{
};

#endif  // #if !defined(GO_BOOST_NO_STD_AUTO_PTR)

#if !defined(GO_BOOST_NO_CXX11)

template <typename T> struct is_smart_ptr<std::shared_ptr<T>>
    : public boost::true_type
{
};

template <typename T> struct is_smart_ptr<std::unique_ptr<T>>
    : public boost::true_type
{
};

template <typename T> struct is_smart_ptr<std::weak_ptr<T>>
    : public boost::true_type
{
};

#endif  // #if !defined(GO_BOOST_NO_CXX11)

}
}

#endif  // #ifndef GO_BOOST_TYPE_TRAITS_IS_SMART_PTR_HPP_INCLUDED
