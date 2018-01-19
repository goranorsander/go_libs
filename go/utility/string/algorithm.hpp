#ifndef GO_UTILITY_STRING_ALGORITHM_HPP_INCLUDED
#define GO_UTILITY_STRING_ALGORITHM_HPP_INCLUDED

//
//  algorithm.hpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

namespace go
{
namespace utility
{
namespace string
{

template<class S>
inline bool equals(const S& s1, const S& s2)
{
    if (s1.size() == s2.size())
    {
        for (auto i1 = s1.begin(), i2 = s2.begin(), e = s1.end(); i1 != e; ++i1, ++i2)
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
}

#endif  // #ifndef GO_UTILITY_STRING_ALGORITHM_HPP_INCLUDED
