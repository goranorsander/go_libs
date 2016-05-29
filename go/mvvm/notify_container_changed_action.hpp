#ifndef GO_MVVM_NOTIFY_CONTAINER_CHANGED_ACTION_HPP_INCLUDED
#define GO_MVVM_NOTIFY_CONTAINER_CHANGED_ACTION_HPP_INCLUDED

//
//  notify_container_changed_action.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

namespace go
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
} // namespace go

#endif  // #ifndef GO_MVVM_NOTIFY_CONTAINER_CHANGED_ACTION_HPP_INCLUDED
