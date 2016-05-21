#ifndef GO_BOOST_MVVM_NOTIFY_CONTAINER_CHANGED_HPP_INCLUDED
#define GO_BOOST_MVVM_NOTIFY_CONTAINER_CHANGED_HPP_INCLUDED

//
//  notify_container_changed.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/signals2.hpp>
#include <go_boost/mvvm/container_changed_arguments.hpp>
#include <go_boost/mvvm/object.hpp>
#include <go_boost/signals/slot.hpp>

namespace go_boost
{
namespace mvvm
{

class notify_container_changed
    : public go_boost::signals::slot
{
public:
    typedef notify_container_changed this_type;
    typedef container_changed_arguments container_changed_arguments_type;
    typedef typename boost::shared_ptr<container_changed_arguments_type> container_changed_arguments_type_ptr;
    typedef typename boost::signals2::signal<void(const object::ptr&, const container_changed_arguments_type_ptr&)> container_changed_signal;

public:
    virtual ~notify_container_changed() = 0;

protected:
    notify_container_changed()
        : go_boost::signals::slot()
    {
    }

public:
    container_changed_signal container_changed;
};

inline notify_container_changed::~notify_container_changed()
{
    container_changed.disconnect_all_slots();
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_NOTIFY_CONTAINER_CHANGED_HPP_INCLUDED
