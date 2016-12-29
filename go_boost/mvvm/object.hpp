#ifndef GO_BOOST_MVVM_OBJECT_HPP_INCLUDED
#define GO_BOOST_MVVM_OBJECT_HPP_INCLUDED

//
//  object.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/enable_shared_from_this.hpp>

namespace go_boost
{
namespace mvvm
{

class object
    : public boost::enable_shared_from_this<object>
{
public:
    typedef object this_type;
    typedef boost::shared_ptr<this_type> ptr;
    typedef boost::weak_ptr<this_type> wptr;

public:
    virtual ~object() = 0;

protected:
    object()
        : boost::enable_shared_from_this<object>()
    {
    }
};

inline object::~object()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBJECT_HPP_INCLUDED
