#ifndef GO_BOOST_UTILITY_IS_LITTLE_ENDIAN_SYSTEM_HPP_INCLUDED
#define GO_BOOST_UTILITY_IS_LITTLE_ENDIAN_SYSTEM_HPP_INCLUDED

//
//  is_little_endian_system.hpp
//
//  Copyright 2020-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

namespace go_boost
{
namespace utility
{

inline bool is_little_endian_system()
{
    static const short endian_test = 0x0102;
    return (reinterpret_cast<const char*>(&endian_test))[0] == 0x02;
}

}
}

#endif  // #ifndef GO_BOOST_UTILITY_IS_LITTLE_ENDIAN_SYSTEM_HPP_INCLUDED
