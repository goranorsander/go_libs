#ifndef GO_BOOST_UTILITY_ITERATOR_ITERATOR_HPP_INCLUDED
#define GO_BOOST_UTILITY_ITERATOR_ITERATOR_HPP_INCLUDED

//
//  iterator.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <iterator>

namespace go_boost
{
namespace utility
{
namespace iterator
{

template<class I, class C>
inline bool try_move_iterator_backward(const C& container, I& it)
{
    I at = container.begin();
    const I end = container.end();
    while(at != end)
    {
        I look_ahead = at;
        ++look_ahead;
        if(look_ahead == it)
        {
            it = at;
            return true;
        }
        ++at;
    }
    return false;
}

template<class I, class C>
inline bool try_move_iterator_backward(const boost::shared_ptr<C>& container, I& it)
{
    if(container)
    {
        I at = container->begin();
        const I end = container->end();
        while(at != end)
        {
            I look_ahead = at;
            ++look_ahead;
            if(look_ahead == it)
            {
                it = at;
                return true;
            }
            ++at;
        }
    }
    return false;
}

}
}
}

#endif  // #ifndef GO_BOOST_UTILITY_ITERATOR_ITERATOR_HPP_INCLUDED
