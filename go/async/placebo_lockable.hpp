#ifndef GO_ASYNC_PLACEBO_LOCKABLE_HPP_INCLUDED
#define GO_ASYNC_PLACEBO_LOCKABLE_HPP_INCLUDED

//
//  placebo_lockable.hpp
//
//  Copyright 2018-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

namespace go
{
namespace async
{

class placebo_lockable
{
public:
    virtual ~placebo_lockable() GO_DEFAULT_DESTRUCTOR
    placebo_lockable() GO_NOEXCEPT GO_DEFAULT_CONSTRUCTOR

public:
    static void lock()
    {
    }

    static bool try_lock()
    {
        return true;
    }

    static void unlock()
    {
    }
};

}
}

#endif  // #ifndef GO_ASYNC_PLACEBO_LOCKABLE_HPP_INCLUDED
