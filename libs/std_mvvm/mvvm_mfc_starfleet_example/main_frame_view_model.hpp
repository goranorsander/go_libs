#ifndef GO_APPLICATION_VIEW_MODEL_HPP_INCLUDED
#define GO_APPLICATION_VIEW_MODEL_HPP_INCLUDED

//
//  main_frame_view_model.hpp
//
//  Copyright 2016-2021 Göran Orsander
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

using dialog_view_container_type = m::observable_set<dialog_view::ptr>;

class main_frame_view_model
    : public m::view_model_interface<std::recursive_mutex>
    , public m::wobservable_object
    , private m::data_context_interface<fleet_repository::wptr>
    , private tt::noncopyable_nonmovable
{
public:
    using this_type = main_frame_view_model;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

public:
    virtual ~main_frame_view_model();

private:
    main_frame_view_model(mdi_frame_interface::pointer mdi_frame_mgr, const m::wcommand_manager::ptr& command_mgr, const m::wevent_manager::ptr& event_mgr, const fleet_repository::ptr& fleet_repo);

public:
    pnro::value_property<mdi_frame_interface::pointer> mdi_frame_manager;
    pnro::value_property<m::wcommand_manager::ptr> command_manager;
    pnro::value_property<m::wevent_manager::ptr> event_manager;
    pnro::value_property<fleet_repository_interface::ptr> fleet_repository;

    pn::value_property<dialog_view_container_type::ptr> dialogs;

    pro::wproperty<m::wcommand_interface::ptr> open_add_equipment_view_command;
    pro::wproperty<m::wcommand_interface::ptr> delete_dialog_view_command;

public:
    static ptr create(mdi_frame_interface::pointer mdi_frame_mgr, const m::wcommand_manager::ptr& command_mgr, const m::wevent_manager::ptr& event_mgr, const fleet_repository::ptr& fleet_repo);

protected:
    virtual void on_data_context_will_change() override;
    virtual void on_data_context_changed() override;

private:
    void bind_properties();
    void subscribe_events();
    void unsubscribe_events();

private:
    m::wcommand_interface::ptr _open_add_equipment_view_command;
    m::wcommand_interface::ptr _delete_dialog_view_command;
    m::event_subscription_key _close_spaceship_event_key;
    m::event_subscription_key _show_spaceship_event_key;
};

#endif  // #ifndef GO_APPLICATION_VIEW_MODEL_HPP_INCLUDED
