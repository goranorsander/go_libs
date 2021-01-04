#ifndef GO_TYPE_TRAITS_IS_WEAK_PTR_HPP_INCLUDED
#define GO_TYPE_TRAITS_IS_WEAK_PTR_HPP_INCLUDED

//
//  is_weak_ptr.hpp
//
//  Copyright 2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <memory>
#include <type_traits>

namespace go
{
namespace type_traits
{

template <typename T> struct is_weak_ptr
    : public std::false_type
{
};

template <typename T> struct is_weak_ptr<std::weak_ptr<T>>
    : public std::true_type
{
};

}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_TYPE_TRAITS_IS_WEAK_PTR_HPP_INCLUDED
