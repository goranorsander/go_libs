#ifndef GO_SIGNALS_SLOT_KEY_HPP_INCLUDED
#define GO_SIGNALS_SLOT_KEY_HPP_INCLUDED

//
//  slot_key.hpp
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

#include <go/utility/primitive_type_specializer.hpp>

namespace go
{
namespace signals
{

GO_IMPLEMENT_UNSIGNED_INTEGER_TYPE_SPECIALIZER(slot_key, uint3264_t, 0)

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
