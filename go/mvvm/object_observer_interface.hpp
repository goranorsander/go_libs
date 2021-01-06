#ifndef GO_MVVM_OBJECT_OBSERVER_INTERFACE_HPP_INCLUDED
#define GO_MVVM_OBJECT_OBSERVER_INTERFACE_HPP_INCLUDED

//
//  object_observer_interface.hpp
//
//  Copyright 2015-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <string>

#include <go/mvvm/container_changed_arguments.hpp>
#include <go/mvvm/object.hpp>
#include <go/mvvm/property_changed_arguments.hpp>

namespace go
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
    basic_object_observer_interface() GO_DEFAULT_CONSTRUCTOR

public:
    virtual void on_container_changed(const std::shared_ptr<object>& /*o*/, const std::shared_ptr<container_changed_arguments>& /*a*/) = 0;
    virtual void on_property_changed(const std::shared_ptr<object>& /*o*/, const std::shared_ptr<basic_property_changed_arguments<S>>& /*a*/) = 0;
};

template<class S>
inline basic_object_observer_interface<S>::~basic_object_observer_interface()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBJECT_OBSERVER_INTERFACE_HPP_INCLUDED
