#ifndef GO_SIGNALS_SLOT_ARGUMENTS_HPP_INCLUDED
#define GO_SIGNALS_SLOT_ARGUMENTS_HPP_INCLUDED

//
//  slot_arguments.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <memory>

namespace go
{
namespace signals
{

class slot_arguments
{
public:
    typedef typename slot_arguments this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~slot_arguments() = 0;

protected:
    slot_arguments()
    {
    }

private:
    slot_arguments(const slot_arguments&) = delete;
};

inline slot_arguments::~slot_arguments()
{
}

} // namespace signals
} // namespace go

#endif  // #ifndef GO_SIGNALS_SLOT_ARGUMENTS_HPP_INCLUDED
