#ifndef GO_BOOST_MVVM_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_BOOST_MVVM_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  command_parameters.hpp
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
namespace mvvm
{

class command_parameters
    : public boost::noncopyable
{
public:
    typedef command_parameters this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~command_parameters()
    {
    }

protected:
    command_parameters()
        : boost::noncopyable()
    {
    }

public:
    static ptr create()
    {
        return ptr(new command_parameters());
    }
};

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_COMMAND_PARAMETERS_HPP_INCLUDED
