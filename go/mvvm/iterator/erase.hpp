#ifndef GO_MVVM_ITERATOR_ERASE_HPP_INCLUDED
#define GO_MVVM_ITERATOR_ERASE_HPP_INCLUDED

//
//  erase.hpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <memory>

namespace go
{
namespace mvvm
{
namespace iterator
{

template<class I, class C>
inline I erase(const std::shared_ptr<C>& container, I& it, const std::size_t& n)
{
    if(container)
    {
        std::size_t count = 0;
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

#endif  // #ifndef GO_MVVM_ITERATOR_ERASE_HPP_INCLUDED