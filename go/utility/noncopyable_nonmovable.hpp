#ifndef GO_UTILITY_NONCOPYABLE_NONMOVABLE_HPP_INCLUDED
#define GO_UTILITY_NONCOPYABLE_NONMOVABLE_HPP_INCLUDED

//
//  noncopyable_nonmovable.hpp
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

class noncopyable_nonmovable
{
public:
    virtual ~noncopyable_nonmovable() = 0;

private:

#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    noncopyable_nonmovable(const noncopyable_nonmovable&) = delete;

#else

    noncopyable_nonmovable(const noncopyable_nonmovable&) {}

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

#if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)
#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    noncopyable_nonmovable(noncopyable_nonmovable&&) = delete;

#else

    noncopyable_nonmovable(noncopyable_nonmovable&&) {}

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
#endif  // #if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    auto operator=(const noncopyable_nonmovable&)->noncopyable_nonmovable& = delete;

#else

    auto operator=(const noncopyable_nonmovable&)->noncopyable_nonmovable& {}

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

#if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)
#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    auto operator=(noncopyable_nonmovable&&)->noncopyable_nonmovable& = delete;

#else

    auto operator=(noncopyable_nonmovable&&)->noncopyable_nonmovable& {}

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
#endif  // #if !defined(GO_NO_CXX11_R_VALUE_REFERENCES)

protected:
    noncopyable_nonmovable() GO_DEFAULT_CONSTRUCTOR
};

inline noncopyable_nonmovable::~noncopyable_nonmovable()
{
}

}
}

#endif  // #ifndef GO_UTILITY_NONCOPYABLE_NONMOVABLE_HPP_INCLUDED
