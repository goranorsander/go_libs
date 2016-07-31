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

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/make_shared.hpp>
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
    typedef boost::shared_ptr<this_type> ptr;
    typedef boost::weak_ptr<this_type> wptr;

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
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() {}
            make_shared_enabler()
                : this_type()
            {
            }
        };

        return boost::make_shared<make_shared_enabler>();
#else
        return boost::shared_ptr<this_type>(new this_type());
#endif // BOOST_MSVC > 1500
    }
};

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_COMMAND_PARAMETERS_HPP_INCLUDED
