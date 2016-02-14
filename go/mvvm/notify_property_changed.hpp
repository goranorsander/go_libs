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
#include <go/mvvm/signal.hpp>
#include <go/mvvm/slot.hpp>

namespace go
{
namespace mvvm
{

template<class S = std::string>
class notify_property_changed
    : public slot
{
public:
    typedef S string_type;
    typedef property_changed_arguments<string_type> property_changed_arguments_type;
    typedef std::shared_ptr<property_changed_arguments_type> property_changed_arguments_type_ptr;
    typedef signal<std::function<void(const object::ptr&, const property_changed_arguments_type_ptr&)>> property_changed_signal;

public:
    virtual ~notify_property_changed() = 0
    {
        property_changed.disconnect_all_slots();
    }

protected:
    notify_property_changed()
    {
    }

public:
    property_changed_signal property_changed;
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_NOTIFY_PROPERTY_CHANGED_HPP_INCLUDED
