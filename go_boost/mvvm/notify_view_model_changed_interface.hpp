#ifndef GO_BOOST_MVVM_NOTIFY_VIEW_MODEL_CHANGED_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_NOTIFY_VIEW_MODEL_CHANGED_INTERFACE_HPP_INCLUDED

//
//  notify_view_model_changed_interface.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/signals2.hpp>
#include <go_boost/mvvm/view_model_changed_arguments.hpp>
#include <go_boost/mvvm/view_model_will_change_arguments.hpp>
#include <go_boost/signals/slot.hpp>

namespace go_boost
{
namespace mvvm
{

class notify_view_model_changed_interface
    : public go_boost::signals::slot
{
public:
    typedef notify_view_model_changed_interface this_type;
    typedef boost::signals2::signal<void(const boost::shared_ptr<view_model_changed_arguments>&)> view_model_changed_signal;
    typedef boost::signals2::signal<void(const boost::shared_ptr<view_model_will_change_arguments>&)> view_model_will_change_signal;

public:
    virtual ~notify_view_model_changed_interface() = 0;

protected:
    notify_view_model_changed_interface()
    {
    }

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
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_NOTIFY_VIEW_MODEL_CHANGED_INTERFACE_HPP_INCLUDED
