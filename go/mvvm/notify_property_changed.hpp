#ifndef GO_MVVM_NOTIFY_PROPERTY_CHANGED_HPP_INCLUDED
#define GO_MVVM_NOTIFY_PROPERTY_CHANGED_HPP_INCLUDED

//
//  notify_property_changed.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/mvvm/object.hpp>
#include <go/mvvm/property_changed_arguments.hpp>
#include <go/signals/signal.hpp>
#include <go/signals/slot.hpp>

namespace go
{
namespace mvvm
{

template<class S>
class basic_notify_property_changed
    : public go::signals::slot
{
public:
    typedef S string_type;
    typedef basic_notify_property_changed<string_type> this_type;
    typedef basic_property_changed_arguments<string_type> property_changed_arguments_type;
    typedef std::shared_ptr<property_changed_arguments_type> property_changed_arguments_type_ptr;
    typedef go::signals::signal<std::function<void(const object::ptr&, const property_changed_arguments_type_ptr&)>> property_changed_signal;

public:
    virtual ~basic_notify_property_changed() = 0;

protected:
    basic_notify_property_changed()
        : go::signals::slot()
    {
    }

public:
    property_changed_signal property_changed;
};

template<class S>
inline basic_notify_property_changed<S>::~basic_notify_property_changed()
{
    property_changed.disconnect_all_slots();
}

class notify_property_changed
    : public basic_notify_property_changed<std::string>
{
public:
    typedef notify_property_changed this_type;

public:
    virtual ~notify_property_changed() = 0;

protected:
    notify_property_changed()
        : basic_notify_property_changed<string_type>()
    {
    }
};

inline notify_property_changed::~notify_property_changed()
{
}

class notify_wproperty_changed
    : public basic_notify_property_changed<std::wstring>
{
public:
    typedef notify_wproperty_changed this_type;

public:
    virtual ~notify_wproperty_changed() = 0;

protected:
    notify_wproperty_changed()
        : basic_notify_property_changed<string_type>()
    {
    }
};

inline notify_wproperty_changed::~notify_wproperty_changed()
{
}

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_NOTIFY_PROPERTY_CHANGED_HPP_INCLUDED
