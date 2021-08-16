#ifndef GO_TYPE_TRAITS_IDENTITY_HPP_INCLUDED
#define GO_TYPE_TRAITS_IDENTITY_HPP_INCLUDED

//
//  identity.hpp
//
//  Copyright 2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

namespace go
{
namespace type_traits
{

template <typename T> struct identity
{
    GO_USING(type, T);
};

}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_TYPE_TRAITS_IDENTITY_HPP_INCLUDED
