#ifndef GO_DIAGNOSTICS_LOG_DETAIL_SPIN_LOCK_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_DETAIL_SPIN_LOCK_HPP_INCLUDED

//
//  spin_lock.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/utility/noncopyable_nonmovable.hpp>

#include <atomic>

namespace go
{
namespace diagnostics
{
namespace log
{
namespace detail
{

struct spin_lock
    : go::utility::noncopyable_nonmovable
{
    virtual ~spin_lock()
    {
        _flag.clear(std::memory_order_release);
    }

    spin_lock(std::atomic_flag& flag)
        : go::utility::noncopyable_nonmovable()
        , _flag(flag)
    {
        while (_flag.test_and_set(std::memory_order_acquire))
        {
        }
    }

private:
    std::atomic_flag& _flag;
};

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_DETAIL_SPIN_LOCK_HPP_INCLUDED
