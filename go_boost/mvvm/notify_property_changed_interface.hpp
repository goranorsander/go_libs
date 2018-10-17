#ifndef GO_BOOST_MVVM_NOTIFY_PROPERTY_CHANGED_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_NOTIFY_PROPERTY_CHANGED_INTERFACE_HPP_INCLUDED

//
//  notify_property_changed_interface.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/mvvm/object.hpp>
#include <go_boost/mvvm/property_changed_arguments.hpp>
#include <go_boost/signals.hpp>

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

protected:
    virtual void notify_property_changed(const boost::shared_ptr<object>& object, const string_type& property_name);
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

template<>
inline void basic_notify_property_changed_interface<std::string>::notify_property_changed(const boost::shared_ptr<object>& object, const std::string& property_name)
{
    if (!property_changed.empty())
    {
        property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<std::wstring>::notify_property_changed(const boost::shared_ptr<object>& object, const std::wstring& property_name)
{
    if (!property_changed.empty())
    {
        property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<class S>
inline void basic_notify_property_changed_interface<S>::notify_property_changed(const boost::shared_ptr<object>&, const string_type& property_name)
{
    if (!property_changed.empty())
    {
        property_changed(shared_from_this(), basic_property_changed_arguments<string_type>::create(property_name));
    }
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_NOTIFY_PROPERTY_CHANGED_INTERFACE_HPP_INCLUDED
