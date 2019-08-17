#ifndef GO_UTILITY_HPP_INCLUDED
#define GO_UTILITY_HPP_INCLUDED

//
//  utility.hpp
//
//  Copyright 2015-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <go/utility/exchange.hpp>
#include <go/utility/min_max.hpp>
#include <go/utility/monitor.hpp>
#include <go/utility/noncopyable.hpp>
#include <go/utility/noncopyable_nonmovable.hpp>
#include <go/utility/nonmovable.hpp>
#include <go/utility/placebo_lockable.hpp>
#include <go/utility/primitive_type_implicit_specializer.hpp>
#include <go/utility/primitive_type_specializer.hpp>
#include <go/utility/recursive_spin_lock.hpp>
#include <go/utility/sanity.hpp>
#include <go/utility/scope_guard.hpp>
#include <go/utility/scope_guard_new.hpp>
#include <go/utility/spin_lock.hpp>
#include <go/utility/string_cast.hpp>
#include <go/utility/u2string.hpp>
#include <go/utility/u8string.hpp>
#include <go/utility/value_guard.hpp>

#include <go/utility/container/circular_buffer.hpp>
#include <go/utility/container/size.hpp>

#include <go/utility/iterator/erase.hpp>
#include <go/utility/iterator/reverse.hpp>
#include <go/utility/iterator/try_move_backward.hpp>

#include <go/utility/string/algorithm.hpp>
#include <go/utility/string/ascii.hpp>
#include <go/utility/string/create.hpp>
#include <go/utility/string/format.hpp>
#include <go/utility/string/iso_8859_1.hpp>
#include <go/utility/string/ucs2.hpp>
#include <go/utility/string/windows_1252.hpp>

#endif  // #ifndef GO_UTILITY_HPP_INCLUDED
