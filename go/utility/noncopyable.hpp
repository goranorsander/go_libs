#ifndef GO_UTILITY_NONCOPYABLE_HPP_INCLUDED
#define GO_UTILITY_NONCOPYABLE_HPP_INCLUDED

//
//  noncopyable.hpp
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

class noncopyable
{
public:
    virtual ~noncopyable() = 0;

private:
    noncopyable(const noncopyable&) = delete;
    auto operator=(const noncopyable&)->noncopyable& = delete;

protected:
    noncopyable() = default;

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    noncopyable(noncopyable&&) = default;
    auto operator=(noncopyable&&)->noncopyable& = default;

#endif  // #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

};

inline noncopyable::~noncopyable()
{
}

}
}

#endif  // #ifndef GO_UTILITY_NONCOPYABLE_HPP_INCLUDED
