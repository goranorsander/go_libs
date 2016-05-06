#ifndef GO_BOOST_SIGNALS_SLOT_HPP_INCLUDED
#define GO_BOOST_SIGNALS_SLOT_HPP_INCLUDED

//
//  slot.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace go_boost
{
namespace signals
{

class slot
{
public:
    typedef boost::shared_ptr<slot> ptr;
    typedef boost::weak_ptr<slot> wptr;

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
} // namespace go_boost

#endif  // #ifndef GO_BOOST_SIGNALS_SLOT_HPP_INCLUDED
