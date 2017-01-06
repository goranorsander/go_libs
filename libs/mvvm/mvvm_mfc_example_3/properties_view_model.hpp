#ifndef GO_PROPERTIES_VIEW_MODEL_HPP_INCLUDED
#define GO_PROPERTIES_VIEW_MODEL_HPP_INCLUDED

//
//  properties_view_model.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go/mvvm.hpp>

#include "fleet_organization_model.hpp"
#include "main_frame_view_model.hpp"

class properties_view_model
    : public m::view_model_interface
    , public m::wobservable_object
    , public m::object_wobserver_interface
    , private m::data_context_interface<fleet_organization_model::ptr>
    , private u::noncopyable_nonmovable
{
public:
    typedef properties_view_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~properties_view_model();

private:
    properties_view_model();

public:
    p::wproperty<main_frame_view_model::ptr> main_frame_vm;
    rop::wproperty<fleet_organization_interface::ptr> fleet_organization;

public:
    static ptr create();

    void set_data_context(const fleet_organization_model::ptr& context);

protected:
    virtual void on_data_context_will_change();
    virtual void on_data_context_changed();
    virtual void on_container_changed(const m::object::ptr& o, const m::container_changed_arguments::ptr& a);
    virtual void on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a);

private:
    void bind_properties();
    void subscribe_events();
    void unsubscribe_events();

private:
    main_frame_view_model::wptr _main_frame_vm;
    s::slot_key_type _on_data_context_property_changed_slot_key;
    m::event_subscription_key_type _select_fleet_organization_event_key;
};

#endif  // #ifndef GO_PROPERTIES_VIEW_MODEL_HPP_INCLUDED
