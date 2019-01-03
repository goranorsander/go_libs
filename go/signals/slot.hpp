#ifndef GO_SIGNALS_SLOT_HPP_INCLUDED
#define GO_SIGNALS_SLOT_HPP_INCLUDED

//
//  slot.hpp
//
//  Copyright 2015-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <memory>

namespace go
{
namespace signals
{

class slot
{
public:
    typedef slot this_type;
    typedef std::shared_ptr<this_type> ptr;
    typedef std::weak_ptr<this_type> wptr;

public:
    virtual ~slot() = 0;

protected:
    slot() GO_DEFAULT_CONSTRUCTOR
};

inline slot::~slot()
{
}

} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_SLOT_HPP_INCLUDED
