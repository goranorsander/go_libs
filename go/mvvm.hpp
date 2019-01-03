#ifndef GO_MVVM_HPP_INCLUDED
#define GO_MVVM_HPP_INCLUDED

//
//  mvvm.hpp
//
//  Copyright 2015-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <go/mvvm/command_execution_observer_interface.hpp>
#include <go/mvvm/command_manager.hpp>
#include <go/mvvm/data_context_interface.hpp>
#include <go/mvvm/event_manager.hpp>
#include <go/mvvm/iterator/erase.hpp>
#include <go/mvvm/iterator/try_move_backward.hpp>
#include <go/mvvm/object_observer_interface.hpp>
#include <go/mvvm/observable_array.hpp>
#include <go/mvvm/observable_deque.hpp>
#include <go/mvvm/observable_forward_list.hpp>
#include <go/mvvm/observable_list.hpp>
#include <go/mvvm/observable_map.hpp>
#include <go/mvvm/observable_multimap.hpp>
#include <go/mvvm/observable_multiset.hpp>
#include <go/mvvm/observable_object.hpp>
#include <go/mvvm/observable_set.hpp>
#include <go/mvvm/observable_unordered_map.hpp>
#include <go/mvvm/observable_unordered_multimap.hpp>
#include <go/mvvm/observable_unordered_multiset.hpp>
#include <go/mvvm/observable_unordered_set.hpp>
#include <go/mvvm/observable_vector.hpp>
#include <go/mvvm/relay_command.hpp>
#include <go/mvvm/view_model_interface.hpp>

#endif  // #ifndef GO_MVVM_HPP_INCLUDED
