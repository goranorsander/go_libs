#ifndef GO_BOOST_MVVM_NOTIFY_PROPERTY_CHANGED_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_NOTIFY_PROPERTY_CHANGED_INTERFACE_HPP_INCLUDED

//
//  notify_property_changed_interface.hpp
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
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/signals2.hpp>
#include <go_boost/mvvm/object.hpp>
#include <go_boost/mvvm/property_changed_arguments.hpp>
#include <go_boost/signals/slot.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S> class basic_notify_property_changed_interface;
typedef basic_notify_property_changed_interface<std::string> notify_property_changed_interface;
typedef basic_notify_property_changed_interface<std::wstring> notify_wproperty_changed_interface;

template<class S>
class basic_notify_property_changed_interface
    : public go_boost::signals::slot
{
public:
    typedef S string_type;
    typedef basic_notify_property_changed_interface<S> this_type;
    typedef typename boost::signals2::signal<void(const boost::shared_ptr<object>&, const boost::shared_ptr<basic_property_changed_arguments<S>>&)> property_changed_signal;

public:
    virtual ~basic_notify_property_changed_interface() = 0;

protected:
    basic_notify_property_changed_interface();

public:
    property_changed_signal property_changed;
};

template<>
inline basic_notify_property_changed_interface<std::string>::~basic_notify_property_changed_interface()
{
    property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<std::wstring>::~basic_notify_property_changed_interface()
{
    property_changed.disconnect_all_slots();
}

template<class S>
inline basic_notify_property_changed_interface<S>::~basic_notify_property_changed_interface()
{
    property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<std::string>::basic_notify_property_changed_interface()
    : go_boost::signals::slot()
{
}

template<>
inline basic_notify_property_changed_interface<std::wstring>::basic_notify_property_changed_interface()
    : go_boost::signals::slot()
{
}

template<class S>
inline basic_notify_property_changed_interface<S>::basic_notify_property_changed_interface()
    : go_boost::signals::slot()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_NOTIFY_PROPERTY_CHANGED_INTERFACE_HPP_INCLUDED
