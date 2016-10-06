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
    noncopyable(noncopyable const&) = delete;
    auto operator=(noncopyable const&)->noncopyable& = delete;

protected:
    noncopyable() = default;
    noncopyable(noncopyable&&) = default;
    auto operator=(noncopyable&&)->noncopyable& = default;
};

inline noncopyable::~noncopyable()
{
}

}
}

#endif  // #ifndef GO_UTILITY_NONCOPYABLE_HPP_INCLUDED
