#ifndef GO_BOOST_MVVM_HPP_INCLUDED
#define GO_BOOST_MVVM_HPP_INCLUDED

//
//  mvvm.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <go_boost/mvvm/command_execution_observer_interface.hpp>
#include <go_boost/mvvm/command_manager.hpp>
#include <go_boost/mvvm/data_context_interface.hpp>
#include <go_boost/mvvm/event_manager.hpp>
#include <go_boost/mvvm/object_observer_interface.hpp>
#include <go_boost/mvvm/observable_array.hpp>
#include <go_boost/mvvm/observable_deque.hpp>
#include <go_boost/mvvm/observable_forward_list.hpp>
#include <go_boost/mvvm/observable_list.hpp>
#include <go_boost/mvvm/observable_map.hpp>
#include <go_boost/mvvm/observable_multimap.hpp>
#include <go_boost/mvvm/observable_multiset.hpp>
#include <go_boost/mvvm/observable_object.hpp>
#include <go_boost/mvvm/observable_set.hpp>
#include <go_boost/mvvm/observable_unordered_map.hpp>
#include <go_boost/mvvm/observable_unordered_multimap.hpp>
#include <go_boost/mvvm/observable_unordered_multiset.hpp>
#include <go_boost/mvvm/observable_unordered_set.hpp>
#include <go_boost/mvvm/observable_vector.hpp>
#include <go_boost/mvvm/relay_command.hpp>
#include <go_boost/mvvm/view_model_interface.hpp>

#endif  // #ifndef GO_BOOST_MVVM_HPP_INCLUDED
