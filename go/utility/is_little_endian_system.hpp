#ifndef GO_UTILITY_IS_LITTLE_ENDIAN_SYSTEM_HPP_INCLUDED
#define GO_UTILITY_IS_LITTLE_ENDIAN_SYSTEM_HPP_INCLUDED

//
//  is_little_endian_system.hpp
//
//  Copyright 2020-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

namespace go
{
namespace utility
{

inline bool is_little_endian_system()
{
    static const char16_t endian_test = 0x0102;
    return (reinterpret_cast<const char*>(&endian_test))[0] == 0x02;
}

}
}

#endif  // #ifndef GO_UTILITY_IS_LITTLE_ENDIAN_SYSTEM_HPP_INCLUDED
