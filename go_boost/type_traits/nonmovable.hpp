#ifndef GO_BOOST_TYPE_TRAITS_NONMOVABLE_HPP_INCLUDED
#define GO_BOOST_TYPE_TRAITS_NONMOVABLE_HPP_INCLUDED

//
//  nonmovable.hpp
//
//  Copyright 2016-2020 Göran Orsander
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
namespace type_traits
{

class nonmovable
{
public:
    virtual ~nonmovable() = 0;

private:

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)

    nonmovable(nonmovable&&) = delete;
    nonmovable& operator=(nonmovable&&) = delete;

#else

    nonmovable(nonmovable&&) {}
    nonmovable& operator=(nonmovable&&) BOOST_NOEXCEPT_OR_NOTHROW { return *this; }

#endif  // #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

protected:
    nonmovable() GO_BOOST_DEFAULT_CONSTRUCTOR
    nonmovable(const nonmovable&) GO_BOOST_DEFAULT_CONSTRUCTOR

#if !defined(GO_BOOST_NO_CXX11_DEFAULTED_COPY_ASSIGN_OPERATOR)

    nonmovable& operator=(const nonmovable&) noexcept = default;

#else  // #if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)

    nonmovable& operator=(const nonmovable&) BOOST_NOEXCEPT_OR_NOTHROW { return *this; }

#endif  // #if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
};

inline nonmovable::~nonmovable()
{
}

}
}

#endif  // #ifndef GO_BOOST_TYPE_TRAITS_NONMOVABLE_HPP_INCLUDED
