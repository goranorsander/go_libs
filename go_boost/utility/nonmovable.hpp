#ifndef GO_BOOST_UTILITY_NONMOVABLE_HPP_INCLUDED
#define GO_BOOST_UTILITY_NONMOVABLE_HPP_INCLUDED

//
//  nonmovable.hpp
//
//  Copyright 2016-2018 Göran Orsander
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
namespace utility
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

#else  // #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)

    nonmovable(nonmovable&&) {}
    nonmovable& operator=(nonmovable&&) { return *this; }

#endif  // #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

protected:

#if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)

    nonmovable() = default;
    nonmovable(const nonmovable&) = default;
    nonmovable& operator=(const nonmovable&) = default;

#else  // #if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)

    nonmovable() {}
    nonmovable(const nonmovable&) {}
    nonmovable& operator=(const nonmovable&) { return *this; }

#endif  // #if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
};

inline nonmovable::~nonmovable()
{
}

}
}

#endif  // #ifndef GO_BOOST_UTILITY_NONMOVABLE_HPP_INCLUDED
