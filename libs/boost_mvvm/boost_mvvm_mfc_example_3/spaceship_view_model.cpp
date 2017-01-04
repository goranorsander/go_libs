//
//  spaceship_view_model.cpp
//
//  Copyright 2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "spaceship_view_model.hpp"
#include "activate_spaceship_command_parameters.hpp"
#include "close_spaceship_command_parameters.hpp"
#include "close_spaceship_event.hpp"
#include "select_fleet_organization_event.hpp"

spaceship_view_model::~spaceship_view_model()
{
}

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
    , on_activate_spaceship_view_command(L"spaceship_view_model::on_activate_spaceship_view_command")
    , on_close_spaceship_view_command(L"spaceship_view_model::on_close_spaceship_view_command")
    , _main_frame_vm(vm)
    , _spaceship_id(id)
    , _on_activate_spaceship_view_command()
    , _on_close_spaceship_view_command()
{
    bind_properties();
}

spaceship_view_model::ptr spaceship_view_model::create(const spaceship_model::ptr& model, const fleet_organization_id_type id, const main_frame_view_model::ptr& vm)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler(const spaceship_model::ptr& model, const fleet_organization_id_type& id, const main_frame_view_model::ptr& vm) : this_type(model, id, vm) {}
    };

    return boost::make_shared<make_shared_enabler, const spaceship_model::ptr&, const fleet_organization_id_type&, const main_frame_view_model::ptr&>(model, id, vm);
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
    main_frame_vm.getter(boost::bind(&this_type::get_main_frame_vm, this));
    spaceship_id.getter(boost::bind(&this_type::get_spaceship_id, this));
    spaceship_class.getter(boost::bind(&this_type::get_spaceship_class, this));
    name.getter(boost::bind(&this_type::get_name, this));
    captain.getter(boost::bind(&this_type::get_captain, this));
    captain.setter(boost::bind(&this_type::set_captain, this, _1));
    crew_complement.getter(boost::bind(&this_type::get_crew_complement, this));
    crew_complement.setter(boost::bind(&this_type::set_crew_complement, this, _1));
    equipment.getter(boost::bind(&this_type::get_equipment, this));
    equipment.setter(boost::bind(&this_type::set_equipment, this, _1));
    on_activate_spaceship_view_command.getter(boost::bind(&this_type::get_activate_spaceship_view_command, this));
    on_close_spaceship_view_command.getter(boost::bind(&this_type::get_close_spaceship_view_command, this));
}

main_frame_view_model::ptr spaceship_view_model::get_main_frame_vm() const
{
    return _main_frame_vm.lock();
}

fleet_organization_id_type spaceship_view_model::get_spaceship_id() const
{
    return _spaceship_id;
}

std::wstring spaceship_view_model::get_spaceship_class() const
{
    if(data_context())
    {
        return data_context()->spaceship_class;
    }
    return std::wstring();
}

std::wstring spaceship_view_model::get_name() const
{
    if(data_context())
    {
        return data_context()->name;
    }
    return std::wstring();
}

std::wstring spaceship_view_model::get_captain() const
{
    if(data_context())
    {
        return data_context()->captain;
    }
    return std::wstring();
}

void spaceship_view_model::set_captain(const std::wstring& v)
{
    if(data_context() && v != data_context()->captain())
    {
        data_context()->captain = v;
        on_property_changed(captain.name());
    }
}

unsigned int spaceship_view_model::get_crew_complement() const
{
    if(data_context())
    {
        return data_context()->crew_complement;
    }
    return 0;
}

void spaceship_view_model::set_crew_complement(const unsigned int& v)
{
    if(data_context() && v != data_context()->crew_complement())
    {
        data_context()->crew_complement = v;
        on_property_changed(crew_complement.name());
    }
}

m::wobservable_list<equipment_interface::ptr>::ptr spaceship_view_model::get_equipment() const
{
    if(data_context())
    {
        return data_context()->equipment;
    }
    return m::wobservable_list<equipment_interface::ptr>::ptr();
}

void spaceship_view_model::set_equipment(const m::wobservable_list<equipment_interface::ptr>::ptr& v)
{
    if(data_context() && v != data_context()->equipment())
    {
        data_context()->equipment = v;
        on_property_changed(equipment.name());
    }
}

m::wcommand_interface::ptr spaceship_view_model::get_activate_spaceship_view_command()
{
    _on_activate_spaceship_view_command = m::relay_wcommand::create(L"spaceship_view_model::on_activate_spaceship_view",
        boost::bind(&this_type::execute_activate_spaceship_view_command, this, _1),
        boost::bind(&this_type::can_execute_activate_spaceship_view_command, this, _1),
        activate_spaceship_command_parameters::create(_spaceship_id));
    return _on_activate_spaceship_view_command;
}

bool spaceship_view_model::can_execute_activate_spaceship_view_command(const m::command_parameters::ptr& p)
{
    activate_spaceship_command_parameters::ptr params = boost::dynamic_pointer_cast<activate_spaceship_command_parameters>(p);
    if(params)
    {
        return params->id == _spaceship_id;
    }
    return false;
}

void spaceship_view_model::execute_activate_spaceship_view_command(const m::command_parameters::ptr& p)
{
    activate_spaceship_command_parameters::ptr cmd_params = boost::dynamic_pointer_cast<activate_spaceship_command_parameters>(p);
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
}

m::wcommand_interface::ptr spaceship_view_model::get_close_spaceship_view_command()
{
    ptr spaceship_vm = boost::dynamic_pointer_cast<this_type, m::object>(shared_from_this());
    _on_close_spaceship_view_command = m::relay_wcommand::create(L"spaceship_view_model::on_close_spaceship_view",
        boost::bind(&this_type::execute_close_spaceship_view_command, this, _1),
        boost::bind(&this_type::can_execute_close_spaceship_view_command, this, _1),
        close_spaceship_command_parameters::create(spaceship_vm));
    return _on_close_spaceship_view_command;
}

bool spaceship_view_model::can_execute_close_spaceship_view_command(const m::command_parameters::ptr& p)
{
    close_spaceship_command_parameters::ptr params = boost::dynamic_pointer_cast<close_spaceship_command_parameters>(p);
    if(params)
    {
        return params->spaceship_vm()->spaceship_id == _spaceship_id;
    }
    return false;
}

void spaceship_view_model::execute_close_spaceship_view_command(const m::command_parameters::ptr& p)
{
    close_spaceship_command_parameters::ptr cmd_params = boost::dynamic_pointer_cast<close_spaceship_command_parameters>(p);
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
}
