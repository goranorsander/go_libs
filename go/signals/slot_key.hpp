#ifndef GO_SIGNALS_SLOT_KEY_HPP_INCLUDED
#define GO_SIGNALS_SLOT_KEY_HPP_INCLUDED

//
//  slot_key.hpp
//
//  Copyright 2018-2020 Göran Orsander
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
namespace signals
{

#if !defined(GO_NO_CXX11_FUNDAMENTAL_TYPE_SPECIALIZER)

GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(slot_key, uint3264_t)

#else

GO_IMPLEMENT_UNSIGNED_INTEGER_TYPE_SPECIALIZER(slot_key, uint3264_t)

#endif  // #if !defined(GO_NO_CXX11_FUNDAMENTAL_TYPE_SPECIALIZER)

inline void reset(slot_key& key)
{
    key = slot_key();
}

inline bool is_null_key(const slot_key& key)
{
    static slot_key null_key;
    return key == null_key;
}

} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_SLOT_KEY_HPP_INCLUDED
