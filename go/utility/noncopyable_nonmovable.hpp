#ifndef GO_UTILITY_NONCOPYABLE_NONMOVABLE_HPP_INCLUDED
#define GO_UTILITY_NONCOPYABLE_NONMOVABLE_HPP_INCLUDED

//
//  noncopyable_nonmovable.hpp
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

class noncopyable_nonmovable
{
public:
    virtual ~noncopyable_nonmovable() = 0;

private:
    noncopyable_nonmovable(noncopyable_nonmovable const&) = delete;
    noncopyable_nonmovable(noncopyable_nonmovable&&) = delete;
    auto operator=(noncopyable_nonmovable const&)->noncopyable_nonmovable& = delete;
    auto operator=(noncopyable_nonmovable&&)->noncopyable_nonmovable& = delete;

protected:
    noncopyable_nonmovable() = default;
};

inline noncopyable_nonmovable::~noncopyable_nonmovable()
{
}

}
}

#endif  // #ifndef GO_UTILITY_NONCOPYABLE_NONMOVABLE_HPP_INCLUDED
