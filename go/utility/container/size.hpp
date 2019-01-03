#ifndef GO_UTILITY_CONTAINER_SIZE_HPP_INCLUDED
#define GO_UTILITY_CONTAINER_SIZE_HPP_INCLUDED

//
//  size.hpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11_RANGE_FOR_LOOP)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <memory>

namespace go
{
namespace utility
{
namespace container
{

template<class C>
inline std::size_t size(C& container)
{
    std::size_t s = 0;
    for (GO_TYPENAME C::value_type v : container) { ++s; }
    return s;
}

template<class C>
inline std::size_t size(const std::shared_ptr<C>& container)
{
    std::size_t s = 0;
    if(container)
    {
        for (GO_TYPENAME C::value_type v : *container) { ++s; }
    }
    return s;
}

}
}
}

#endif  // #if defined(GO_NO_CXX11_RANGE_FOR_LOOP)

#endif  // #ifndef GO_UTILITY_CONTAINER_SIZE_HPP_INCLUDED
