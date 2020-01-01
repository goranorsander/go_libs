#ifndef GO_BOOST_DIAGNOSTICS_LOG_THREAD_ID_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_THREAD_ID_HPP_INCLUDED

//
//  thread_id.hpp
//
//  Copyright 2018-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/thread.hpp>

namespace go_boost
{
namespace diagnostics
{
namespace log
{

inline boost::thread::id this_thread_id()
{
#if defined(GO_BOOST_NO_CXX11_THREAD_LOCAL_STORAGE)
    return boost::this_thread::get_id();
#else
    static thread_local const boost::thread::id id = boost::this_thread::get_id();
    return id;
#endif  // #if defined(GO_BOOST_NO_CXX11_THREAD_LOCAL_STORAGE)
}

} // namespace log
} // namespace diagnostics
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_THREAD_ID_HPP_INCLUDED
