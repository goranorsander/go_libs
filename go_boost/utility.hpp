#ifndef GO_BOOST_UTILITY_HPP_INCLUDED
#define GO_BOOST_UTILITY_HPP_INCLUDED

//
//  utility.hpp
//
//  Copyright 2015-2018 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/utility/noncopyable_nonmovable.hpp>
#include <go_boost/utility/nonmovable.hpp>
#include <go_boost/utility/placebo_lockable.hpp>
#include <go_boost/utility/primitive_type_implicit_specializer.hpp>
#include <go_boost/utility/primitive_type_specializer.hpp>
#include <go_boost/utility/sanity.hpp>
#include <go_boost/utility/scope_guard.hpp>
#include <go_boost/utility/scope_guard_new.hpp>
#include <go_boost/utility/string_cast.hpp>
#include <go_boost/utility/u2string.hpp>
#include <go_boost/utility/u8string.hpp>
#include <go_boost/utility/u16string.hpp>
#include <go_boost/utility/u32string.hpp>
#include <go_boost/utility/value_guard.hpp>

#include <go_boost/utility/container/size.hpp>

#include <go_boost/utility/iterator/erase.hpp>
#include <go_boost/utility/iterator/try_move_backward.hpp>

#include <go_boost/utility/string/algorithm.hpp>
#include <go_boost/utility/string/ascii.hpp>
#include <go_boost/utility/string/create.hpp>
#include <go_boost/utility/string/iso_8859_1.hpp>
#include <go_boost/utility/string/ucs2.hpp>
#include <go_boost/utility/string/windows_1252.hpp>

#endif  // #ifndef GO_BOOST_UTILITY_HPP_INCLUDED
