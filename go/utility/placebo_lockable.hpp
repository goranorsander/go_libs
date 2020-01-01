#ifndef GO_UTILITY_PLACEBO_LOCKABLE_HPP_INCLUDED
#define GO_UTILITY_PLACEBO_LOCKABLE_HPP_INCLUDED

//
//  placebo_lockable.hpp
//
//  Copyright 2018-2020 Göran Orsander
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

class placebo_lockable
{
public:
    virtual ~placebo_lockable() GO_DEFAULT_DESTRUCTOR
    placebo_lockable() GO_NOEXCEPT GO_DEFAULT_CONSTRUCTOR

public:
    void lock();
    bool try_lock();
    void unlock();
};

inline void placebo_lockable::lock()
{
}

inline bool placebo_lockable::try_lock()
{
    return true;
}

inline void placebo_lockable::unlock()
{
}

}
}

#endif  // #ifndef GO_UTILITY_PLACEBO_LOCKABLE_HPP_INCLUDED
