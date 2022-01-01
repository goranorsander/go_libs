#ifndef GO_SIGNALS_DETAIL_INT_SEQUENCE_KEY_HPP_INCLUDED
#define GO_SIGNALS_DETAIL_INT_SEQUENCE_KEY_HPP_INCLUDED

//
//  int_sequence.hpp
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

namespace go
{
namespace signals
{
namespace detail
{

template<int... Ns>
struct int_sequence
{
};

template<int N, int... Ns>
struct make_int_sequence
    : make_int_sequence<N - 1, N - 1, Ns...>
{
};

template<int... Ns>
struct make_int_sequence<0, Ns...>
    : int_sequence<Ns...>
{
};

} // namespace detail
} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_DETAIL_INT_SEQUENCE_KEY_HPP_INCLUDED
