#ifndef GO_UTILITY_ITERATOR_TRY_MOVE_ITERATOR_BACKWARD_HPP_INCLUDED
#define GO_UTILITY_ITERATOR_TRY_MOVE_ITERATOR_BACKWARD_HPP_INCLUDED

//
//  try_move_iterator_backward.hpp
//
//  Copyright 2016-2017 Göran Orsander
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
inline bool try_move_iterator_backward(const std::shared_ptr<C>& container, I& it)
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

#endif  // #ifndef GO_UTILITY_ITERATOR_TRY_MOVE_ITERATOR_BACKWARD_HPP_INCLUDED
