#ifndef GO_APPLICATION_VIEW_MODEL_HPP_INCLUDED
#define GO_APPLICATION_VIEW_MODEL_HPP_INCLUDED

//
//  main_frame_view_model.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go/property.hpp>
#include <go/mvvm/object_observer_interface.hpp>

#include "fleet_repository.hpp"
#include "properties_view_model.hpp"

class main_frame_view_model
    : public m::view_model_interface
    , public m::wobservable_object
    , public m::object_wobserver_interface
    , private m::data_context_interface<fleet_repository::wptr>
    , private u::noncopyable_nonmovable
{
public:
    typedef main_frame_view_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~main_frame_view_model() = default;

private:
    main_frame_view_model(const m::wcommand_manager::ptr& command_mgr, const fleet_repository::ptr& fleet_repo, const properties_view_model::ptr& prop_vm);

public:
    p::wproperty<fleet_organization_id_type> active_spaceship_view_id;

    rop::wproperty<m::wcommand_manager::ptr> command_manager;
    rop::wproperty<m::wcommand::ptr> show_spaceship_command;
    rop::wproperty<m::wcommand::ptr> close_spaceship_command;

public:
    static ptr create(const m::wcommand_manager::ptr& command_mgr, const fleet_repository::ptr& fleet_repo, const properties_view_model::ptr& prop_vm);

    virtual void on_container_changed(const m::object::ptr& o, const m::container_changed_arguments::ptr& a);
    virtual void on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a);

protected:
    virtual void on_data_context_changing();
    virtual void on_data_context_changed();

private:
    void bind_properties();

private:
    fleet_organization_id_type _active_spaceship_view_id;
    m::wcommand_manager::wptr _command_manager;
    m::wcommand::ptr _show_spaceship_command;
    m::wcommand::ptr _close_spaceship_command;
    properties_view_model::wptr _properties_view_model;
};

#endif  // #ifndef GO_APPLICATION_VIEW_MODEL_HPP_INCLUDED
