#ifndef GO_BOOST_MVVM_NOTIFY_CONTAINER_CHANGED_INTERFACE_ACTION_HPP_INCLUDED
#define GO_BOOST_MVVM_NOTIFY_CONTAINER_CHANGED_INTERFACE_ACTION_HPP_INCLUDED

//
//  notify_container_changed_action.hpp
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
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

namespace go_boost
{
namespace mvvm
{

enum notify_container_changed_action
{
    notify_container_changed_action_add,
    notify_container_changed_action_remove,
    notify_container_changed_action_reset,
    notify_container_changed_action_swap,
    undefined_notify_container_changed_action = ~0
};

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_NOTIFY_CONTAINER_CHANGED_INTERFACE_ACTION_HPP_INCLUDED
