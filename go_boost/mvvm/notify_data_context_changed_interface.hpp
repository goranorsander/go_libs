#ifndef GO_BOOST_MVVM_NOTIFY_DATA_CONTEXT_CHANGED_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_NOTIFY_DATA_CONTEXT_CHANGED_INTERFACE_HPP_INCLUDED

//
//  notify_data_context_changed_interface.hpp
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
#endif

#include <boost/signals2.hpp>
#include <go_boost/mvvm/data_context_changed_arguments.hpp>
#include <go_boost/mvvm/data_context_will_change_arguments.hpp>
#include <go_boost/signals/slot.hpp>

namespace go_boost
{
namespace mvvm
{

class notify_data_context_changed_interface
    : public go_boost::signals::slot
{
public:
    typedef notify_data_context_changed_interface this_type;
    typedef boost::signals2::signal<void(const boost::shared_ptr<data_context_changed_arguments>&)> data_context_changed_signal;
    typedef boost::signals2::signal<void(const boost::shared_ptr<data_context_will_change_arguments>&)> data_context_will_change_signal;

public:
    virtual ~notify_data_context_changed_interface() = 0;

protected:
    notify_data_context_changed_interface()
    {
    }

public:
    data_context_will_change_signal data_context_will_change;
    data_context_changed_signal data_context_changed;
};

inline notify_data_context_changed_interface::~notify_data_context_changed_interface()
{
    data_context_will_change.disconnect_all_slots();
    data_context_changed.disconnect_all_slots();
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_NOTIFY_DATA_CONTEXT_CHANGED_INTERFACE_HPP_INCLUDED
