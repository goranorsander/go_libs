#ifndef GO_MVVM_ITERATOR_TRY_MOVE_BACKWARD_HPP_INCLUDED
#define GO_MVVM_ITERATOR_TRY_MOVE_BACKWARD_HPP_INCLUDED

//
//  try_move_backward.hpp
//
//  Copyright 2016-2018 Göran Orsander
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
namespace mvvm
{
namespace iterator
{

template<class I, class C>
inline bool try_move_backward(const std::shared_ptr<C>& container, I& it)
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

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_ITERATOR_TRY_MOVE_BACKWARD_HPP_INCLUDED
