#ifndef GO_MVVM_NOTIFY_CONTAINER_CHANGED_INTERFACE_ACTION_HPP_INCLUDED
#define GO_MVVM_NOTIFY_CONTAINER_CHANGED_INTERFACE_ACTION_HPP_INCLUDED

//
//  notify_container_changed_action.hpp
//
//  Copyright 2015-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_STRONGLY_TYPED_ENUM)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

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

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_NOTIFY_CONTAINER_CHANGED_INTERFACE_ACTION_HPP_INCLUDED
