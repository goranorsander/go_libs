#ifndef GO_SPACESHIP_VIEW_MODEL_HPP_INCLUDED
#define GO_SPACESHIP_VIEW_MODEL_HPP_INCLUDED

//
//  spaceship_view_model.hpp
//
//  Copyright 2016-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/mvvm.hpp>
#include <go/property.hpp>

#include "main_frame_view_model.hpp"
#include "spaceship_model.hpp"

class spaceship_view_model
    : public m::view_model_interface<std::recursive_mutex>
    , public m::wobservable_object
    , private m::data_context_interface<spaceship_model::ptr>
    , private tt::noncopyable_nonmovable
{
public:
    typedef spaceship_view_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~spaceship_view_model() GO_DEFAULT_DESTRUCTOR

private:
    spaceship_view_model(const spaceship_model::ptr& model, const fleet_organization_id_type id, const main_frame_view_model::ptr& vm);

public:
    pro::wproperty<main_frame_view_model::ptr> main_frame_vm;
    pro::wproperty<fleet_organization_id_type> spaceship_id;

    pro::wproperty<std::wstring> spaceship_class;
    pro::wproperty<std::wstring> name;
    p::wproperty<std::wstring> captain;
    p::wproperty<unsigned int> crew_complement;
    p::wproperty<m::wobservable_deque<equipment_interface::ptr>::ptr> equipment;
    p::wproperty<equipment_interface::ptr> selected_equipment;

    pro::wproperty<m::wcommand_interface::ptr> on_activate_spaceship_view_command;
    pro::wproperty<m::wcommand_interface::ptr> on_close_spaceship_view_command;
    pro::wproperty<m::wcommand_interface::ptr> on_add_equipment_command;
    pro::wproperty<m::wcommand_interface::ptr> on_remove_equipment_command;

public:
    static ptr create(const spaceship_model::ptr& model, const fleet_organization_id_type id, const main_frame_view_model::ptr& vm);

protected:
    virtual void on_data_context_will_change() override;
    virtual void on_data_context_changed() override;

private:
    void bind_properties();

    void set_captain(const std::wstring& v);
    void set_crew_complement(const unsigned int& v);
    void set_equipment(const m::wobservable_deque<equipment_interface::ptr>::ptr& v);
    void set_selected_equipment(const equipment_interface::ptr& v);

    m::wcommand_interface::ptr get_activate_spaceship_view_command();
    bool can_execute_activate_spaceship_view_command(const m::command_parameters::ptr& p);
    void execute_activate_spaceship_view_command(const m::command_parameters::ptr& p);

    m::wcommand_interface::ptr get_close_spaceship_view_command();
    bool can_execute_close_spaceship_view_command(const m::command_parameters::ptr& p);
    void execute_close_spaceship_view_command(const m::command_parameters::ptr& p);

    m::wcommand_interface::ptr get_add_equipment_command();
    bool can_execute_add_equipment_command(const m::command_parameters::ptr& p);
    void execute_add_equipment_command(const m::command_parameters::ptr& p);

    m::wcommand_interface::ptr get_remove_equipment_command();
    bool can_execute_remove_equipment_command(const m::command_parameters::ptr& p);
    void execute_remove_equipment_command(const m::command_parameters::ptr& p);

private:
    main_frame_view_model::wptr _main_frame_vm;
    fleet_organization_id_type _spaceship_id;
    equipment_interface::ptr _selected_equipment;
    m::wcommand_interface::ptr _on_activate_spaceship_view_command;
    m::wcommand_interface::ptr _on_close_spaceship_view_command;
    m::wcommand_interface::ptr _on_add_equipment_command;
    m::wcommand_interface::ptr _on_remove_equipment_command;
};

#endif  // #ifndef GO_SPACESHIP_VIEW_MODEL_HPP_INCLUDED
