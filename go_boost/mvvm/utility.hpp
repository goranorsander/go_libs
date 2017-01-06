#ifndef GO_BOOST_MVVM_UTILITY_HPP_INCLUDED
#define GO_BOOST_MVVM_UTILITY_HPP_INCLUDED

//
//  utility.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(GO_BOOST_MSVC_MFC)
#include <go_boost/mvvm/utility/mfc_dlgdata.hpp>
#endif  // #if defined(GO_BOOST_MSVC_MFC)

#include <go_boost/mvvm/utility/phoenix_property_get_relay_command_functor.hpp>
#include <go_boost/mvvm/utility/phoenix_property_set_value_notify_changed_functor.hpp>
#include <go_boost/mvvm/utility/phoenix_property_value_access_functor.hpp>

#endif  // #ifndef GO_BOOST_MVVM_UTILITY_HPP_INCLUDED
