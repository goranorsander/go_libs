#ifndef GO_MVVM_NOTIFY_PROPERTY_CHANGED_INTERFACE_HPP_INCLUDED
#define GO_MVVM_NOTIFY_PROPERTY_CHANGED_INTERFACE_HPP_INCLUDED

//
//  notify_property_changed_interface.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/object.hpp>
#include <go/mvvm/property_changed_arguments.hpp>
#include <go/signals/signal.hpp>
#include <go/signals/slot.hpp>

namespace go
{
namespace mvvm
{

template<class S> class basic_notify_property_changed_interface;
typedef basic_notify_property_changed_interface<std::string> notify_property_changed_interface;
typedef basic_notify_property_changed_interface<std::wstring> notify_wproperty_changed_interface;

template<class S>
class basic_notify_property_changed_interface
    : public go::signals::slot
{
public:
    typedef S string_type;
    typedef basic_notify_property_changed_interface<S> this_type;
    typedef typename go::signals::signal<std::function<void(const std::shared_ptr<object>&, const std::shared_ptr<basic_property_changed_arguments<S>>&)>> property_changed_signal;

public:
    virtual ~basic_notify_property_changed_interface() = 0;

protected:
    basic_notify_property_changed_interface() GO_DEFAULT_CONSTRUCTOR

public:
    property_changed_signal property_changed;

protected:
    virtual void notify_property_changed(const string_type& property_name) = 0;
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

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_NOTIFY_PROPERTY_CHANGED_INTERFACE_HPP_INCLUDED
