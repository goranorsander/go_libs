#ifndef GO_UTILITY_SMART_PTR_EQUAL_HPP_INCLUDED
#define GO_UTILITY_SMART_PTR_EQUAL_HPP_INCLUDED

//
//  equal.hpp
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

template<typename T1, typename T2>
inline bool equal(const std::shared_ptr<T1>& sp1, const std::shared_ptr<T2>& sp2)
{
    return sp1.get() == sp2.get();
}

template<typename T1, typename T2>
inline bool equal(const std::shared_ptr<T1>& sp1, const std::weak_ptr<T2>& wp2)
{
    return sp1.get() == wp2.lock().get();
}

template<typename T1, typename T2>
inline bool equal(const std::weak_ptr<T1>& wp1, const std::shared_ptr<T2>& sp2)
{
    return wp1.lock().get() == sp2.get();
}

template<typename T1, typename T2>
inline bool equal(const std::weak_ptr<T1>& wp1, const std::weak_ptr<T2>& wp2)
{
    return wp1.lock().get() == wp2.lock().get();
}

}
}
}

#endif  // #ifndef GO_UTILITY_SMART_PTR_EQUAL_HPP_INCLUDED
