#ifndef GO_SIGNALS_SLOT_HPP_INCLUDED
#define GO_SIGNALS_SLOT_HPP_INCLUDED

//
//  slot.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if (GO_COMP_MSVC) && (_MSC_VER <= 1800)
#pragma message("C++11/14 is not supported by this compiler")
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
    slot()
    {
    }
};

inline slot::~slot()
{
}

} // namespace signals
} // namespace go

#endif // C++11/14 is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_SLOT_HPP_INCLUDED
