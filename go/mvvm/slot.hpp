#ifndef GO_MVVM_SLOT_HPP_INCLUDED
#define GO_MVVM_SLOT_HPP_INCLUDED

//
//  slot.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <memory>

namespace go
{
namespace mvvm
{

class slot
{
public:
    typedef std::shared_ptr<slot> ptr;
    typedef std::weak_ptr<slot> wptr;

public:
    virtual ~slot() = 0
    {
    }

protected:
    slot()
    {
    }
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_SLOT_HPP_INCLUDED
