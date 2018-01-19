#ifndef GO_MVVM_NOTIFY_VIEW_MODEL_CHANGED_INTERFACE_HPP_INCLUDED
#define GO_MVVM_NOTIFY_VIEW_MODEL_CHANGED_INTERFACE_HPP_INCLUDED

//
//  notify_view_model_changed_interface.hpp
//
//  Copyright 2016-2018 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/view_model_changed_arguments.hpp>
#include <go/mvvm/view_model_will_change_arguments.hpp>
#include <go/signals/signal.hpp>
#include <go/signals/slot.hpp>

namespace go
{
namespace mvvm
{

class notify_view_model_changed_interface
    : public go::signals::slot
{
public:
    typedef notify_view_model_changed_interface this_type;
    typedef go::signals::signal<std::function<void(const std::shared_ptr<view_model_changed_arguments>&)>> view_model_changed_signal;
    typedef go::signals::signal<std::function<void(const std::shared_ptr<view_model_will_change_arguments>&)>> view_model_will_change_signal;

public:
    virtual ~notify_view_model_changed_interface() = 0;

protected:
    notify_view_model_changed_interface() GO_DEFAULT_CONSTRUCTOR

public:
    view_model_will_change_signal view_model_will_change;
    view_model_changed_signal view_model_changed;
};

inline notify_view_model_changed_interface::~notify_view_model_changed_interface()
{
    view_model_will_change.disconnect_all_slots();
    view_model_changed.disconnect_all_slots();
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_NOTIFY_VIEW_MODEL_CHANGED_INTERFACE_HPP_INCLUDED
