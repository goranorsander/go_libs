#ifndef GO_BOOST_UTILITY_ITERATOR_ERASE_HPP_INCLUDED
#define GO_BOOST_UTILITY_ITERATOR_ERASE_HPP_INCLUDED

//
//  erase.hpp
//
//  Copyright 2016-2018 Göran Orsander
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
namespace iterator
{

template<class I, class C, class D>
inline I erase(C& container, I& it, const D& n)
{
    D count = 0;
    while ((count < n) && (it != container.end()))
    {
        ++count;
        it = container.erase(it);
    }
    return it;
}

template<class I, class C, class D>
inline bool erase(boost::shared_ptr<C>& container, I& it, const D& n)
{
    if(container)
    {
        D count = 0;
        while ((count < n) && (it != container.end()))
        {
            ++count;
            it = container->erase(it);
        }
    }
    return it;
}

}
}
}

#endif  // #ifndef GO_BOOST_UTILITY_ITERATOR_ERASE_HPP_INCLUDED
