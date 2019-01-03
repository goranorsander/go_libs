#ifndef GO_BOOST_MVVM_ITERATOR_TRY_MOVE_BACKWARD_HPP_INCLUDED
#define GO_BOOST_MVVM_ITERATOR_TRY_MOVE_BACKWARD_HPP_INCLUDED

//
//  try_move_backward.hpp
//
//  Copyright 2016-2019 Göran Orsander
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

namespace go_boost
{
namespace mvvm
{
namespace iterator
{

template<class I, class C>
inline bool try_move_backward(const boost::shared_ptr<C>& container, I& it)
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

#endif  // #ifndef GO_BOOST_MVVM_ITERATOR_TRY_MOVE_BACKWARD_HPP_INCLUDED
