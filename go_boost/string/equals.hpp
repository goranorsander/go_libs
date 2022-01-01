#ifndef GO_BOOST_STRING_EQUALS_HPP_INCLUDED
#define GO_BOOST_STRING_EQUALS_HPP_INCLUDED

//
//  equals.hpp
//
//  Copyright 2020-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

namespace go_boost
{
namespace string
{

template<class S>
inline bool equals(const S& s1, const S& s2)
{
    if (s1.size() == s2.size())
    {
        for (typename S::const_iterator i1 = s1.begin(), i2 = s2.begin(), e = s1.end(); i1 != e; ++i1, ++i2)
        {
            if (*i1 != *i2)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

}
}

#endif  // #ifndef GO_BOOST_STRING_EQUALS_HPP_INCLUDED
