#ifndef GO_SPACESHIP_VIEW_MODEL_HPP_INCLUDED
#define GO_SPACESHIP_VIEW_MODEL_HPP_INCLUDED

//
//  spaceship_view_model.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go/mvvm.hpp>
#include <go/property.hpp>

#include "main_frame_view_model.hpp"
#include "spaceship_model.hpp"

class spaceship_view_model
    : public m::view_model_interface
    , public m::wobservable_object
    , private m::data_context_interface<spaceship_model::ptr>
    , private u::noncopyable_nonmovable
{
public:
    typedef spaceship_view_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~spaceship_view_model() = default;

private:
    spaceship_view_model(const spaceship_model::ptr& model, const fleet_organization_id_type id, const main_frame_view_model::ptr& vm);

public:
    rop::wproperty<main_frame_view_model::ptr> main_frame_vm;
    rop::wproperty<fleet_organization_id_type> spaceship_id;

    rop::wproperty<std::wstring> spaceship_class;
    rop::wproperty<std::wstring> name;
    p::wproperty<std::wstring> captain;
    p::wproperty<unsigned int> crew_complement;
    p::wproperty<m::wobservable_deque<equipment_interface::ptr>::ptr> equipment;
    p::wproperty<equipment_interface::ptr> selected_equipment;

    rop::wproperty<m::wcommand_interface::ptr> on_activate_spaceship_view_command;
    rop::wproperty<m::wcommand_interface::ptr> on_close_spaceship_view_command;
    rop::wproperty<m::wcommand_interface::ptr> on_add_equipment_command;
    rop::wproperty<m::wcommand_interface::ptr> on_remove_equipment_command;

public:
    static ptr create(const spaceship_model::ptr& model, const fleet_organization_id_type id, const main_frame_view_model::ptr& vm);

protected:
    virtual void on_data_context_will_change();
    virtual void on_data_context_changed();

private:
    void bind_properties();

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
