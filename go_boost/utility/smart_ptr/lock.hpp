#ifndef GO_BOOST_UTILITY_SMART_PTR_LOCK_HPP_INCLUDED
#define GO_BOOST_UTILITY_SMART_PTR_LOCK_HPP_INCLUDED

//
//  lock.hpp
//
//  Copyright 2020-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace go_boost
{
namespace utility
{
namespace smart_ptr
{

template<typename T>
inline boost::shared_ptr<T> lock(const boost::shared_ptr<T>& sp)
{
    return sp;
}

template<typename T>
inline boost::shared_ptr<T> lock(const boost::weak_ptr<T>& wp)
{
    return wp.lock();
}

}
}
}

#endif  // #ifndef GO_BOOST_UTILITY_SMART_PTR_LOCK_HPP_INCLUDED
