#ifndef GO_BOOST_UTILITY_CONTAINER_SIZE_HPP_INCLUDED
#define GO_BOOST_UTILITY_CONTAINER_SIZE_HPP_INCLUDED

//
//  size.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <iterator>
#include <boost/shared_ptr.hpp>

namespace go_boost
{
namespace utility
{
namespace container
{

template<class C>
inline std::size_t size(C& container)
{
    std::size_t s = 0;
    C::const_iterator it = container.begin();
    while (it != container.end())
    {
        ++s;
        ++it;
    }
    return s;
}

template<class C>
inline std::size_t size(const boost::shared_ptr<C>& container)
{
    std::size_t s = 0;
    if(container)
    {
        C::const_iterator it = container->begin();
        while (it != container->end())
        {
            ++s;
            ++it;
        }
    }
    return s;
}

}
}
}

#endif  // #ifndef GO_BOOST_UTILITY_CONTAINER_SIZE_HPP_INCLUDED
