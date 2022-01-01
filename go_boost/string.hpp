#ifndef GO_BOOST_STRING_HPP_INCLUDED
#define GO_BOOST_STRING_HPP_INCLUDED

//
//  string.hpp
//
//  Copyright 2020-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/string/algorithm.hpp>
#include <go_boost/string/create.hpp>
#include <go_boost/string/string_cast.hpp>
#include <go_boost/string/u2string.hpp>
#include <go_boost/string/u8string.hpp>
#include <go_boost/string/u16string.hpp>
#include <go_boost/string/u32string.hpp>

#include <go_boost/string/encoding/ascii.hpp>
#include <go_boost/string/encoding/iso_8859_1.hpp>
#include <go_boost/string/encoding/ucs2.hpp>
#include <go_boost/string/encoding/utf8.hpp>
#include <go_boost/string/encoding/utf16.hpp>
#include <go_boost/string/encoding/utf32.hpp>
#include <go_boost/string/encoding/windows_1252.hpp>

#endif  // #ifndef GO_BOOST_STRING_HPP_INCLUDED
