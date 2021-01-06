#ifndef GO_BOOST_MVVM_UTILITY_HPP_INCLUDED
#define GO_BOOST_MVVM_UTILITY_HPP_INCLUDED

//
//  utility.hpp
//
//  Copyright 2015-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#if defined(GO_BOOST_MSVC_MFC)
#include <go_boost/mvvm/utility/mfc_dlgdata.hpp>
#endif  // #if defined(GO_BOOST_MSVC_MFC)

#include <go_boost/mvvm/utility/phoenix_property_get_relay_command_functor.hpp>
#include <go_boost/mvvm/utility/phoenix_property_set_value_notify_changed_functor.hpp>
#include <go_boost/mvvm/utility/phoenix_property_value_access_functor.hpp>

#endif  // #ifndef GO_BOOST_MVVM_UTILITY_HPP_INCLUDED
