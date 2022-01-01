#ifndef GO_BOOST_UTILITY_HPP_INCLUDED
#define GO_BOOST_UTILITY_HPP_INCLUDED

//
//  type_traits.hpp
//
//  Copyright 2019-2022 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/type_traits/fundamental_type_implicit_specializer.hpp>
#include <go_boost/type_traits/fundamental_type_specializer.hpp>
#include <go_boost/type_traits/is_auto_ptr.hpp>
#include <go_boost/type_traits/is_intrusive_ptr.hpp>
#include <go_boost/type_traits/is_scoped_array.hpp>
#include <go_boost/type_traits/is_scoped_ptr.hpp>
#include <go_boost/type_traits/is_shared_array.hpp>
#include <go_boost/type_traits/is_shared_ptr.hpp>
#include <go_boost/type_traits/is_smart_ptr.hpp>
#include <go_boost/type_traits/is_unique_ptr.hpp>
#include <go_boost/type_traits/is_weak_ptr.hpp>
#include <go_boost/type_traits/noncopyable.hpp>
#include <go_boost/type_traits/noncopyable_nonmovable.hpp>
#include <go_boost/type_traits/nonmovable.hpp>

#endif  // #ifndef GO_BOOST_UTILITY_HPP_INCLUDED
