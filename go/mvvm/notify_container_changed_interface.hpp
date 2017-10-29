#ifndef GO_MVVM_NOTIFY_CONTAINER_CHANGED_INTERFACE_HPP_INCLUDED
#define GO_MVVM_NOTIFY_CONTAINER_CHANGED_INTERFACE_HPP_INCLUDED

//
//  notify_container_changed_interface.hpp
//
//  Copyright 2015-2017 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/container_changed_arguments.hpp>
#include <go/mvvm/object.hpp>
#include <go/signals/signal.hpp>
#include <go/signals/slot.hpp>

namespace go
{
namespace mvvm
{

class notify_container_changed_interface
    : public go::signals::slot
{
public:
    typedef notify_container_changed_interface this_type;
    typedef container_changed_arguments container_changed_arguments_type;
    typedef go::signals::signal<std::function<void(const std::shared_ptr<object>&, const std::shared_ptr<container_changed_arguments_type>&)>> container_changed_signal;

public:
    virtual ~notify_container_changed_interface() = 0;

protected:
    notify_container_changed_interface() GO_DEFAULT_CONSTRUCTOR

public:
    container_changed_signal container_changed;
};

inline notify_container_changed_interface::~notify_container_changed_interface()
{
    container_changed.disconnect_all_slots();
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_NOTIFY_CONTAINER_CHANGED_INTERFACE_HPP_INCLUDED
