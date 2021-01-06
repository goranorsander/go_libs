#ifndef GO_UTILITY_SMART_PTR_LOCK_HPP_INCLUDED
#define GO_UTILITY_SMART_PTR_LOCK_HPP_INCLUDED

//
//  lock.hpp
//
//  Copyright 2020-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#ifdef HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef HAS_PRAGMA_ONCE

#include <memory>

namespace go
{
namespace utility
{
namespace smart_ptr
{

template<typename T>
inline std::shared_ptr<T> lock(const std::shared_ptr<T>& sp)
{
    return sp;
}

template<typename T>
inline std::shared_ptr<T> lock(const std::weak_ptr<T>& wp)
{
    return wp.lock();
}

}
}
}

#endif  // #ifndef GO_UTILITY_SMART_PTR_LOCK_HPP_INCLUDED
