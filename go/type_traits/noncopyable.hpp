#ifndef GO_TYPE_TRAITS_NONCOPYABLE_HPP_INCLUDED
#define GO_TYPE_TRAITS_NONCOPYABLE_HPP_INCLUDED

//
//  noncopyable.hpp
//
//  Copyright 2016-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

namespace go
{
namespace type_traits
{

class noncopyable
{
public:
    virtual ~noncopyable() = 0;

private:

#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    noncopyable(const noncopyable&) = delete;
    auto operator=(const noncopyable&) ->noncopyable& = delete;

#else

    noncopyable(const noncopyable&) {}
    auto operator=(const noncopyable&) ->noncopyable& {}

#endif  // !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

protected:
    noncopyable() GO_DEFAULT_CONSTRUCTOR

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    noncopyable(noncopyable&&) GO_DEFAULT_CONSTRUCTOR
    auto operator=(noncopyable&&) ->noncopyable& GO_DEFAULT_CONSTRUCTOR

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

};

inline noncopyable::~noncopyable()
{
}

}
}

#endif  // #ifndef GO_TYPE_TRAITS_NONCOPYABLE_HPP_INCLUDED
