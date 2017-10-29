#ifndef GO_BOOST_MVVM_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_BOOST_MVVM_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  command_parameters.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <go_boost/utility/noncopyable_nonmovable.hpp>

namespace go_boost
{
namespace mvvm
{

class command_parameters
    : private go_boost::utility::noncopyable_nonmovable
{
public:
    typedef command_parameters this_type;
    typedef boost::shared_ptr<this_type> ptr;
    typedef boost::weak_ptr<this_type> wptr;

public:
    virtual ~command_parameters() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
    command_parameters()
        : go_boost::utility::noncopyable_nonmovable()
    {
    }

public:
    static ptr create()
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            make_shared_enabler() GO_BOOST_DEFAULT_CONSTRUCTOR
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
