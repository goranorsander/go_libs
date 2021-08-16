#ifndef GO_MVVM_EVENT_SUBSCRIPTION_KEY_INCLUDED
#define GO_MVVM_EVENT_SUBSCRIPTION_KEY_INCLUDED

//
//  event_subscription_key.hpp
//
//  Copyright 2019-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/type_traits/fundamental_type_specializer.hpp>

namespace go
{
namespace mvvm
{

#if !defined(GO_NO_CXX11_FUNDAMENTAL_TYPE_SPECIALIZER)

GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(event_subscription_key, uint3264_t)

#else

GO_IMPLEMENT_UNSIGNED_INTEGER_TYPE_SPECIALIZER(event_subscription_key, uint3264_t)

#endif  // #if !defined(GO_NO_CXX11_FUNDAMENTAL_TYPE_SPECIALIZER)

inline void reset(event_subscription_key& key)
{
    key = event_subscription_key();
}

inline bool is_null_key(const event_subscription_key& key)
{
    static GO_THREAD_LOCAL event_subscription_key null_key = event_subscription_key();
    return key == null_key;
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_EVENT_SUBSCRIPTION_KEY_INCLUDED
