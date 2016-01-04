#ifndef GO_MVVM_NOTIFY_CONTAINER_CHANGED_ACTION_HPP_INCLUDED
#define GO_MVVM_NOTIFY_CONTAINER_CHANGED_ACTION_HPP_INCLUDED

//
//  notify_container_changed_action.hpp
//
//  Copyright 2015 G�ran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

namespace go
{
namespace mvvm
{

enum notify_container_changed_action
{
    notify_container_changed_action_add,
    notify_container_changed_action_move,
    notify_container_changed_action_remove,
    notify_container_changed_action_replace,
    notify_container_changed_action_reset,
    undefined_notify_container_changed_action = ~0
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_NOTIFY_CONTAINER_CHANGED_ACTION_HPP_INCLUDED
