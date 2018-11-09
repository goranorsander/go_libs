#ifndef GO_APPLICATION_VIEW_MODEL_HPP_INCLUDED
#define GO_APPLICATION_VIEW_MODEL_HPP_INCLUDED

//
//  main_frame_view_model.hpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/property.hpp>
#include <go/mvvm/object_observer_interface.hpp>

#include "fleet_repository.hpp"
#include "mdi_frame_interface.hpp"

typedef m::observable_set<dialog_view::ptr> dialog_view_container_type;

class main_frame_view_model
    : public m::view_model_interface<u::placebo_mutex>
    , public mst::wobservable_object
    , private m::data_context_interface<fleet_repository::wptr>
    , private u::noncopyable_nonmovable
{
public:
    typedef main_frame_view_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~main_frame_view_model();

private:
    main_frame_view_model(mdi_frame_interface::pointer mdi_frame_mgr, const mst::wcommand_manager::ptr& command_mgr, const mst::wevent_manager::ptr& event_mgr, const fleet_repository::ptr& fleet_repo);

public:
    nrop::value_property<mdi_frame_interface::pointer> mdi_frame_manager;
    nrop::value_property<mst::wcommand_manager::ptr> command_manager;
    nrop::value_property<mst::wevent_manager::ptr> event_manager;
    nrop::value_property<fleet_repository_interface::ptr> fleet_repository;

    np::value_property<dialog_view_container_type::ptr> dialogs;

    rop::wproperty<mst::wcommand_interface::ptr> open_add_equipment_view_command;
    rop::wproperty<mst::wcommand_interface::ptr> delete_dialog_view_command;

public:
    static ptr create(mdi_frame_interface::pointer mdi_frame_mgr, const mst::wcommand_manager::ptr& command_mgr, const mst::wevent_manager::ptr& event_mgr, const fleet_repository::ptr& fleet_repo);

protected:
    virtual void on_data_context_will_change();
    virtual void on_data_context_changed();

private:
    void bind_properties();
    void subscribe_events();
    void unsubscribe_events();

private:
    mst::wcommand_interface::ptr _open_add_equipment_view_command;
    mst::wcommand_interface::ptr _delete_dialog_view_command;
    m::event_subscription_key_type _close_spaceship_event_key;
    m::event_subscription_key_type _show_spaceship_event_key;
};

#endif  // #ifndef GO_APPLICATION_VIEW_MODEL_HPP_INCLUDED
