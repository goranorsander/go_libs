//
//  spaceship_view_model.cpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "spaceship_view_model.hpp"
#include "activate_spaceship_command_parameters.hpp"
#include "add_equipment_command_parameters.hpp"
#include "close_spaceship_command_parameters.hpp"
#include "close_spaceship_event.hpp"
#include "equipment_model.hpp"
#include "open_add_equipment_view_command_parameters.hpp"
#include "remove_equipment_command_parameters.hpp"
#include "select_fleet_organization_event.hpp"

#include <functional>

spaceship_view_model::spaceship_view_model(const spaceship_model::ptr& model, const fleet_organization_id_type id, const main_frame_view_model::ptr& vm)
    : m::view_model_interface()
    , m::wobservable_object()
    , m::data_context_interface<spaceship_model::ptr>(model)
    , u::noncopyable_nonmovable()
    , main_frame_vm(L"spaceship_view_model::main_frame_vm")
    , spaceship_id(L"spaceship_view_model::spaceship_id")
    , spaceship_class(L"spaceship_view_model::spaceship_class")
    , name(L"spaceship_view_model::name")
    , captain(L"spaceship_view_model::captain")
    , crew_complement(L"spaceship_view_model::crew_complement")
    , equipment(L"spaceship_view_model::equipment")
    , selected_equipment(L"spaceship_view_model::selected_equipment")
    , on_activate_spaceship_view_command(L"spaceship_view_model::on_activate_spaceship_view_command")
    , on_close_spaceship_view_command(L"spaceship_view_model::on_close_spaceship_view_command")
    , on_add_equipment_command(L"spaceship_view_model::on_add_equipment_command")
    , on_remove_equipment_command(L"spaceship_view_model::on_remove_equipment_command")
    , _main_frame_vm(vm)
    , _spaceship_id(id)
    , _selected_equipment()
    , _on_activate_spaceship_view_command()
    , _on_close_spaceship_view_command()
    , _on_add_equipment_command()
    , _on_remove_equipment_command()
{
    bind_properties();
}

spaceship_view_model::ptr spaceship_view_model::create(const spaceship_model::ptr& model, const fleet_organization_id_type id, const main_frame_view_model::ptr& vm)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler(const spaceship_model::ptr& model, const fleet_organization_id_type& id, const main_frame_view_model::ptr& vm) : this_type(model, id, vm) {}
    };

    return std::make_shared<make_shared_enabler, const spaceship_model::ptr&, const fleet_organization_id_type&, const main_frame_view_model::ptr&>(model, id, vm);
}

void spaceship_view_model::on_data_context_will_change()
{
    m::data_context_interface<spaceship_model::ptr>::on_data_context_will_change();
    on_view_model_will_change();
}

void spaceship_view_model::on_data_context_changed()
{
    m::data_context_interface<spaceship_model::ptr>::on_data_context_changed();
    on_view_model_changed();
}

void spaceship_view_model::bind_properties()
{
    main_frame_vm.getter([this]() -> main_frame_view_model::ptr { return _main_frame_vm.lock(); });
    spaceship_id.getter([this]() -> fleet_organization_id_type { return _spaceship_id; });
    spaceship_class.getter([this]() -> std::wstring { if(data_context()) { return data_context()->spaceship_class; } return std::wstring(); });
    name.getter([this]() -> std::wstring { if(data_context()) { return data_context()->name; } return std::wstring(); });
    captain.getter([this]() -> std::wstring { if(data_context()) { return data_context()->captain; } return std::wstring(); });
    captain.setter([this](const std::wstring& v) { if(data_context() && v != data_context()->captain()) { data_context()->captain = v; notify_property_changed(captain.name()); } });
    crew_complement.getter([this]() -> unsigned int { if(data_context()) { return data_context()->crew_complement; } return 0; });
    crew_complement.setter([this](const unsigned int& v) { if(data_context() && v != data_context()->crew_complement()) { data_context()->crew_complement = v; notify_property_changed(crew_complement.name()); } });
    equipment.getter([this]() -> m::wobservable_deque<equipment_interface::ptr>::ptr { if(data_context()) { return data_context()->equipment; } return nullptr; });
    equipment.setter([this](const m::wobservable_deque<equipment_interface::ptr>::ptr& v) { if(data_context() && v != data_context()->equipment()) { data_context()->equipment = v; notify_property_changed(equipment.name()); } });
    selected_equipment.getter([this]() -> equipment_interface::ptr { return _selected_equipment; });
    selected_equipment.setter(
        [this](const equipment_interface::ptr& v)
        {
            if(_selected_equipment != v)
            {
                _selected_equipment = v;
                notify_property_changed(selected_equipment.name());
            }
        });
    on_activate_spaceship_view_command.getter(
        [this]()
        {
            _on_activate_spaceship_view_command = m::relay_wcommand::create(L"spaceship_view_model::on_activate_spaceship_view",
                [this](const m::command_parameters::ptr& p)
                {
                    activate_spaceship_command_parameters::ptr cmd_params = std::dynamic_pointer_cast<activate_spaceship_command_parameters>(p);
                    if(cmd_params)
                    {
                        main_frame_view_model::ptr vm = _main_frame_vm.lock();
                        if(vm)
                        {
                            m::wevent_manager::ptr event_mgr = vm->event_manager();
                            if(event_mgr)
                            {
                                event_mgr->post(select_fleet_organization_event::create(cmd_params->id, L"spaceship_view_model"));
                            }
                        }
                    }
                },
                [this](const m::command_parameters::ptr& p)
                {
                    activate_spaceship_command_parameters::ptr params = std::dynamic_pointer_cast<activate_spaceship_command_parameters>(p);
                    if(params)
                    {
                        return params->id == _spaceship_id;
                    }
                    return false;
                },
                activate_spaceship_command_parameters::create(_spaceship_id));
            return _on_activate_spaceship_view_command;
        });
    on_close_spaceship_view_command.getter(
        [this]()
        {
            _on_close_spaceship_view_command = m::relay_wcommand::create(L"spaceship_view_model::on_close_spaceship_view",
                [this](const m::command_parameters::ptr& p)
                {
                    close_spaceship_command_parameters::ptr cmd_params = std::dynamic_pointer_cast<close_spaceship_command_parameters>(p);
                    if(cmd_params)
                    {
                        main_frame_view_model::ptr vm = _main_frame_vm.lock();
                        if(vm)
                        {
                            m::wevent_manager::ptr event_mgr = vm->event_manager();
                            if(event_mgr)
                            {
                                event_mgr->post(close_spaceship_event::create(cmd_params->spaceship_vm));
                            }
                        }
                    }
                },
                [this](const m::command_parameters::ptr& p)
                {
                    close_spaceship_command_parameters::ptr params = std::dynamic_pointer_cast<close_spaceship_command_parameters>(p);
                    if(params)
                    {
                        return params->spaceship_vm()->spaceship_id == _spaceship_id;
                    }
                    return false;
                },
                close_spaceship_command_parameters::create(std::dynamic_pointer_cast<spaceship_view_model>(shared_from_this())));
            return _on_close_spaceship_view_command;
        });
    on_add_equipment_command.getter(
        [this]()
        {
            _on_add_equipment_command = m::relay_wcommand::create(L"spaceship_view_model::on_add_equipment_command",
                [this](const m::command_parameters::ptr& p)
                {
                    main_frame_view_model::ptr vm = _main_frame_vm.lock();
                    if(vm)
                    {
                        m::wcommand_manager::ptr command_mgr = vm->command_manager();
                        if(command_mgr)
                        {
                            m::wcommand_interface::ptr commander_ = vm->open_add_equipment_view_command;
                            std::dynamic_pointer_cast<open_add_equipment_view_command_parameters>(commander_->parameters())->spaceship = data_context();
                            command_mgr->post(commander_);
                        }
                    }
                },
                [this](const m::command_parameters::ptr& p)
                {
                    add_equipment_command_parameters::ptr params = std::dynamic_pointer_cast<add_equipment_command_parameters>(p);
                    if(params)
                    {
                        return params->spaceship_id == _spaceship_id;
                    }
                    return false;
                },
                add_equipment_command_parameters::create(_spaceship_id));
            return _on_add_equipment_command;
        });
    on_remove_equipment_command.getter(
        [this]()
        {
            _on_remove_equipment_command = m::relay_wcommand::create(L"spaceship_view_model::on_remove_equipment_command",
                [this](const m::command_parameters::ptr& p)
                {
                    remove_equipment_command_parameters::ptr cmd_params = std::dynamic_pointer_cast<remove_equipment_command_parameters>(p);
                    if(cmd_params)
                    {
                        const equipment_id_type equipment_id = cmd_params->equipment_id;
                        if (std::dynamic_pointer_cast<equipment_model>(selected_equipment())->id == equipment_id)
                        {
                            selected_equipment = nullptr;
                        }
                        m::wobservable_deque<equipment_interface::ptr>::iterator it = std::find_if(equipment()->begin(), equipment()->end(), [equipment_id](const auto& e) { return std::dynamic_pointer_cast<equipment_model>(e)->id == equipment_id; });
                        if (it != equipment()->end())
                        {
                            equipment()->erase(it);
                        }
                    }
                },
                [this](const m::command_parameters::ptr& p)
                {
                    remove_equipment_command_parameters::ptr params = std::dynamic_pointer_cast<remove_equipment_command_parameters>(p);
                    if(params)
                    {
                        return params->spaceship_id == _spaceship_id;
                    }
                    return false;
                },
                remove_equipment_command_parameters::create(_spaceship_id, std::dynamic_pointer_cast<equipment_model>(selected_equipment())->id));
            return _on_remove_equipment_command;
        });
}
