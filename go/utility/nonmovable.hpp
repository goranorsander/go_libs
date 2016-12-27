#ifndef GO_UTILITY_NONMOVABLE_HPP_INCLUDED
#define GO_UTILITY_NONMOVABLE_HPP_INCLUDED

//
//  nonmovable.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

namespace go
{
namespace utility
{

class nonmovable
{
public:
    virtual ~nonmovable() = 0;

private:
    nonmovable(nonmovable&&) = delete;
    auto operator=(nonmovable&&)->nonmovable& = delete;

protected:
    nonmovable() = default;
    nonmovable(const nonmovable&) = default;
    auto operator=(const nonmovable&)->nonmovable& = default;
};

inline nonmovable::~nonmovable()
{
}

}
}

#endif  // #ifndef GO_UTILITY_NONMOVABLE_HPP_INCLUDED
