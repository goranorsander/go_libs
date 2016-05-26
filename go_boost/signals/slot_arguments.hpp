#ifndef GO_BOOST_SIGNALS_SLOT_ARGUMENTS_HPP_INCLUDED
#define GO_BOOST_SIGNALS_SLOT_ARGUMENTS_HPP_INCLUDED

//
//  slot_arguments.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace go_boost
{
namespace signals
{

class slot_arguments
    : public boost::noncopyable
{
public:
    typedef boost::shared_ptr<slot_arguments> ptr;
    typedef boost::weak_ptr<slot_arguments> wptr;

public:
    virtual ~slot_arguments() = 0;

protected:
    slot_arguments()
    {
    }
};

inline slot_arguments::~slot_arguments()
{
}

} // namespace signals
} // namespace go_boost

#endif  // #ifndef GO_BOOST_SIGNALS_SLOT_ARGUMENTS_HPP_INCLUDED
