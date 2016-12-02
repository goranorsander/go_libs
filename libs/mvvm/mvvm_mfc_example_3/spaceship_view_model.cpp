//
//  spaceship_view_model.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "spaceship_view_model.hpp"
#include "close_spaceship_command_parameters.hpp"

#include <functional>

spaceship_view_model::spaceship_view_model(const spaceship_model::ptr& model, const fleet_organization_id_type id, const main_frame_view_model::ptr& main_frame_vm)
    : m::view_model_interface()
    , m::wobservable_object()
    , m::data_context_interface<spaceship_model::ptr>(model)
    , u::noncopyable_nonmovable()
    , main_frame_view_model(L"spaceship_view_model::main_frame_view_model")
    , spaceship_id(L"spaceship_view_model::spaceship_id")
    , spaceship_class(L"spaceship_view_model::spaceship_class")
    , name(L"spaceship_view_model::name")
    , captain(L"spaceship_view_model::captain")
    , crew_complement(L"spaceship_view_model::crew_complement")
    , equipment(L"spaceship_view_model::equipment")
    , on_close_spaceship_view_command(L"spaceship_view_model::on_close_spaceship_view_command")
    , _main_frame_view_model(main_frame_vm)
    , _spaceship_id(id)
    , _on_close_spaceship_view_command()
{
    bind_properties();
}

spaceship_view_model::ptr spaceship_view_model::create(const spaceship_model::ptr& model, const fleet_organization_id_type id, const main_frame_view_model::ptr& main_frame_vm)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler(const spaceship_model::ptr& model, const fleet_organization_id_type& id, const main_frame_view_model::ptr& main_frame_vm) : this_type(model, id, main_frame_vm) {}
    };

    return std::make_shared<make_shared_enabler, const spaceship_model::ptr&, const fleet_organization_id_type&, const main_frame_view_model::ptr&>(model, id, main_frame_vm);
}

void spaceship_view_model::on_data_context_changing()
{
    m::data_context_interface<spaceship_model::ptr>::on_data_context_changing();
    on_view_model_changing();
}

void spaceship_view_model::on_data_context_changed()
{
    m::data_context_interface<spaceship_model::ptr>::on_data_context_changed();
    on_view_model_changed();
}

void spaceship_view_model::bind_properties()
{
    main_frame_view_model.getter([this]() -> main_frame_view_model::ptr { return _main_frame_view_model.lock(); });
    spaceship_id.getter([this]() -> fleet_organization_id_type { return _spaceship_id; });
    spaceship_class.getter([this]() -> std::wstring { if(data_context()) { return data_context()->spaceship_class; } return std::wstring(); });
    name.getter([this]() -> std::wstring { if(data_context()) { return data_context()->name; } return std::wstring(); });
    captain.getter([this]() -> std::wstring { if(data_context()) { return data_context()->captain; } return std::wstring(); });
    captain.setter([this](const std::wstring& v) { if(data_context() && v != data_context()->captain()) { data_context()->captain = v; on_property_changed(captain.name()); } });
    crew_complement.getter([this]() -> unsigned int { if(data_context()) { return data_context()->crew_complement; } return 0; });
    crew_complement.setter([this](const unsigned int& v) { if(data_context() && v != data_context()->crew_complement()) { data_context()->crew_complement = v; on_property_changed(crew_complement.name()); } });
    equipment.getter([this]() -> m::wobservable_list<equipment_interface::ptr>::ptr { if(data_context()) { return data_context()->equipment; } return nullptr; });
    equipment.setter([this](const m::wobservable_list<equipment_interface::ptr>::ptr& v) { if(data_context() && v != data_context()->equipment()) { data_context()->equipment = v; on_property_changed(equipment.name()); } });
    on_close_spaceship_view_command.getter(
        [this]()
        {
            _on_close_spaceship_view_command = m::relay_wcommand::create(L"spaceship_view_model::on_close_spaceship_view",
                [this](const m::command_parameters::ptr& p)
                {
                    main_frame_view_model::ptr main_frame_vm = _main_frame_view_model.lock();
                    if(main_frame_vm)
                    {
                        m::wcommand_manager::ptr command_manager = main_frame_vm->command_manager();
                        if(command_manager)
                        {
                            m::wcommand::ptr close_spaceship = main_frame_vm->close_spaceship_command;
                            if(close_spaceship)
                            {
                                close_spaceship_command_parameters::ptr this_cmd_params = std::dynamic_pointer_cast<close_spaceship_command_parameters>(p);
                                close_spaceship_command_parameters::ptr close_spaceship_params = std::dynamic_pointer_cast<close_spaceship_command_parameters>(close_spaceship->parameters());
                                if(this_cmd_params && close_spaceship_params)
                                {
                                    close_spaceship_params->spaceship_view_model = this_cmd_params->spaceship_view_model;
                                    command_manager->issue_command(close_spaceship);
                                }
                            }
                        }
                    }
                },
                [this](const m::command_parameters::ptr& p)
                {
                    close_spaceship_command_parameters::ptr params = std::dynamic_pointer_cast<close_spaceship_command_parameters>(p);
                    if(params)
                    {
                        return static_cast<bool>(params->spaceship_view_model());
                    }
                    return false;
                },
                close_spaceship_command_parameters::create(std::dynamic_pointer_cast<spaceship_view_model>(shared_from_this())));
            return _on_close_spaceship_view_command;
        });
}
