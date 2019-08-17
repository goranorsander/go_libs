#ifndef GO_BOOST_UTILITY_NONCOPYABLE_NONMOVABLE_HPP_INCLUDED
#define GO_BOOST_UTILITY_NONCOPYABLE_NONMOVABLE_HPP_INCLUDED

//
//  noncopyable_nonmovable.hpp
//
//  Copyright 2016-2019 Göran Orsander
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
namespace utility
{

class noncopyable_nonmovable
    : private boost::noncopyable
{
public:
    virtual ~noncopyable_nonmovable() = 0;


private:

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    noncopyable_nonmovable(noncopyable_nonmovable&&) GO_BOOST_DELETE_FUNCTION
    noncopyable_nonmovable& operator=(noncopyable_nonmovable&&) GO_BOOST_DELETE_FUNCTION

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

protected:
    noncopyable_nonmovable() GO_BOOST_DEFAULT_CONSTRUCTOR
};

inline noncopyable_nonmovable::~noncopyable_nonmovable()
{
}

}
}

#endif  // #ifndef GO_BOOST_UTILITY_NONCOPYABLE_NONMOVABLE_HPP_INCLUDED
