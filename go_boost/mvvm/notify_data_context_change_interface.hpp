#ifndef GO_BOOST_MVVM_NOTIFY_DATA_CONTEXT_CHANGE_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_NOTIFY_DATA_CONTEXT_CHANGE_INTERFACE_HPP_INCLUDED

//
//  notify_data_context_change_interface.hpp
//
//  Copyright 2015-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/mvvm/data_context_changed_arguments.hpp>
#include <go_boost/mvvm/data_context_will_change_arguments.hpp>
#include <go_boost/signals.hpp>

namespace go_boost
{
namespace mvvm
{

template<class L = go_boost::utility::recursive_spin_lock>
class notify_data_context_change_interface
{
public:
    typedef L lockable_type;
    typedef notify_data_context_change_interface<L> this_type;
    typedef boost::signals2::signal<void(const boost::shared_ptr<data_context_changed_arguments>&)> data_context_changed_signal;
    typedef boost::signals2::signal<void(const boost::shared_ptr<data_context_will_change_arguments>&)> data_context_will_change_signal;

public:
    virtual ~notify_data_context_change_interface() = 0;

protected:
    notify_data_context_change_interface()
    {
    }

public:
    data_context_will_change_signal data_context_will_change;
    data_context_changed_signal data_context_changed;
};

template<class L>
inline notify_data_context_change_interface<L>::~notify_data_context_change_interface()
{
    data_context_will_change.disconnect_all_slots();
    data_context_changed.disconnect_all_slots();
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_NOTIFY_DATA_CONTEXT_CHANGE_INTERFACE_HPP_INCLUDED
