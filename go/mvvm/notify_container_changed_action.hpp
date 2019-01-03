#ifndef GO_MVVM_NOTIFY_CONTAINER_CHANGED_INTERFACE_ACTION_HPP_INCLUDED
#define GO_MVVM_NOTIFY_CONTAINER_CHANGED_INTERFACE_ACTION_HPP_INCLUDED

//
//  notify_container_changed_action.hpp
//
//  Copyright 2015-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

namespace go
{
namespace mvvm
{

enum class notify_container_changed_action
    : int8_t
{
    add,
    remove,
    reset,
    swap,
    undefined = ~0
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_NOTIFY_CONTAINER_CHANGED_INTERFACE_ACTION_HPP_INCLUDED
