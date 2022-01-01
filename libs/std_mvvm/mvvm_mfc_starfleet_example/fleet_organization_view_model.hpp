#ifndef GO_FLEET_ORGANIZATION_VIEW_MODEL_HPP_INCLUDED
#define GO_FLEET_ORGANIZATION_VIEW_MODEL_HPP_INCLUDED

//
//  fleet_organization_view_model.hpp
//
//  Copyright 2016-2022 Göran Orsander
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
    : public m::view_model_interface<std::recursive_mutex>
    , public m::wobservable_object
    , private m::data_context_interface<fleet_organization_interface::ptr>
    , private tt::noncopyable_nonmovable
{
public:
    using this_type = fleet_organization_view_model;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

public:
    virtual ~fleet_organization_view_model();

private:
    fleet_organization_view_model();

public:
    p::wproperty<main_frame_view_model::ptr> main_frame_vm;
    p::wproperty<fleet_organization_id_type> selected_fleet_organization_id;

    pro::wproperty<m::wcommand_interface::ptr> on_left_double_click_command;

    pnro::property<fleet_organization_interface::ptr> fleet_organization_root;

public:
    static ptr create();

    void set_data_context(const fleet_organization_interface::ptr& context);

protected:
    virtual void on_data_context_will_change() override;
    virtual void on_data_context_changed() override;

private:
    void bind_properties();
    void subscribe_events();
    void unsubscribe_events();

    void set_main_frame_vm(const main_frame_view_model::ptr& v);
    void set_selected_fleet_organization_id(const fleet_organization_id_type& v);

    m::wcommand_interface::ptr get_on_left_double_click_command();
    bool can_execute_on_left_double_click_command(const m::command_parameters::ptr& p);
    void execute_on_left_double_click_command(const m::command_parameters::ptr& p);

private:
    main_frame_view_model::wptr _main_frame_vm;
    fleet_organization_id_type _selected_fleet_organization_id;
    m::wcommand_interface::ptr _on_left_double_click_command;
    m::event_subscription_key _select_fleet_organization_event_key;
};

#endif  // #ifndef GO_FLEET_ORGANIZATION_VIEW_MODEL_HPP_INCLUDED
