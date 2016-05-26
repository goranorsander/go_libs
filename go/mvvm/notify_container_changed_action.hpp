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

#if (GO_COMP_MSVC) && (_MSC_VER <= 1800)
#pragma message("C++11/14 is not supported by this compiler")
#else

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

#endif // C++11/14 is not supported by this compiler

#endif  // #ifndef GO_MVVM_NOTIFY_CONTAINER_CHANGED_ACTION_HPP_INCLUDED
