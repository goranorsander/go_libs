#ifndef GO_SIGNALS_PLACEHOLDER_HPP_INCLUDED
#define GO_SIGNALS_PLACEHOLDER_HPP_INCLUDED

//
//  placeholder.hpp
//
//  Copyright 2021-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <functional>

namespace go
{
namespace signals
{

template<int>
struct placeholder
{
};

} // namespace signals
} // namespace go

namespace std
{

template<int N>
struct is_placeholder<go::signals::placeholder<N>>
    : integral_constant<int, N + 1>
{
};

} // namespace std

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_PLACEHOLDER_HPP_INCLUDED
