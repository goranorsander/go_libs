#ifndef GO_UTILITY_ITERATOR_REVERSE_HPP_INCLUDED
#define GO_UTILITY_ITERATOR_REVERSE_HPP_INCLUDED

//
//  reverse.hpp
//
//  Copyright 2019-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX14) || defined(GO_NO_CXX14_ARGUMENT_DEPENDENT_LOOKUP)
GO_MESSAGE("Required C++14 feature is not supported by this compiler")
#else

namespace go
{
namespace utility
{
namespace iterator
{

template <typename I>
struct reverse_adaptor_wrapper
{
    I& iterable;
};

template <typename A>
auto begin(reverse_adaptor_wrapper<A> adaptor)
{
    return std::rbegin(adaptor.iterable);
}

template <typename A>
auto end(reverse_adaptor_wrapper<A> adaptor)
{
    return std::rend(adaptor.iterable);
}

template <typename C>
reverse_adaptor_wrapper<C> reverse(C&& iterable)
{
    return { iterable };
}

}
}
}

#endif  // Required C++14 feature is not supported by this compiler

#endif  // #ifndef GO_UTILITY_ITERATOR_REVERSE_HPP_INCLUDED
