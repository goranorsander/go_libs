#ifndef GO_UTILITY_NONMOVABLE_HPP_INCLUDED
#define GO_UTILITY_NONMOVABLE_HPP_INCLUDED

//
//  nonmovable.hpp
//
//  Copyright 2016-2019 Göran Orsander
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

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)
#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    nonmovable(nonmovable&&) = delete;
    auto operator=(nonmovable&&) ->nonmovable& = delete;

#else

    nonmovable(nonmovable&&) {}
    auto operator=(nonmovable&&) ->nonmovable& {}

#endif  // #!defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

protected:
    nonmovable() GO_DEFAULT_CONSTRUCTOR
    nonmovable(const nonmovable&) GO_DEFAULT_CONSTRUCTOR
    auto operator=(const nonmovable&) ->nonmovable& GO_DEFAULT_CONSTRUCTOR
};

inline nonmovable::~nonmovable()
{
}

}
}

#endif  // #ifndef GO_UTILITY_NONMOVABLE_HPP_INCLUDED
