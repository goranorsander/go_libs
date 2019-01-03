//
//  spaceship_view_model.cpp
//
//  Copyright 2016-2019 Göran Orsander
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

namespace
{

class matches_equipment_id
    : std::unary_function<equipment_interface::ptr, bool>
{
public:
    virtual ~matches_equipment_id() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit matches_equipment_id(const equipment_id_type id)
        : std::unary_function<equipment_interface::ptr, bool>()
        , _id(id)
    {
    }

    bool operator()(const equipment_interface::ptr& v) const
    {
        return boost::dynamic_pointer_cast<equipment_model>(v)->id == _id;
    }

private:
    const equipment_id_type _id;
};

}

spaceship_view_model::~spaceship_view_model()
{
}

spaceship_view_model::spaceship_view_model(const spaceship_model::ptr& model, const fleet_organization_id_type id, const main_frame_view_model::ptr& vm)
    : m::view_model_interface<u::placebo_lockable>()
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
}

spaceship_view_model::ptr spaceship_view_model::create(const spaceship_model::ptr& model, const fleet_organization_id_type id, const main_frame_view_model::ptr& vm)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler(const spaceship_model::ptr& model, const fleet_organization_id_type& id, const main_frame_view_model::ptr& vm) : this_type(model, id, vm) {}
    };

    spaceship_view_model::ptr view_model = boost::make_shared<make_shared_enabler, const spaceship_model::ptr&, const fleet_organization_id_type&, const main_frame_view_model::ptr&>(model, id, vm);
#else
    spaceship_view_model::ptr view_model = boost::shared_ptr<this_type>(new this_type(model, id, vm));
#endif // BOOST_MSVC > 1500
    view_model->bind_properties();
    return view_model;
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
    selected_equipment.getter(boost::bind(&this_type::get_selected_equipment, this));
    selected_equipment.setter(boost::bind(&this_type::set_selected_equipment, this, _1));
    on_activate_spaceship_view_command.getter(boost::bind(&this_type::get_activate_spaceship_view_command, this));
    on_close_spaceship_view_command.getter(boost::bind(&this_type::get_close_spaceship_view_command, this));
    on_add_equipment_command.getter(boost::bind(&this_type::get_add_equipment_command, this));
    on_remove_equipment_command.getter(boost::bind(&this_type::get_remove_equipment_command, this));
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
        notify_property_changed(this->shared_from_this(), captain.name());
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
        notify_property_changed(this->shared_from_this(), crew_complement.name());
    }
}

m::wobservable_deque<equipment_interface::ptr>::ptr spaceship_view_model::get_equipment() const
{
    if(data_context())
    {
        return data_context()->equipment;
    }
    return m::wobservable_deque<equipment_interface::ptr>::ptr();
}

void spaceship_view_model::set_equipment(const m::wobservable_deque<equipment_interface::ptr>::ptr& v)
{
    if(data_context() && v != data_context()->equipment())
    {
        data_context()->equipment = v;
        notify_property_changed(this->shared_from_this(), equipment.name());
    }
}

equipment_interface::ptr spaceship_view_model::get_selected_equipment() const
{
    return _selected_equipment;
}

void spaceship_view_model::set_selected_equipment(const equipment_interface::ptr& v)
{
    if (_selected_equipment != v)
    {
        _selected_equipment = v;
        notify_property_changed(this->shared_from_this(), selected_equipment.name());
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
    ptr this_vm = boost::dynamic_pointer_cast<this_type, m::object>(this->shared_from_this());
    _on_close_spaceship_view_command = m::relay_wcommand::create(L"spaceship_view_model::on_close_spaceship_view",
        boost::bind(&this_type::execute_close_spaceship_view_command, this, _1),
        boost::bind(&this_type::can_execute_close_spaceship_view_command, this, _1),
        close_spaceship_command_parameters::create(this_vm));
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

m::wcommand_interface::ptr spaceship_view_model::get_add_equipment_command()
{
    _on_add_equipment_command = m::relay_wcommand::create(L"spaceship_view_model::on_close_spaceship_view",
        boost::bind(&this_type::execute_add_equipment_command, this, _1),
        boost::bind(&this_type::can_execute_add_equipment_command, this, _1),
        add_equipment_command_parameters::create(_spaceship_id));
    return _on_add_equipment_command;
}

bool spaceship_view_model::can_execute_add_equipment_command(const m::command_parameters::ptr& p)
{
    add_equipment_command_parameters::ptr params = boost::dynamic_pointer_cast<add_equipment_command_parameters>(p);
    if (params)
    {
        return params->spaceship_id == _spaceship_id;
    }
    return false;
}

void spaceship_view_model::execute_add_equipment_command(const m::command_parameters::ptr& p)
{
    main_frame_view_model::ptr vm = _main_frame_vm.lock();
    if (vm)
    {
        m::wcommand_manager::ptr command_mgr = vm->command_manager();
        if (command_mgr)
        {
            m::wcommand_interface::ptr commander_ = vm->open_add_equipment_view_command;
            boost::dynamic_pointer_cast<open_add_equipment_view_command_parameters>(commander_->parameters())->spaceship = data_context();
            command_mgr->post(commander_);
        }
    }
}

m::wcommand_interface::ptr spaceship_view_model::get_remove_equipment_command()
{
    _on_remove_equipment_command = m::relay_wcommand::create(L"spaceship_view_model::on_close_spaceship_view",
        boost::bind(&this_type::execute_remove_equipment_command, this, _1),
        boost::bind(&this_type::can_execute_remove_equipment_command, this, _1),
        remove_equipment_command_parameters::create(_spaceship_id, boost::dynamic_pointer_cast<equipment_model>(selected_equipment())->id));
    return _on_remove_equipment_command;
}

bool spaceship_view_model::can_execute_remove_equipment_command(const m::command_parameters::ptr& p)
{
    remove_equipment_command_parameters::ptr params = boost::dynamic_pointer_cast<remove_equipment_command_parameters>(p);
    if (params)
    {
        return params->spaceship_id == _spaceship_id;
    }
    return false;
}

void spaceship_view_model::execute_remove_equipment_command(const m::command_parameters::ptr& p)
{
    remove_equipment_command_parameters::ptr cmd_params = boost::dynamic_pointer_cast<remove_equipment_command_parameters>(p);
    if (cmd_params)
    {
        const equipment_id_type equipment_id = cmd_params->equipment_id;
        if (boost::dynamic_pointer_cast<equipment_model>(selected_equipment())->id == equipment_id)
        {
            selected_equipment = equipment_interface::ptr();
        }
        m::wobservable_deque<equipment_interface::ptr>::iterator it = std::find_if(equipment()->begin(), equipment()->end(), matches_equipment_id(equipment_id));
        if (it != equipment()->end())
        {
            equipment()->erase(it);
        }
    }
}
