#ifndef GO_BOOST_FLEET_ORGANIZATION_VIEW_MODEL_HPP_INCLUDED
#define GO_BOOST_FLEET_ORGANIZATION_VIEW_MODEL_HPP_INCLUDED

//
//  fleet_organization_view_model.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go_boost/mvvm.hpp>
#include <go_boost/property.hpp>

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
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

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

    void on_select_fleet_organization_event(const m::wevent::ptr& e);

    main_frame_view_model::ptr get_main_frame_vm() const;
    void set_main_frame_vm(const main_frame_view_model::ptr& v);
    fleet_organization_id_type get_selected_fleet_organization_id() const;
    void set_selected_fleet_organization_id(const fleet_organization_id_type& v);
    fleet_organization_interface::ptr get_fleet_organization_root() const;

    m::wcommand_interface::ptr get_on_left_double_click_command();
    bool can_execute_on_left_double_click_command(const m::command_parameters::ptr& p);
    void execute_on_left_double_click_command(const m::command_parameters::ptr& p);

private:
    main_frame_view_model::wptr _main_frame_vm;
    fleet_organization_id_type _selected_fleet_organization_id;
    mutable m::wcommand_interface::ptr _on_left_double_click_command;
    m::event_subscription_key_type _select_fleet_organization_event_key;
};

#endif  // #ifndef GO_BOOST_FLEET_ORGANIZATION_VIEW_MODEL_HPP_INCLUDED
