#ifndef GO_BOOST_STRING_ENCODING_UCS4_HPP_INCLUDED
#define GO_BOOST_STRING_ENCODING_UCS4_HPP_INCLUDED

//
//  ucs4.hpp
//
//  Copyright 2020-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/string/u2string.hpp>
#include <go_boost/string/u8string.hpp>

namespace go_boost
{
namespace string
{
namespace encoding
{

struct ucs4_tag {};

}
}
}

#endif  // #ifndef GO_BOOST_STRING_ENCODING_UCS4_HPP_INCLUDED
