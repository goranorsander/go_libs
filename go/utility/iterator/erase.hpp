#ifndef GO_UTILITY_ITERATOR_ERASE_HPP_INCLUDED
#define GO_UTILITY_ITERATOR_ERASE_HPP_INCLUDED

//
//  erase.hpp
//
//  Copyright 2016-2019 Göran Orsander
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

namespace go
{
namespace utility
{
namespace iterator
{

template<class I, class C>
inline I erase(C& container, I& it, const std::size_t& n)
{
    std::size_t count = 0;
    while ((count < n) && (it != container.end()))
    {
        ++count;
        it = container.erase(it);
    }
    return it;
}

}
}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_UTILITY_ITERATOR_ERASE_HPP_INCLUDED
