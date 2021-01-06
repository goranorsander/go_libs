#ifndef GO_BOOST_TYPE_TRAITS_NONCOPYABLE_NONMOVABLE_HPP_INCLUDED
#define GO_BOOST_TYPE_TRAITS_NONCOPYABLE_NONMOVABLE_HPP_INCLUDED

//
//  noncopyable_nonmovable.hpp
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

#include <boost/noncopyable.hpp>

namespace go_boost
{
namespace type_traits
{

class noncopyable_nonmovable
    : private boost::noncopyable
{
public:
    virtual ~noncopyable_nonmovable() = 0;


private:

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)

    noncopyable_nonmovable(noncopyable_nonmovable&&) = delete;
    noncopyable_nonmovable& operator=(noncopyable_nonmovable&&) = delete;

#else

    noncopyable_nonmovable(noncopyable_nonmovable&&) {}
    noncopyable_nonmovable& operator=(noncopyable_nonmovable&&) BOOST_NOEXCEPT_OR_NOTHROW { return *this; }

#endif  // #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

protected:
    noncopyable_nonmovable() GO_BOOST_DEFAULT_CONSTRUCTOR
};

inline noncopyable_nonmovable::~noncopyable_nonmovable()
{
}

}
}

#endif  // #ifndef GO_BOOST_TYPE_TRAITS_NONCOPYABLE_NONMOVABLE_HPP_INCLUDED
