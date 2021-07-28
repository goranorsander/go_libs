#ifndef GO_MVVM_NOTIFY_VIEW_MODEL_CHANGE_INTERFACE_HPP_INCLUDED
#define GO_MVVM_NOTIFY_VIEW_MODEL_CHANGE_INTERFACE_HPP_INCLUDED

//
//  notify_view_model_change_interface.hpp
//
//  Copyright 2016-2021 Göran Orsander
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

namespace go
{
namespace mvvm
{

template<class L = std::recursive_mutex>
class notify_view_model_change_interface
{
public:
    typedef L lockable_type;
    typedef notify_view_model_change_interface<L> this_type;
    typedef go::signals::signal<void(const std::shared_ptr<view_model_changed_arguments>&)> view_model_changed_signal;
    typedef go::signals::signal<void(const std::shared_ptr<view_model_will_change_arguments>&)> view_model_will_change_signal;

public:
    virtual ~notify_view_model_change_interface() = 0;

protected:
    notify_view_model_change_interface() GO_DEFAULT_CONSTRUCTOR

public:
    view_model_will_change_signal view_model_will_change;
    view_model_changed_signal view_model_changed;
};

template<class L>
inline notify_view_model_change_interface<L>::~notify_view_model_change_interface()
{
    view_model_will_change.disconnect_all_slots();
    view_model_changed.disconnect_all_slots();
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_NOTIFY_VIEW_MODEL_CHANGE_INTERFACE_HPP_INCLUDED
