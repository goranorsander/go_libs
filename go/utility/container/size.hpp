#ifndef GO_UTILITY_CONTAINER_SIZE_HPP_INCLUDED
#define GO_UTILITY_CONTAINER_SIZE_HPP_INCLUDED

//
//  size.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

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
    for (C::value_type v : container) { ++s; }
    return s;
}

template<class C>
inline std::size_t size(const std::shared_ptr<C>& container)
{
    std::size_t s = 0;
    if(container)
    {
        for (C::value_type v : *container) { ++s; }
    }
    return s;
}

}
}
}

#endif  // #ifndef GO_UTILITY_CONTAINER_SIZE_HPP_INCLUDED
