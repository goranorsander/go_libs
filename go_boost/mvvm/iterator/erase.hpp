#ifndef GO_BOOST_MVVM_ITERATOR_ERASE_HPP_INCLUDED
#define GO_BOOST_MVVM_ITERATOR_ERASE_HPP_INCLUDED

//
//  erase.hpp
//
//  Copyright 2016-2021 Göran Orsander
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
namespace mvvm
{
namespace iterator
{

template<class I, class C>
inline I erase(const boost::shared_ptr<C>& container, I& it, const std::size_t& n)
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

#endif  // #ifndef GO_BOOST_MVVM_ITERATOR_ERASE_HPP_INCLUDED
