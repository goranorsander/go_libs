#ifndef GO_BOOST_MVVM_ARGUMENTS_HPP_INCLUDED
#define GO_BOOST_MVVM_ARGUMENTS_HPP_INCLUDED

//
//  arguments.hpp
//
//  Copyright 2015-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/type_traits/noncopyable_nonmovable.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace go_boost
{
namespace mvvm
{

class arguments
    : go_boost::type_traits::noncopyable_nonmovable
{
public:
    typedef boost::shared_ptr<arguments> ptr;
    typedef boost::weak_ptr<arguments> wptr;

public:
    virtual ~arguments() = 0;

protected:
    arguments()
        : go_boost::type_traits::noncopyable_nonmovable()
    {
    }
};

inline arguments::~arguments()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_ARGUMENTS_HPP_INCLUDED
