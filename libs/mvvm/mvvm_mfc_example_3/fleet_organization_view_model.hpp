#ifndef GO_FLEET_ORGANIZATION_VIEW_MODEL_HPP_INCLUDED
#define GO_FLEET_ORGANIZATION_VIEW_MODEL_HPP_INCLUDED

//
//  fleet_organization_view_model.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/mvvm.hpp>
#include <go/property.hpp>

#include "fleet_organization_interface.hpp"
#include "main_frame_view_model.hpp"

class fleet_organization_view_model
    : public m::view_model_interface
    , public m::wobservable_object
    , private m::data_context_interface<fleet_organization_interface::ptr>
    , private u::noncopyable_nonmovable
{
public:
    typedef fleet_organization_view_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~fleet_organization_view_model();

private:
    fleet_organization_view_model();

public:
    p::wproperty<main_frame_view_model::ptr> main_frame_vm;
    p::wproperty<fleet_organization_id_type> selected_fleet_organization_id;

    rop::wproperty<m::wcommand_interface::ptr> on_left_double_click_command;

    nrop::property<fleet_organization_interface::ptr> fleet_organization_root;

public:
    static ptr create();

    void set_data_context(const fleet_organization_interface::ptr& context);

protected:
    virtual void on_data_context_will_change();
    virtual void on_data_context_changed();

private:
    void bind_properties();
    void subscribe_events();
    void unsubscribe_events();

private:
    main_frame_view_model::wptr _main_frame_vm;
    fleet_organization_id_type _selected_fleet_organization_id;
    m::wcommand_interface::ptr _on_left_double_click_command;
    m::event_subscription_key_type _select_fleet_organization_event_key;
};

#endif  // #ifndef GO_FLEET_ORGANIZATION_VIEW_MODEL_HPP_INCLUDED
