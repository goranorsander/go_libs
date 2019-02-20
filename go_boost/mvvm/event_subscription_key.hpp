#ifndef GO_BOOST_MVVM_EVENT_SUBSCRIPTION_KEY_INCLUDED
#define GO_BOOST_MVVM_EVENT_SUBSCRIPTION_KEY_INCLUDED

//
//  event_subscription_key.hpp
//
//  Copyright 2019 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/utility/primitive_type_specializer.hpp>

namespace go_boost
{
namespace mvvm
{

GO_BOOST_IMPLEMENT_UNSIGNED_INTEGER_TYPE_SPECIALIZER(event_subscription_key, uint3264_t, 0)

inline void reset(event_subscription_key& key)
{
    key = event_subscription_key();
}

inline bool is_null_key(const event_subscription_key& key)
{
    static event_subscription_key null_key;
    return key == null_key;
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_EVENT_SUBSCRIPTION_KEY_INCLUDED
