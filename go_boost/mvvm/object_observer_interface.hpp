#ifndef GO_BOOST_MVVM_OBJECT_OBSERVER_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_OBJECT_OBSERVER_INTERFACE_HPP_INCLUDED

//
//  object_observer_interface.hpp
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

#include <string>

#include <go_boost/mvvm/container_changed_arguments.hpp>
#include <go_boost/mvvm/object.hpp>
#include <go_boost/mvvm/property_changed_arguments.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S> class basic_object_observer_interface;
typedef basic_object_observer_interface<std::string> object_observer_interface;
typedef basic_object_observer_interface<std::wstring> object_wobserver_interface;

template<class S>
class basic_object_observer_interface
{
public:
    typedef S string_type;
    typedef basic_object_observer_interface<S> this_type;

public:
    virtual ~basic_object_observer_interface() = 0;

protected:
    basic_object_observer_interface();

public:
    virtual void on_container_changed(const boost::shared_ptr<object>& /*o*/, const boost::shared_ptr<container_changed_arguments>& /*a*/) = 0;
    virtual void on_property_changed(const boost::shared_ptr<object>& /*o*/, const boost::shared_ptr<basic_property_changed_arguments<S>>& /*a*/) = 0;
};

template<class S>
inline basic_object_observer_interface<S>::~basic_object_observer_interface()
{
}

template<class S>
inline basic_object_observer_interface<S>::basic_object_observer_interface()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBJECT_OBSERVER_INTERFACE_HPP_INCLUDED
