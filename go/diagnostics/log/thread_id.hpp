#ifndef GO_DIAGNOSTICS_LOG_THREAD_ID_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_THREAD_ID_HPP_INCLUDED

//
//  thread_id.hpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <thread>

namespace go
{
namespace diagnostics
{
namespace log
{

inline std::thread::id this_thread_id()
{
#if defined(GO_NO_CXX11_THREAD_LOCAL_STORAGE)
    return std::this_thread::get_id();
#else
    static thread_local const std::thread::id id = std::this_thread::get_id();
    return id;
#endif  // #if defined(GO_NO_CXX11_THREAD_LOCAL_STORAGE)
}

} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_THREAD_ID_HPP_INCLUDED
