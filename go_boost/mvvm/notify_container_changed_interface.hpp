#ifndef GO_BOOST_MVVM_NOTIFY_CONTAINER_CHANGED_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_NOTIFY_CONTAINER_CHANGED_INTERFACE_HPP_INCLUDED

//
//  notify_container_changed_interface.hpp
//
//  Copyright 2015-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/mvvm/container_changed_arguments.hpp>
#include <go_boost/mvvm/object.hpp>
#include <go_boost/signals.hpp>

namespace go_boost
{
namespace mvvm
{

template<class L = boost::recursive_mutex>
class notify_container_changed_interface
{
public:
    typedef L lockable_type;
    typedef notify_container_changed_interface<L> this_type;
    typedef boost::signals2::signal<void(const boost::shared_ptr<object>&, const boost::shared_ptr<container_changed_arguments>&)> container_changed_signal;

public:
    virtual ~notify_container_changed_interface() = 0;

protected:
    notify_container_changed_interface()
    {
    }

public:
    container_changed_signal container_changed;

protected:
    virtual void notify_container_changed(const notify_container_changed_action& action, const std::size_t& added_elements, const std::size_t& removed_elements, const std::size_t& new_size) = 0;
};

template<class L>
inline notify_container_changed_interface<L>::~notify_container_changed_interface()
{
    container_changed.disconnect_all_slots();
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_NOTIFY_CONTAINER_CHANGED_INTERFACE_HPP_INCLUDED
