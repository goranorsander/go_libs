#ifndef GO_UTILITY_NONMOVABLE_HPP_INCLUDED
#define GO_UTILITY_NONMOVABLE_HPP_INCLUDED

//
//  nonmovable.hpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
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

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    nonmovable(nonmovable&&) = delete;
    auto operator=(nonmovable&&)->nonmovable& = delete;

#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

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
